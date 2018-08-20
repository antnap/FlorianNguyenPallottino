/*
 * FIND-POSITION.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_FIND_POSITION_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_FIND_POSITION_H_

xy_in_MLB *find_position(Multi_Level_Bucket *MLB, int distance, int bucket_for_level)
{
   /**
      This function take in input a value, that represents the distance value
      of a node, and finds the relative position of the node in the multi level bucket.
   */

   int l=MLB->actual_level; // varibale that represents the level in the multi level graph;

   while (1)
   {

      if (distance<=MLB->LEVEL[l].upper_distance)
      {
         /**
            checks whether the node can be insert into this level, so its
            label distance should not be greater than the maximum allowed
            value in this level, i.e. upper_distance.
         */

         break; // The level is OK!

      }

      l=l+1;

   }

   /**
      After this loop we are sure that we have the right level.
      So, now, we need to find also the right bucket in the level
   */

   int range=MLB->LEVEL[l].upper_distance-MLB->LEVEL[l].base_distance+1;
   /**
     This is the range of values that the level can hold.
     Range of level i is equal to : Ui-Bi+1, where Ui and Bi are, respectively,
     the upper level and the base level of the level i.
   */

   float x=distance-MLB->LEVEL[l].base_distance;

   float f=x/range;

   int b=floor(f*bucket_for_level);

   /**
     This is the bucket that will contain the node
   */

   xy_in_MLB *pos=(xy_in_MLB *)malloc(sizeof(xy_in_MLB));

   pos->l=l;
   pos->b=b;

   return pos;

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_FIND_POSITION_H_ */
