/*
 * initial_settings.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_INITIAL_SETTINGS_H_
#define DUAL_SIMPLEX_PROCEDURE_INITIAL_SETTINGS_H_

void init_dual_variables(V_set *VERTICES, int n)
{
   int i;
   for (i=1; i<=n; i++)
   {
      VERTICES->V[i].tt=VERTICES->V[i].dist;
      VERTICES->V[i].in_Nz = 0;
      VERTICES->V[i].label = INT_MAX;
      VERTICES->V[i].f = NULL;
   }

   return;
}

int **compute_reduced_cost(V_set *VERTICES, int **W, int n)
{
   int i,j;
   list_node *temp;
   int **W_r_c=(int **)malloc((n+1)*sizeof(int *));
   for (i=0; i<=n; i++) W_r_c[i]=(int *)malloc((n+1)*sizeof(int));
   for (i=0; i<=n; i++)
      for(j=0; j<=n; j++)
         W_r_c[i][j]=INT_MAX;

   for (i=1; i<=n; i++)
   {
      temp=VERTICES->V[i].adj->L;
      while (temp!=NULL)
      {
         if (W[i][temp->v]!=0 || W[i][temp->v]!=INT_MAX)
         {
            W_r_c[i][temp->v]=W[i][temp->v]+(VERTICES->V[i].dist-VERTICES->V[temp->v].dist);
         }
         temp=temp->next;
      }
   }
   temp=NULL;
   free(temp);
   return W_r_c;
}

#endif /* DUAL_SIMPLEX_PROCEDURE_INITIAL_SETTINGS_H_ */
