/*
 * UNFOLD_BUCKET.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_UNFOLD_BUCKET_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_UNFOLD_BUCKET_H_

void unfold_bucket(Multi_Level_Bucket *MLB, int k, int p, V_set *V)
{

   /** This function redistributes the vertices from the current bucket
       to bucket of the previous level. */

   xy_in_MLB *pos=(xy_in_MLB *)malloc(sizeof(xy_in_MLB));
   pos->l=MLB->actual_level;
   pos->b=MLB->LEVEL[MLB->actual_level].active_bucket;

   if (pos->l-1>0)
   {

      int l=pos->l-1;

      int Bi=MLB->LEVEL[l+1].base_distance;
      int ai=MLB->LEVEL[l+1].active_bucket;
      float p_raised_i=pow(p, l+1);

      MLB->LEVEL[l].base_distance=Bi+ai*p_raised_i;
      MLB->LEVEL[l].upper_distance=MLB->LEVEL[l].base_distance+(float)p_raised_i-1;



         MLB->actual_level=MLB->actual_level-1;

         /*******************************************************************************************************/
         /********************************** INSERT THE NODES IN LOWEST BUCKETS *********************************/
         /*******************************************************************************************************/
         list_node *temp=MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L;                           /**/
         while (1)                                                                                            /**/
         {                                                                                                    /**/
         /**/if (temp!=NULL)                                                                                  /**/
         /**/{                                                                                                /**/
         /**/                                                                                                 /**/
         /**/  xy_in_MLB *new_pos=find_position(MLB, V->V[temp->v].dist, p);                                  /**/
         /**/                                                                                                 /**/
         /**/  new_pos->l=MLB->actual_level;                                                                  /**/

//               printf("\n\n The node %d will be replaced in [%d, %d]\n", temp->v, new_pos->l, new_pos->b);
//               system("pause");

         /**/                                                                                                 /**/
         /**/  add_in_bucket(MLB, V, new_pos, temp->v, p);                                                    /**/
         /**/                                                                                                 /**/
         /**/  // IF NECESSARY SET THE NEW ACTIVE BUCKET                                                      /**/
         /**/  if (MLB->LEVEL[new_pos->l].active_bucket > new_pos->b)                                         /**/
         /**/     MLB->LEVEL[new_pos->l].active_bucket=new_pos->b;                                            /**/
         /**/                                                                                                 /**/
         /**/  // DELETE THE NODE FROM THE OLD BUCKET                                                         /**/
         /**/  delete_node_from_bucket(MLB, pos, temp->v,  p);                                                /**/
         /**/                                                                                                 /**/
         /**/  temp=temp->next;                                                                               /**/
         /**/                                                                                                 /**/
         /**/}                                                                                                /**/
         /**/else break;                                                                                      /**/
         }                                                                                                    /**/
         /*******************************************************************************************************/
         /*******************************************************************************************************/

        return;

   }

   pos=NULL;free(pos);

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_UNFOLD_BUCKET_H_ */
