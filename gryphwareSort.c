//made by gryphware
//cre: by gryphware

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define size_buffer 50

char buffer[size_buffer];

void sort(int *arr, int size){

  int left = 0;
  int right = size - 1;

  while(left <= right){

        int min = INT_MAX, max = INT_MIN;
        int index_min = -1, index_max = -1;

        for(size_t i = left; i <= right; i++){
            if(min > arr[i]){
                min = arr[i];
                index_min = i;
            }
            if(max < arr[i]){
                max = arr[i];
                index_max = i;
            }
        }
        arr[index_min] = arr[left];
        arr[left] = min;

        if(index_max == left){
            index_max = index_min;
        }

        arr[index_max] = arr[right];
        arr[right] = max;

        left++;
        right--;
    }
    for(size_t i = 0; i < size; i++){
        snprintf(buffer, sizeof(buffer), "%d", arr[i]);
        fprintf(stdout, "%s ", buffer);
    }
    printf("\n");
}

int main(){

    int size;

    if(scanf("%d", &size) != 1){
        perror("Size!\n");
        exit(1);
    }

    int *arr = (int*) malloc (size * sizeof(int));

    if(arr == NULL){
        perror("Arr!\n");
        exit(1);
    }

    for(size_t i = 0; i < size; i++){
        if(scanf("%d", &(arr[i])) != 1){
            perror("Something wrong!\n");
            exit(1);
        }
    }

    sort(arr, size);
    return 0;
}