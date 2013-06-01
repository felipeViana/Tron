#include <string>
#include "global.h"

int n=4;
HANDLE hConsole;
int colors[8] = {972, 938, 921, 238, 12, 10, 9, 14};
std::string names[4] = {"RED", "GREEN", "BLUE", "YELLOW"};
int commands[29] = {'d', 'D', 'w', 'W', 'a', 'A', 's', 'S', 
				  'h', 'H', 't', 'T', 'f', 'F', 'g', 'G',
				  'l', 'L', 'i', 'I', 'j', 'J', 'k', 'K',
				  -32, 77, 72, 75, 80};
int direcoes[4] = {DIREITA, CIMA, ESQUERDA, BAIXO};
