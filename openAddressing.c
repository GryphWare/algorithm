#include <stdio.h>

#define HASH_KEY -1
#define HASH_VALUE 0

#define TABLE_SIZE 10
#define BUFFER_SIZE 50

char buffer[BUFFER_SIZE]; //de in thay printf

typedef struct Node{
    int key;
    int value;
}Node; //dinh nghia Node

typedef struct hashmap{
    Node table[TABLE_SIZE];
}hashmap; //dinh nghia hashmap

void initHashmap(hashmap *map){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        map->table[i].key = HASH_KEY;
        map->table[i].value = HASH_VALUE;
    }
}

//hash
unsigned int hash(int value){
    return value % TABLE_SIZE;
}

//ham chen
void insert(hashmap *map, int key_data, int value_data){
    unsigned int index = hash(key_data);
    int originIndex = index;

    while(map->table[index].key != HASH_KEY && map->table[index].key != key_data){
        index = (index + 1) % TABLE_SIZE;
        if(index == originIndex){
            printf("Maxed out!\n");
            return;
        }
    }
    map->table[index].key = key_data;
    map->table[index].value = value_data;
}

//ham in
void printOpenAddressing(hashmap *map){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        snprintf(buffer, sizeof(buffer), "Bucket %zu: ", i);
        fprintf(stdout, "%s", buffer);
        if(map->table[i].key != HASH_KEY){
            snprintf(buffer, sizeof(buffer), "key = %d, value = %d", map->table[i].key, map->table[i].value);
            fprintf(stdout, "%s\n", buffer);
        } else {
            snprintf(buffer, sizeof(buffer), "GONE");
            fprintf(stdout, "%s\n", buffer);
        }
    }
}

int main(){
    hashmap map;

    initHashmap(&map);

    insert(&map, 1, 2);
    insert(&map, 2, 2);
    insert(&map, 3, 4);

    //in
    printOpenAddressing(&map);

    return 0;
}
