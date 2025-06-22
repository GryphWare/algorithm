#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

void bubble_sort(int *arr){
  for(size_t i = 0; i < 5 - 1; i++){
    for(size_t j = 0; j < 5 - i - 1; j++){
      if(arr[j] > arr[j + 1]){
	swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}
int main(){

  int suffle_num[5] = {3, 2, 9, 6, 6};

  bubble_sort(suffle_num);

  for(size_t i = 0; i < 5; i++){
    printf("%d ", suffle_num[i]);
  }
  
  return EXIT_SUCCESS;
}
