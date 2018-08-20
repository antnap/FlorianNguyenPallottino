/*
 * EXTRACT-MIN-VERTEX.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_EXTRACT_MIN_VERTEX_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_EXTRACT_MIN_VERTEX_H_

int extract_min_vertex(Multi_Level_Bucket *MLB, int k, int p, V_set *V)
{
   /**
       This function extract the min vertex from the minimum level bucket
   */

   /***************************************************************************/
   /*** THE POSITION, IN THE MULTI LEVEL BUCKET, OF THE VERTEX THAT WILL BE ***/
   /********************************* CANCELLED *******************************/
   /***************************************************************************/
   /**/xy_in_MLB *pos=(xy_in_MLB *)malloc(sizeof(xy_in_MLB));               /**/
   /**/pos->l=MLB->actual_level;                                            /**/
   /**/pos->b=MLB->LEVEL[MLB->actual_level].active_bucket;                  /**/
   /***************************************************************************/
   /***************************************************************************/

   /**********************************************************************************/
   /****************** FIND AND DELETE MIN VERTEX IN THE BUCKET **********************/
   /**********************************************************************************/
   /**/int min_vertex=MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L->v;/**/
   /**/delete_node_from_bucket(MLB, pos, min_vertex, p);                           /**/
   /**********************************************************************************/
   /**********************************************************************************/

   if (MLB->LEVEL[pos->l].array_bucket_pointer!=NULL)
      if (MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket!=NULL)
         unfold_bucket(MLB, k, p, V);

   pos=NULL;
   free(pos);

   return min_vertex;

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_EXTRACT_MIN_VERTEX_H_ */
