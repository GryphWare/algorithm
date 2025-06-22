#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define table_size 10
#define buffer_size 50

//CANH BAO
//chuong trinh nay co the dan den loi tagged pointer
//tagged pointer xay ra khi chay code nay o kien truc ARM
//ko anh huong den bo nho
//nhung khuyen khich chay code o kien truc x86/x64

char buffer[buffer_size]; //de in thay printf

typedef struct Node{
    char *key;
    int data;
    struct Node *next;
}Node; //dinh nghia node

typedef struct Bucket{
    Node *head;
    pthread_mutex_t lock;
}Bucket; //phan lon hon node chua cac phan tu

typedef struct concurrent_Hashmap{
    Bucket buckets[table_size];
}concurrent_Hashmap; //dinh nghia

//ham lam sach
void initHashmap(concurrent_Hashmap *map){
    for(size_t i = 0; i < table_size; i++){
        map->buckets[i].head = NULL;
        pthread_mutex_init(&map->buckets[i].lock, NULL);
    }
}
//ham lay index
unsigned int hash(char *key){
    unsigned int hash = 0;
    while(*key){
        hash = (hash << 8) + *key++;
    }
    return hash % table_size;
}
//ham them
void insert(concurrent_Hashmap *map, char *word, int value){
    unsigned int index = hash(word); //lay index tai vi tri
    Bucket *entry = &map->buckets[index];

    //tao luong hoat dong tai luong entry
    pthread_mutex_lock(&entry->lock);

    //dinh huong
    Node *node = entry->head;

    while(node){
        if(strcmp(node->key, word) == 0){
            node->data = value;
            pthread_mutex_unlock(&entry->lock); //thoat luong
            return;
        }
        node = node->next;
    }
    
    //neu ko co node
    Node *new = (Node*) malloc (sizeof(Node));
    new->key = strdup(word);
    new->data = value;
    new->next = entry->head;
    entry->head = new;

    pthread_mutex_unlock(&entry->lock);
}

//ham look up
void lookup(concurrent_Hashmap *map, char *word){
    unsigned int index = hash(word);//lay index
    Bucket *bucket = &map->buckets[index];

    pthread_mutex_lock(&bucket->lock); //dong khoa work inside

    //dinh huong
    Node *node = bucket->head;

    while(node){
        if(strcmp(node->key, word) == 0){
            snprintf(buffer, sizeof(buffer), "%d", node->data);
            pthread_mutex_unlock(&bucket->lock);
            fprintf(stdout, "%s\n", buffer);
            return;
        }
        node = node->next;
    }
    snprintf(buffer, sizeof(buffer), "-1");
    pthread_mutex_unlock(&bucket->lock);
    fprintf(stdout, "%s\n", buffer);
}

//ham delete
void delete(concurrent_Hashmap *map, char *word){
    unsigned int index = hash(word);
    Bucket *bucket = &map->buckets[index];

    pthread_mutex_lock(&bucket->lock); //khoa

    //ke tu day code hoat dong o luong nay
    
    Node *node = bucket->head; //dinh huong
    Node *prev = NULL; //bien de xoa

    while(node){
        if(strcmp(node->key, word) == 0){
            if(prev){
                prev->next = node->next; 
            } else {
                bucket->head = node->next;
            }
            free(node);
            pthread_mutex_unlock(&bucket->lock);//end luong
            return;
        }
        prev = node;
        node = node->next;
    }
    pthread_mutex_unlock(&bucket->lock);
    //end luong
}

//ham in hashmap
void printAll(concurrent_Hashmap *map){
    for(size_t i = 0; i < table_size; i++){
        Bucket *entry = &map->buckets[i];

        //lock in
        pthread_mutex_lock(&entry->lock);
        
        Node *node = entry->head;
        snprintf(buffer, sizeof(buffer), " bucket: %zu", i);
        fprintf(stdout, "%s\n", buffer);
        
        while(node){
            if(node){
                snprintf(buffer, sizeof(buffer), "key: %s, value: %d -> ", node->key, node->data);
                fprintf(stdout, "%s", buffer);
            }
            node = node->next;
        }
        snprintf(buffer, sizeof(buffer), "Node lol");
        fprintf(stdout, "%s\n", buffer);
        pthread_mutex_unlock(&entry->lock);
    }
}
//ham destroyWholeThing
void destroyWholeThing(concurrent_Hashmap *map){
    for(size_t i = 0; i < table_size; i++){
        Bucket *entry = &map->buckets[i];

        //khoa luong
        pthread_mutex_lock(&entry->lock);
        Node *node = entry->head;
        while(node){
            Node *temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
        pthread_mutex_unlock(&entry->lock); //end luong
        pthread_mutex_destroy(&entry->lock); //pha het luong de NULL
    }
    free(map);
}

int main(){

    //goi hash map
    concurrent_Hashmap hash_map;

    //lam sach map
    initHashmap(&hash_map);

    //them
    insert(&hash_map, "Chanh", 9);
    insert(&hash_map, "Vy", 18);

    //in ra
    printAll(&hash_map);

    //in so
    lookup(&hash_map, "Chanh");
    lookup(&hash_map, "Tram");

    //xoa node
    delete(&hash_map, "Chanh");

    //in sau khi xoa
    printAll(&hash_map);

    //xoa toan bo map
    destroyWholeThing(&hash_map);
    
    return 0;
}
