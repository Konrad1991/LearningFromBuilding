#include "reverse.hpp"

using namespace reverse;


int main() {
	std::vector<Number<double> > tape;
    std::vector<int> operations;
    Number<double> x(2, 0);
    Number<double> y(3, 0);

    TimesOp<double> test(x, y);
    Number<TimesOp<double>> test2(test);

}

