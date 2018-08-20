/*
 * build_forward_array.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_BUILD_FORWARD_ARRAY_H_
#define DUAL_SIMPLEX_PROCEDURE_BUILD_FORWARD_ARRAY_H_

int *build_forward_array(int n, int **W)
{
   int *F=(int *)malloc(((n*n)+1)*sizeof(int));

   int i,j;

   for (i=1; i<=n*n; i++) F[i]=0;

   for (i=1; i<=n; i++)
   {
      for (j=1; j<=n; j++)
      {
         if (W[i][j]>0)
         {
            int pos=((i*n)-n)+j;
            F[pos]=i;
         }
      }
   }

   return F;

}

#endif /* DUAL_SIMPLEX_PROCEDURE_BUILD_FORWARD_ARRAY_H_ */
