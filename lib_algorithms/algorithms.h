//Copyright 2026 Danila Puzanov
#pragma once

#include <stdexcept>
#include <string>
#include "../lib_stack_on_mass/stack_on_mass.h"
#include "../lib_set/set.h"
                                                                                
float division(int a, int b);

bool check_brackets(std::string expression);

Set sieve_of_eratosthenes(size_t N);
