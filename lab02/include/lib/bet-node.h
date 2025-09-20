#include <memory>
#include <string>

class BETNode {
  private:
    std::string value;
    std::unique_ptr<BETNode> left;
    std::unique_ptr<BETNode> right;

  public:
    BETNode(const std::string& val) : value(val), left(nullptr), right(nullptr) {}

    bool isOperator() const;
    bool isOperand() const;

    friend class BinaryExpressionTree;

};
