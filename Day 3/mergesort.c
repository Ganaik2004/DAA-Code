#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int l, int m, int r) {
    int a, b, c;
    int x = m - l + 1;
    int y = r - m;

    int* left = (int*) malloc(x * sizeof(int));
    int* right = (int*) malloc(y * sizeof(int));

    for(int i = 0; i < x; i++) {
        left[i] = arr[l + i];
    }

    for (int j = 0; j < y; j++) {
        right[j] = arr[m + 1 + j];
    }

    a = 0;
    b = 0;
    c = l;

    while(a < x && b < y) {
        if(left[a] <= right[b]) {
            arr[c] = left[a];
            a++;
        } else {
            arr[c] = right[b];
            b++;
        }
        c++;
    }

    while(a < x) {
        arr[c] = left[a];
        a++;
        c++;
    }

    while(b < y) {
        arr[c] = right[b];
        b++;
        c++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void read(char *file_name, int arr[], int *n) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }
    *n = 0;
    while (fscanf(file, "%d", &arr[(*n)++]) != EOF);
    (*n)--;
    fclose(file);
}

void write(char *file_name, int arr[], int n) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", file_name);
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

int main(int args, char *argv[]) {
    char *input_file = argv[1];
    char *output_file = argv[2];

    int arr[1000];
    int n;

    read(input_file, arr, &n);
    mergeSort(arr, 0, n - 1);
    write(output_file, arr, n);

    printf("done");
    return 0;
}