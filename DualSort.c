#include <stdio.h>
#include <limits.h>

void dualSort(int *arr, int size){
    int arrSorted[size];

    int right = size - 1, left = 0;

    while (left <= right){
        int min = INT_MAX, max = INT_MIN;
        int min_index = -1, max_index = -1;

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
    arrSorted[left++] = min;
    arrSorted[right--] = max;

    arr[min_index] = INT_MAX;
    arr[max_index] = INT_MAX;
    }
    for(size_t i = 0; i < size; i++){
        printf("%d ", arrSorted[i]);
    }
    printf("\n");
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
