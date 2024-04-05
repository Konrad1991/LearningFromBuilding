#include "reverse.hpp"

using namespace reverse;

int main() {
    
    std::vector<Number<double> > tape;
    std::vector<int> operations;

    // f(x) = (4x - 3)^5
    // f(x) = 3125 where x = 2
    // df/dx = 20*(4x-3)^4 = 20*(5)^4 = 20*625 = 12500
    Number<double> x(2, 0);

    // Forward pass
    TimesOp<double> to;
    MinusOp<double> mo;
    ExpOp<double> eo;
    
    to.Forward(x, Number<double>().SetValue(4.0), tape, operations); // 4*x
    mo.Forward(to.output, Number<double>().SetValue(3.0), tape, operations); // 4*x - 3
    eo.Forward(mo.output, 5, tape, operations);

    // Reverse pass
    eo.output.SetGradient(1.0);
    eo.Backward(mo.output);
    mo.Backward(to.output, Number<double>().SetValue(3.0));
    to.Backward(x, Number<double>().SetValue(4.0));
    
    to.print();
    mo.print();
    eo.print();
    x.print();

    std::cout << std::endl;

    tape[2].SetGradient(1.0);
    double exponent = 5;
    tape[1].AddGradient(tape[2].GetGradient() * exponent * std::pow(tape[1].GetValue(), exponent - 1));
    tape[0].AddGradient(tape[1].GetGradient());
    Number result(x.GetValue(), 0.0);
    result.AddGradient(tape[0].GetGradient() * 4.0);
    for(auto i: tape) i.print();
    result.print();


    // first goal
    // the forward pass should look like: (4*x - 3)^5
    // Number anpassen wie etr::VEC
    // add tape as attribute to Number class

    // second goal
    // define a function which automaticallies calculate the backward pass

    return 0;
}
