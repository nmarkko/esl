#include "rnd_gen.hpp"
#include <cstdlib>
#include <ctime>

	using namespace sc_core;
	using namespace std;

	rnd_gen::rnd_gen(sc_module_name n) : sc_module(n)
	{
		cout << name() << " constructed.\n";
		SC_METHOD(process1);
		dont_initialize();
		sensitive << gen;
		SC_METHOD(process2);
		dont_initialize();
		sensitive << event_out;
		srand(time(NULL));
	}

	void rnd_gen::process1()
	{
		int time = 5 + rand()%6;
		event_out.notify(time, SC_NS);	
	}


	void rnd_gen::process2()
	{
		int value = rand()%100;
		if(gen) {
			num->write(value);
			start->write(true);
		}
	}