/*
 * manage_FS_and_BS.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_MANAGE_FS_AND_BS_H_
#define DUAL_SIMPLEX_PROCEDURE_MANAGE_FS_AND_BS_H_

typedef struct connection_list_element
{
   int id;
   int prev;
   int next;
} EDGENODE;

typedef struct connection_list
{
    EDGENODE **EDGES;
} EDGELIST;

EDGELIST *build_BS_list(int **W, int n)
{
   int i,j;

   EDGELIST *BS=(EDGELIST *)malloc(sizeof(EDGELIST));
   BS->EDGES=(EDGENODE **)malloc(((n*n)+1)*sizeof(EDGENODE*));

   for (i=0; i<=n*n; i++) BS->EDGES[i]=NULL;

   for (j=1; j<=n; j++)
   {
      int actual=0;
      for (i=1; i<=n; i++)
      {
         if (/*W[i][j]!=0 && */i!=j && W[i][j]!=INT_MAX)
         {
            int edge=((i*n)-n)+j;
            int position=((j-1)*n)+i;

            EDGENODE *newnode=(EDGENODE *)malloc(sizeof(EDGENODE));
            newnode->id=edge;
            newnode->prev=actual;
            newnode->next=0;

            BS->EDGES[position]=newnode;

            if (actual!=0) BS->EDGES[actual]->next=position;

            actual=position;
         }
      }
   }
   return BS;
}

int *build_pBS(EDGELIST *BS, int n)
{
   int *p=(int *)malloc((n+2)*sizeof(int));

   int i,j;

   for (i=1; i<=n; i++) p[i]=0;
   j=1;

   for (i=1; i<=n*n; i++)
   {
      if (i>j*n)
      {
         j=j+1;
         i=(j-1)*n;
      }
      else if (BS->EDGES[i]!=NULL)
      {
         p[j]=i;
         j=j+1;
         i=(j-1)*n;
      }
   }

   return p;
}

#endif /* DUAL_SIMPLEX_PROCEDURE_MANAGE_FS_AND_BS_H_ */
