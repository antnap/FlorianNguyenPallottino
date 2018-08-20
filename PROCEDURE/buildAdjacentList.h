/*
 * buildAdjacentList.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_BUILDADJACENTLIST_H_
#define DUAL_SIMPLEX_PROCEDURE_BUILDADJACENTLIST_H_

list_node *buildAdjacentList (int n, int m, int id_node, int **W)
{
   list_node *temp=(list_node *)malloc(sizeof(list_node));
   list_node *aux;

   temp=NULL;
   aux=temp;

   int j;

   for (j=1; j<=n; j++)
   {

      if (j!=id_node && W[id_node][j]>0)
      {

         list_node *n=(list_node *)malloc(sizeof(list_node));
         n->v=j;
         n->prev=NULL;
         n->next=NULL;

         if (aux==NULL)
         {
            temp=n;
            aux=temp;
         }
         else
         {
            aux->next=n;
            n->prev=aux;
            aux=aux->next;
         }

         n=NULL;
         free(n);

      }

   }

   aux=NULL;
   free(aux);

   return temp;

}

#endif /* DUAL_SIMPLEX_PROCEDURE_BUILDADJACENTLIST_H_ */
