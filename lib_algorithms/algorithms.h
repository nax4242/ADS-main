#pragma once

#include <stdexcept>
#include "stack_on_mass.h"
#include "set.h"

float division(int a, int b);

bool check_brackets(std::string expression);

Set sieve_of_eratosthenes(size_t N);