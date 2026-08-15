#ifndef GRADIENT_DESCENT_H
#define GRADIENT_DESCENT_H

#include <vector>
#include <string>

struct GDInput{
	int degree;
	std::vector<double> coeffs;  
	double x0;
	double alpha;   
	double tol;
	long long maxIter;
};

struct GDResult
{
	double finalX;
	double finalFx;
    long long iterations;
	bool converged;
    double timeMs;
};

GDInput readInput(const std::string& filename);

double f(const std::vector<double>& coeffs, double x);       
double fprime(const std::vector<double>& coeffs, double x);  

GDResult runGD(const GDInput& in, int runs);

#endif