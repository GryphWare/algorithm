#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//ham loc input
void clear(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    puts("\nchuong trinh da dung tai day");
}

//ham kiem tra mang hop le
void checkArr(int *arr){
    if(!arr){
        perror("malloc ko thanh cong!");
        exit(EXIT_FAILURE);
    }
}

//ham tinh cac duong cheo
int multiDianogal(int **arr, int8_t row, int8_t index, int direction){
    int8_t product = 1;
    for(int8_t i = 0; i < row; i++){
        product *= arr[i][index];
        index += direction;
    }
        return product;
}

//ham dinh thuc
void determinant(int **arr, int row, int column){
    //tang so cot
    column += 2;
    
    //them hai cot sau
    for(int8_t i = 0; i < row; i++){
        arr[i] = (int*) realloc (arr[i], (column + 2) * sizeof(int));
        arr[i][column] = arr[i][0];
        arr[i][column + 1] = arr[i][1];
    }
    
    //in ra
    for(int8_t i = 0; i < row; i++){
        for(int8_t j = 0; j < column; j++){
            printf("%d ", arr[i][j]);
         }
        
        printf("\n");
    }

    //giai quyet tong duong cheo chinh
    int mainDianogal = 0;

    //tinh cac duong cheo ke chinh
    for(int8_t i = 0; i < 3; i++){
        mainDianogal += multiDianogal(arr, row, i, 1);
    }

    //tinh cac duong cheo phu
    int8_t subDianogal = 0;

    for(int8_t i = 0; i < 3; i++){
        subDianogal += multiDianogal(arr, row, row - 1 - i, -1);
    }

    //in ket qua ma tran
    printf("dinh thuc ma tran: %d\n", mainDianogal - subDianogal);
}

int main(){

    //dang ky ham thoat
    atexit(clear);

    //happy coding bro!

    //nhap so hang so cot
    int row, column;
    scanf("%d %d", &row, &column);

    //dinh thuc phai la ma tran vuong
    if(row != column || (row == 2 && column == 2) ){
        perror("Ko phai ma tran vuong va ko ho tro 2x2lol");
        exit(EXIT_FAILURE);
    }

    //tao mang theo hang
    int **arr = (int**) malloc (row * sizeof(int*));

    //kiem tra mang hop le?
    if(!arr){
        perror("mang ko malloc dc?");
        exit(EXIT_FAILURE);
    }

    for(int8_t i = 0; i < row; i++){
        //tao mang trong mang
        arr[i] = (int*) malloc (column * sizeof(int));
        checkArr(arr[i]); //kiem tra
        for(int8_t j = 0; j < column; j++){
            scanf("%d", &arr[i][j]); //input
        }
    }

    //tinh dinh thuc
    determinant(arr, row, column);

    //free
    for(int8_t i = 0; i < row; i++){
        free(arr[i]); //don mang trong
    }
    free(arr); //don mang ngoai
    
    return EXIT_SUCCESS;
}
