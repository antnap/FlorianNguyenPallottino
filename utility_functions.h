/*
 * utility_functions.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef UTILITY_FUNCTIONS_H_
#define UTILITY_FUNCTIONS_H_

int **allocateMatrix(int n, int m)
{
     // This Function dinamically allocates a bidimensional matrix of
     // n x m elements, and initializes it at zero!

     int **W=(int **)malloc((n)*sizeof(int*));
     int i,j;
     for (i=0; i<n; i++)
         W[i]=(int *)malloc((m)*sizeof(int));

     for (i=0; i<n; i++)
         for (j=0; j<m; j++)
             W[i][j]=0;

     return W;
}

#endif /* UTILITY_FUNCTIONS_H_ */
