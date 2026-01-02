#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// binary search O(log n)

int binary_search(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

int main() {
    int arr[] = {2, 5, 8, 12, 15, 20, 25};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 15;

    int idx = binary_search(arr, n, target);
    if (idx != -1) {
        printf("Element %d found at index %d.\n", target, idx);
    }
    else {
        printf("Element %d not found.\n", target);
    }
    /*
    Out:
    Element 15 found at index 4.
    */
    return 0;
}