//TRON	29/05/2013
//compiled with Dev C++ 5.4.1
#include <windows.h>
#include <conio.h>
#include <unistd.h>
#include <dos.h>
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//defines
#define DIREITA 0 
#define CIMA 1
#define ESQUERDA 2
#define BAIXO 3

int n=4;
HANDLE hConsole;
int colors[8] = {972, 938, 921, 238, 12, 10, 9, 14};
std::string names[4] = {"RED", "GREEN", "BLUE", "YELLOW"};
int commands[29] = {'d', 'D', 'w', 'W', 'a', 'A', 's', 'S', 
				  'h', 'H', 't', 'T', 'f', 'F', 'g', 'G',
				  'l', 'L', 'i', 'I', 'j', 'J', 'k', 'K',
				  -32, 77, 72, 75, 80};
int direcoes[4] = {DIREITA, CIMA, ESQUERDA, BAIXO};

const int DELAY = 30000;
const int WIDTH = 101;
const int HEIGHT = 81;
const int MAX = 8000;
const int SPACE = 4;

struct tron{
	int x[8000];
	int y[8000];
	int size;
	bool alive;
	int direcao;
};


void drawTable();


void gotoxy ( int x, int y ){
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

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



void initializeWorld(){
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	FlushConsoleInputBuffer(hConsole);	
	
	drawTable();
	
	rotatingBar(WIDTH/2, HEIGHT/2, 10);
	
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

void updateInput(tron *t){
	while(kbhit()){
		char c = getch();	
		
		if(c=='p' || c=='P'){
			c=0;
			
			SetConsoleTextAttribute(hConsole, 7);
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2);
			printf(" ____   __   _  _  ____  ____  ____");
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+1);
			printf("(  _ \\ / _\\ / )( \\/ ___)(  __)(    \\");
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+2);
			printf(" ) __//    \\) \\/ (\\___ \\ ) _)  ) D (");
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+3);
			printf("(__)  \\_/\\_/\\____/(____/(____)(____/");
			
			
			while(c!='p' && c!='P'){
				if(kbhit()){
					c = getch();
				}
			}
			
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2);
			printf("                                     ");
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+1);
			printf("                                     ");
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+2);
			printf("                                     ");
			gotoxy(SPACE+WIDTH+3, SPACE+HEIGHT/2+3);
			printf("                                     ");
			
			
			c=0;
			goto finish;
		}
		
		
		for(int i=0; i<8; i+=2){
			for(int j=0; j<3; j++){
				if((c == commands[i+j*8] || c == commands[i+1+j*8]) && t[j].direcao != direcoes[(i/2+2)%4]){
					t[j].direcao = direcoes[i/2];
					goto finish;
					
				}
			}
		}
		
		
		if(c==commands[24]){
			c = getch();
			if( (c == commands[25]) && t[3].direcao != ESQUERDA){
				t[3].direcao = DIREITA;
			}
			else if( (c == commands[26]) && t[3].direcao != BAIXO){
				t[3].direcao = CIMA;
			}
			else if( (c == commands[27]) && t[3].direcao != DIREITA){
				t[3].direcao = ESQUERDA;
			}
			else if( (c == commands[28]) && t[3].direcao != CIMA){
				t[3].direcao = BAIXO;
			}
		}
		
		finish:;
	}
}

void update(tron *j){
	updateInput(j);
	
	for(tron *t = j; t<j+4; t++){
		if(!t->alive){
			continue;	
		}
		
		t->size++;
		for(int i=t->size; i>0; i--){
			t->x[i] = t->x[i-1];
			t->y[i] = t->y[i-1];
			
		}
		
		if(t->direcao==DIREITA){
			t->x[0]++;
		}
		else if(t->direcao==CIMA){
			t->y[0]--;
		}
		else if(t->direcao==ESQUERDA){
			t->x[0]--;
		}
		else if(t->direcao==BAIXO){
			t->y[0]++;
		}
		
		bool collided = false;
		
		for(tron *p = j; p<j+4; p++){
			for(int i=0; i<p->size; i++){
				if(p==t && i==0){
					continue;
				}
				if( t->x[0] == p->x[i] && t->y[0] == p->y[i]){
					collided = true;
					goto finished;
				}
			}	
		}
		
		
		if(t->x[0]<1 || t->x[0]>=WIDTH || t->y[0]<1 || t->y[0]>=HEIGHT){
			collided = true;
		}
		
		finished:
		
		if(collided){
			t->alive = false;
			n--;
			//Beep(2050, 100);
		}
	}
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



int main(){
	tron *t = (tron*)malloc(4*sizeof(tron));
	time_t start,end;
	
	while(1){
		initialize(t);
		
		while(n>=2){
			start = time(0);
		
			update(t);
			draw(t);
			
			end = time(0);
			usleep(DELAY - difftime(start,end));
			
		}
		
		showWinner(t);
	}
	
	
	return 0;
}
