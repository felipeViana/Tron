#include <windows.h>

#include "initialize.h"
#include "functions.h"
#include "global.h"
#include "draw.h"

void initializeWorld(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);	
	
	drawTable();
	
	rotatingBar(WIDTH/2, HEIGHT/2, 0);
	
	gotoxy(0,0);
	SetConsoleTextAttribute(hConsole, colors[0]);
	printf("O");
	SetConsoleTextAttribute(hConsole, colors[1]);
	gotoxy(WIDTH,0);
	printf("O");
	SetConsoleTextAttribute(hConsole, colors[2]);
	gotoxy(WIDTH,HEIGHT);
	printf("O");
	SetConsoleTextAttribute(hConsole, colors[3]);
	gotoxy(0,HEIGHT);
	printf("O");
	
}

void initialize(tron *t){
	initializeWorld();
	for(int i=0; i<4; i++){
		t[i].size=1;
		t[i].alive=true;
		t[i].direcao = direcoes[(-i+4)%4];
		if(i<2){
			t[i].y[0] = SPACE;
		}
		else{
			t[i].y[0] = HEIGHT - SPACE;
		}
		if(i%3==0){
			t[i].x[0] = SPACE;
		}
		else{
			t[i].x[0] = WIDTH - SPACE;
		}
	}
}
