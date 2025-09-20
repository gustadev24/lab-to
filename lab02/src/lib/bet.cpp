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
    root = copyTree(other.root.get());
}

BinaryExpressionTree& BinaryExpressionTree::operator=(const BinaryExpressionTree& other) {
    if (this != &other) {
        root = copyTree(other.root.get());
    }
    return *this;
}

std::unique_ptr<BETNode> BinaryExpressionTree::copyTree(const BETNode* node) {
    if (!node) {
        return nullptr;
    }


    auto newNode = std::make_unique<BETNode>(node->value);
    newNode->left = copyTree(node->left.get());
    newNode->right = copyTree(node->right.get());
    return newNode;
}

void BinaryExpressionTree::buildTree(const std::string& inorderExpression) {
    std::vector<std::string> tokens = tokenizeInorder(inorderExpression);
    buildTree(tokens);
}

void BinaryExpressionTree::buildTree(const std::vector<std::string>& tokens) {
    root.reset();

    if (tokens.empty()) {
        return;
    }

    int index = 0;
    root = parseExpression(tokens, index);

    if (index != tokens.size()) {
        root.reset();
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
std::unique_ptr<BETNode> BinaryExpressionTree::parseExpression(const std::vector<std::string>& tokens, int& index) {
    auto left = parseTerm(tokens, index);

    while (index < tokens.size() && (tokens[index] == "+" || tokens[index] == "-")) {
        std::string op = tokens[index];
        index++;
        auto right = parseTerm(tokens, index);

        auto opNode = std::make_unique<BETNode>(op);
        opNode->left = std::move(left);
        opNode->right = std::move(right);
        left = std::move(opNode);
    }

    return left;
}

std::unique_ptr<BETNode> BinaryExpressionTree::parseTerm(const std::vector<std::string>& tokens, int& index) {
    auto left = parseFactor(tokens, index);

    while (index < tokens.size() && (tokens[index] == "*" || tokens[index] == "/")) {
        std::string op = tokens[index];
        index++;
        auto right = parseFactor(tokens, index);

        auto opNode = std::make_unique<BETNode>(op);
        opNode->left = std::move(left);
        opNode->right = std::move(right);
        left = std::move(opNode);
    }

    return left;
}

std::unique_ptr<BETNode> BinaryExpressionTree::parseFactor(const std::vector<std::string>& tokens, int& index) {
    if (index >= tokens.size()) {
        throw std::runtime_error("Unexpected end of expression");
    }

    if (tokens[index] == "(") {
        index++; // consume '('
        auto node = parseExpression(tokens, index);

        if (index >= tokens.size() || tokens[index] != ")") {
            throw std::runtime_error("Missing closing parenthesis");
        }
        index++; // consume ')'
        return node;
    }

    // Must be a number
    auto node = std::make_unique<BETNode>(tokens[index]);
    if (!node->isOperand()) {
        throw std::runtime_error("Expected number or opening parenthesis, got: " + tokens[index]);
    }

    index++;
    return node;
}

double BinaryExpressionTree::evaluate() const {
    if (!root) {
        throw std::runtime_error("Cannot evaluate empty tree");
    }
    return evaluateNode(root.get());
}

double BinaryExpressionTree::evaluateNode(const BETNode* node) const {
    if (!node) {
        throw std::runtime_error("Null node encountered during evaluation");
    }

    if (node->isOperand()) {
        return std::stod(node->value);
    }

    if (node->isOperator()) {
        double leftVal = evaluateNode(node->left.get());
        double rightVal = evaluateNode(node->right.get());

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

std::vector<std::string> BinaryExpressionTree::getStepByStepSolution() const {
    std::vector<std::string> steps;

    if (!root) {
        steps.push_back("Error: Empty expression tree");
        return steps;
    }

    // Add initial expression
    steps.push_back("Original expression: " + getInorderExpression());
    steps.push_back("Postorder evaluation sequence: " + getPostorderExpression());
    steps.push_back("");
    steps.push_back("Step-by-step evaluation:");

    generateSteps(root.get(), steps);

    steps.push_back("");
    steps.push_back("Final result: " + formatNumber(evaluate()));

    return steps;
}

std::string BinaryExpressionTree::getStepByStepString() const {
    std::vector<std::string> steps = getStepByStepSolution();
    std::string result;

    for (size_t i = 0; i < steps.size(); ++i) {
        result += steps[i];
        if (i < steps.size() - 1) {
            result += "\n";
        }
    }

    return result;
}

void BinaryExpressionTree::generateSteps(const BETNode* node, std::vector<std::string>& steps) const {
    if (!node) {
        return;
    }

    if (node->isOperand()) {
        steps.push_back("  Value: " + node->value);
        return;
    }

    if (node->isOperator()) {
        // First evaluate left and right subtrees
        if (node->left) {
            steps.push_back("  Evaluating left operand for '" + node->value + "':");
            generateSteps(node->left.get(), steps);
        }

        if (node->right) {
            steps.push_back("  Evaluating right operand for '" + node->value + "':");
            generateSteps(node->right.get(), steps);
        }

        // Now perform the operation
        double leftVal = evaluateNode(node->left.get());
        double rightVal = evaluateNode(node->right.get());

        std::string leftStr = nodeToString(node->left.get());
        std::string rightStr = nodeToString(node->right.get());

        std::string operation = leftStr + " " + node->value + " " + rightStr;

        double result;
        if (node->value == "+") {
            result = leftVal + rightVal;
            steps.push_back("  " + operation + " = " + formatNumber(leftVal) + " + " + formatNumber(rightVal) + " = " + formatNumber(result));
        } else if (node->value == "-") {
            result = leftVal - rightVal;
            steps.push_back("  " + operation + " = " + formatNumber(leftVal) + " - " + formatNumber(rightVal) + " = " + formatNumber(result));
        } else if (node->value == "*") {
            result = leftVal * rightVal;
            steps.push_back("  " + operation + " = " + formatNumber(leftVal) + " × " + formatNumber(rightVal) + " = " + formatNumber(result));
        } else if (node->value == "/") {
            if (rightVal == 0) {
                steps.push_back("  " + operation + " = " + formatNumber(leftVal) + " ÷ " + formatNumber(rightVal) + " = ERROR: Division by zero");
                return;
            }
            result = leftVal / rightVal;
            steps.push_back("  " + operation + " = " + formatNumber(leftVal) + " ÷ " + formatNumber(rightVal) + " = " + formatNumber(result));
        }
    }
}

std::string BinaryExpressionTree::nodeToString(const BETNode* node) const {
    if (!node) {
        return "";
    }

    if (node->isOperand()) {
        return node->value;
    }

    if (node->isOperator()) {
        std::string leftStr = nodeToString(node->left.get());
        std::string rightStr = nodeToString(node->right.get());
        return "(" + leftStr + " " + node->value + " " + rightStr + ")";
    }

    return "";
}

std::string BinaryExpressionTree::formatNumber(double number) const {
    // Convert to string with 6 decimal places
    std::string str = std::to_string(number);

    // Find decimal point
    size_t decimalPos = str.find('.');
    if (decimalPos == std::string::npos) {
        return str;
    }

    // Remove trailing zeros
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);

    // Remove trailing decimal point if no decimals left
    if (!str.empty() && str.back() == '.') {
        str.pop_back();
    }

    return str;
}

std::string BinaryExpressionTree::getInorderExpression() const {
    if (!root) {
        return "";
    }
    return inorderTraversal(root.get());
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
    result += inorderTraversal(node->left.get());

    // Current node
    if (!result.empty() && node->left) {
        result += " ";
    }
    result += node->value;

    // Right subtree
    if (node->right) {
        result += " ";
    }
    result += inorderTraversal(node->right.get());

    if (node->isOperator()) {
        result += ")";
    }

    return result;
}

std::string BinaryExpressionTree::getPreorderExpression() const {
    if (!root) {
        return "";
    }
    return preorderTraversal(root.get());
}

std::string BinaryExpressionTree::preorderTraversal(const BETNode* node) const {
    if (!node) {
        return "";
    }

    std::string result = node->value;

    std::string leftResult = preorderTraversal(node->left.get());
    if (!leftResult.empty()) {
        result += " " + leftResult;
    }

    std::string rightResult = preorderTraversal(node->right.get());
    if (!rightResult.empty()) {
        result += " " + rightResult;
    }

    return result;
}

std::string BinaryExpressionTree::getPostorderExpression() const {
    if (!root) {
        return "";
    }
    return postorderTraversal(root.get());
}

std::string BinaryExpressionTree::postorderTraversal(const BETNode* node) const {
    if (!node) {
        return "";
    }

    std::string result;

    std::string leftResult = postorderTraversal(node->left.get());
    if (!leftResult.empty()) {
        result += leftResult + " ";
    }

    std::string rightResult = postorderTraversal(node->right.get());
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
    root.reset();
}

int BinaryExpressionTree::getHeight() const {
    return getHeightHelper(root.get());
}

int BinaryExpressionTree::getHeightHelper(const BETNode* node) const {
    if (!node) {
        return 0;
    }

    int leftHeight = getHeightHelper(node->left.get());
    int rightHeight = getHeightHelper(node->right.get());

    return 1 + std::max(leftHeight, rightHeight);
}

int BinaryExpressionTree::getNodeCount() const {
    return getNodeCountHelper(root.get());
}

int BinaryExpressionTree::getNodeCountHelper(const BETNode* node) const {
    if (!node) {
        return 0;
    }

    return 1 + getNodeCountHelper(node->left.get()) + getNodeCountHelper(node->right.get());
}
