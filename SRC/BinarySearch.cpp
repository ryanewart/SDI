#include <string>

int binarySearch(std::string searchList[],std::string item) {
    int pos = -1;
    int count = 0;
    int low = 0;
    int mid;
    int high = searchList->size();
    std::string searched;
    while ((count<searchList->size()) && item != searched) {
        mid = (high+low) / 2;
        //std::cout<<mid<<std::endl;
        if (searchList[mid] < item) {
            low = mid;
        }
        else if (searchList[mid] > item) {
            high = mid;
        }
        else if (searchList[mid] == item) {
            pos = mid;
            break;
        }
        count++;
    }
    return pos;
}
