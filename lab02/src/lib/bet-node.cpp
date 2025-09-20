#include "lib/bet.h"
#include <regex>

bool BETNode::isOperator() const {
    static const std::regex operatorRegex("[\\+\\-\\*\\/]");
    return std::regex_match(value, operatorRegex);
}

bool BETNode::isOperand() const {
    static const std::regex numberRegex("^[-\\+]?\\d+(\\.\\d+)?$");
    return std::regex_match(value, numberRegex);
}
