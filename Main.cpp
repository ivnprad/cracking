#include <span> 
#include <filesystem> 
#include <iostream> 
#include <array>
#include <cctype>

#include "LinkProblems.h"
#include "ArrayStrings.h"
#include "StackQueueProblems.h"

// Main function
#pragma warning(suppress: 26461) // The pointer argument 'argv' for function 'main' can be marked as a pointer to const (con.3).
#pragma warning(suppress: 26485) // Expression 'argv': No array to pointer decay (bounds.3).
int main(int argc, char* argv[])
{
	try
	{
		std::cout<< "hola"<<std::endl;

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

}
