/*
 * CREATE_GRAPH.h
 *
 *  Created on: 20 giu 2018
 *      Author: antonio
 */

#ifndef GRAPH_CREATE_GRAPH_H_
#define GRAPH_CREATE_GRAPH_H_

int find_node_number (FILE *F, char *instance) {

	int n;

	fscanf(F, "%d", &n);

	return n;

}

int find_edge_number (FILE *F, char *instance) {

	int m;

	fscanf(F, "%d\n", &m);

	return m;

}

void compute_OUTDEG_FS_CMAX(FILE *F, GRAPH *G) {

	int i, j, deg, max;

	G->FS = (BASIC_NODE ***) malloc ((G->n + 1) * sizeof(BASIC_NODE**));

	G->SORTFS = (BASIC_NODE ***) malloc ((G->n + 1) * sizeof(BASIC_NODE**));

	G->deg_ = (int *) malloc ((G->n + 1) * sizeof(int));

	G->pSORTFS = (int *) malloc ((G->n + 1) * sizeof(int));

	G->remain_FS = (int *) malloc ((G->n + 1) * sizeof(int));

	max = 0;

	while ( !feof(F) ) {

		fscanf(F, "%d %d", &i, &deg);

		G->deg_[i] = deg;

		G->FS[i] = (BASIC_NODE **) malloc ( G->deg_[i] * sizeof(BASIC_NODE*) );

		G->SORTFS[i] = (BASIC_NODE **) malloc ( ( G->deg_[i] + 1 ) * sizeof(BASIC_NODE*) );

		G->remain_FS[i] = G->deg_[i];

		for ( j = 0; j < G->deg_[i]; j++ ) {

			G->FS[i][j] = NULL;

			G->SORTFS[i][j] = NULL;

			BASIC_NODE *bn = (BASIC_NODE *) malloc (sizeof(BASIC_NODE));

			bn->i = i;

			int w_ij;

			fscanf(F, " %d %d", &bn->j, &w_ij);

			bn->w_ij = w_ij;

			if ( max < bn->w_ij ) max = bn->w_ij;

			G->FS[i][j] = bn;

			bn = NULL;

			free(bn);

		}

		fscanf(F, "\n");

	}

	G->Cmax = max;

	return;

}

GRAPH *build_graph(char *instance) {

	FILE *F;

	F = fopen(instance, "r");

	if ( F == NULL ) {
		fprintf(stderr, " IMPOSSIBLE TO OPEN THE FILE\n");
		fprintf(stderr, " -> %s", instance);
		exit(1);
	}

	GRAPH *G = (GRAPH *) malloc (sizeof(GRAPH));

	G->n = find_node_number(F, instance);

	G->m = find_edge_number(F, instance);

	compute_OUTDEG_FS_CMAX(F, G);

	fclose(F);

	return G;

}


#endif /* GRAPH_CREATE_GRAPH_H_ */
