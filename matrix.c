#include <stdio.h>
#include <stdlib.h>

#define DIM 5
#define B 1
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


void second()
{
    register int i, j, k;
    for (i = 0; i < DIM; i++) {
        unsigned long long* orig_line_a0 = &a[0][i][0];
        unsigned long long* orig_line_a1 = &a[1][i][0];
        unsigned long long* orig_line_a2 = &a[2][i][0];
        
        for (j = 0; j < DIM; j++) {
            register unsigned long long* line_a0 = orig_line_a0;
            register unsigned long long* line_a1 = orig_line_a1;
            register unsigned long long* line_a2 = orig_line_a2;
        
            register unsigned long long* col_b0 = &b[0][0][j];
            register unsigned long long* col_b1 = &b[1][0][j];
            register unsigned long long* col_b2 = &b[2][0][j];
            
            register unsigned long long s00, s01, s02, s10, s11, s12, s20, s21, s22;
            s00 = 0; s01 = 0; s02 = 0; s10= 0; s11 = 0; s12 = 0; s20 = 0; s21 = 0; s22 = 0;
            
            for (k = 0; k < DIM; k++) {
                s00 += *line_a0 * *col_b0;
                s01 += *line_a0 * *col_b1;
                s02 += *line_a0 * *col_b2;
                
                s10 += *line_a1 * *col_b0;
                s11 += *line_a1 * *col_b1;
                s12 += *line_a1 * *col_b2;
                
                s20 += *line_a2 * *col_b0;
                s21 += *line_a2 * *col_b1;
                s22 += *line_a2 * *col_b2;
                
                line_a0++;
                line_a1++;
                line_a2++;
                
                col_b0 += DIM;
                col_b1 += DIM;
                col_b2 += DIM;
            }
            
            a0b0[i][j] = s00;
            a0b1[i][j] = s01;
            a0b2[i][j] = s02;
            
            a1b0[i][j] = s10;
            a1b1[i][j] = s11;
            a1b2[i][j] = s12;
            
            a2b0[i][j] = s20;
            a2b1[i][j] = s21;
            a2b2[i][j] = s22;
        }
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

void third()
{
    register int i, j, k, l, m;
    register int N = DIM / B;
    register int R = DIM % B;
    
    for (l = 0; l < N; l++) {
        for (m = 0; m < N; m++) {
            for (i = l * B; i < B * (l + 1); i++) {
				for (j = m * B; j < B * (m + 1); j++) {
					for (k = 0; k < N; k++) {
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
				}
			}
		}
	}
	
	/*for (i = 0; i < DIM; i++) {
	    for (j = 0; j < DIM; j++)
	        printf("%llu ", a[0][i][j]);
	   printf("\n");
	   }
    printf("\n");
	
	for (l = 0; l < N; l++) {
        for (m = 0; m < N; m++) {
            for (i = l * B; i < B * (l + 1); i++) {
				for (j = m * B; j < B * (m + 1); j++) {
					printf("%llu ", a[0][i][j]);
				}
            printf("\n");
            }}}

*/
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

void output(const char* filename)
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
    int run = atoi(argv[2]);
    switch(run) {
    case 1:
        first();
        break;
    case 2:
        second();
        break;
    case 3:
        third();
        break;
    case 4:
        break;
    }
    output(argv[1]);
    return 0;
}
