#include <string>

bool sorted(std::string array[],int high) {
    for (int i = 0; i< high; i++) {
        if (array[i] > array[i+1]) {
            return false;
        }
    }
    return true;
}


std::string* quickSort(std::string array[],int pivot, int low){
        std::string temp;
        int l = low;
        int r = pivot -1;
        while (r > l) {
            if ((array[r] < array[pivot]) and (array[l] > array[pivot])) {
                temp = array[r];
                array[r] = array[l];
                array[l] = temp;
            }
            else if (array[l] < array[pivot]) {
                l = l + 1;
                if (array[r] > array[pivot]) {
                    r = r - 1;
                }
            }
            else if (array[r] > array[pivot]) {
                r = r - 1;
                if (array[l] < array[pivot]) {
                    l = l + 1;
                }
            }
        }
        if (array[pivot] < array[l]) {
            temp = array[pivot];
            array[pivot] = array[l];
            array[l] = temp;
        }
        if (sorted(array,pivot) != true) {
            quickSort(array, l-1, 0);
            quickSort(array, pivot, l+1);
        }
    return array;
}


