#include <stdio.h>
#include <stdlib.h>

#define DIM 787
unsigned long long a0[DIM][DIM], a1[DIM][DIM], a2[DIM][DIM],
                   b0[DIM][DIM], b1[DIM][DIM], b2[DIM][DIM];

void init()
{
    unsigned int i, j;
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


int main(int argc, char** argv)
{
    init();
    return 0;
}
