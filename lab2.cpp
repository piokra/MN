#include <iostream>

double f(double x, double y) {
	return y*y + 1;
}

double rkStep(double x0, double y0, double h) {
	double f0 = f(x0, y0);

	double f1 = f(x0 + h / 2, y0 + h / 2 * f0);
	double f2 = f(x0 + h / 2, y0 + h / 2 * f1);
	double f3 = f(x0 + h, y0 + h*f2);

	return y0 + h / 6 * (f0 + 2*f1 + 2*f2+ f3);
}

double improvedEulerStep(double x0, double y0, double h) {
	double f0 = f(x0, y0);

	return y0 + h / 2 * (f0 + f(x0+h, y0+h*f0));
}

double modifiedEulerStep(double x0, double y0, double h) {
	double f0 = f(x0, y0);
	return y0 + h*f(x0 + h / 2, y0 + h / 2 * f0);
}

using Method = double(*)(double, double, double);
Method methods[] = { modifiedEulerStep, improvedEulerStep, rkStep };

int main(int argc, char** argv) {
	if (argc != 2)
		return -1;
	
	int methodNb = std::atoi(argv[1]);

	if (methodNb < 0 || methodNb > 2) 
		return -2;


	auto method = methods[methodNb];

	double y0 = 0.;
	double x0 = 0;
	double h = 0.05;

	while (x0 <= 1) {
		y0 = method(x0, y0, h);
		x0 += h;
		std::cout << x0 << " " << y0 << std::endl;
	}

	return 0;
}