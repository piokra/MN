#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
float h = 0.05;
float x0 = 0, xe = 1;
float epsilon = 0.0000005;

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
	v[1].second = 1./(-15+50*h+120*h*h)*(-v[5].second+(6+5*h)*v[4].second + (-14 - 30*h)*v[3].second + (4+90*h)* v[2].second + (-10-15*h)*v[0].second +120*h*h*v[1].first);
	for (int i = 2; i<v.size()-2; ++i) {
		v[i].second = 1./(-30 + 120 * h*h)*((1.-5.*h)*v[i+2].second + (-16. + 40. * h)*v[i+1].second +
		(-16. - 40*h)*v[i-1].second + (1 + 5*h)*v[i-2].second + 120 * h*h*v[i].first);
	}
	int M = v.size()-2;
	v[M].second = 1./(-15 - 50*h + 120*h*h)*(-v[M-4].second + (6 - 5*h)*v[M-3].second + (-14 + 30 * h)*v[M-2].second + (4 - 90*h)*v[M-1].second + (-10+15*h)*v[M+1].second + 120*h*h*v[M].first);
	
	
	return maxError(prev, v);
}



int main() {
	auto xy = xy0();
	float err = 1;
	while (err > epsilon) {
		err = jacobiStep(xy);
	}
	print(xy);	
}
