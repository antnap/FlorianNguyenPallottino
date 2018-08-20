/*
 * STEP1.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_STEP1_H_
#define DUAL_SIMPLEX_PROCEDURE_STEP1_H_

int determine_basic_reverse_arc_with_head_z(minHeap *N_s_neg, int *p, int z, int n)
{

   int e=0;

   int i;

   for (i=0; i<N_s_neg->size; i++)
   {
      if (p[z]==N_s_neg->elem[i]->id)
      {
         e=((p[z]*n)-n)+z;
         break;
      }
   }

   return e;
}

// Must return the arc which connect z with its predecessor
BASIC_NODE *find_basic_reverse_arc_with_head_z(V_set *VERTICES, GRAPH *G, int z)
{

	int j;
	BASIC_NODE *e = NULL;

   int pred_z=VERTICES->V[z].pred;

   if (pred_z!=0)
   {
      VERTICES->V[z].pred=0;

      for ( j = 0; j < G->deg_[ pred_z ]; ++j ) {
    	if ( G->FS[ pred_z ][ j ]->j == z ) {
    		e = &(*G->FS[ pred_z ][ j ]);
    		break;
    	}
      }

   }

   return e;

}

#endif /* DUAL_SIMPLEX_PROCEDURE_STEP1_H_ */
