#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int quicksort(int arr[], int low, int high, int *comparisons, int random_pivot, int descending);
int partition(int arr[], int low, int high, int *comparisons, int random_pivot, int descending);
int is_best_case(int arr[], int size);
int is_worst_case(int arr[], int size);

void display_menu();
void handle_sorting(int data[], int size, int random_pivot, int descending);

int main() {
    int choice;
    int size, data[1000];

    srand(time(0));

    printf("Enter the number of elements: ");
    scanf("%d", &size);

    printf("Enter the elements: \n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &data[i]);
    }

    while (1) {
        display_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                handle_sorting(data, size, 0, 0);
                break;
            case 2:
                handle_sorting(data, size, 0, 1);
                break;
            case 3:
                handle_sorting(data, size, 1, 0);
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

void display_menu() {
    printf("\nMAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Pivot Sorting\n");
    printf("4. Exit\n");
}

void handle_sorting(int data[], int size, int random_pivot, int descending) {
    int comparisons = 0;

    printf("Before Sorting: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    comparisons = quicksort(data, 0, size - 1, &comparisons, random_pivot, descending);

    printf("After Sorting: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");

    printf("Number of Comparisons: %d\n", comparisons);

    if (is_best_case(data, size)) {
        printf("Best case\n");
    } else if (is_worst_case(data, size)) {
        printf("Worst case\n");
    } else {
        printf("Average case\n");
    }
}

int quicksort(int arr[], int low, int high, int *comparisons, int random_pivot, int descending) {
    if (low < high) {
        int pi = partition(arr, low, high, comparisons, random_pivot, descending);
        quicksort(arr, low, pi - 1, comparisons, random_pivot, descending);
        quicksort(arr, pi + 1, high, comparisons, random_pivot, descending);
    }
    return *comparisons;
}

int partition(int arr[], int low, int high, int *comparisons, int random_pivot, int descending) {
    int pivot_index = high;
    if (random_pivot) {
        pivot_index = low + rand() % (high - low + 1);
        printf("Random pivot chosen: %d\n", arr[pivot_index]);
        int temp = arr[pivot_index];
        arr[pivot_index] = arr[high];
        arr[high] = temp;
    }
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        (*comparisons)++;
        if (descending ? arr[j] > pivot : arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

int is_best_case(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int is_worst_case(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}
