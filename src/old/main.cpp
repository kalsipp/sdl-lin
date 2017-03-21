#include <iostream>
#include <stdio.h>

#include "mainclass.hpp"
int main( int argc, char* args[] )
{
	std::cout << "main started" << std::endl;
	Mainclass game;
	game.run();
	std::cout << "main ended" << std::endl;
	return 0;
}  