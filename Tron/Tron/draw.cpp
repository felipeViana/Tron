#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>

#include "functions.h"
#include "draw.h"
#include "global.h"

void drawTable(){
	int a=1,b=0;
	
	for(int i=0; i<WIDTH-1; i++){
		gotoxy(a,b);
		printf("%c", 205);
		gotoxy(a,b+HEIGHT);
		printf("%c", 205);
		a++;
	}
	
	a=0;
	b=1;
	
	for(int i=0; i<HEIGHT-1; i++){
		gotoxy(a,b);
		printf("%c", 186);
		gotoxy(a+WIDTH, b);
		printf("%c", 186);
		b++;
	}
	
}

void clear(tron *t){
	for(tron* i=t; i<t+4; i++){
		gotoxy(i->x[i->size], i->y[i->size]);
		printf(" ");
	}
	
}

void print(tron *t){
	int k=0;
	for(tron *i=t; i<t+4; i++, k++){
		if(!i->alive){
			continue;
		}
		gotoxy(i->x[0], i->y[0]);
		
		SetConsoleTextAttribute(hConsole, colors[k]);
		printf("O");
	}
	
}

void draw(tron *t){
	print(t);
	//clear(t);
}

void showWinner(tron *t){
	SetConsoleTextAttribute(hConsole, 7);
	gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2);
	
	int a=0;
	int b=0;
	if(n==0){
		printf("DRAW");
		gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+2);
		printf("Press ENTER to play again");
		gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+8);
		printf("Press ESC to exit");
		goto finish;
	}
	
	for(tron *j=t; j<t+4; j++, a++){
		if(j->alive){
			break;
		}
	}
	
	
	for(tron *j=t; j<t+4; j++, b++){
		if(b!=a && j->x[0]==(t+a)->x[0] && j->y[0]==(t+a)->y[0]){
			printf("DRAW");
			goto finish;
		}
	}
	
	SetConsoleTextAttribute(hConsole, colors[a+4]);
	std::cout << names[a] << " is the Winner";
	
	gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+2);
	printf("Press ENTER to play again");
	gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+8);
	printf("Press ESC to exit");
	
	
	finish:
	fflush(stdin);
	char c=0;
	while(c!=13){
		c=getch();
		if(c==27){
			exit(1);
		}
	}
	system("cls");
	n=4;
}
