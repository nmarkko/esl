#ifndef _COLL_HPP_
#define _COLL_HPP_

#include <systemc>


using namespace sc_core;

SC_MODULE(coll)
{
public:
	SC_HAS_PROCESS(coll);
	coll(sc_module_name);

	sc_in<int> num0;
	sc_in<int> num1;
	sc_in<int> num2;
	sc_out<int> nums;
protected:
	void process1();
	void process2();
	sc_event event_out;
	sc_fifo<int> f0;
};

#endif
