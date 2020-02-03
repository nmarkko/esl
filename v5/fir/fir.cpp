#include "fir.hpp"
#include <cstdlib>
#include <ctime>

philosopher::philosopher(sc_core::sc_module_name name)  {
		SC_THREAD(comb);
		SC_THREAD(seq);
		srand(time(NULL));
}

void philosopher::life() {
	while(1) {
		int time_to_think = rand()%5;
		std::cout << "Philosopher " << name() << " started thinking @" << sc_core::sc_time_stamp() << std::endl;
		wait(time_to_think, sc_core::SC_SEC);
		std::cout << "Philosopher " << name() << " stopped thinking @" << sc_core::sc_time_stamp() << std::endl;
		left->lock();
		right->lock();
		std::cout << "Philosopher " << name() << " started eating @" << sc_core::sc_time_stamp() << std::endl;
		wait(6, sc_core::SC_SEC);
		std::cout << "Philosopher " << name() << " stopped eating @" << sc_core::sc_time_stamp() << std::endl;
		left->unlock();
		right->unlock();
	}
}
