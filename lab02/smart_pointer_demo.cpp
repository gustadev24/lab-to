#include "include/lib/bet.h"
#include <iostream>
#include <vector>
#include <string>
#include <memory>

int main() {
    std::cout << "=== Binary Expression Tree (Smart Pointers) Demo ===" << std::endl;

    // Test expressions in inorder notation
    std::vector<std::string> expressions = {
        "3 + 4",
        "3 + 4 * 2",
        "10 - 5 - 2",
        "(3 + 4) * 2",
        "12 + 34 - 5 * 6 / 2",
        "-5 + 10",
        "3.5 * 2.0",
        "((2 + 3) * 4) - (8 / 2)"
    };

    for (const std::string& expr : expressions) {
        std::cout << "\n--- Expression: " << expr << " ---" << std::endl;

        try {
            // Build Binary Expression Tree from inorder expression using smart pointer
            std::unique_ptr<BinaryExpressionTree> bet = std::make_unique<BinaryExpressionTree>(expr);

            // Show tree properties
            std::cout << "Tree Height: " << bet->getHeight() << std::endl;
            std::cout << "Node Count: " << bet->getNodeCount() << std::endl;

            // Show different traversals
            std::cout << "Inorder:    " << bet->getInorderExpression() << std::endl;
            std::cout << "Preorder:   " << bet->getPreorderExpression() << std::endl;
            std::cout << "Postorder:  " << bet->getPostorderExpression() << std::endl;

            // Evaluate the expression
            double result = bet->evaluate();
            std::cout << "Result: " << result << std::endl;

            // Show step-by-step solution
            std::cout << "\nStep-by-step solution:" << std::endl;
            std::cout << bet->getStepByStepString() << std::endl;

            // Smart pointer automatically cleans up when bet goes out of scope

        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "\n=== Advanced BET Operations Demo ===" << std::endl;

    // Demonstrate tree manipulation with smart pointers
    std::unique_ptr<BinaryExpressionTree> tree = std::make_unique<BinaryExpressionTree>();

    std::cout << "\nEmpty tree check:" << std::endl;
    std::cout << "Is empty: " << (tree->isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Height: " << tree->getHeight() << std::endl;
    std::cout << "Node count: " << tree->getNodeCount() << std::endl;

    // Build a tree manually
    tree->buildTree("(2 + 3) * 4 - 1");

    std::cout << "\nAfter building tree for '(2 + 3) * 4 - 1':" << std::endl;
    std::cout << "Is empty: " << (tree->isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Height: " << tree->getHeight() << std::endl;
    std::cout << "Node count: " << tree->getNodeCount() << std::endl;
    std::cout << "Inorder: " << tree->getInorderExpression() << std::endl;
    std::cout << "Result: " << tree->evaluate() << std::endl;

    // Clear and rebuild
    tree->clear();
    std::cout << "\nAfter clearing:" << std::endl;
    std::cout << "Is empty: " << (tree->isEmpty() ? "Yes" : "No") << std::endl;

    // Rebuild with different expression
    tree->buildTree("100 / 4 * 3 - 2 + 1");

    std::cout << "\nAfter rebuilding with '100 / 4 * 3 - 2 + 1':" << std::endl;
    std::cout << "Height: " << tree->getHeight() << std::endl;
    std::cout << "Node count: " << tree->getNodeCount() << std::endl;
    std::cout << "Inorder: " << tree->getInorderExpression() << std::endl;
    std::cout << "Result: " << tree->evaluate() << std::endl;

    std::cout << "\n=== Copy and Assignment Demo ===" << std::endl;

    // Test copy constructor with smart pointers
    std::unique_ptr<BinaryExpressionTree> originalTree = std::make_unique<BinaryExpressionTree>("6 * 7");
    std::unique_ptr<BinaryExpressionTree> copiedTree = std::make_unique<BinaryExpressionTree>(*originalTree);

    std::cout << "\nOriginal tree: " << originalTree->getInorderExpression() << " = " << originalTree->evaluate() << std::endl;
    std::cout << "Copied tree: " << copiedTree->getInorderExpression() << " = " << copiedTree->evaluate() << std::endl;

    // Test assignment operator with smart pointers
    std::unique_ptr<BinaryExpressionTree> assignedTree = std::make_unique<BinaryExpressionTree>();
    *assignedTree = *originalTree;

    std::cout << "Assigned tree: " << assignedTree->getInorderExpression() << " = " << assignedTree->evaluate() << std::endl;

    // Modify original to show independence
    originalTree->buildTree("1 + 1");
    std::cout << "\nAfter modifying original:" << std::endl;
    std::cout << "Original: " << originalTree->getInorderExpression() << " = " << originalTree->evaluate() << std::endl;
    std::cout << "Copied: " << copiedTree->getInorderExpression() << " = " << copiedTree->evaluate() << std::endl;
    std::cout << "Assigned: " << assignedTree->getInorderExpression() << " = " << assignedTree->evaluate() << std::endl;

    std::cout << "\n=== Step-by-Step Solution Demo ===" << std::endl;

    // Demonstrate step-by-step solution
    std::unique_ptr<BinaryExpressionTree> stepTree = std::make_unique<BinaryExpressionTree>("(5 + 3) * (10 - 8)");

    std::cout << "\nDetailed step-by-step solution for '(5 + 3) * (10 - 8)':" << std::endl;
    std::cout << stepTree->getStepByStepString() << std::endl;

    // Show complex expression steps
    stepTree->buildTree("1 + 2 * 3 - 4 / 2");
    std::cout << "\nDetailed steps for '1 + 2 * 3 - 4 / 2':" << std::endl;
    std::vector<std::string> steps = stepTree->getStepByStepSolution();
    for (const std::string& step : steps) {
        std::cout << step << std::endl;
    }

    // All smart pointers automatically clean up when going out of scope
    std::cout << "\n=== Demo Complete (All memory automatically managed) ===" << std::endl;

    return 0;
}
