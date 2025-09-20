#include <gtest/gtest.h>
#include "lib/bet.h"
#include <vector>
#include <string>

class BinaryExpressionTreeTest : public ::testing::Test {
protected:
    BinaryExpressionTree* tree;

    void SetUp() override {
        tree = new BinaryExpressionTree();
    }

    void TearDown() override {
        delete tree;
    }
};

TEST_F(BinaryExpressionTreeTest, EmptyTreeInitialization) {
    EXPECT_TRUE(tree->isEmpty());
    EXPECT_EQ(tree->getHeight(), 0);
    EXPECT_EQ(tree->getNodeCount(), 0);
    EXPECT_EQ(tree->getInorderExpression(), "");
    EXPECT_EQ(tree->getPreorderExpression(), "");
    EXPECT_EQ(tree->getPostorderExpression(), "");
}

TEST_F(BinaryExpressionTreeTest, SingleNumberExpression) {
    tree->buildTree("42");

    EXPECT_FALSE(tree->isEmpty());
    EXPECT_EQ(tree->getHeight(), 1);
    EXPECT_EQ(tree->getNodeCount(), 1);
    EXPECT_DOUBLE_EQ(tree->evaluate(), 42.0);
    EXPECT_EQ(tree->getInorderExpression(), "42");
    EXPECT_EQ(tree->getPreorderExpression(), "42");
    EXPECT_EQ(tree->getPostorderExpression(), "42");
}

TEST_F(BinaryExpressionTreeTest, SimpleAddition) {
    tree->buildTree("3 + 4");

    EXPECT_FALSE(tree->isEmpty());
    EXPECT_EQ(tree->getHeight(), 2);
    EXPECT_EQ(tree->getNodeCount(), 3);
    EXPECT_DOUBLE_EQ(tree->evaluate(), 7.0);
    EXPECT_EQ(tree->getInorderExpression(), "(3 + 4)");
    EXPECT_EQ(tree->getPreorderExpression(), "+ 3 4");
    EXPECT_EQ(tree->getPostorderExpression(), "3 4 +");
}

TEST_F(BinaryExpressionTreeTest, SimpleSubtraction) {
    tree->buildTree("10 - 3");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 7.0);
    EXPECT_EQ(tree->getInorderExpression(), "(10 - 3)");
    EXPECT_EQ(tree->getPreorderExpression(), "- 10 3");
    EXPECT_EQ(tree->getPostorderExpression(), "10 3 -");
}

TEST_F(BinaryExpressionTreeTest, SimpleMultiplication) {
    tree->buildTree("6 * 7");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 42.0);
    EXPECT_EQ(tree->getInorderExpression(), "(6 * 7)");
    EXPECT_EQ(tree->getPreorderExpression(), "* 6 7");
    EXPECT_EQ(tree->getPostorderExpression(), "6 7 *");
}

TEST_F(BinaryExpressionTreeTest, SimpleDivision) {
    tree->buildTree("15 / 3");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 5.0);
    EXPECT_EQ(tree->getInorderExpression(), "(15 / 3)");
    EXPECT_EQ(tree->getPreorderExpression(), "/ 15 3");
    EXPECT_EQ(tree->getPostorderExpression(), "15 3 /");
}

TEST_F(BinaryExpressionTreeTest, OperatorPrecedence) {
    // Expression: 3 + 4 * 2 (should be parsed as 3 + (4 * 2))
    tree->buildTree("3 + 4 * 2");

    EXPECT_EQ(tree->getHeight(), 3);
    EXPECT_EQ(tree->getNodeCount(), 5);
    EXPECT_DOUBLE_EQ(tree->evaluate(), 11.0); // 3 + (4 * 2) = 11
    EXPECT_EQ(tree->getInorderExpression(), "(3 + (4 * 2))");
    EXPECT_EQ(tree->getPreorderExpression(), "+ 3 * 4 2");
    EXPECT_EQ(tree->getPostorderExpression(), "3 4 2 * +");
}

TEST_F(BinaryExpressionTreeTest, ParenthesesHandling) {
    // Expression: (3 + 4) * 2
    tree->buildTree("(3 + 4) * 2");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 14.0); // (3 + 4) * 2 = 7 * 2 = 14
    EXPECT_EQ(tree->getInorderExpression(), "((3 + 4) * 2)");
    EXPECT_EQ(tree->getPreorderExpression(), "* + 3 4 2");
    EXPECT_EQ(tree->getPostorderExpression(), "3 4 + 2 *");
}

TEST_F(BinaryExpressionTreeTest, ComplexExpression) {
    // Expression: 12 + 34 - 5 * 6 / 2
    tree->buildTree("12 + 34 - 5 * 6 / 2");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 31.0); // 12 + 34 - (5 * 6 / 2) = 46 - 15 = 31
    EXPECT_EQ(tree->getHeight(), 4);
    EXPECT_EQ(tree->getNodeCount(), 9);
}

TEST_F(BinaryExpressionTreeTest, NegativeNumbers) {
    tree->buildTree("-5 + 10");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 5.0);
    EXPECT_EQ(tree->getInorderExpression(), "(-5 + 10)");
    EXPECT_EQ(tree->getPreorderExpression(), "+ -5 10");
    EXPECT_EQ(tree->getPostorderExpression(), "-5 10 +");
}

TEST_F(BinaryExpressionTreeTest, DecimalNumbers) {
    tree->buildTree("3.5 * 2.0");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 7.0);
    EXPECT_EQ(tree->getInorderExpression(), "(3.5 * 2.0)");
}

TEST_F(BinaryExpressionTreeTest, DivisionByZero) {
    tree->buildTree("5 / 0");

    EXPECT_THROW(tree->evaluate(), std::runtime_error);
}

TEST_F(BinaryExpressionTreeTest, MismatchedParentheses) {
    EXPECT_THROW(tree->buildTree("(3 + 4"), std::runtime_error);
    EXPECT_THROW(tree->buildTree("3 + 4)"), std::runtime_error);
    EXPECT_THROW(tree->buildTree("((3 + 4)"), std::runtime_error);
}

TEST_F(BinaryExpressionTreeTest, InvalidExpression) {
    EXPECT_THROW(tree->buildTree("3 + * 4"), std::runtime_error);
    EXPECT_THROW(tree->buildTree("3 + "), std::runtime_error);
    EXPECT_THROW(tree->buildTree("+ 3 *"), std::runtime_error);
}

TEST_F(BinaryExpressionTreeTest, ClearTree) {
    tree->buildTree("3 + 4");

    EXPECT_FALSE(tree->isEmpty());
    EXPECT_EQ(tree->getNodeCount(), 3);

    tree->clear();

    EXPECT_TRUE(tree->isEmpty());
    EXPECT_EQ(tree->getHeight(), 0);
    EXPECT_EQ(tree->getNodeCount(), 0);
}

TEST_F(BinaryExpressionTreeTest, RebuildTree) {
    // Build first tree
    tree->buildTree("3 + 4");
    EXPECT_DOUBLE_EQ(tree->evaluate(), 7.0);

    // Build second tree (should replace the first)
    tree->buildTree("10 - 5");
    EXPECT_DOUBLE_EQ(tree->evaluate(), 5.0);
    EXPECT_EQ(tree->getNodeCount(), 3);
}

TEST_F(BinaryExpressionTreeTest, ConstructorWithInorderExpression) {
    BinaryExpressionTree* constructedTree = new BinaryExpressionTree("8 / 2");

    EXPECT_FALSE(constructedTree->isEmpty());
    EXPECT_DOUBLE_EQ(constructedTree->evaluate(), 4.0);
    EXPECT_EQ(constructedTree->getInorderExpression(), "(8 / 2)");

    delete constructedTree;
}

TEST_F(BinaryExpressionTreeTest, ConstructorWithTokenVector) {
    std::vector<std::string> tokens = {"6", "*", "7"};
    BinaryExpressionTree* constructedTree = new BinaryExpressionTree(tokens);

    EXPECT_FALSE(constructedTree->isEmpty());
    EXPECT_DOUBLE_EQ(constructedTree->evaluate(), 42.0);
    EXPECT_EQ(constructedTree->getInorderExpression(), "(6 * 7)");

    delete constructedTree;
}

TEST_F(BinaryExpressionTreeTest, CopyConstructor) {
    tree->buildTree("5 + 3");
    BinaryExpressionTree* copiedTree = new BinaryExpressionTree(*tree);

    EXPECT_DOUBLE_EQ(copiedTree->evaluate(), 8.0);
    EXPECT_EQ(copiedTree->getNodeCount(), 3);
    EXPECT_EQ(copiedTree->getInorderExpression(), "(5 + 3)");

    // Modify original tree
    tree->buildTree("10 * 2");
    EXPECT_DOUBLE_EQ(tree->evaluate(), 20.0);

    // Copied tree should remain unchanged
    EXPECT_DOUBLE_EQ(copiedTree->evaluate(), 8.0);

    delete copiedTree;
}

TEST_F(BinaryExpressionTreeTest, AssignmentOperator) {
    tree->buildTree("7 - 2");
    BinaryExpressionTree* otherTree = new BinaryExpressionTree("4 + 1");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 5.0);
    EXPECT_DOUBLE_EQ(otherTree->evaluate(), 5.0);

    // Assign
    *otherTree = *tree;

    EXPECT_DOUBLE_EQ(otherTree->evaluate(), 5.0);
    EXPECT_EQ(otherTree->getInorderExpression(), "(7 - 2)");

    delete otherTree;
}

TEST_F(BinaryExpressionTreeTest, EmptyStringExpression) {
    tree->buildTree("");

    EXPECT_TRUE(tree->isEmpty());
    EXPECT_THROW(tree->evaluate(), std::runtime_error);
}

TEST_F(BinaryExpressionTreeTest, NodeTypeChecking) {
    // Test BETNode helper methods
    BETNode* operatorNode = new BETNode("+");
    BETNode* operandNode = new BETNode("42");
    BETNode* negativeNode = new BETNode("-3.5");

    EXPECT_TRUE(operatorNode->isOperator());
    EXPECT_FALSE(operatorNode->isOperand());

    EXPECT_FALSE(operandNode->isOperator());
    EXPECT_TRUE(operandNode->isOperand());

    EXPECT_FALSE(negativeNode->isOperator());
    EXPECT_TRUE(negativeNode->isOperand());

    delete operatorNode;
    delete operandNode;
    delete negativeNode;
}

TEST_F(BinaryExpressionTreeTest, ComplexNestedExpression) {
    // Expression: (2 + 3) * 4 - 8 / 2
    tree->buildTree("(2 + 3) * 4 - 8 / 2");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 16.0); // (2+3)*4 - 8/2 = 5*4 - 4 = 20 - 4 = 16
    EXPECT_EQ(tree->getHeight(), 4);
    EXPECT_EQ(tree->getNodeCount(), 9);
}

TEST_F(BinaryExpressionTreeTest, LeftAssociativeOperations) {
    // Expression: 10 - 5 - 2
    // Should be evaluated as (10 - 5) - 2 = 3, not 10 - (5 - 2) = 7
    tree->buildTree("10 - 5 - 2");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 3.0);
    EXPECT_EQ(tree->getInorderExpression(), "((10 - 5) - 2)");
}

TEST_F(BinaryExpressionTreeTest, EvaluateEmptyTree) {
    EXPECT_THROW(tree->evaluate(), std::runtime_error);
}

TEST_F(BinaryExpressionTreeTest, SpacesInExpression) {
    tree->buildTree("  3   +   4  ");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 7.0);
    EXPECT_EQ(tree->getInorderExpression(), "(3 + 4)");
}

TEST_F(BinaryExpressionTreeTest, MultipleParentheses) {
    tree->buildTree("((3 + 4) * 2)");

    EXPECT_DOUBLE_EQ(tree->evaluate(), 14.0);
    EXPECT_EQ(tree->getInorderExpression(), "((3 + 4) * 2)");
}
