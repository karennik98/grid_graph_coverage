#include <iostream>

#include "SquareGridGraph.h"

int main()
{
	size_t horizontalSize, verticalSize;
	std::cout << "Put horizontal size: "; std::cin >> horizontalSize;
	std::cout << "Put vertical size: "; std::cin >> verticalSize;
	std::cout << std::endl;
	try
	{
		SquareGridGraph grid(horizontalSize, verticalSize);
		grid.twoThreeLenghtSimpleChainCoverage();
		grid.printCoverage();
	}
	catch (std::exception& ex)
	{
		std::cout<<ex.what()<<std::endl;
	}
	system("pause");
	return 0;
}