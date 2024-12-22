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
            snprintf(buffer, sizeof(buffer), "Maxed out of size!");
            fprintf(stderr, "%s\n", buffer);
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

//ham sreach
void sreach(hashmap *map, int key_data){
    unsigned int index = hash(key_data);
    int origin = index;
    while(map->table[index].key != HASH_KEY){
        if(map->table[index].key == key_data){
            snprintf(buffer, sizeof(buffer), "key = %d, value = %d", map->table[index].key, map->table[index].value);
            fprintf(stdout, "%s\n", buffer);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
        if(origin == index){
            break;
        }
    }
    snprintf(buffer, sizeof(buffer), "Dont have key %d", key_data);
    fprintf(stderr, "%s\n", buffer);
}

//ham xoa
void delete(hashmap *map, int key_value){
    unsigned int index = hash(key_value);
    int origin = index;
    while(map->table[index].key != HASH_KEY){
        if(map->table[index].key == key_value){
            map->table[index].key = HASH_KEY;
            map->table[index].value = HASH_VALUE;
        }
        index = (index + 1) % TABLE_SIZE;
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

    //in node chi dinh
    sreach(&map, 1); //ton tai
    sreach(&map, 9); //ko ton tai

    //xoa node chi dinh
    delete(&map, 1);
    delete(&map, 3);

    //in sau khi xoa node
    printOpenAddressing(&map);

    return 0;
}
