#include "coll.hpp"
#include <cstdlib>
#include <ctime>

	using namespace sc_core;
	using namespace std;

	coll::coll(sc_module_name n) : sc_module(n)
	{
		cout << name() << " constructed.\n";
		SC_METHOD(process1);
		dont_initialize();
		sensitive << num0 << num1 << num2;
		srand(time(NULL));
	}

	void coll::process1()
	{
		int time = 5 + rand()%6;
		event_out.notify(time, SC_NS);	
	}


	void coll::process2()
	{
		int value = rand()%100;
		if(gen) {
			num->write(value);
			start->write(true);
		}
	}