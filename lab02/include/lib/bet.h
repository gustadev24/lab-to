#pragma once
#include "bet-node.h"
#include <memory>
#include <string>
#include <vector>

class BinaryExpressionTree {
private:
    std::unique_ptr<BETNode> root;

    // Helper methods for tree operations
    std::unique_ptr<BETNode> buildFromInorder(const std::vector<std::string>& tokens, int& index);
    std::unique_ptr<BETNode> parseExpression(const std::vector<std::string>& tokens, int& index);
    std::unique_ptr<BETNode> parseTerm(const std::vector<std::string>& tokens, int& index);
    std::unique_ptr<BETNode> parseFactor(const std::vector<std::string>& tokens, int& index);

    double evaluateNode(const BETNode* node) const;
    std::string inorderTraversal(const BETNode* node) const;
    std::string preorderTraversal(const BETNode* node) const;
    std::string postorderTraversal(const BETNode* node) const;

    // Helper methods for copying
    std::unique_ptr<BETNode> copyTree(const BETNode* node);

    // Helper methods for structure analysis
    int getHeightHelper(const BETNode* node) const;
    int getNodeCountHelper(const BETNode* node) const;

    // Helper methods for step-by-step solution
    void generateSteps(const BETNode* node, std::vector<std::string>& steps) const;
    std::string nodeToString(const BETNode* node) const;
    std::string formatNumber(double number) const;

    // Tokenization helper
    std::vector<std::string> tokenizeInorder(const std::string& expression) const;

public:
    BinaryExpressionTree();
    BinaryExpressionTree(const std::string& inorderExpression);
    BinaryExpressionTree(const std::vector<std::string>& tokens);
    BinaryExpressionTree(const BinaryExpressionTree& other);
    BinaryExpressionTree& operator=(const BinaryExpressionTree& other);

    // Tree construction
    void buildTree(const std::string& inorderExpression);
    void buildTree(const std::vector<std::string>& tokens);

    // Tree evaluation
    double evaluate() const;

    // Step-by-step solution
    std::vector<std::string> getStepByStepSolution() const;
    std::string getStepByStepString() const;

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
