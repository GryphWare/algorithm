#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void dualSort(int *arr, int size){
    int *arrSorted = (int*) malloc (size * sizeof(int));

    //check mang ok?
    if(arrSorted == NULL){
        perror("Thieu bo nho\n");
        exit(1);
    }

    //tao vi tri
    int right = size - 1, left = 0;

    //stop cho den khi 2 diem cham nhau
    while (left <= right){
        int min = INT_MAX, max = INT_MIN;
        int min_index = -1, max_index = -1;

        //tim so lon nhat va nho nhat
        for(size_t i = 0; i < size; i++){
            if(arr[i] != INT_MAX && min > arr[i]){
                min = arr[i];
                min_index = i;
            }
            if(arr[i] != INT_MAX && max < arr[i]){
                max = arr[i];
                max_index = i;
            }
        }
    //chen so vao day
    arrSorted[left++] = min;
    arrSorted[right--] = max;

    //danh dau mang
    arr[min_index] = INT_MAX;
    arr[max_index] = INT_MAX;
    }

    //in
    for(size_t i = 0; i < size; i++){
        printf("%d ", arrSorted[i]);
    }

    printf("\n");
    free(arrSorted);//free bo nho
}


int main(){

    //tao mang so
    int arr[] = {1, 0, 7, 2, 4};

    //tinh size
    int size = sizeof(arr) / sizeof(arr[0]);

    //ham sap xep
    dualSort(arr, size);

    return 0;
}
