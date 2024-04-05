#include <iostream>

class Number {
	private:
		double value;
		double gradient;
	public:
	Number(double val = 0.0, double grad = 0.0) : value(val), gradient(grad) {}

	double GetGradient() const {
		return gradient;
	}
	double GetValue() const {
		return value;
	}

	Number& SetValue(double val) {
		this -> value = val;
		return *this;
	}

	Number& SetGradient(double grad) {
		this -> gradient = grad;
		return *this;
	}

	Number& AddGradient(double grad) {
		this -> gradient += grad;
		return *this;
	}

	Number& operator=(const Number n) {
		this -> value = n.GetValue();
		this -> gradient = n.GetGradient();
		return *this;
	}

	Number& operator+=(const Number& other) {
		value += other.value;
		gradient += other.gradient;
		return *this;
	}

	Number& operator*=(const Number& other) {
		gradient = gradient * other.value + value * other.gradient;
		value *= other.value;
		return *this;
	}
};

Number operator+(const Number& a, const Number& b) {
	return Number(a.GetValue() + b.GetValue(), a.GetGradient() + b.GetGradient());
}

Number operator*(const Number& a, const Number& b) {
	return Number(a.GetValue() * b.GetValue(), a.GetGradient() * b.GetValue() + b.GetGradient() * a.GetValue());
}

class TimesOp {
public:
	Number output;

    void Forward(Number& a, Number& b) {
        output.SetValue(a.GetValue() * b.GetValue());
    }

    void Backward(Number& a, Number& b) {
        a.AddGradient(output.GetGradient() * b.GetValue());
        b.AddGradient(output.GetGradient() * a.GetValue());
    }
};

class PlusOp {
public:
	Number output;

    void Forward(Number& a, Number& b) {
        output.SetValue(a.GetValue() + b.GetValue());
    }

    void Backward(Number& a, Number& b) {
        a.AddGradient(output.GetGradient());
        b.AddGradient(output.GetGradient());
    }
};

int main() {

}
