#include <iostream>
#include <stdio.h>
#include "editor.hpp"
#include "mainclass.hpp"
int main( int argc, char* args[] )
{
	std::cout << "\nmain started" << std::endl;
	Editor edit;
	edit.editor_run();
	//Mainclass game;
	//game.run();
	std::cout << "main ended" << std::endl;
	return 0;
}  