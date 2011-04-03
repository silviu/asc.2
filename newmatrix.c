#include <stdio.h>
#include <stdlib.h>

#define DIM 787
#define BIGGER 800
#define B 50
unsigned long long a0b0[BIGGER][BIGGER], a0b1[BIGGER][BIGGER], a0b2[BIGGER][BIGGER],
                   a1b0[BIGGER][BIGGER], a1b1[BIGGER][BIGGER], a1b2[BIGGER][BIGGER],
                   a2b0[BIGGER][BIGGER], a2b1[BIGGER][BIGGER], a2b2[BIGGER][BIGGER],
                   mrez[BIGGER][BIGGER];
    
unsigned long long a[3][BIGGER][BIGGER], b[3][BIGGER][BIGGER], c[5][BIGGER][BIGGER], bt[3][BIGGER][BIGGER];

void init()
{
    int i, j, k;
    for (k = 0; k < 3; k++) {
        for (i = 0; i < DIM; i++) {
	    	for (j = 0; j < DIM; j++) {
                a[k][i][j] = ((k + 1) * (i + j + 2)) % 10000;
                b[k][i][j] = ((k + i + 1) * (j + 5)) % 10000;
                bt[k][j][i] = b[k][i][j];
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
    register int i, j, k, l, m, p;
    register int N = BIGGER / B;
    
    for (l = 0; l < N; l++) {
        for (m = 0; m < N; m++) {
            for (p = 0; p < N; p++) {   
                for (i = l * B; i < B * (l + 1); i++) {
                    for (j = m * B; j < B * (m + 1); j++) {
                        register unsigned long long s00, s01, s02, s10, s11, s12, s20, s21, s22;
                        s00 = a0b0[i][j]; s01 = a0b1[i][j]; s02 = a0b2[i][j];
                        s10 = a1b0[i][j]; s11 = a1b1[i][j]; s12 = a1b2[i][j]; 
                        s20 = a2b0[i][j]; s21 = a2b1[i][j]; s22 = a2b2[i][j];

                        for (k = p*B; k < B *(p+1); k++) {
                            unsigned long long a0ik = a[0][i][k];
                            unsigned long long a1ik = a[1][i][k];
                            unsigned long long a2ik = a[2][i][k];
                            
                            unsigned long long bt0jk = bt[0][j][k];
                            unsigned long long bt1jk = bt[1][j][k];
                            unsigned long long bt2jk = bt[2][j][k];
                            
                            s00 += a0ik * bt0jk;
                            s01 += a0ik * bt1jk;
                            s02 += a0ik * bt2jk;
                    
                            s10 += a1ik * bt0jk;
                            s11 += a1ik * bt1jk;
                            s12 += a1ik * bt2jk;
                    
                            s20 += a2ik * bt0jk;
                            s21 += a2ik * bt1jk;
                            s22 += a2ik * bt2jk;
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
           }
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
