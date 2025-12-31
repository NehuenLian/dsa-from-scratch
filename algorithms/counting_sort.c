#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// counting sort O(n + k)

void counting_sort(int arr[], int n) {

    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    int *count = calloc(max + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    int *output = malloc(sizeof(int) * n);

    for (int i = n - 1; i >= 0; i--) {
        int num = arr[i];
        output[count[num] - 1] = num;
        count[num]--;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    free(count);
    free(output);
}

int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    counting_sort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    /*
    Out:
    Sorted array: 1 2 2 3 3 4 8 
    */
    return 0;
}
