#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define limit (1024 * 1024 * 5) / sizeof(int)
#define size_buffer 10

char buffer[size_buffer]; //thay the printf vi ly do bao mat

void clear(){
    int c;
    while((c = getchar() != '\n' && c != EOF));
}
void gryphwareSort(int *arr, int size){

    //tao ben trai, ben phai
    int left = 0, right = size - 1;

    while(left <= right){
        
        int min_index = -1, max_index = -1; //lay index luu tru so
        int min = INT_MAX, max = INT_MIN; //lay min, max
        
        for(int i = left; i <= right; i++){
            
            if(min > arr[i]){
                min = arr[i]; //tim so thap nhat
                min_index = i; //luu index
            }
            
            if(max < arr[i]){
                max = arr[i]; //tim so lon
                max_index = i; //luu index
            }

        }
        
        arr[min_index] = arr[left]; //hoan doi index
        arr[left] = min; //so thap -> ben trai

        if(max_index == left){
            max_index = min_index; //neu case la so lon nhat o ben phai
        }

        arr[max_index] = arr[right]; // nhu tren
        arr[right] = max;

        left++; //day sang phai
        right--; //lui
    }

    //in
    for(size_t i = 0; i < size; i++){
        snprintf(buffer, sizeof(buffer), "%d", arr[i]);
        fprintf(stdout, "%s ", buffer);
    }
    
    printf("\n");
    
}

int main(){

    //bao mat
    char input_Size[21];
    int size;

    fgets(input_Size, sizeof(input_Size), stdin); //nhap

    input_Size[strcspn(input_Size, "\n")] = '\0'; //chuyen sang \n sang \0 neu user ko nhap

    if(input_Size[0] == '\0'){
        perror("Size ko dc de trong\n");
        clear();
        exit(1);
    }

    //chuyen char sang int
    char *end;
    size = strtol(input_Size, &end, 10);

    //ko chuyen dc
    if(*end != '\0' || size > limit){
        perror("Ko chuyen dc hoac qua 5mb\n");
        clear();
        exit(1);
    }

    int *arr = (int*) malloc (size * sizeof(int)); //tao mang

    if(arr == NULL){
        perror("ko the tao size\n");
        clear();
        exit(1);
    }

    //nhap so vao mang
    for(size_t i = 0; i < size; i++){
        if(scanf("%d", &(arr[i])) != 1 || arr[i] > limit){
            perror("Loi bi qua phan tu\n");
            free(arr);
            clear();
            exit(1);
        }
    }

    gryphwareSort(arr, size);

    //free all arr
    memset(arr, 0, size * sizeof(int));
    free(arr);
    arr = NULL;
    
    return 0;
}
