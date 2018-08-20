/*
 * FIND_NODE_IN_MLB.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_INSERT_NODE_IN_MLB_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_INSERT_NODE_IN_MLB_H_

/**
   This function insert a node in the correct position in the Multi Level Bucekt.
   The function, at first find the level and then the correct bucket in the level.
   If the level pointer is null, there isn't no one bucket in it. Then the
   function builds the bucket array and assigns each bucket the relative range.
*/

void insert_node_in_MLB(Multi_Level_Bucket *MLB, V_set *set_of_vertex, int id_in_node, int p)
{

	xy_in_MLB *pos=(xy_in_MLB *)malloc(sizeof(xy_in_MLB));

   pos=find_position(MLB, set_of_vertex->V[id_in_node].dist, p);
   // Find the position that the node will occupy in the Multi level bucket.


   if (pos->l < MLB->actual_level) MLB->actual_level=pos->l;
   // Update the lower not empty level in the structure

   /************************************************************************************/
   /********************************* ADD A NODE IN A BUCKET ***************************/
   /************************************************************************************/
   /**/// Insert the node in the correct bucket.                                     /**/
   /**/add_in_bucket(MLB, set_of_vertex, pos, id_in_node, p);                        /**/
   /************************************************************************************/
   /************************************************************************************/

   if (MLB->LEVEL[pos->l].active_bucket > pos->b)
      MLB->LEVEL[pos->l].active_bucket=pos->b;

   pos=NULL;free(pos);

   return;

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_INSERT_NODE_IN_MLB_H_ */
