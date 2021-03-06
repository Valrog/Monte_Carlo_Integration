// Monte_Carlo_Integration.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

double integral(double integral_val, int n); // Calculates a numerical value of an integral
double standard_err(double a, double b, int n, double sum, double sum_two); // Calculates standard error
double test_function(double x); // Calculates the value of f(x)

int main()
{
	double integral_val = 0; // Value of the integral
	double standard_err = 0; // Standard error
	unsigned int n = 2; // Counter for Monte Carlo iterations

	std::cout.precision(10);

	for (int i = 0; i < 16; i++) // This loop will perform 16 Monte Carlo integrations on n iterations
	{
		integral_val = integral(integral_val, n);
		n = n * 2;
	}

	std::cout << "\nPress any key to exit: ";
	std::cin.get(); // So the console window doesn't close
	return 0;
}

double integral(double integral_val, int n)
{
	std::ofstream file;
	file.open("Integration.txt", std::fstream::app);

	double st_err = 0; // Standard error
	double sum = 0, sum_two = 0;
	double x_coordinate = 0;

	std::default_random_engine generator(std::random_device{}()); // Random number generator
	std::uniform_real_distribution<double> distribution(0.0, 1.0); // Uniform distribution on interval [0, 1)

	double a = 0.0; // Interval lower bound
	double b = 3.0; // Interval upper bound
	double u = 0; // Randomly generated number
	double function_result;

	for (int i = 0; i < n; i++)
	{
		u = distribution(generator); // Generates a random number u
		x_coordinate = a + (b - a) * u;
		function_result = test_function(x_coordinate);
		sum = sum + function_result;
		sum_two = sum_two + pow(function_result, 2);
	}

	integral_val = (sum*(b - a)) / n;
	sum = sum / n;
	sum_two = sum_two / n;
	st_err = standard_err(a, b, n, sum, sum_two);


	file << n << " " << integral_val << " " << st_err << std::endl; // Writes data into the file

	std::cout << "\nIterations: " << n << "; Integral value = " << integral_val << "; Standard error: " << st_err; // Test output


	file.close();

	return integral_val;
}

double standard_err(double a, double b, int n, double sum, double sum_two)
{
	return (b - a) * sqrt(((sum_two - pow(sum, 2)) / n));
}

double test_function(double x)
{
	double numerator = 0;
	double denominator = 0;
	double fraction = 0;
	double function_result = 0;

	numerator = cosh(2 + cos(pow(x, 2)*sqrt(x)));
	denominator = pow(x, 2) + 3 * x + 1;
	fraction = numerator / denominator;

	function_result = pow(fraction, 0.25);

	return function_result;
}