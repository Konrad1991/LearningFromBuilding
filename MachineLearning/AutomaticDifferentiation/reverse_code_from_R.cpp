#include <iostream>
#include <vector>

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
        std::cout << "old gradient " << this -> gradient << " gradient added " << grad  << " new gradient " << gradient + grad << std::endl;
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

    void print(std::string s) {
        std::cout << s << value << " " << gradient << std::endl;
    }
};

class TimesOp {

public:
    Number output;

    void Forward(Number& a, Number& b, std::vector<Number>& tape) {
        Number temp;
        temp.SetValue(a.GetValue() * b.GetValue());
        tape.push_back(temp);
        output.SetValue(a.GetValue() * b.GetValue());
    }

    void Backward(Number& a, Number& b, std::string a_ = "", std::string b_ = "", std::string output_ = "") {
        output.print(output_);
        a.print(a_);
        b.print(b_);
        a.AddGradient(output.GetGradient() * b.GetValue());
        b.AddGradient(output.GetGradient() * a.GetValue());
    }
};

int main() {

    // Test Nr.3 f(x) = x*x*x
    std::vector<Number> tape;
    Number x;
    x.SetValue(4.0);
    x.SetGradient(0.0);
    // f(x) = x*x*x
    // f(x) = 4*4*4 = 64
    // df/dx = 3*x*x = 48

    TimesOp to1, to2;
    to1.output.SetGradient(0.0);
    to1.Forward(x, x, tape);
    to2.Forward(to1.output, x, tape);

    for(auto i: tape) i.print();
    std::cout << std::endl;
    x.print();
    std::cout << std::endl;
    
    to2.output.SetGradient(1.0);
    to2.Backward(to1.output, x, "to1.output ", "x ", "to2 ");
    std::cout << std::endl;
    to1.Backward(x, x, "x ", "x ", "to1 ");
    std::cout << std::endl;
    //std::cout << to2.output.GetValue() << " " << x.GetGradient() << std::endl;
    //std::cout << std::endl;

}