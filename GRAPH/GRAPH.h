/*
 * GRAPH.h
 *
 *  Created on: 20 giu 2018
 *      Author: antonio
 */

#ifndef GRAPH_GRAPH_H_
#define GRAPH_GRAPH_H_

typedef struct basic_node_element {

	int i;
	int j;
	int w_ij;
	int f_ij;
	int wr_ij;

}BASIC_NODE;

typedef struct list_of_node_Ts {

	int id;
	struct list_of_node_Ts *prev;
	struct list_of_node_Ts *next;

}L_Ts;

typedef struct general_graph_structure {

	BASIC_NODE ***FS;		// The forward star list for each node
	BASIC_NODE ***SORTFS;	// The sorted forward star list for each node
	int *pSORTFS;			// The pointer to the first valid element in SORTF
	int *deg_;				// The outdeg dimension for each node
	int n;					// The number of nodes in the graph
	int m;					// The number of edges in the graph
	int Cmax;				// The max cost in the graph
	int pos_tail;
	int pos_head;
	L_Ts *Ts;				// First fragment of the new solution
	int *remain_FS;			// Remaining node in FS for each node

}GRAPH;


#endif /* GRAPH_GRAPH_H_ */
