
#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
double g = 9.8;
double m = 1e-2;
double k = 1e-4;

double f(double x0, double y0)
{
	return g - k/m*y0*y0;
}

double RKFError(double h, double f0, double f2, double f3, double f4, double f5)
{
	return std::abs(h*(1./360.*f0 - 128./4275.*f2 - 2197./75240.*f3 + 1./50.*f4 + 2./55.* f5));
}

double RKFStep(double& h, double x0, double y0, double epsilon)
{
	double f0, f1, f2, f3, f4, f5, error, hnew = h;
	do {
		
		if ( h != hnew)
		{
			h = hnew;
			std::cout << "Step rejected: " << x0 << " " << h << std::endl;
		}
		
		f0 = f(x0, y0);
		f1 = f(x0 + h/4., y0 + h/4.*f0);
		f2 = f(x0 + 3./8.*h, y0+3./32.*h*f0+9./32.*h*f1);
		f3 = f(x0 + 12./13.*h, y0+1932./2197.*h*f0-7200./2197.*h*f1+7296./2197.*h*f2);
		f4 = f(x0 + h, y0 + 439./216.*h*f0 - 8*h*f1 + 3680.*h/513.*f2-845.*h/4104.*f3);
		f5 = f(x0 + h/2, y0 
		- 8.*h/27.*f0 
		+ 2.*h*f1
		-3544.*h/2565.*f2
		+1859.*h/4104.*f3
		 - 11.*h/40.*f4);	
		error = RKFError(h, f0, f2, f3, f4, f5);
		//std::cout << hnew << std::endl;
		//std::cout << error << std::endl;
		hnew = 0.9*h*std::pow(std::abs(h)*epsilon/error, 0.25);
		
		//std::cout << f0 << " " << f1 << " " << f2 << " " << f3 << " " << f4 << " " << f5 << std::endl;
	} while (error > h*epsilon);
	
	double ret = y0 + h*(16./135.*f0+6656./12825.*f2+28561./56430.*f3 - 9./50.*f4 + 2./55. * f5);
	h = hnew;
	return ret;
}



int main() {
	double h=0.2, t = 0, y0 = 0, tmax = 10., epsilon = 1e-5;
	std::vector<std::pair<double, double>> results;
	while (t < tmax)
	{
		double tn = t + h;
		y0 = RKFStep(h, t, y0, epsilon);
		t = tn;
		results.push_back({y0, t});
	}
	
	for(auto&& result: results)
	{
		std::cout << result.first << " " << result.second << std::endl;
	}
	std::cout << results.size() << std::endl;
	
}
