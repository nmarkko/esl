/* Determine the degree of the Maclaurin polynomial 
necessary to succesfully approximate sine function
on the interval from 0 to 2*pi with approximation error 
less than   const double error */

#include <iostream>
#include <cmath>

#define PI 3.14159265
#define SIZE 50 //number of points in which the sine function will be calculated


//factorial has got to be of type DOUBLE
//because INT does not have enough space for large numbers (arguments >=14 were causing problems)
 double factorial(int n)
 {
 	double val = 1;
 	for (int i = n; i > 1; --i)
 		val *= i;
 	return val;
 }
 

double sine_taylor(double x, int n){
	double sum = 0;
	int k;
	for(k=1; k<=n;k+=2) {
		if( k%4 == 1 )
			sum = sum + pow(x,k)/factorial(k);
		else
			sum = sum - pow(x,k)/factorial(k);
	}
	return sum;
}

bool passCheck(const double *gold, const double *sys,
			   double delta)
{
	for (size_t i = 0; i != SIZE; ++i)
	{
		if (std::abs(gold[i] - sys[i]) > delta)
			return false;
	}
	return true;
}
	
int main(){
	const double error = 1e-5;
	int N=0; //the degree of Taylor's (Maclaurin's) polynomial
	double x=0;
	
	double sine_gold_vector[SIZE];
	double sine_by_series_vector[SIZE];
	
	for(int i=0; i<SIZE; i++) {
		x = i*2*PI/SIZE;
		sine_gold_vector[i]=sin(x);
		std::cout<<i<<"-th member of the gold array is "<<sine_gold_vector[i]<<std::endl;
	}
	
	
	
	bool pass = false;
	
	// Main loop
	do
	{
		N++;
		std::cout << "\nIteration number " << N << endl;
		for(int i=0; i<SIZE; i++) {
			x = i*2*PI/SIZE;
			sine_by_series_vector[i] = sine_taylor(x, N);
			std::cout<<i<<". array member is "<<sine_by_series_vector[i]<<std::endl;
		}

		// Check if error is small enough
		pass = passCheck(sine_gold_vector, sine_by_series_vector, error);
		
	} while(pass == false);
	
	std::cout<<"\nWe need polynomial of degree "<< N<<" in order for the error to be less than "<< error << std::endl;

	
	return 0;
}
