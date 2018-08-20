/*
 * build_point_array.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_BUILD_POINT_ARRAY_H_
#define DUAL_SIMPLEX_PROCEDURE_BUILD_POINT_ARRAY_H_

int *build_point_array(int n, int **W)
{
   int *p=(int *)malloc((n+2)*sizeof(int));

   int i,j;

   for (i=1; i<=n; i++) p[i]=0;

   for (i=1; i<=n; i++)
   {
      for (j=1; j<=n; j++)
      {
         if (W[i][j]>0)
         {
            int pos=((i*n)-n)+j;
            p[i]=pos;
            break;
         }
      }
   }

   return p;

}

int *build_point_array_of_tree(int *T, int n)
{
   int i, j;
   int *p=(int *)malloc((n+1)*sizeof(int));
   for (i=0; i<=n; i++) p[i]=0;

   j=1;

   for (i=1; i<=n*n; i++)
   {
      if (i>j*n) j=j+1;
      if (T[i]!=0)
      {
         p[j]=i;
         i=j*n+1;
      }
   }
   return p;
}

#endif /* DUAL_SIMPLEX_PROCEDURE_BUILD_POINT_ARRAY_H_ */
