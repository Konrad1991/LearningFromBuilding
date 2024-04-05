#include <iostream>
#include <vector>
#include <math.h>

class Number {
	private:
		double value;
		double gradient;
	public:

    Number(double val = 0, double grad = 0) : value(val), gradient(grad) {}
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

    void print() {
        std::cout << value << " " << gradient << std::endl;
    }
};

std::vector<Number> tape;
std::vector<int> operations;

class TimesOp {

public:
	Number output;

    void Forward(Number& a, Number& b) {
        output.SetValue(a.GetValue() * b.GetValue());
        tape.push_back(output);
        operations.push_back(0);
    }

    void Backward(Number& a, Number& b) {
        a.AddGradient(output.GetGradient() * b.GetValue());
        b.AddGradient(output.GetGradient() * a.GetValue());
    }

    void print() {
        output.print();
    }
};

class ExpOp {

public:
    Number output;
    double exponent;

    void Forward(Number&a, double exp) {
        output.SetValue(std::pow(a.GetValue(), exp));
        tape.push_back(output);
        operations.push_back(3);
        exponent = exp;
    }

    void Backward(Number&a) {
        a.AddGradient(output.GetGradient() * exponent * std::pow(a.GetValue(), exponent - 1.0) );
    }

    void print() {
        output.print();
    }
};

class PlusOp {
public:
    Number output;

    void Forward(Number& a, Number& b) {
        output.SetValue(a.GetValue() + b.GetValue());
        tape.push_back(output);
        operations.push_back(1);
    }

    void Backward(Number& a, Number& b) {
        a.AddGradient(output.GetGradient());
        b.AddGradient(output.GetGradient());
    }

    void print() {
        output.print();
    }
};

class MinusOp {
public:
    Number output;

    void Forward(Number& a, Number& b) {
        output.SetValue(a.GetValue() - b.GetValue());
        tape.push_back(output);
        operations.push_back(2);
    }

    void Backward(Number& a, Number& b) {
        a.AddGradient(output.GetGradient());
        b.AddGradient(-1.0 * output.GetGradient());
    }

    void print() {
        output.print();
    }
};

int main() {
    
    // f(x) = (4x - 3)^5
    // f(x) = 3125 where x = 2
    // df/dx = 20*(4x-3)^4 = 20*(5)^4 = 20*625 = 12500
    Number x(2, 0);

    // Forward pass
    TimesOp to;
    MinusOp mo;
    ExpOp eo;
    
    to.Forward(x, Number().SetValue(4.0)); // 4*x
    mo.Forward(to.output, Number().SetValue(3.0)); // 4*x - 3
    eo.Forward(mo.output, 5);

    // Reverse pass
    eo.output.SetGradient(1.0);
    eo.Backward(mo.output);
    mo.Backward(to.output, Number().SetValue(3.0));
    to.Backward(x, Number().SetValue(4.0));
    
    to.print();
    mo.print();
    eo.print();
    x.print();

    std::cout << std::endl;

    tape[2].SetGradient(1.0);
    double exponent = 5;
    tape[1].AddGradient(tape[2].GetGradient() *     exponent * std::pow(tape[1].GetValue(), exponent - 1));
    tape[0].AddGradient(tape[1].GetGradient());
    Number result(x.GetValue(), 0.0);
    result.AddGradient(tape[0].GetGradient() * 4.0);
    for(auto i: tape) i.print();
    result.print();

    return 0;
}
