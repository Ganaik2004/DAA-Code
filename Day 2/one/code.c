#include <stdio.h>
void copy_file(const char* src, const char* dest) {
    FILE *fptr1, *fptr2;
    int c;

    fptr1 = fopen(src, "r");
    fptr2 = fopen(dest, "w");

    while ((c = fgetc(fptr1)) != EOF) {
        fputc(c, fptr2);
    }

    printf("Copied %s to %s\n", src, dest);

    fclose(fptr1);
    fclose(fptr2);
}

int main(int args, char* arr[]) {
    copy_file(arr[1], arr[2]);
    return 0;
}