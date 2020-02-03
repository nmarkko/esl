#include <systemc>
#include "philosopher.hpp"

int sc_main(int argc, char* argv[])
{
	sc_core::sc_mutex fork1, fork2, fork3, fork4, fork5;
	philosopher p1("Aristotle",&fork1, &fork2);
	philosopher p2("Socrates", &fork2, &fork3);
	philosopher p3("Democritus", &fork3, &fork4);
	philosopher p4("Plato", &fork4, &fork5);
	philosopher p5("Pythagoras", &fork5, &fork1);

	sc_start(60, sc_core::SC_SEC);

	std::cout << "Simulation finished at " << sc_core::sc_time_stamp() << std::endl;
	return 0;
	
}
