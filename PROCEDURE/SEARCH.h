/*
 * SEARCH.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_SEARCH_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_SEARCH_H_

int search(Multi_Level_Bucket *MLB, int k, int p, V_set *V)
{

   /**
      This function find and extract a vertex with the minimum label distance
      from the structure
   */

   search_min_level(MLB, k, p);

   if (MLB->actual_level<k)
   {

      int min_vertex=extract_min_vertex(MLB, k, p, V);

      return min_vertex;

    }

    return 0;

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_SEARCH_H_ */
