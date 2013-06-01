//TRON	29/05/2013
//compiled with Dev C++ 5.4.1

#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "global.h"
#include "functions.h"
#include "initialize.h"
#include "update.h"
#include "draw.h"


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
