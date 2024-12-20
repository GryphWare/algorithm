#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 50
#define TABLE_SIZE 100

char buffer[BUFFER_SIZE];

typedef struct Entry{
    char *key;
    int data;
    struct Entry *next;
}Entry; //tao node

typedef struct hashmap{
    Entry *table[TABLE_SIZE]; //tao mang index voi size table
}hashmap;

//ham lam sach index hash
void initHashmap(hashmap *map){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        map->table[i] = NULL;
    }
}

//bam ra index
unsigned int hash(char *word){
    unsigned int hash = 0;
    while(*word){
        hash = (hash << 5) + *(word++);
    }
    return hash % TABLE_SIZE;
}

//ham chen 
void insert(hashmap *map, char *word, int value){
    unsigned int index = hash(word); //lay index hash key
    Entry *entry = map->table[index];

    while(entry){
        if(strcmp(entry->key, word) == 0){
            entry->data = value; //neu co node san
            return;
        }
        entry = entry->next; //next pls
    }
    //tao node neu index hash cho do ko co
    Entry *new = (Entry*) malloc (sizeof(Entry));
    new->key = strdup(word);
    new->data = value;
    new->next = map->table[index];
    map->table[index] = new;
}

//kiem gia tri theo data RETURN key
char *lookupByData(hashmap *map, int value){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        Entry *entry = map->table[i];
        while(entry){
            if(entry->data == value){
                return entry->key;
            }
            entry = entry->next;
        }
    }
    return "NONE"; //kiem ko co
}

//kiem gia tri theo key RETURN data
int lookupByKey(hashmap *map, char *word){
    unsigned int index = hash(word);
    Entry *entry = map->table[index];

    while(entry){
        if(strcmp(entry->key, word) == 0){
            return entry->data;
        }
        entry = entry->next;
    }
    return -1;
}

//ham xoa phan tu theo Data
void deleteByData(hashmap *map, int value){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        Entry *entry = map->table[i];
        Entry *prev = NULL;
        while(entry){
            if(entry->data == value){
                if(prev){
                    prev->next = entry->next;
                } else {
                    map->table[i] = entry->next;
                }
                Entry *temp = entry;
                entry = entry->next;
                free(temp);
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}

//xoa phan tu theo key
void deleteByKey(hashmap *map, char *word){
    unsigned int index = hash(word);
    Entry *entry = map->table[index];
    Entry *prev = NULL;

    while(entry){
        if(strcmp(entry->key, word) == 0){
            if(prev){
                prev->next = entry->next;
            } else {
                map->table[index] = entry->next;
            }
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

//reset all hash node
void freeAll(hashmap *map){
    for(size_t i = 0; i < TABLE_SIZE; i++){
        Entry *entry = map->table[i];
        while(entry){
            Entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
}

int main(){

    hashmap map; //goi hashmap

    initHashmap(&map); //lam sach hashmap
    
    //chen vao hashmap
    insert(&map, "Chanh", 18);
    insert(&map, "Vy", 19);
    insert(&map, "Tram", 19);
    
    //in gia tri
    snprintf(buffer, sizeof(buffer), "%s", lookupByData(&map, 18));
    fprintf(stdout, "%s\n", buffer);

    snprintf(buffer, sizeof(buffer), "%d", lookupByKey(&map, "Vy"));
    fprintf(stdout, "%s\n", buffer);
    
    //xoa phan tu
    deleteByData(&map, 18);
    deleteByKey(&map, "Vy");

    //xoa hashmap lun
    freeAll(&map);

    return 0;
}
