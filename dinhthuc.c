#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//tot nhat nen sai int8_t, int16_t....

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

//ham tinh dinh thuc

 /* 1 4 7 1 4
    2 5 8 2 5
    3 6 9 3 6
 */

void determinant(int **arr, int row, int column){

    //them hai cot sau
    for(int8_t i = 0; i < row; i++){
        arr[i] = (int*) realloc (arr[i], (column + 2) * sizeof(int));
        arr[i][column] = arr[i][0];
        arr[i][column + 1] = arr[i][1];
    }

    //tang so cot
    column += 2;
    
    //in ra
    for(int8_t i = 0; i < row; i++){
        for(int8_t j = 0; j < column; j++){
            printf("%d ", arr[i][j]);
         }
        printf("\n");
    }

    //giai quyet tong duong cheo chinh
    int mainDianogal = 1;

    //cong theo duong cheo chinh
    for(int8_t i = 0; i < row; i++){
        mainDianogal *= arr[i][i];  
    }
    
    printf("hien tai co duong chinh la: %d \n", mainDianogal); //in ra lan 1

    int8_t increase_index = 1; //day ra index 1
    int8_t secondDianogal = 1; //duong cheo 2

    //nhu duong cheo chinh
    for(int8_t i = 0; i < row; i++){
        secondDianogal *= arr[i][increase_index++];
    }

    printf("duong cheo 2: %d \n", secondDianogal);

    increase_index = 2;
    int8_t third_dianogal = 1; //tinh duong cheo 3

    for(int8_t i = 0; i < row; i++){
        third_dianogal *= arr[i][increase_index++];
    }

    printf("duong cheo 3: %d \n", third_dianogal);

    //tinh cac duong cheo phu
    increase_index = 0;
    int mainDownToUp = 1;

    //tinh duong phu chinh
    for(int8_t i = row - 1; i >= 0; i--){
        mainDownToUp *= arr[i][increase_index++];
    }

    printf("tich duong cheo phu 1: %d\n", mainDownToUp);
    
    //tinh duong cheo phu 2
    int8_t DownToUp_2 = 1;
    increase_index = 1;
    
    for(int8_t i = row - 1; i >= 0; i--){
        DownToUp_2 *= arr[i][increase_index++];
    }

    printf("tich duong cheo phu 2: %d\n", DownToUp_2);
    
    //tinh duong cheo phu 3
    int8_t DownToUp_3 = 1;
    increase_index = 2;

    for(int8_t i = row - 1; i >= 0; i--){
        DownToUp_3 *= arr[i][increase_index++];
    }

    printf("tich duong cheo phu 3: %d\n", DownToUp_3);

    printf("dinh thuc ma tran: %d\n", (mainDianogal + secondDianogal + third_dianogal) - (mainDownToUp + DownToUp_2 + DownToUp_3)); 

    
}

int main(){

    //dang ky ham thoat
    atexit(clear);

    //happy coding bro!

    //nhap so hang so cot
    int row, column;
    scanf("%d %d", &row, &column);

    //dinh thuc phai la ma tran vuong
    if(row != column || (row == 2 && column) ){
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

    return EXIT_SUCCESS;
}
