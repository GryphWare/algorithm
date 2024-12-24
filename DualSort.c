#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define spaceLimit (1024 * 1024 * 10) / sizeof(int)

//ham clear
void clear(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}
//ham sap xep
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

    //vung tao bien
    int sizeMain;
    char sizeChar[21]; //neu co long long int

    fgets(sizeChar, sizeof(sizeChar), stdin); //nhap
    sizeChar[strcspn(sizeChar, "\n")] = '\0'; //bo \n neu co
                                              //
    //bao loi empty
    if(sizeChar[0] == '\0'){
        perror("Size must'nt be empty\n");
        clear();
        exit(1);
    }

    //doi char sang int
    char *end;
    sizeMain = strtol(sizeChar, &end, 10);
    //bao loi
    if((*end != '\n' && *end != '\0') || sizeMain > spaceLimit){
        perror("Cant convert char to int!\n");
        clear();
        exit(1);
    }

    //tao mang
    int *arr = (int*) malloc (sizeMain * sizeof(int));
    if(arr == NULL){
        perror("loi cap phat bo nho\n");
        clear();
        exit(1);
    }

    //nhap so vao mang
    for(size_t i = 0; i < sizeMain; i++){
        if(scanf("%d", &(arr[i]))  > spaceLimit){
            perror("loi hoa qua bi nho!\n");
            clear();
            exit(1);
        }
    }

    //ham sap xep
    dualSort(arr, sizeMain);

    //free
    memset(arr, 0, sizeMain * sizeof(int));
    free(arr);
    arr = NULL;

    return 0;
}
