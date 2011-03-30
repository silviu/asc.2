#include <stdio.h>
#include <stdlib.h>

#define DIM 787
unsigned long long a0b0[DIM][DIM], a0b1[DIM][DIM], a0b2[DIM][DIM],
                   a1b0[DIM][DIM], a1b1[DIM][DIM], a1b2[DIM][DIM],
                   a2b0[DIM][DIM], a2b1[DIM][DIM], a2b2[DIM][DIM],
                   mrez[DIM][DIM];
    
unsigned long long a[3][DIM][DIM], b[3][DIM][DIM], c[5][DIM][DIM];

void init()
{
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < DIM; i++) {
	    	for (j = 0; j < DIM; j++) {
                a[k][i][j] = ((k + 1) * (i + j + 2)) % 10000;
                b[k][i][j] = ((k + i + 1) * (j + 5)) % 10000;
            }
        }
    }
}

void first()
{
    int i, j, k;
    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            for (k = 0; k < DIM; k++) {
                a0b0[i][j] += a[0][i][k] * b[0][k][j];
                a0b1[i][j] += a[0][i][k] * b[1][k][j];
                a0b2[i][j] += a[0][i][k] * b[2][k][j];
                
                a1b0[i][j] += a[1][i][k] * b[0][k][j];
                a1b1[i][j] += a[1][i][k] * b[1][k][j];
                a1b2[i][j] += a[1][i][k] * b[2][k][j];
                
                a2b0[i][j] += a[2][i][k] * b[0][k][j];
                a2b1[i][j] += a[2][i][k] * b[1][k][j];
                a2b2[i][j] += a[2][i][k] * b[2][k][j];
            }

    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++) {
            c[0][i][j] = a0b0[i][j];
            c[1][i][j] = a0b1[i][j] + a1b0[i][j];
            c[2][i][j] = a0b2[i][j] + a1b1[i][j] + a2b0[i][j];
            c[3][i][j] = a1b2[i][j] + a2b1[i][j];
            c[4][i][j] = a2b2[i][j];
        }
    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            mrez[i][j] = c[0][i][j] ^ c[1][i][j] ^ c[2][i][j] ^ c[3][i][j] ^ c[4][i][j];
}

void first_output(const char* filename)
{
    int i, j;
    
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return;
    }
    /*
    for (k = 0; k < 5; k++) {
        for (i = 0; i < DIM; i++) {
            for (j = 0; j < DIM; j++)
                fprintf(f, "%llu ", c[k][i][j]);
            fprintf(f, "\n");
        }
        fprintf(f, "\n");
    }
    */
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            fprintf(f, "%llu ", mrez[i][j]);
        }
        fprintf(f, "\n");
    }
    
    fclose(f);
}

int main(int argc, char** argv)
{
    init();
    first();
    first_output(argv[1]);
    return 0;
}
