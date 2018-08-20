/*
 * general_settings.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_GENERAL_SETTINGS_H_
#define DUAL_SIMPLEX_PROCEDURE_GENERAL_SETTINGS_H_

int head_min_label_edge=INT_MAX;

void set_N_s_negate_label(V_set *VERTICES, Ns_NotNs *DisjointVertexSet, int z, int **W)
{
   int i;
   list_node *temp1; list_node *temp2;
   temp2=DisjointVertexSet->N_s_negate;

   while (temp2!=NULL)
   {
      temp1=DisjointVertexSet->N_s;

      int min=INT_MAX;

      while (temp1!=NULL)
      {
         if (W[temp1->v][temp2->v]!=0 && W[temp1->v][temp2->v]!=INT_MAX)
         {
            int dummy=W[temp1->v][temp2->v]+VERTICES->V[temp1->v].tt - VERTICES->V[temp2->v].tt + VERTICES->V[z].label;
            if (min > dummy) min=dummy;
            head_min_label_edge=temp1->v;
         }

         temp1=temp1->next;

      }

      if (VERTICES->V[temp2->v].label > min)
         VERTICES->V[temp2->v].label=min;

      temp2=temp2->next;
   }

   temp1=NULL;
   temp2=NULL;
   free(temp1);
   free(temp2);

   return;

}

int get_head_min_label_edge()
{
   return head_min_label_edge;
}

#endif /* DUAL_SIMPLEX_PROCEDURE_GENERAL_SETTINGS_H_ */
