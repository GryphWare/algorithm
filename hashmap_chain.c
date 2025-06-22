#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 20
#define BUFFER_SIZE 50

char buffer[BUFFER_SIZE]; //dung de in snprintf va fprintf

typedef struct Entry{
    int data;
    int data2;
    struct Entry *next;
}Entry; //tao node

typedef struct hashmap{
    Entry *table[TABLE_SIZE];
}hashmap; //dinh nghia hashmap

//ham lam sach hashmap
void initHashmap(hashmap *map){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        map->table[i] = NULL;//lam sach hashmap
    }
}

//ham lay index
unsigned int hash(int value){
    return value % TABLE_SIZE;
}
//chen
void insert(hashmap *map, int value, int value2){
    unsigned int index = hash(value);
    Entry *entry = map->table[index];

    while(entry){
        if(entry->data == value){
            entry->data2 = value2;
            return;
        }
        entry = entry->next;
    }
    Entry *new = (Entry*) malloc (sizeof(Entry));
    new->data = value;
    new->data2 = value2;
    new->next = map->table[index];
    map->table[index] = new;
}

//in theo bucket
void printBucket(hashmap *map){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        Entry *entry = map->table[i];
        snprintf(buffer, sizeof(buffer), "Bucket %zu: ", i);
        fprintf(stdout, "%s", buffer);
        while(entry){
            if(entry){
                snprintf(buffer, sizeof(buffer), "(%d, %d)-> ", entry->data, entry->data2);
                fprintf(stdout, "%s", buffer);
            }
            entry = entry->next;
        }
        snprintf(buffer, sizeof(buffer), "NULL");
        fprintf(stdout, "%s\n", buffer);
    }
}

int main(){

    //goi hashmap
    hashmap map;

    //lam sach hashmap
    initHashmap(&map);

    //chen
    insert(&map, 1, 2);
    insert(&map, 2, 3);
    insert(&map, 4, 10);

    //in theo bucket
    printBucket(&map);

    return 0;
}
