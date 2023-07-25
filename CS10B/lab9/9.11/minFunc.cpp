#include "minFunc.h"
const int * min(const int arr[], int arrSize) {

    if(arrSize == 0){
        return nullptr;
    }
    else{
        if(arrSize == 1){
            return arr;
        }
        else{
            const int *least = min(arr, arrSize-1);
            if(*least < arr[arrSize-1]){
                return least;
            }
            else{
                return arr + arrSize - 1;
            }
        }
    }
    
}