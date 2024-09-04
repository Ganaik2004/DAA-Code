#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 100

struct person {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    int height;
    int weight;
};

void readData(struct person **array, int *n, const char *filename);
void createMinHeap(struct person *array, int n);
void createMaxHeap(struct person *array, int n);
void displayYoungestWeight(struct person *array, int n);
void insertMinHeap(struct person **array, int *n, struct person newPerson);
void deleteOldest(struct person *array, int *n);
void displayWeightByName(struct person *array, int n, const char *name);
void heapifyMin(struct person *array, int n, int i);
void heapifyMax(struct person *array, int n, int i);
void swap(struct person *a, struct person *b);
void printMenu();

int main() {
    struct person *heapArray = NULL;
    int n = 0;
    int choice;
    char filename[100];
    struct person newPerson;
    char name[MAX_NAME_LENGTH];

    while (1) {
        printMenu();
        scanf("%d", &choice);
        getchar(); // To consume the newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter filename to read data from: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                readData(&heapArray, &n, filename);
                break;

            case 2:
                createMinHeap(heapArray, n);
                break;

            case 3:
                createMaxHeap(heapArray, n);
                break;

            case 4:
                displayYoungestWeight(heapArray, n);
                break;

            case 5:
                printf("Enter ID: ");
                scanf("%d", &newPerson.id);
                getchar();
                printf("Enter Name: ");
                fgets(newPerson.name, sizeof(newPerson.name), stdin);
                newPerson.name[strcspn(newPerson.name, "\n")] = '\0';
                printf("Enter Age: ");
                scanf("%d", &newPerson.age);
                printf("Enter Height: ");
                scanf("%d", &newPerson.height);
                printf("Enter Weight (pounds): ");
                scanf("%d", &newPerson.weight);
                insertMinHeap(&heapArray, &n, newPerson);
                break;

            case 6:
                deleteOldest(heapArray, &n);
                break;

            case 7:
                printf("Enter the name of the person: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                displayWeightByName(heapArray, n, name);
                break;

            case 8:
                free(heapArray);
                return 0;

            default:
                printf("Invalid option. Try again.\n");
                break;
        }
    }

    return 0;
}

void readData(struct person **array, int *n, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    *n = 0;
    struct person temp;
    while (fscanf(file, "%d %s %d %d %d",
                  &temp.id,
                  temp.name,
                  &temp.age,
                  &temp.height,
                  &temp.weight) == 5) {
        *array = (struct person *)realloc(*array, (*n + 1) * sizeof(struct person));
        if (!*array) {
            perror("Error reallocating memory");
            fclose(file);
            return;
        }
        (*array)[*n] = temp;
        (*n)++;
    }

    fclose(file);
}

void createMinHeap(struct person *array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMin(array, n, i);
    }
}

void heapifyMin(struct person *array, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left].age < array[smallest].age) {
        smallest = left;
    }

    if (right < n && array[right].age < array[smallest].age) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&array[i], &array[smallest]);
        heapifyMin(array, n, smallest);
    }
}

void createMaxHeap(struct person *array, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapifyMax(array, n, i);
    }
}

void heapifyMax(struct person *array, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && array[left].weight > array[largest].weight) {
        largest = left;
    }

    if (right < n && array[right].weight > array[largest].weight) {
        largest = right;
    }

    if (largest != i) {
        swap(&array[i], &array[largest]);
        heapifyMax(array, n, largest);
    }
}

void displayYoungestWeight(struct person *array, int n) {
    if (n == 0) {
        printf("No data available.\n");
        return;
    }

    int youngestIndex = 0;
    for (int i = 1; i < n; i++) {
        if (array[i].age < array[youngestIndex].age) {
            youngestIndex = i;
        }
    }

    // Convert weight from pounds to kg (1 pound = 0.453592 kg)
    double weightInKg = array[youngestIndex].weight * 0.453592;
    printf("Weight of youngest student: %.2f kg\n", weightInKg);
}

void insertMinHeap(struct person **array, int *n, struct person newPerson) {
    *array = (struct person *)realloc(*array, (*n + 1) * sizeof(struct person));
    if (!*array) {
        perror("Error reallocating memory");
        return;
    }

    (*array)[*n] = newPerson;
    (*n)++;

    int i = *n - 1;
    while (i > 0 && (*array)[i].age < (*array)[(i - 1) / 2].age) {
        swap(&(*array)[i], &(*array)[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void deleteOldest(struct person *array, int *n) {
    if (*n == 0) {
        printf("Heap is empty.\n");
        return;
    }

    swap(&array[0], &array[*n - 1]);
    (*n)--;

    heapifyMax(array, *n, 0);
}

void displayWeightByName(struct person *array, int n, const char *name) {
    for (int i = 0; i < n; i++) {
        if (strcmp(array[i].name, name) == 0) {
            double weightInKg = array[i].weight * 0.453592;
            printf("Weight of %s: %.2f kg\n", name, weightInKg);
            return;
        }
    }
    printf("Person named %s not found.\n", name);
}

void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

void printMenu() {
    printf("\nMAIN MENU (HEAP)\n");
    printf("1. Read Data\n");
    printf("2. Create a Min-heap based on the age\n");
    printf("3. Create a Max-heap based on the weight\n");
    printf("4. Display weight of the youngest person\n");
    printf("5. Insert a new person into the Min-heap\n");
    printf("6. Delete the oldest person\n");
    printf("7. Display weight by name\n");
    printf("8. Exit\n");
    printf("Enter option: ");
}