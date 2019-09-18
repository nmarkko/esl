#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <systemc>
#include <vector>

SC_MODULE(Fibonacci) {
	public:
		SC_HAS_PROCESS(Fibonacci);
		Fibonacci(sc_core::sc_module_name name);
		void method1();
		void method2();
		long unsigned int fib_calc(int n);
		void print(std::vector<long unsigned int> container);
	protected:
	    sc_core::sc_event e1;
		std::vector<long unsigned int> numbers;
};

#endif
