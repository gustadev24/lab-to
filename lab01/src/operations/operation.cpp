#include "operations/operation.h"
#include <stdexcept>

Operation::Operation(double a, double b): leftOperand(a), rightOperand(b) {}

double Operation::getResult() const {
       if (!result.has_value()) {
           throw std::runtime_error("Result not computed yet");
       }
       return result.value();
   }
