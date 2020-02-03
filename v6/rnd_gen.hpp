#ifndef _RND_GEN_HPP_
#define _RND_GEN_HPP_

#include <systemc>


using namespace sc_core;

SC_MODULE(rnd_gen)
{
public:
	SC_HAS_PROCESS(rnd_gen);
	rnd_gen(sc_module_name);

	sc_in<bool> gen;
	sc_out<bool> start;
	sc_out<int> num;
protected:
	void process1();
	void process2();
	sc_event event_out;
};

#endif
