#include <iostream>
#include <string>
#include "ConfigBase.h"

class MyConfig : public ConfigBase {
public:
	int i;
	long l;
	long long ll;
	unsigned long ul;
	unsigned long long ull;
	float f;
	double d;
	long double ld;
	std::string str;
	
	MyConfig() {
		V(i);
		V(l);
		V(ll);
		V(ul);
		V(ull);
		V(f);
		V(d);
		V(ld);
		V(str);
	}
};

#define P(x) std::cout << #x << "\t=\t" << x << std::endl

int main() {
	MyConfig config;
	config.load("config.ini");
	
	P(config.i);
	P(config.l);
	P(config.ll);
	P(config.ul);
	P(config.ull);
	P(config.f);
	P(config.d);
	P(config.ld);
	P(config.str);
	
	return 0;
}