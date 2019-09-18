#include <systemc>
#include "fibonacci.hpp"

int sc_main(int argc, char* argv[])
{
	Fibonacci uut("UUT");

	sc_start(20, sc_core::SC_SEC);

	std::cout << "Simulation finished at " << sc_core::sc_time_stamp() << std::endl;
	return 0;
}
