#define SC_INCLUDE_FX
#include <systemc>
#include <iostream>
#include <deque>
#include <vector>
#include <cmath>

#define PI 3.14159265
#define NUM_OF_POINTS 50 // Number of points in which the sine function will be calculated
#define DEGREE 23 // Degree of taylor's polynomial

typedef sc_dt::sc_fix_fast num_t;
typedef std::deque<num_t> array_t;
typedef std::vector<double> orig_array_t;

 double factorial(int n)
 {
 	double val = 1;
 	for (int i = n; i > 1; --i)
 		val *= i;
 	return val;
 }
// template <typename T> function_declaration;
template <typename T>
T sine_taylor(double x, int n){
	T sum = 0;
	int k;
	for(k=1; k<=n;k+=2) {
		if( k%4 == 1 )
			sum = sum + pow(x,k)/factorial(k);
		else
			sum = sum - pow(x,k)/factorial(k);
	}
	return (sum);
}


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
    orig_array_t x_orig;
	orig_array_t gold;
	orig_array_t sys;

	//array_t x;
	//array_t y;

	const double error_d = 1e-3;
	int W = 1;
	const int F = 1;

	double argument_value;
	// Calculate gold vector and
	// vector of fixed-point inputs for sine function
	for(int i=0; i<NUM_OF_POINTS; i++) {
		argument_value = i*2*PI/NUM_OF_POINTS;
		x_orig.push_back(argument_value);
        gold.push_back(sine_taylor<double> (x_orig[i], DEGREE));
		std::cout << "Sine of " << x_orig.back()<< " is " << gold.back() << std::endl;
	}


	bool pass = false;
	// Main loop
	do
	{
		std::cout <<
			"Starting pass for number format " << F <<
			"." << W-F << std::endl;
		// Convert numbers
		//copy2fix(x, x_orig, W, F);

		// Calculate output
		num_t sum(W,F);
		for (size_t i = 0; i < NUM_OF_POINTS; ++i)
		{
//			num_t new_value(W, F);
//			new_value = sine_taylor<num_t>(x_orig[i], DEGREE);
            // Raèunanje sinusa preko tejlorov razvoja,
            // jer nisam uspeo da parametrizujem sa usranim sc_fix_fast tipom
            sum = 0;
            int k;
            for(k=1; k<=DEGREE;k+=2) {
                if( k%4 == 1 )
                    sum = sum + pow(x_orig[i],k)/factorial(k);
                else
                    sum = sum - pow(x_orig[i],k)/factorial(k);
            }

			sys.push_back(sum.to_double());
			std::cout << sum << " ";
		}
		std::cout << std::endl;

		// Check if error is small enough
		pass = passCheck(gold, sys, error_d);
		W++;
//		x.clear();
		sys.clear();
	} while(pass == false);

	std::cout << "W = "<< W <<" and F = " << F <<std::endl;

	return 0;
}
