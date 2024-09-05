#include <stdio.h>
#include <stdlib.h>


void merge(int arr[], int l, int m, int r, int descending) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

  
    int* L = (int*) malloc(n1 * sizeof(int));
    int* R = (int*) malloc(n2 * sizeof(int));

   
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

   
    i = 0;    
    j = 0;    
    k = l;   

    while (i < n1 && j < n2) {
        if (descending ? (L[i] >= R[j]) : (L[i] <= R[j])) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    
    free(L);
    free(R);
}


void mergeSort(int arr[], int l, int r, int descending) {
    if (l < r) {
        
        int m = l + (r - l) / 2;

       
        mergeSort(arr, l, m, descending);
        mergeSort(arr, m + 1, r, descending);

        merge(arr, l, m, r, descending);
    }
}

int main() {
    int arr[1000], n;
    int choice;
    int descending;

    while (1) {
      
        printf("\n===== MERGE SORT MENU =====\n");
        printf("1. Sort in Ascending Order\n");
        printf("2. Sort in Descending Order\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                descending = 0;
                break;
            case 2:
                descending = 1;
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
                continue;
        }

       
        printf("Enter the number of elements: ");
        scanf("%d", &n);

        
        if (n <= 0 || n > 1000) {
            printf("Invalid number of elements. Please enter a value between 1 and 1000.\n");
            continue;
        }

       
        printf("Enter the elements:\n");
        for (int i = 0; i < n; i++) {
            printf("Element %d: ", i + 1);
            scanf("%d", &arr[i]);
        }

        
        printf("\nBefore Sorting: ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        
        mergeSort(arr, 0, n - 1, descending);

        
        printf("After Sorting:  ");
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}
