#include <stdio.h>
#include <conio.h>

#include "update.h"
#include "global.h"
#include "functions.h"

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
