#include <windows.h>
#include <string>

#ifndef GLOBAL_H
#define GLOBAL_H

#define DIREITA 0 
#define CIMA 1
#define ESQUERDA 2
#define BAIXO 3

const int DELAY = 30000;
const int WIDTH = 101;
const int HEIGHT = 81;
const int MAX = WIDTH*HEIGHT;
const int SPACE = 4;

struct tron{
	int x[MAX];
	int y[MAX];
	int size;
	bool alive;
	int direcao;
};

extern int n;
extern HANDLE hConsole;
extern int colors[8];
extern std::string names[4];
extern int commands[29];
extern int direcoes[4];

#endif
