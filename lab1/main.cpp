#include "iostream"
#include "solving.h"
#include "coefs.h"
using namespace std;

int main() {

	Coefficients coefs;
	cout << "Enter coefficients";
	cin >> coefs.a >> coefs.b >> coefs.c;

	Roots roots = IsQuadratic(coefs);

	if (roots.count == 0) {
		cout << "Equalation has no roots";
	}
	if (roots.count == 1) {
		cout << " x = " << roots.x1;
	}
	if (roots.count == 2) {
		cout << " x1 = " << roots.x1 << " x2 = " << roots.x2;
	}

	return 0;
}