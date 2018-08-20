/*
 * allocateVertices.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_ALLOCATEVERTICES_H_
#define DUAL_SIMPLEX_PROCEDURE_ALLOCATEVERTICES_H_

node *allocateVertices( GRAPH *G )
{

   /**
      This function builds the vertex set of the graph. For each node we have
      informations about:
            - id node;
            - distance of the node from the source in the SPT;
            - predecessor of the node in the SPT;
            - adjacent list of the node
   */


   node *V = (node *) malloc ( (G->n + 1) *sizeof(node) );

   int i;

   for ( i = 0; i <= G->n; i++)
   {
	      V[i].id=i;
	      V[i].dist=INT_MAX;
	      V[i].pred=0;
	      V[i].in_Nz=0;
	      V[i].adj=(head_list *)malloc(sizeof(head_list));
	      V[i].f;
   }

   return V;

}

#endif /* DUAL_SIMPLEX_PROCEDURE_ALLOCATEVERTICES_H_ */
