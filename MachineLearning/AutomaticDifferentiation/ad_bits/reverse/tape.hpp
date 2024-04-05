#ifndef TAPE_H
#define TAPE_H

#include "header.hpp"

namespace reverse{
	
	template<typename T>
	class Tape{
		public:
			T value;
			T gradient;
			int operation;

			Tape& SetValue(T val) {
				this -> value = val;
				return *this;
			}
	};
};

#endif