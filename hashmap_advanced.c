#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 65 /*size of hashmap at begin = 65*/
#define LOAD_FACTOR 0.75 /*if load factor of old table greater than 75% = load a new hashmap*/

/*define node*/
typedef struct Node{
  char *key;
  int data;
  struct Node *next;
}Node;

/*linked list*/
typedef struct HashMap{
  Node** table;
  int capacity;
  int size;
}HashMap;

/*create hashmap based on the first hashmap*/
HashMap* create_hashMap(){
  HashMap* map = malloc(sizeof(HashMap));
  map->capacity = INITIAL_SIZE;
  map->size = 0;
  map->table = calloc(map->capacity, sizeof(Node*));
  printf("new!\n");
  return map;
}

/*create a new node when a new data accessed*/
Node* new_node(char *word, int data){
  Node* new = malloc(sizeof(Node));
  new->key = _strdup(word);
  new->data = data;
  new->next = NULL;
  return new;
}

/*djb2 hash function*/
unsigned int hash(char *word, int capacity){
  unsigned int index = 5381;
  int c;
  while((c = *word++)){
    index = ((index << 5) + index) + c;
  }
  return index % capacity;
}

int primes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593};
int next_size(int current){
  for(size_t i = 0; i < (sizeof(primes) / sizeof(primes[0])); i++){
    if(primes[i] > current){
      return primes[i];
    }
  }
  return primes[sizeof(primes) / sizeof(primes[0]) - 1] * 2 + 1;
}

void resize(HashMap *map){
  int old_capacity = map->capacity;
  Node** table = map->table;

  int new_capacity = next_size(map->capacity);
  map->capacity = new_capacity;
  map->table = calloc(new_capacity, sizeof(Node*));
  map->size = 0;

  for(size_t i = 0; i < old_capacity; i++){
    Node* curr = table[i];
    while(curr){
      Node* next = curr->next;
      unsigned long index = hash(curr->key, new_capacity);
      curr->next = map->table[index];
      map->table[index] = curr;
      curr = next;
      map->size++;
    }
  }
  free(table);
}

void insert_node(char* word, int data, HashMap *map){
  if((float)(map->size + 1) / (map->capacity) > LOAD_FACTOR){
    resize(map);
  }
  unsigned long index = hash(word, map->capacity);
  Node *curr = map->table[index];
  while(curr){
    if(strcmp(curr->key, word) == 0){
      curr->data = data;
      return;
    }
    curr = curr->next;
  }
  Node *new = new_node(word, data);
  new->next = map->table[index];
  map->table[index] = new;
  map->size++;
}

int *get_data(char *word, HashMap *map){
  unsigned long index = hash(word, map->capacity);
  Node *entry = map->table[index];
  while(entry){
    if(strcmp(entry->key, word) == 0){
      return &entry->data;
    }
    entry = entry->next;
  }
  return NULL;
}

void delete_node(char *word, HashMap *map){
  unsigned long index = hash(word, map->capacity);
  Node *curr = map->table[index];
  Node *prev = NULL;
  while(curr){
    if(strcmp(curr->key, word) == 0){
      if(prev){
	prev->next = curr->next;
      } else {
	map->table[index] = curr->next;
      }
      free(curr->key); free(curr); map->size--;
      return;
    }
    prev = curr;
    curr = curr->next;
  }
}

void free_HashMap(HashMap *map){
  for(size_t i = 0; i < map->capacity; i++){
    Node *curr = map->table[i];
    while(curr){
      Node *temp = curr;
      curr = curr->next;
      free(temp->key);
      free(temp);
    }
  }
  free(map->table);
  free(map);
}

int main(){

  HashMap *map = create_hashMap();

  for(size_t i = 0; i < 200; i++){
    char key[30];
    sprintf(key, "key %zu", i);
    insert_node(key, i * 5, map);
  }

  printf("%d\n", map->capacity);
  
  int *val = get_data("key 12", map);
  if(val){
    printf("found it!\n");
  } else {
    printf("not found\n");
  }

  delete_node("key 12", map);

  val = get_data("key 12", map);
  if(val){
    printf("found it!\n");
  } else {
    printf("not found\n");
  }                                    

  free_HashMap(map);
  
  return EXIT_SUCCESS;
}
