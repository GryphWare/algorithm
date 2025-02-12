#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WORD_LIMIT 40
#define MEMORY_SLOT 1000

typedef struct {
    uint64_t value : WORD_LIMIT;
}word;

word memory[MEMORY_SLOT];

void load(int num, uint64_t data){
    if(num >= 0 && num < MEMORY_SLOT){
        memory[num].value = data & ((1ULL << WORD_LIMIT) - 1);
    } else {
        printf("hell nah");
    }
}

uint64_t read(int num){
    if(num >= 0 && num < MEMORY_SLOT){
        return memory[num].value;
    }
    return 0;
}

void simulate_program(){
    load(0, 0x1234);
    load(1, 0xabcd);

    printf("num 0 at 0x%lX\n", read(0));
    printf("num 1 at 0x%lX\n", read(1));
}

int main(){

    simulate_program();
    
    exit(EXIT_FAILURE);
}
