#include <stdio.h>
#include <windows.h>
#include <unistd.h>
#include "functions.h"

void rotatingBar(int x, int y, int time){
	char chars[] = {'-', '\\', '|', '/'};
    unsigned int i;
	
	gotoxy(x-4, y+3);
	printf("LOADING");
    for (i = 0; i<time; i++) {
		gotoxy(x, y);
    	printf("%c", chars[i % sizeof(chars)]);
        fflush(stdout);
        usleep(200000);
        if(i%4==0){
	        gotoxy(x+4+i/2, y+3);
	        printf(".");
    	}
    }
    gotoxy(x, y);
    printf(" ");
    gotoxy(x-4, y+3);
    printf("                 ");
}

void gotoxy ( int x, int y ){
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

