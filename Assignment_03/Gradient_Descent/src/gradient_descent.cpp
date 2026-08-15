#include "gradient_descent.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <chrono>

GDInput readInput(const std::string& filename){

	std::ifstream fin(filename);
	if(!fin.is_open()){
		throw std::runtime_error("could not open file: " + filename);
	}

	GDInput in;
	bool gotDegree=false, gotCoeffs=false, gotX0=false;
	bool gotAlpha=false, gotTol=false, gotMaxIter=false;

	std::string tag;
	while(fin >> tag)
	{
		if(tag=="DEGREE"){
			fin >> in.degree;
			gotDegree = true;
		}
		else if(tag == "COEFFICIENTS")
		{
			std::string rest;
			std::getline(fin, rest);
			std::istringstream ss(rest);
			double val;
			while(ss >> val){
				in.coeffs.push_back(val);
			}
			gotCoeffs=true;
		}
		else if(tag=="INITIAL_X"){
			fin>>in.x0;
			gotX0 = true;
		}
		else if(tag=="LEARNING_RATE")
		{
			fin >> in.alpha;
			gotAlpha=true;
		}
		else if (tag == "TOLERANCE") {
			fin >> in.tol;
			gotTol = true;
		}
		else if(tag=="MAX_ITERATIONS"){
			fin >> in.maxIter;
			gotMaxIter=true;
		}
	}
	if(!gotDegree || !gotCoeffs || !gotX0 || !gotAlpha || !gotTol || !gotMaxIter){
		throw std::runtime_error("input file is missing one of the required fields");
	}
	if(in.degree < 0){
		throw std::runtime_error("degree can't be negative");
	}
	if((int)in.coeffs.size() != in.degree+1)
	{
		throw std::runtime_error("expected " + std::to_string(in.degree+1) + " coefficients but got " + std::to_string(in.coeffs.size()));
	}
	if(in.alpha <= 0){
		throw std::runtime_error("learning rate must be positive");
	}
	if(in.tol<=0){
		throw std::runtime_error("tolerance must be positive");
	}
	if (in.maxIter <= 0) {
		throw std::runtime_error("max iterations must be positive");
	}

	return in;
}

double f(const std::vector<double>& coeffs, double x){
	double result = 0.0;
	for(int i=(int)coeffs.size()-1; i>=0; i--){
		result = result*x + coeffs[i];
	}
	return result;
}

double fprime(const std::vector<double>& coeffs, double x)
{
	int deg = (int)coeffs.size() - 1;
	double result=0.0;
	for(int i=deg;i>=1;i--)
	{
		result = result*x + i*coeffs[i];
	}
	return result;
}

GDResult runGD(const GDInput& in, int runs){

	if(runs<1) runs=1;  

	GDResult res;
	auto t1 = std::chrono::high_resolution_clock::now();

	for(int r=0;r<runs;r++){

		double x = in.x0;
		long long iter = 0;
		bool converged = false;

		while(iter < in.maxIter)
		{
			double grad = fprime(in.coeffs, x);

			if(std::fabs(grad) <= in.tol){
				converged=true;
				break;
			}

			x = x - in.alpha*grad;
			iter++;
		}
		res.finalX = x;
		res.finalFx = f(in.coeffs,x);
		res.iterations = iter;
		res.converged = converged;
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double,std::milli> diff = t2-t1;
	double totalTime = diff.count();

	res.timeMs = totalTime/runs;
	return res;
}