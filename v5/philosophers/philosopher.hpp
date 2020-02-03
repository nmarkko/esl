#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <systemc>

SC_MODULE(philosopher) {
	public:
		SC_HAS_PROCESS(philosopher);
		philosopher(sc_core::sc_module_name name, sc_core::sc_mutex *left, sc_core::sc_mutex *right);
		void life();
	protected:
		sc_core::sc_mutex *left;
		sc_core::sc_mutex *right;
};

#endif