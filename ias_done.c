#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define word_size 40
#define slot 1000

typedef struct memoryWord{
    uint64_t data : word_size;
}memoryWord; //dinh dang 40bit moi slot

memoryWord memory[slot]; //ias

uint32_t accumalator = 0; //thanh ghi can it

//ham load
void load_memory(int address, uint64_t value){
    if(address > slot && address < 0){
        perror("qua hoac het slot");
        exit(EXIT_FAILURE); //neu address la qua slot
    }
    memory[address].data = value & ((1ULL << word_size) - 1); //giu lai 40 bit and -1 de giu lai data
}

//ham doc theo address
uint64_t read_memory(int address){
    if(address < slot && address >= 0){
        return memory[address].data; //tra ve gia tri
    }
    return 0;
}

//ham giai ma va thuc thi
void exexute_instruction(uint64_t instruction){
    uint8_t opcode = (instruction >> 32) & 0xFF; //opcode la 8 bit tu 32-39
    uint16_t address = (instruction >> 20) & 0xFFF; //address la 12 bit tu (20-31)

    switch(opcode){
    case 0x01: //load
        accumalator = read_memory(address) & 0xFFFFF; //giu 20bit thap nhat
        printf("LOAD: Accumulator = 0x%X\n", accumalator);
        break;
    case 0x02://add
        accumalator = (accumalator + read_memory(address) & 0xFFFFF) & 0xFFFFF;
        printf("add: Accumulator = 0x%X\n", accumalator);
        break;
    case 0x03: //store
        load_memory(address, accumalator);
        printf("store: saved 0x%X to index %d\n ", accumalator, address);
        break;
    case 0xFF:
        printf("stop\n");
        exit(0);
    default:
        perror("address hoac het slot");
        exit(1);
    }
}
void simulate_program(){
    load_memory(0, ((0x01ULL << 32) | 10)); //load voi che do 10
    load_memory(1, ((0x02ULL << 32) | 11)); //add voi che do 11
    load_memory(2, ((0x03ULL << 32) | 12)); //store voi che do 12
    load_memory(3, (0xFFULL << 32)); //stop

    //use
    load_memory(10, 0x15);
    load_memory(12, 0x17);

    printf("start: \n");
    for(size_t i = 0; i < slot; i++){
        uint64_t instruction = read_memory(i);
        if(instruction == 0) break; //neu gap o trong

        exexute_instruction(instruction);
    }
}

int main(){

    simulate_program();
    
    exit(EXIT_SUCCESS);
}
