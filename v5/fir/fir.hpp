#ifndef FIR_H
#define FIR_H

#include <systemc>
#include <deque>

SC_MODULE(fir)
{
public:
	SC_HAS_PROCESS(fir);
	fir(sc_core::sc_module_name name,sc_core::sc_mutex *left_fork, sc_core::sc_mutex *right_fork);
	void seq();
	void comb();
	
protected:
	sc_core::sc_signal<double>
	bool left_taken=false;
	bool right_taken=false;
};

#endif
