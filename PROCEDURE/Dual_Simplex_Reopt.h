/*
 * Dual_Simplex_Reopt.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_DUAL_SIMPLEX_REOPT_H_
#define DUAL_SIMPLEX_PROCEDURE_DUAL_SIMPLEX_REOPT_H_

void Dual_Simplex_Reopt(V_set *VERTICES, Multi_Level_Bucket *NsNEG, GRAPH *G,
		int new_source, int n, int m, int p, int k, int source, V_set *DUMMY,
		char *f_sol, char *f_time) {

	int i, j;

	/***************************************************************************/
	/******************************** STEP 0 ***********************************/
	/***************************************************************************/
	int *pred = (int *) malloc((n + 1) * sizeof(int));
	for (i = 0; i <= n; i++)
		pred[i] = VERTICES->V[i].pred;

	init_dual_variables(VERTICES, n);

	Ns_NotNs *DisjointVertexSet = build_new_vertex_list( VERTICES, new_source, n );

	int z = new_source;
	BASIC_NODE *e_arc = NULL;
	BASIC_NODE *f_arc = NULL;

	T_info *TREE_info = build_tree_info(VERTICES, DisjointVertexSet->N_s,
			DisjointVertexSet->N_s_negate, n);

	T *TREE = buildTree( TREE_info, VERTICES, source, n );

	T *TREE_s = searchInTree( TREE, z );

	update_TREE_and_TREEs( TREE, TREE_s, z, f, n );

	VERTICES->V[z].label = 0;
//	VERTICES->V[z].dist = 0;
//	insert_node_in_MLB( NsNEG, VERTICES, z, p );

	set_label_in_N_z(TREE_s->child, VERTICES, z);
//	_setLabelInNz( TREE_s->child, VERTICES, z );

	minHeap *N_s_neg_tree = buildMinHeap(N_s_neg_tree,
			DisjointVertexSet->N_s_negate, VERTICES,
			DisjointVertexSet->N_s_negate_number);

	set_notNs_label_less_Nz(N_s_neg_tree, TREE_s, VERTICES, G, z, n);
//	_setLabelInNsNEG ( NsNEG, TREE_s, VERTICES, G, z, n, p );

	for (i = (N_s_neg_tree->size - 1) / 2; i >= 0; i--) {
		heapify(N_s_neg_tree, i);
	}

	DUMMY->V[new_source].dist = 0;
	DUMMY->V[new_source].pred = 0;

	/***************************************************************************/
	/***************************************************************************/
	/***************************************************************************/
	int step = 1;

	T *z_root;

	clock_t start = clock();

	while (1) {

		switch (step) {
		case 1:

			/***************************************************************************/
			/******************************** STEP 1 ***********************************/
			/***************************************************************************/
//			fprintf(stderr, " step 1 -init\n ");
			e_arc = find_basic_reverse_arc_with_head_z(VERTICES, G, z);
			if ( e_arc == NULL ) {
				step = 4;
				break;
			}
//			fprintf(stderr, " step 1 -end\n ");
			/***************************************************************************/
			/***************************************************************************/
			/***************************************************************************/

			step = 2;
			break;

		case 2:
//			fprintf(stderr, " step 2 -init\n ");
			/***************************************************************************/
			/******************************** STEP 2 ***********************************/
			/***************************************************************************/
			f_arc = get_min_connecting_arc(N_s_neg_tree, 0, VERTICES);
			z = get_min_head_connecting_arc(VERTICES, n);
			/***************************************************************************/
			/***************************************************************************/
			/***************************************************************************/


//			fprintf(stderr, " ---> %d \n", f_arc->i);

			int u = *&(f_arc->i);
			int v = *&(f_arc->j);

//			fprintf(stderr, " step 2 -middle 2\n ");

			DUMMY->V[v].pred = u;

			step = 3;
//			fprintf(stderr, " step 2 -end\n ");
			break;

		case 3:

//			fprintf(stderr, " step 3 -init\n ");
			/*************************************************************************************************/
			/********************************************** STEP 3 *******************************************/
			/*************************************************************************************************/
			z_root = searchInTree(TREE, z);
			set_label_in_N_z(z_root->child, VERTICES, z);
			VERTICES->V[z].in_Nz = 1; /***/
			set_notNs_label_less_Nz(N_s_neg_tree, z_root, VERTICES, G, z, n);
			for (i = 0; i < N_s_neg_tree->size; i++) {
				if (N_s_neg_tree->elem[i]->id == z_root->id) {
					h_node *temp = N_s_neg_tree->elem[i];
					N_s_neg_tree->elem[i] =
							N_s_neg_tree->elem[N_s_neg_tree->size - 1];
					N_s_neg_tree->elem[N_s_neg_tree->size - 1] = NULL;
					free(temp);
					N_s_neg_tree->size--;
					break;
				}
			}
			delete_Nz_from_notNs(N_s_neg_tree, z_root->child);

//			fprintf( stderr, " Remaining %d / %d \n", N_s_neg_tree->size, G->n);

			for (i = (N_s_neg_tree->size - 1) / 2; i >= 0; i--) {
				heapify(N_s_neg_tree, i);
			}
			update_TREE_and_TREEs(TREE, TREE_s, z, f_arc, n);
			/*************************************************************************************************/
			/*************************************************************************************************/
			/*************************************************************************************************/

			step = 1;
//			fprintf(stderr, " step 3 -end\n ");
		}

		if (step == 4)
			break;

	}

	clock_t end = clock();

	double exec_time = ((double) (end - start)) / CLOCKS_PER_SEC;

	set_new_distance(DUMMY, TREE_s, G, TREE_s->id);

	FILE *F_sol = fopen(f_sol, "w");

	FILE *F_time = fopen(f_time, "a");

	for (i = 1; i <= n; i++) {

		fprintf(F_sol, "%d : %d %d\n", DUMMY->V[i].id, DUMMY->V[i].pred, DUMMY->V[i].dist);

	}

	fprintf(F_time, "%f\n", exec_time);

	fclose(F_sol);
	fclose(F_time);

	return;

}

#endif /* DUAL_SIMPLEX_PROCEDURE_DUAL_SIMPLEX_REOPT_H_ */
