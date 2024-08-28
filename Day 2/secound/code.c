#include <stdio.h>
#include <stdlib.h>

void decimalToBinaryUtil(int num, FILE *fptr2);
void decimalToBinary(int n, FILE *fptr1, FILE *fptr2);

int main(int argc, char *args[]) {
    int n = atoi(args[1]);

    FILE *fptr1 = fopen(args[2], "r");
    FILE *fptr2 = fopen(args[3], "w");

    decimalToBinary(n, fptr1, fptr2);

    fclose(fptr1);
    fclose(fptr2);

    fptr2 = fopen(args[3], "r");

    if (fptr2 == NULL) {
        printf("Error opening output file for reading\n");
        return 1;
    }

    char c;
    while ((c = fgetc(fptr2)) != EOF) {
        printf("%c", c);
    }

    fclose(fptr2);

    return 0;
}

void decimalToBinary(int n, FILE *fptr1, FILE *fptr2) {
    int num;
    if (n <= 0) return;

    if (fscanf(fptr1, "%d", &num) != 1) {
        printf("Error reading from input file\n");
        return;
    }

    fprintf(fptr2, "The binary equivalent of %d is ", num);
    decimalToBinaryUtil(num, fptr2);
    fprintf(fptr2, "\n");

    decimalToBinary(n-1, fptr1, fptr2);
}

void decimalToBinaryUtil(int num, FILE *fptr2) {
    if (num == 0) return;
    decimalToBinaryUtil(num/2, fptr2);
    fprintf(fptr2, "%d", num % 2);
}