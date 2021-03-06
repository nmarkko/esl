#include "fibonacci.hpp"
#include <cstdlib>
#include <ctime>

Fibonacci::Fibonacci(sc_core::sc_module_name name)  {
		SC_THREAD(method1);
		SC_THREAD(method2);
		dont_initialize();
		sensitive<<e1;
		srand(time(NULL));
}
long unsigned int Fibonacci::fib_calc(int n) {
	if( n == 0 || n == 1) return n;
	else {
		long unsigned int a=0, b=1;
		for(int i = 2; i <= n; i++) {
			b = a + b;
			a = b - a;
		}
		return b;
	}
}

void Fibonacci::method1() {
	int k=0;
	while(true) {
		int x = rand() % 90 + 10;
		wait(x, sc_core::SC_NS); //change to NS
		numbers.push_back(fib_calc(k));
        e1.notify();
		k++;
		k = k % 64;
	}
}

void Fibonacci::method2() {
    while(true) {

        wait(5,sc_core::SC_NS);
		//std::cout << "Number of generated Fib numbers " << numbers.size() << std::endl;
		std::cout << "@ " << sc_core::sc_time_stamp() << std::endl;
		//std::cout << "Generated numbers are: " << std::endl;
		//print(numbers);
		numbers.clear();
		wait(e1);
    }
}

void Fibonacci::print(std::vector<long unsigned int> container) {
	std::vector<long unsigned int>::iterator it = container.begin();
	while(it != container.end()) {
		std::cout << *it << ", " ;
		++it;
	}
	std::cout << std::endl;
}
