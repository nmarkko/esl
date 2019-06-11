#define SC_INCLUDE_FX
#include <systemc>
#include <iostream>
#include <deque>
#include <vector>
#include <cmath>

#define NUMBER_OF_POINTS 64

typedef sc_dt::sc_fix_fast num_t;
typedef std::deque<num_t> array_t;
typedef std::vector<double> orig_array_t;

void copy2fix(array_t& dest, const orig_array_t& src, int W, int F)
{
    for (size_t i = 0; i != src.size(); ++i)
    {
        num_t d(W, F);
        d = src[i];
        if (d.overflow_flag())
            std::cout << "Overflow in conversion.\n";
        dest.push_back(d);
    }
}

bool passCheck(const orig_array_t& gold, const orig_array_t& sys,
			   double delta)
{
	for (size_t i = 0; i != gold.size(); ++i)
	{
		if (std::abs(gold[i] - sys[i]) > delta)
			return false;
	}
	return true;
}

int sc_main(int argc, char* argv[])
{
    //f(0)=0, f(1)=1
    orig_array_t fib_orig = {0, 1};
    orig_array_t gold = {0,1};
    orig_array_t sys = {0,1};
    array_t fib;

    int W = 1;

    const double error_d = 0;
    bool pass = false;
    orig_array_t::iterator it;
    array_t::iterator lol;

    // Calculate gold vector
    double new_value=0;
    for (size_t i = 2; i < NUMBER_OF_POINTS; ++i)
        {
            it = gold.end();
            // Calculate new value by formula f(n) = f(n-1) + f(n-2)
            //new_value=*(--it)+*(--it);
            new_value=gold[i-1]+gold[i-2];
            gold.push_back(new_value);
            std::cout<<i<<"-th value is "<<new_value<<std::endl;
        }

    // Main loop
    do
    {

        std::cout <<
                  "Starting pass for number format " << W <<
                  "." << "0" << std::endl;

        // Convert numbers
        copy2fix(fib, fib_orig, W, W);

        // Calculate output
        for (size_t i = 2; i < NUMBER_OF_POINTS; ++i)
        {
            num_t sum(W, W);
            sum=0;
            lol = fib.end();
            // Calculate new value by formula f(n) = f(n-1) + f(n-2)
            sum=*(--lol)+*(--lol);
            fib.push_back(sum);

            sys.push_back(sum.to_double());
            std::cout << sum << " ";

        }
        std::cout << std::endl;

        // Check if error is small enough
        pass = passCheck(gold, sys, error_d);
        W++;
        sys.clear();
        sys = {0,1};
        fib.clear();
    } while(pass == false);

    //for (std::vector<double>::iterator it = fib_orig.begin() ; it != fib_orig.end(); ++it)
    //    std::cout << ' ' << *it;
    std::cout << "Potrebno je " << W << "bita" << std::endl;

    return 0;
}
