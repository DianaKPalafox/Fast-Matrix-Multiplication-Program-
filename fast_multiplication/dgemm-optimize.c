#define min(a,b) ((a < b) ? a : b)                                                            //min function for tiling
#define tile 64                                                                                                    //optimal tile size

/* Tiling */
void dgemm(int m, int n, float *A, float *C) {
    for(int cl = 0; cl < n; cl += tile) {
      int x = min(cl + tile, n);                                //creating tile column limit
    for(int rw = 0; rw < m; rw += tile) {
      int y = min(rw + tile, m);                                //creating tile row limit
    for(int loop = 0; loop < m; loop += tile) {
      int z = min(loop + tile, m);                                //loop limit
    for(int tileCl = cl; tileCl < x; ++tileCl) {
        for(int tileRw = rw; tileRw < y; ++tileRw) {
            for(int tileLoop = loop; tileLoop < z; ++tileLoop) {
          C[tileRw * m + tileLoop] += A[m * tileCl + tileLoop] * A[m * tileCl + tileRw];
        }
      }
    }
    }
    }
    }
}

/* Reordering */ /*
void dgemm(int m, int n, float *A, float *C){
    for(int j=0; j<m; j++){                                                                    //switched i and j for loops
      for(int k=0; k<n; k++){
        for(int i=0; i<m; i++){
        C[i+j*m] += A[i+k*m] * A[j+k*m];
      }
    }
  }
}
*/

/* Prefeching */ /*
void dgemm( int m, int n, float *A, float *C ){
    int i, j, k;
    for(i = 0; i < m; i++){
                                                                                                                                        //printf("Here");
        for(k = 0; k < n; k++){
            for(j = 0; j < m; j++){
                C[i+j*m] += A[i+k*m] * A[j+k*m];
                __builtin_prefetch(&A[(j+1)+k*m]);                                        //prefetching next element in A and C, (j+1)
                __builtin_prefetch(&C[i+(j+1)*m]);
            }
            __builtin_prefetch(&A[i+(k+1)*m]);                                                //prefetching next element in A and C, (k+1)
            __builtin_prefetch(&C[j+(k+1)*m]);
        }
        __builtin_prefetch(&C[(i+1)+j*m]);                                                        //prefetching next element in A and C, (i+1)
               __builtin_prefetch(&A[(i+1)+k*m]);
  }
}
 */

/* Unrolling */ /*
 void dgemm(int m, int n, float *A, float *C) {
  int unrolled = m / 6, loop;
  for (int cl = 0; cl < n; ++cl) {                                                                         // Column
    for(int rw = 0; rw < m; ++rw) {                                                                        // Rows
      for(loop = 0; loop < unrolled; loop += 6) {                                            // apply Unrolling
        C[loop + rw * m] += A[loop + cl * m] * A[rw + cl * m];
        C[loop + 1 + rw * m] += A[loop + 1 + cl * m] * A[rw + cl * m];
        C[loop + 2 + rw * m] += A[loop + 2 + cl * m] * A[rw + cl * m];
        C[loop + 3 + rw * m] += A[loop + 3 + cl * m] * A[rw + cl * m];
        C[loop + 4 + rw * m] += A[loop + 4 + cl * m] * A[rw + cl * m];
        C[loop + 5 + rw * m] += A[loop + 5 + cl * m] * A[rw + cl * m];
      }
      while (loop < m) {
        C[loop + rw * m] += A[loop + m * cl] * A[rw + m * cl];
          loop++;
      }
    }
  }
}

*/
