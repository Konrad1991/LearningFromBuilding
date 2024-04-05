#ifndef NUMBER_H
#define NUMBER_H

#include "header.hpp"

namespace reverse {

template<typename T>
class Number {
	private:
		T value;
		T gradient;
		std::vector<T> tape_vals;
		std::vector<T> tape_operations;
	public:

    Number(T val = 0, T grad = 0) : value(val), gradient(grad) {}
	T GetGradient() const {
		return gradient;
	}
	T GetValue() const {
		return value;
	}

	Number& SetValue(T val) {
		this -> value = val;
		return *this;
	}

	Number& SetGradient(T grad) {
		this -> gradient = grad;
		return *this;
	}

	Number& AddGradient(T grad) {
		this -> gradient += grad;
		return *this;
	}

    Number& operator=(const Number n) {
        this -> value = n.GetValue();
        this -> gradient = n.GetGradient();
        for(auto& i: n.tape_vals) tape_vals.push_back(i);
        for(auto& i: n.tape_operations) tape_operations.push_back(i);
        return *this;
    }

    template<typename T2>
    Number& operator=(const Number<T2>& n) {
    	this -> value = n.GetValue();
        this -> gradient = n.GetGradient();
        for(auto& i: n.tape_vals) tape_vals.push_back(i);
        for(auto& i: n.tape_operations) tape_operations.push_back(i);
        return *this;
    }

    void print() {
        std::cout << value << " " << gradient << std::endl;
    }
};

};

#endif