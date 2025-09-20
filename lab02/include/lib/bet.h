#pragma once
#include <string>
#include <vector>
#include "bet-node.h"

class BinaryExpressionTree {
private:
    BETNode* root;

    // Helper methods for tree operations
    BETNode* buildFromInorder(const std::vector<std::string>& tokens, int& index);
    BETNode* parseExpression(const std::vector<std::string>& tokens, int& index);
    BETNode* parseTerm(const std::vector<std::string>& tokens, int& index);
    BETNode* parseFactor(const std::vector<std::string>& tokens, int& index);

    double evaluateNode(const BETNode* node) const;
    std::string inorderTraversal(const BETNode* node) const;
    std::string preorderTraversal(const BETNode* node) const;
    std::string postorderTraversal(const BETNode* node) const;

    // Helper methods for memory management
    void deleteTree(BETNode* node);
    BETNode* copyTree(const BETNode* node);

    // Helper methods for structure analysis
    int getHeightHelper(const BETNode* node) const;
    int getNodeCountHelper(const BETNode* node) const;

    // Tokenization helper
    std::vector<std::string> tokenizeInorder(const std::string& expression) const;

public:
    BinaryExpressionTree();
    BinaryExpressionTree(const std::string& inorderExpression);
    BinaryExpressionTree(const std::vector<std::string>& tokens);
    BinaryExpressionTree(const BinaryExpressionTree& other);
    BinaryExpressionTree& operator=(const BinaryExpressionTree& other);
    ~BinaryExpressionTree();

    // Tree construction
    void buildTree(const std::string& inorderExpression);
    void buildTree(const std::vector<std::string>& tokens);

    // Tree evaluation
    double evaluate() const;

    // Tree traversal methods
    std::string getInorderExpression() const;
    std::string getPreorderExpression() const;
    std::string getPostorderExpression() const;

    // Utility methods
    bool isEmpty() const;
    void clear();

    // Tree structure analysis
    int getHeight() const;
    int getNodeCount() const;
};
