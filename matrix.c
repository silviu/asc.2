#include <stdio.h>
#include <stdlib.h>

#define DIM 5
unsigned long long a0[DIM][DIM], a1[DIM][DIM], a2[DIM][DIM],
                   b0[DIM][DIM], b1[DIM][DIM], b2[DIM][DIM],
                   c0[DIM][DIM], c1[DIM][DIM], c2[DIM][DIM],
                   c3[DIM][DIM], c4[DIM][DIM],
                   a0b0[DIM][DIM], a0b1[DIM][DIM], a0b2[DIM][DIM],
                   a1b0[DIM][DIM], a1b1[DIM][DIM], a1b2[DIM][DIM],
                   a2b0[DIM][DIM], a2b1[DIM][DIM], a2b2[DIM][DIM],
                   mrez[DIM][DIM];
    
void init()
{
    int i, j;
    for (i = 0; i < DIM; i++)
		for (j = 0; j < DIM; j++) {
            a0[i][j] = (i + j + 2) % 10000;
            a1[i][j] = (2 * (i + j + 2)) % 10000;
            a2[i][j] = (3 * (i + j + 2)) % 10000;
            
            b0[i][j] = ((i + 1) * (j + 5)) % 10000;
            b1[i][j] = ((i + 2) * (j + 5)) % 10000;
            b2[i][j] = ((i + 3) * (j + 5)) % 10000;
        }
 }

void first()
{
    int i, j, k;
    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            for (k = 0; k < DIM; k++) {
                a0b0[i][j] += a0[i][k] * b0[k][j];
                a0b1[i][j] += a0[i][k] * b1[k][j];
                a0b2[i][j] += a0[i][k] * b2[k][j];
                
                a1b0[i][j] += a1[i][k] * b0[k][j];
                a1b1[i][j] += a1[i][k] * b1[k][j];
                a1b2[i][j] += a1[i][k] * b2[k][j];
                
                a2b0[i][j] += a2[i][k] * b0[k][j];
                a2b1[i][j] += a2[i][k] * b1[k][j];
                a2b2[i][j] += a2[i][k] * b2[k][j];
            }

    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++) {
            c0[i][j] = a0b0[i][j];
            c1[i][j] = a0b1[i][j] + a1b0[i][j];
            c2[i][j] = a0b2[i][j] + a1b1[i][j] + a2b0[i][j];
            c3[i][j] = a1b2[i][j] + a2b1[i][j];
            c4[i][j] = a2b2[i][j];
        }
    for (i = 0; i < DIM; i++)
        for (j = 0; j < DIM; j++)
            mrez[i][j] = c0[i][j] ^ c1[i][j] ^ c2[i][j] ^ c3[i][j] ^ c4[i][j];
}

void first_output(const char* filename)
{
    int i, j;
    
    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        return;
    }
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++)
            fprintf(f, "%llu ", c0[i][j]);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++)
            fprintf(f, "%llu ", c1[i][j]);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++)
            fprintf(f, "%llu ", c2[i][j]);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++)
            fprintf(f, "%llu ", c3[i][j]);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++)
            fprintf(f, "%llu ", c4[i][j]);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
    
    fclose(f);
}

int main(int argc, char** argv)
{
    init();
    first();
    first_output(argv[1]);
    return 0;
}
