/*
 * SEARCH-MIN-LEVEL.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_SEARCH_MIN_LEVEL_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_SEARCH_MIN_LEVEL_H_

void search_min_level(Multi_Level_Bucket *MLB, int k, int p)
{

   while (1)
   {

      if (MLB->actual_level >= k) return;

      if (MLB->LEVEL[MLB->actual_level].active_bucket<p) return;

      MLB->actual_level=MLB->actual_level+1;

   }
}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_SEARCH_MIN_LEVEL_H_ */
