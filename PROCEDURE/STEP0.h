/*
 * STEP0.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_STEP0_H_
#define DUAL_SIMPLEX_PROCEDURE_STEP0_H_

Ns_NotNs *build_new_vertex_list(V_set *VERTICES, int new_source, int n)
{

   Ns_NotNs *B=(Ns_NotNs *)malloc(sizeof(Ns_NotNs));
   B->N_s=NULL;
   B->N_s_negate=NULL;
   B->N_s_number=0;
   B->N_s_negate_number=0;

   int i,j;
   for (i=1; i<=n; i++)
   {
      j=i;

      if (i!=new_source)
      {
         while (1)
         {
            if (VERTICES->V[j].pred==0)
            {
               if (B->N_s_negate==NULL)
               {
                  B->N_s_negate=(list_node *)malloc(sizeof(list_node));
                  B->N_s_negate->v=i;
                  VERTICES->V[i].label=INT_MAX;
                  VERTICES->V[i].dist=INT_MAX;
                  B->N_s_negate->next=NULL;
                  B->N_s_negate->prev=NULL;
                  B->N_s_negate_number++;
               }
               else
               {
                  list_node *new_node=(list_node *)malloc(sizeof(list_node));
                  new_node->v=i;
                  VERTICES->V[i].label=INT_MAX;
                  VERTICES->V[i].dist=INT_MAX;
                  new_node->next=B->N_s_negate;
                  B->N_s_negate->prev=new_node;
                  new_node->prev=NULL;
                  B->N_s_negate=new_node;
                  new_node=NULL;
                  free(new_node);
                  B->N_s_negate_number++;
               }
               break;
            }
            if (VERTICES->V[j].pred==new_source)
            {
               if (B->N_s==NULL)
               {
                  B->N_s=(list_node *)malloc(sizeof(list_node));
                  B->N_s->v=i;
                  VERTICES->V[i].label=0;
                  VERTICES->V[i].dist=0;
                  B->N_s->next=NULL;
                  B->N_s->prev=NULL;
                  B->N_s_number++;
               }
               else
               {
                  list_node *new_node=(list_node *)malloc(sizeof(list_node));
                  new_node->v=i;
                  VERTICES->V[i].label=0;
                  VERTICES->V[i].dist=0;
                  new_node->next=B->N_s;
                  B->N_s->prev=new_node;
                  new_node->prev=NULL;
                  B->N_s=new_node;
                  new_node=NULL;
                  free(new_node);
                  B->N_s_number++;
               }
               break;
            }
            j=VERTICES->V[j].pred;
         }
      }
   }

   if (B->N_s==NULL)
   {
      B->N_s=(list_node *)malloc(sizeof(list_node));
      B->N_s->v=new_source;
      VERTICES->V[new_source].label=0;
      VERTICES->V[new_source].dist=0;
      B->N_s->next=NULL;
      B->N_s->prev=NULL;
      B->N_s_number++;
      return B;

   }

   list_node *new_node=(list_node *)malloc(sizeof(list_node));
   new_node->v=new_source;
   VERTICES->V[new_source].label=0;
   VERTICES->V[new_source].dist=0;
   new_node->next=B->N_s;
   B->N_s->prev=new_node;
   new_node->prev=NULL;
   B->N_s=new_node;
   new_node=NULL;
   free(new_node);
   B->N_s_number++;
   return B;
}

#endif /* DUAL_SIMPLEX_PROCEDURE_STEP0_H_ */
