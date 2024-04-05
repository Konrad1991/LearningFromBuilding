#include <iostream>

class DualNumber {
public:
    DualNumber(double value = 0.0, double derivative = 0.0) : value_(value), derivative_(derivative) {}
    double value() const { return value_; }
    double derivative() const { return derivative_; }
    void setDerivative(double derivative) { derivative_ = derivative; }

private:
    double value_;
    double derivative_;
};


DualNumber operator+(const DualNumber& lhs, const DualNumber& rhs) {
    return DualNumber(lhs.value() + rhs.value(), lhs.derivative() + rhs.derivative());
}

DualNumber operator-(const DualNumber& lhs, const DualNumber& rhs) {
    return DualNumber(lhs.value() - rhs.value(), lhs.derivative() - rhs.derivative());
}

DualNumber operator*(const DualNumber& lhs, const DualNumber& rhs) {
    return DualNumber(lhs.value() * rhs.value(), lhs.derivative() * rhs.value() + lhs.value() * rhs.derivative());
}

DualNumber operator/(const DualNumber& lhs, const DualNumber& rhs) {
    return DualNumber(lhs.value() / rhs.value(), (lhs.derivative() * rhs.value() - lhs.value() * rhs.derivative()) / (rhs.value() * rhs.value()));
}

DualNumber operator*(const double& lhs, const DualNumber& rhs) {
    return DualNumber(lhs * rhs.value(), lhs * rhs.derivative());
}

DualNumber operator*(const DualNumber& lhs, const double& rhs) {
    return DualNumber(lhs.value() * rhs, lhs.derivative() * rhs);
}

int main() {
	DualNumber a(2.0, 1.0);  // Represents a = 2.0 with derivative 1.0
	DualNumber b(3.0, 0.0);  // Represents b = 3.0 with derivative 0.0
		
	DualNumber z = a * 5.0 * a + b;  // Represents z = a * 5 * a + b = 23.0 with derivative 21.0
	std::cout << "z = a * 5.0 * a + b " << "with: a = 2 and b = 3" << std::endl; 
	std::cout << "z = " << z.value() << " dz/da = " << z.derivative() << std::endl;

	a.setDerivative(0.0);
	b.setDerivative(1.0);
	z = a * 5.0 * a + b;  // Represents z = a * 5 * a + b = 23.0 with derivative 21.0
	std::cout << "z = a * 5.0 * a + b " << "with: a = 2 and b = 3" << std::endl; 
	std::cout << "z = " << z.value() << " dz/db = " << z.derivative() << std::endl;
					
}
