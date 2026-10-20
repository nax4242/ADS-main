#include <stdexcept>
#include "../lib_algorithms/algorithms.h"
#include "stack_on_mass.h"

float division(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Input Error: can't divide by zero!");
    }
    return static_cast<float>(a) / b;
}

//"[{}(){()[]}]"
bool check_brackets(std::string expression) {
    TStackOnMass<char> stack(expression.size());

    for (int i = 0; i < expression.size(); i++) {
        if (expression[i] == '(' || expression[i] == '[' || expression[i] == '{') {
            stack.push(expression[i]);
        }
        else {
            if (expression[i] == ')' && !stack.is_empty() && stack.top() == '(') {
                stack.pop();
                continue;
            }
            else if (expression[i] == ']' && !stack.is_empty() && stack.top() == '[') {
                stack.pop();
                continue;
            }
            else if (expression[i] == '}' && !stack.is_empty() && stack.top() == '{') {
                stack.pop();
                continue;
            }
            else return false;
        }
    }

    if (!stack.is_empty()) return false;
    else return true;
}