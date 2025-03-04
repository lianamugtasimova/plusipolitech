#pragma once
#include "coefs.h"

Roots SolveEqualation(Coefficients coefs);
Roots SolveLinearEq(Coefficients coefs);
Roots SolveQuadratic(Coefficients coefs);
double FindDiscr(Coefficients coefs);