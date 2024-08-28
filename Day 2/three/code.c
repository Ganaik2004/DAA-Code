#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a % b);
}
void calculateGCDs(int n, FILE *fptr1, FILE *fptr2) {
    int num1, num2;
    if (n <= 0) return;

    if (fscanf(fptr1, "%d %d", &num1, &num2) != 2) {
        printf("Error reading from input file\n");
        return;
    }

    fprintf(fptr2, "GCD of %d and %d is %d\n", num1, num2, gcd(num1, num2));

    calculateGCDs(n - 1, fptr1, fptr2);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    FILE *fptr1 = fopen(argv[2], "r");
    FILE *fptr2 = fopen(argv[3], "w");

    if (fptr1 == NULL || fptr2 == NULL) {
        printf("Error opening files\n");
        return 1;
    }

    calculateGCDs(n, fptr1, fptr2);

    fclose(fptr1);
    fclose(fptr2);

    return 0;
}