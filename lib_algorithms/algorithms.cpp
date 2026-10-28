#include "../lib_algorithms/algorithms.h"

float division(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("Input Error: can't divide by zero!");
    }
    return static_cast<float>(a) / b;
}

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

Set sieve_of_eratosthenes(size_t N) {
    Set result(N);
    result = -result;
    
    result.erase(1);

    for (size_t i = 2; i * i <= N; i++) {
        if (result.is_member(i)) {
            for (size_t j = i * i; j <= N; j += i) {
                result.erase(j);
            }
        }
    }

    return result;
}