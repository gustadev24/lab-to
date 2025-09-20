#include <string>

class BETNode {
  private:
    std::string value;
    BETNode* left;
    BETNode* right;

  public:
    BETNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {}

    bool isOperator() const;
    bool isOperand() const;

    friend class BinaryExpressionTree;

};
