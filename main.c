/*
 * main.c
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */
#include "header.h"

int main(int argc, char *argv[]) {

	int source, new_source;

	source = atoi(argv[1]);
	new_source = atoi(argv[2]);

	char *instance = argv[3];

	GRAPH *G = build_graph( instance );

	int n = G->n;
	// Stores the number of verteces

	int m = G->m;
	// Stores the number of edges

	fprintf(stderr, " old s %d - new s %d\n", source, new_source);

	input_controller(argc, source, new_source, n);

	char *f_sol = argv[4];
	char *f_time = argv[5];
	char *f_sol_prev = argv[6];

	V_set *VERTICES = (V_set *) malloc(sizeof(V_set));
	// Allocaters the space for the vertex set

	VERTICES->V = allocateVertices( G );
	// Build the vertex set

	int k = defineNumberOfLevels( n, m, G->Cmax );
	// Stores the number of levels of the multi-level graph

	int p = defineBucketsNumberForLevel( G->Cmax, k );
	// Stores the number of buckets for each levels of the graph

	k = k + 15;

	Multi_Level_Bucket *MLB = (Multi_Level_Bucket *) malloc (sizeof (Multi_Level_Bucket));
	// Allocates the space for the Multi Level Bucket data structure

	MLB->LEVEL = allocateLevels(k, p);
	// Allocates the space for the levels

	FILE *F_sol_prev = fopen(f_sol_prev, "r");
	while (!feof(F_sol_prev)) {

	   int node, dist, pred;

	   fscanf(F_sol_prev, " %d : %d %d\n", &node, &dist, &pred);
	   VERTICES->V[node].dist = dist;
	   VERTICES->V[node].pred = pred;

	}

	fclose(F_sol_prev);

	V_set *DUMMY = (V_set*) malloc(sizeof(V_set));
	DUMMY->V = allocateVertices( G );
	int i;
	for (i = 1; i <= n; i++) {
		DUMMY->V[i].pred = VERTICES->V[i].pred;
		DUMMY->V[i].dist = VERTICES->V[i].dist;
	}

	Dual_Simplex_Reopt(VERTICES, MLB, G, new_source, n, m, p, k, source, DUMMY,
			f_sol, f_time);



	return 0;

}
