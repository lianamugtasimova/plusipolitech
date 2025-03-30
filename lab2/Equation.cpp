#include "Equation.h"
#include <cmath>

Equation::Equation(double a, double b, double c) : a(a), b(b), c(c) {}

std::vector<double> Equation::solve() const {
    double discriminant = b * b - 4.0 * a * c;
    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b - sqrt(discriminant)) / (2.0 * a);
        return { root1, root2 };
    }
    else if (discriminant == 0) {
        double root = -b / (2.0 * a);
        return { root };
    }
    else {
        return {}; 
    }
}

std::vector<Equation> Equation::loadFromFile(const std::string& filename) {
    std::vector<Equation> equations;
    std::ifstream file(filename);
    double a, b, c;
    while (file >> a >> b >> c) {
        equations.emplace_back(a, b, c);
    }
    return equations;
}
