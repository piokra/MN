#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
float h = 0.1;
float x0 = 0, xe = 1;
float epsilon = 0.0005;

std::vector<std::pair<float, float>> xy0() {
	std::vector<std::pair<float,float>> ret;
	float x = 0;
	while (x<=xe+0.5*h) {
		ret.emplace_back(x, 100*x);
		x+=h;
	}
	return ret;
}

void print(const std::vector<std::pair<float, float>>& v) {
	for (auto&& el: v) {
		std::cout << el.first << " " << el.second << std::endl;
	}
}

float maxError(const std::vector<std::pair<float, float>>& left, const std::vector<std::pair<float, float>>& right) {
	if (left.size() != right.size()) {
		return 1./0.;
	}
	float maxErr = 0;
	for(int i=0; i<left.size(); ++i) {
		maxErr = std::max(maxErr, std::abs((left[i].second - right[i].second)/right[i].second));
	}
	return maxErr;
}

float jacobiStep(std::vector<std::pair<float, float>>& v) {
	auto prev = v;
	for (int i = 1; i<v.size()-1; ++i) {
		v[i].second = 1./(2-10*h*h)*((1 - 5*h/2.)*prev[i+1].second+(1 + 5*h/2.)*prev[i-1].second-10*h*h*prev[i].first);
	}
	return maxError(prev, v);
}

float gaussStep(std::vector<std::pair<float, float>>& v) {
	auto prev = v;
	for (int i = 1; i<v.size()-1; ++i) {
		v[i].second = 1./(2-10*h*h)*((1 - 5*h/2.)*prev[i+1].second+(1 + 5*h/2.)*v[i-1].second-10*h*h*prev[i].first);
	}
	return maxError(prev, v);
}


int main() {
	auto xy = xy0();
	float err = 1;
	while (err > epsilon) {
		err = jacobiStep(xy);
	}
	print(xy);
	
	xy = xy0();
	err = 1;
	while (err > epsilon) {
		err = gaussStep(xy);
	}
	print(xy);
	
	
}
