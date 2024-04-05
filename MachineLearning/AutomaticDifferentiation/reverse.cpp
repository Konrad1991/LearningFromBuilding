#include <iostream>

class Number {
	private:
		double value;
		double gradient;
	public:
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

class TimesOp {

public:
	Number output;

    void Forward(Number& a, Number& b) {
        a.print(); b.print();
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

class MinusOp {
public:
    Number output;

    void Forward(Number& a, Number& b) {
        output.SetValue(a.GetValue() - b.GetValue());
    }

    void Backward(Number& a, Number& b) {
        a.AddGradient(output.GetGradient());
        b.AddGradient(output.GetGradient());
    }
};

int main() {

    {
    // Test Nr.1 f(x) = x*x
    Number x;
    x.SetValue(3.0);
    x.SetGradient(0.0);
    // f(x) = 3*3 = 9
    // df/dx = 2*x = 6
    TimesOp to;
    to.Forward(x, x);
    to.output.SetGradient(1.0);
    to.Backward(x, x);
    std::cout << to.output.GetValue() << " " << x.GetGradient() << std::endl;

    // reset to and x
    x.SetGradient(0.0); to.output.SetGradient(0.0);
    std::cout << std::endl;
    }

    {
    // Test Nr.2 f(y, x) = y*x
    // f(x) = 4*3 = 12
    // df/dx = y = 4
    // df/dy = x = 3
    Number x;
    Number y;
    x.SetValue(3.0);
    x.SetGradient(0.0);
    y.SetValue(4.0);
    y.SetGradient(0.0);
    TimesOp to;
    to.Forward(x, y);
    to.output.SetGradient(1.0);
    to.Backward(x, y);
    std::cout << to.output.GetValue() << " " << x.GetGradient() << " " << y.GetGradient() << std::endl;
    // reset to and x
    x.SetGradient(0.0); to.output.SetGradient(0.0);
    std::cout << std::endl;
    }

    {
    // Test Nr.3 f(x) = x*x*x
    Number x;
    x.SetValue(4.0);
    x.SetGradient(0.0);
    // f(x) = x*x*x
    // f(x) = 4*4*4 = 64
    // df/dx = 3*x*x = 48

    // f(x) = x*x*x
    // y = x*x
    // f(x) = y*x

    // df/dy = x
    // df/dx = y
    // df/dx = (dy/dx)*x + (dx/dx)*y = 2*x*x + 1*y = 2*x*x + x*x = 48  

    TimesOp to1, to2;
    to1.output.SetGradient(0.0);
    to1.Forward(x, x);
    to2.Forward(to1.output, x);
    to2.output.SetGradient(1.0);
    to2.Backward(to1.output, x);
    to1.Backward(x, x);
    std::cout << to2.output.GetValue() << " " << x.GetGradient() << std::endl;
    std::cout << std::endl;
    }

    {
    // Test Nr.4 f(x, y) = (x + y) * x
    Number x, y;
    x.SetValue(3.0);
    x.SetGradient(0.0);
    y.SetValue(4.0);
    y.SetGradient(0.0);

    PlusOp po;
    TimesOp to;

    po.Forward(x, y);
    to.Forward(po.output, x);

    to.output.SetGradient(1.0);
    po.output.SetGradient(0.0);
    to.Backward(po.output, x);
    po.Backward(x, y);

    // df/dx = (x + y) * x = (3 + 4) * 3 = 21 where x = 3 and y = 4
    // df/dx = 2*x + y = 10 where x = 3 and y = 4
    // df/dy = x = 3 where y = 4 and x = 3
    std::cout << to.output.GetValue() << " " << x.GetGradient() << " " << y.GetGradient() << std::endl;
    }    
}