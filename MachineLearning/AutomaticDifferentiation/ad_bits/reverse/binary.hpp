#ifndef BINARY_H
#define BINARY_H

#include "Number.hpp"

namespace reverse {

template<typename T>
class TimesOp {

public:
	Number<T> output;

    TimesOp(Number<T>& l, Number<T>& r) {
        
    }

    void Forward(Number<T>& a, Number<T>& b, std::vector<Number<T> >& tape, std::vector<int>& operations) {
        output.SetValue(a.GetValue() * b.GetValue());
        tape.push_back(output);
        operations.push_back(0);
    }

    void Backward(Number<T>& a, Number<T>& b) {
        a.AddGradient(output.GetGradient() * b.GetValue());
        b.AddGradient(output.GetGradient() * a.GetValue());
    }

    void print() {
        output.print();
    }
};

template<typename T>
class ExpOp {

public:
    Number<T> output;
    double exponent;

    void Forward(Number<T>& a, double exp, std::vector<Number<T> >& tape, std::vector<int>& operations) {
        output.SetValue(std::pow(a.GetValue(), exp));
        tape.push_back(output);
        operations.push_back(3);
        exponent = exp;
    }

    void Backward(Number<T>& a) {
        a.AddGradient(output.GetGradient() * exponent * std::pow(a.GetValue(), exponent - 1.0) );
    }

    void print() {
        output.print();
    }
};

template<typename T>
class PlusOp {
public:
    Number<T> output;

    void Forward(Number<T>& a, Number<T>& b, std::vector<Number<T> >& tape, std::vector<int>& operations) {
        output.SetValue(a.GetValue() + b.GetValue());
        tape.push_back(output);
        operations.push_back(1);
    }

    void Backward(Number<T>& a, Number<T>& b) {
        a.AddGradient(output.GetGradient());
        b.AddGradient(output.GetGradient());
    }

    void print() {
        output.print();
    }
};

template<typename T>
class MinusOp {
public:
    Number<T> output;

    void Forward(Number<T>& a, Number<T>& b, std::vector<Number<T> >& tape, std::vector<int>& operations) {
        output.SetValue(a.GetValue() - b.GetValue());
        tape.push_back(output);
        operations.push_back(2);
    }

    void Backward(Number<T>& a, Number<T>& b) {
        a.AddGradient(output.GetGradient());
        b.AddGradient(-1.0 * output.GetGradient());
    }

    void print() {
        output.print();
    }
};

};

#endif