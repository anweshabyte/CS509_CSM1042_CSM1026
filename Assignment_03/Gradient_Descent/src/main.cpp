#include <iostream>
#include <iomanip>
#include "gradient_descent.h"

int main(int argc, char* argv[]){

	if(argc<2){
		std::cout << "usage: " << argv[0] << " <input file> [runs]\n";
		return 1;
	}
	std::string filename = argv[1];
	int runs = 1;
	if(argc>=3){
		runs = std::stoi(argv[2]);
	}

	GDInput input;
	try
	{
		input = readInput(filename);  
	}
	catch(std::exception& e){
		std::cout << "Error: " << e.what() << "\n";
		return 1;
	}

	GDResult result = runGD(input, runs);   
	std::cout << std::fixed << std::setprecision(6);
	std::cout << "Algorithm: Gradient Descent\n";
	std::cout << "Degree: " << input.degree << "\n";
	std::cout<<"Final x: "<<result.finalX<<"\n";
	std::cout << "Final f(x): " << result.finalFx << "\n";
	std::cout << "Iterations: " << result.iterations << "\n";
	std::cout << "Converged: " << (result.converged ? "true":"false") << "\n";
	std::cout << std::setprecision(6);
	std::cout << "Execution time: " << result.timeMs << " ms";
	if(runs>1){
		std::cout << " (avg of " << runs << " runs)";
	}
	std::cout << "\n";

	return 0;
}