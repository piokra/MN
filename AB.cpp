#include <iostream>
#include <vector>

double h = 0.05;
double epsilon = 1e-6;
double x0 = 0;
double y0 = 0;
double xend = 1;

double f(double x, double y)
{
	return y*y + 1;
}

double rkStep(double x, double y) 
{
	double f0 = f(x, y);
	double f1 = f(x + h/2, y + h/2*f0);
	double f2 = f(x + h/2, y + h/2*f1);
	double f3 = f(x + h, y + h * f2);
	return y + h/6 * (f0 + 2*f1 + 2*f2 + f3);	
}
double modifiedEulerStep(double x, double y)
{
	double f0 = f(x, y);
	return y + h*f(x + h/2, y0 + h/2*f0);
}

double fourthOrderABStep(double* xs, double* ys)
{
	double ps[4];
	for (int i = 0; i < 4; ++i)
	{
		ps[i] = f(xs[i], ys[i]);
	}
	return ys[3] + h/24*(55*ps[3] - 59*ps[2] + 37*ps[1]-9*ps[0]); 
}

std::pair<std::vector<double>, std::vector<double>> fourthOrderABMethod()
{
	double x = x0;
	std::vector<double> ys;
	std::vector<double> xs;
	
	while(x < xend+h)
	{
		xs.push_back(x);
		x += h;
	}
	
	ys.push_back(y0);
	for(int i = 0; i<4; ++i)
	{
		ys.push_back(rkStep(xs[i], ys[i]));
	}
	
	for(int i = 4; i<xs.size(); ++i)
	{
		ys.push_back(fourthOrderABStep(xs.data()+(i-3), ys.data()+(i-3)));
	}
	return {xs, ys};
}

double secondOrderABStep(double* x, double* y)
{
	double f0 = f(x[1], y[1]);
	double f1 = f(x[0], y[0]);
	return y[1] + h/2*(3*f0 - f1);
}

std::pair<std::vector<double>, std::vector<double>> secondOrderABMethod()
{
	double x = x0;
	std::vector<double> ys;
	std::vector<double> xs;
	
	while(x < xend+h)
	{
		xs.push_back(x);
		x += h;
	}
	
	ys.push_back(y0);
	for(int i = 0; i<2; ++i)
	{
		ys.push_back(modifiedEulerStep(xs[i], ys[i]));
	}
	
	for(int i = 2; i<xs.size(); ++i)
	{
		ys.push_back(secondOrderABStep(xs.data()+(i-1), ys.data()+(i-1)));
	}
	return {xs, ys};
}

std::pair<std::vector<double>, std::vector<double>> diffMethod()
{
	auto ret = fourthOrderABMethod();
	auto x4s = ret.first;
	auto y4s = ret.second;
	
	auto ret2 = secondOrderABMethod();
	auto y2s = ret2.second;
	
	for (int i=0; i<y4s.size(); ++i)
	{
		y4s[i] -= y2s[i];
	}
	return {x4s, y4s};
}

void printMethod(std::string title, std::pair<std::vector<double>, std::vector<double>>(*method)())
{
	std::cout << title << std::endl;
	auto ret = method();
	auto xs = ret.first;
	auto ys = ret.second;
	
	for (int i = 0; i<xs.size(); ++i)
	{
		std::cout << xs[i] << " " << ys[i] << std::endl;
	}
}

int main() {
	printMethod("--- Second Order ---", secondOrderABMethod);
	printMethod("--- Fourth Order ---", fourthOrderABMethod);
	printMethod("--- Difference ---", diffMethod);
	
	return 0;
}
