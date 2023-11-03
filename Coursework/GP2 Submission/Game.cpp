#include <iostream>
#include "MainGame.h"
bool debuggingEnabled = true;

int main(int argc, char** argv) //argument used to call SDL main
{
	MainGame mainGame;
	mainGame.run();

	return 0;
}