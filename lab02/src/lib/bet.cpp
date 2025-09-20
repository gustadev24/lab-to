#include "lib/bet.h"
#include <stdexcept>
#include <regex>

#include <algorithm>

// BinaryExpressionTree implementation
BinaryExpressionTree::BinaryExpressionTree() : root(nullptr) {}

BinaryExpressionTree::BinaryExpressionTree(const std::string& inorderExpression) : root(nullptr) {
    buildTree(inorderExpression);
}

BinaryExpressionTree::BinaryExpressionTree(const std::vector<std::string>& tokens) : root(nullptr) {
    buildTree(tokens);
}

BinaryExpressionTree::BinaryExpressionTree(const BinaryExpressionTree& other) : root(nullptr) {
    root = copyTree(other.root);
}

BinaryExpressionTree& BinaryExpressionTree::operator=(const BinaryExpressionTree& other) {
    if (this != &other) {
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

BinaryExpressionTree::~BinaryExpressionTree() {
    deleteTree(root);
}

void BinaryExpressionTree::deleteTree(BETNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

BETNode* BinaryExpressionTree::copyTree(const BETNode* node) {
    if (!node) {
        return nullptr;
    }

    BETNode* newNode = new BETNode(node->value);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

void BinaryExpressionTree::buildTree(const std::string& inorderExpression) {
    std::vector<std::string> tokens = tokenizeInorder(inorderExpression);
    buildTree(tokens);
}

void BinaryExpressionTree::buildTree(const std::vector<std::string>& tokens) {
    deleteTree(root);
    root = nullptr;

    if (tokens.empty()) {
        return;
    }

    int index = 0;
    root = parseExpression(tokens, index);

    if (index != tokens.size()) {
        deleteTree(root);
        root = nullptr;
        throw std::runtime_error("Invalid expression: unexpected tokens after parsing");
    }
}

std::vector<std::string> BinaryExpressionTree::tokenizeInorder(const std::string& expression) const {
    std::vector<std::string> tokens;
    std::string currentToken;
    std::string pendingSign;

    for (char c : expression) {
        if (c == ' ') continue;

        std::string currentChar(1, c);

        bool isParenthesis = (currentChar == "(" || currentChar == ")");
        static const std::regex operatorRegex("[\\+\\-\\*\\/]");

        if (std::regex_match(currentChar, operatorRegex) || isParenthesis) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken.clear();
            }

            if (isParenthesis) {
                tokens.push_back(currentChar);
                continue;
            }

            bool allowedPlace = tokens.empty() || tokens.back() == "(" ||
                              std::regex_match(tokens.back(), operatorRegex);

            if ((currentChar == "+" || currentChar == "-") && allowedPlace) {
                pendingSign += currentChar;
                continue;
            }

            if ((currentChar == "*" || currentChar == "/") && allowedPlace) {
                throw std::runtime_error("Invalid operator sequence: unexpected " + currentChar);
            }

            tokens.push_back(currentChar);
        } else {
            if (!pendingSign.empty()) {
                int minusCount = std::count(pendingSign.begin(), pendingSign.end(), '-');
                if (minusCount % 2 == 1)
                    currentToken = "-";
                pendingSign.clear();
            }
            currentToken += c;
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

// Recursive descent parser implementation
BETNode* BinaryExpressionTree::parseExpression(const std::vector<std::string>& tokens, int& index) {
    BETNode* left = parseTerm(tokens, index);

    while (index < tokens.size() && (tokens[index] == "+" || tokens[index] == "-")) {
        std::string op = tokens[index];
        index++;
        BETNode* right = parseTerm(tokens, index);

        BETNode* opNode = new BETNode(op);
        opNode->left = left;
        opNode->right = right;
        left = opNode;
    }

    return left;
}

BETNode* BinaryExpressionTree::parseTerm(const std::vector<std::string>& tokens, int& index) {
    BETNode* left = parseFactor(tokens, index);

    while (index < tokens.size() && (tokens[index] == "*" || tokens[index] == "/")) {
        std::string op = tokens[index];
        index++;
        BETNode* right = parseFactor(tokens, index);

        BETNode* opNode = new BETNode(op);
        opNode->left = left;
        opNode->right = right;
        left = opNode;
    }

    return left;
}

BETNode* BinaryExpressionTree::parseFactor(const std::vector<std::string>& tokens, int& index) {
    if (index >= tokens.size()) {
        throw std::runtime_error("Unexpected end of expression");
    }

    if (tokens[index] == "(") {
        index++; // consume '('
        BETNode* node = parseExpression(tokens, index);

        if (index >= tokens.size() || tokens[index] != ")") {
            deleteTree(node);
            throw std::runtime_error("Missing closing parenthesis");
        }
        index++; // consume ')'
        return node;
    }

    // Must be a number
    BETNode* node = new BETNode(tokens[index]);
    if (!node->isOperand()) {
        delete node;
        throw std::runtime_error("Expected number or opening parenthesis, got: " + tokens[index]);
    }

    index++;
    return node;
}

double BinaryExpressionTree::evaluate() const {
    if (!root) {
        throw std::runtime_error("Cannot evaluate empty tree");
    }
    return evaluateNode(root);
}

double BinaryExpressionTree::evaluateNode(const BETNode* node) const {
    if (!node) {
        throw std::runtime_error("Null node encountered during evaluation");
    }

    if (node->isOperand()) {
        return std::stod(node->value);
    }

    if (node->isOperator()) {
        double leftVal = evaluateNode(node->left);
        double rightVal = evaluateNode(node->right);

        if (node->value == "+") {
            return leftVal + rightVal;
        } else if (node->value == "-") {
            return leftVal - rightVal;
        } else if (node->value == "*") {
            return leftVal * rightVal;
        } else if (node->value == "/") {
            if (rightVal == 0) {
                throw std::runtime_error("Division by zero");
            }
            return leftVal / rightVal;
        } else {
            throw std::runtime_error("Unknown operator: " + node->value);
        }
    }

    throw std::runtime_error("Invalid node type");
}

std::string BinaryExpressionTree::getInorderExpression() const {
    if (!root) {
        return "";
    }
    return inorderTraversal(root);
}

std::string BinaryExpressionTree::inorderTraversal(const BETNode* node) const {
    if (!node) {
        return "";
    }

    std::string result;

    if (node->isOperator()) {
        result += "(";
    }

    // Left subtree
    result += inorderTraversal(node->left);

    // Current node
    if (!result.empty() && node->left) {
        result += " ";
    }
    result += node->value;

    // Right subtree
    if (node->right) {
        result += " ";
    }
    result += inorderTraversal(node->right);

    if (node->isOperator()) {
        result += ")";
    }

    return result;
}

std::string BinaryExpressionTree::getPreorderExpression() const {
    if (!root) {
        return "";
    }
    return preorderTraversal(root);
}

std::string BinaryExpressionTree::preorderTraversal(const BETNode* node) const {
    if (!node) {
        return "";
    }

    std::string result = node->value;

    std::string leftResult = preorderTraversal(node->left);
    if (!leftResult.empty()) {
        result += " " + leftResult;
    }

    std::string rightResult = preorderTraversal(node->right);
    if (!rightResult.empty()) {
        result += " " + rightResult;
    }

    return result;
}

std::string BinaryExpressionTree::getPostorderExpression() const {
    if (!root) {
        return "";
    }
    return postorderTraversal(root);
}

std::string BinaryExpressionTree::postorderTraversal(const BETNode* node) const {
    if (!node) {
        return "";
    }

    std::string result;

    std::string leftResult = postorderTraversal(node->left);
    if (!leftResult.empty()) {
        result += leftResult + " ";
    }

    std::string rightResult = postorderTraversal(node->right);
    if (!rightResult.empty()) {
        result += rightResult + " ";
    }

    result += node->value;

    return result;
}

bool BinaryExpressionTree::isEmpty() const {
    return root == nullptr;
}

void BinaryExpressionTree::clear() {
    deleteTree(root);
    root = nullptr;
}

int BinaryExpressionTree::getHeight() const {
    return getHeightHelper(root);
}

int BinaryExpressionTree::getHeightHelper(const BETNode* node) const {
    if (!node) {
        return 0;
    }

    int leftHeight = getHeightHelper(node->left);
    int rightHeight = getHeightHelper(node->right);

    return 1 + std::max(leftHeight, rightHeight);
}

int BinaryExpressionTree::getNodeCount() const {
    return getNodeCountHelper(root);
}

int BinaryExpressionTree::getNodeCountHelper(const BETNode* node) const {
    if (!node) {
        return 0;
    }

    return 1 + getNodeCountHelper(node->left) + getNodeCountHelper(node->right);
}
