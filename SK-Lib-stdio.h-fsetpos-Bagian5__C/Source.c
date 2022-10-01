#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
    Source by CPPReference (https://en.cppreference.com)
    Modified For Learn by RK
    I.D.E : VS2022
*/

int main() {
    /* Siapkan array nilai f-p. */
#define SIZE 5
    double A[SIZE] = { 1.,2.,3.,4.,5. };
    /* Menulis array ke file. */
    FILE* fp = fopen("test.bin", "wb");
    fwrite(A, sizeof(double), SIZE, fp);
    fclose(fp);

    /* Membaca nilai f-p ke dalam array B. */
    double B[SIZE];
    fp = fopen("test.bin", "rb");
    fpos_t pos;

    if (fgetpos(fp, &pos) != 0) {      /* posisi saat ini: awal file */
        perror("fgetpos()");
        fprintf(stderr, "fgetpos() failed in file %s at line # %d\n", __FILE__, __LINE__ - 3);
        exit(EXIT_FAILURE);
    }

    int ret_code = fread(B, sizeof(double), 1, fp);   /* membaca satu nilai f-p */
    /* posisi saat ini: setelah membaca satu nilai f-p */
    printf("%.1f; read count = %d\n", B[0], ret_code);   /* mencetak satu nilai f-p dan ret_code */

    if (fsetpos(fp, &pos) != 0) {   /* reset posisi sekarang ke awal file */
        if (ferror(fp)) {
            perror("fsetpos()");
            fprintf(stderr, "fsetpos() failed in file %s at line # %d\n", __FILE__, __LINE__ - 5);
            exit(EXIT_FAILURE);
        }
    }

    ret_code = fread(B, sizeof(double), 1, fp);   /* membaca ulang nilai f-p pertama */
    printf("%.1f; read count = %d\n", B[0], ret_code);   /* mencetak satu nilai f-p dan ret_code */
    fclose(fp);

    _getch();
    return EXIT_SUCCESS;
}