#include "solving.h"
#include <cmath>

Roots SolveLinearEq(Coefficients coef) {
	Roots root;
	root.count = 1;
	root.x1 = -coef.c / coef.b;
	return root;
}

double FindDiscr(Coefficients c) {
	double discriminant = c.b * c.b - 4 * c.a * c.c;
	return discriminant;
}

Roots SolveQuadratic(Coefficients coef) {
	double Disc = FindDiscr(coef);
	Roots root;
	if (Disc < 0) {
		root.count = 0;
	}
	if (Disc == 0) {
		root.count = 1;
		root.x1 = -coef.b / (2 * coef.a);
	}
	if (Disc > 0) {
		root.count = 2;
		root.x1 = (-coef.b - sqrt(Disc)) / (2 * coef.a);
		root.x2 = (-coef.b + sqrt(Disc)) / (2 * coef.a);
	}

	return root;
}

Roots IsQuadratic(Coefficients coef) {
	Roots roots;
	if (coef.a == 0) {
		roots = SolveLinearEq(coef);
	}
	else {
		roots = SolveQuadratic(coef);
	}
	return roots;
}