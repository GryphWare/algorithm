#include <stdio.h>
#include <stdint.h> //use int8_t,...
#include <stdlib.h>
#include <stdbool.h>

#define max_n 100
//program exit message
void say_Goodbye(){
    printf("\nThis program end here");
}

void sieve(int n){
    bool marked[max_n + 1]; //because this arr have 0
    
    for(int8_t i = 0; i <= max_n; i++){
	marked[i] = true;
    }

    marked[0] = marked[1] = false; //0 & 1 not a prime

    //mark index(number) not a prime
    for(int8_t i = 2; i * i  <=  n; i++){
	if(marked[i]){
	    for(int8_t j = i * i; j <= n; j+=i){
		marked[j] = false;
	    }
	}
    }

    //print it out
    for(int8_t i = 2; i <= n; i++){
	if(marked[i]){
	    printf("%d ", i);
	}
    }
}

int main(){
    atexit(say_Goodbye);

    //code here and happy coding
    int n = 50;
    sieve(n);

    exit(EXIT_SUCCESS);
}
