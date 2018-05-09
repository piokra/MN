#include <cmath>
#include <vector>
#include <iostream>

float A(int i, int j) {
	if (i == j)
		return 2;
		
	if (std::abs<int>(i-j) == 1)
		return -1;
		
	return 0;
}

float B(int i) {
	return i;
}

float maxError(const std::vector<float>& l, const std::vector<float>& r) {
	float error = 0;
	for (int i = 0; i<l.size(); ++i) {
		float err = (l[i]-r[i])/l[i];
		if (err > error) {
			error = err;
		}
	}
	return error;
}

std::vector<float> jacobiStep(const std::vector<float>& p) {
	auto v = p;
	for (int i=0; i<p.size(); ++i) {
		float r = B(i);
		for(int j = 0; j<p.size(); ++j) {
			if (i!=j) {
				r -= A(i, j)*p[j];
			}
		}
		v[i] = 1./A(i,i)*r;
	}
	return v;
}

std::vector<float> gaussSeidelStep(const std::vector<float>& p) {
	auto v = p;
	for (int i=0; i<p.size(); ++i) {
		float r = B(i);
		for(int j = 0; j<p.size(); ++j) {
			if (i!=j) {
				r -= A(i, j)*v[j];
			}
		}
		v[i] = 1./A(i,i)*r;
	}
	return v;
}

std::vector<float> initialGuess() {
	return {1, 1, 1, 1, 1};
}

template<typename F>
std::vector<float> method(F f) {
	auto p = initialGuess();
	auto v = p;
	float error = 1;
	do {
		p = v;
		v = f(p);
		error = maxError(v, p);
	} while(error > 0.00001);
	return v;
}

void print(const std::vector<float>& v) {
	for(auto&& e: v) {
		std::cout << e << std::endl;
	}
}

int main() {
	print(method(jacobiStep));
	std::cout << std::endl;
	print(method(gaussSeidelStep));
	return 0;
}
