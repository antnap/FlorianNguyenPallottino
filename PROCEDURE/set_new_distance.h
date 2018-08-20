/*
 * set_new_distance.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_SET_NEW_DISTANCE_H_
#define DUAL_SIMPLEX_PROCEDURE_SET_NEW_DISTANCE_H_

void set_new_distance(V_set *DUMMY, T *Ts, GRAPH *G, int root)
{

	int j;

	if (Ts==NULL)return;

	if (Ts->id!=root)
	{

		double arc_cost = INT_MAX;
		int tail = DUMMY->V[Ts->id].pred;
		int head = Ts->id;

		for ( j = 0; j < G->deg_[ tail ]; ++j ) {
			if ( G->FS[ tail ][ j ]->j == head ) {
				arc_cost = G->FS[ tail ][ j ]->w_ij;
				break;
			}
		}


		DUMMY->V[Ts->id].dist = arc_cost + DUMMY->V[DUMMY->V[Ts->id].pred].dist;
	}

	set_new_distance(DUMMY, Ts->child, G, root);

	set_new_distance(DUMMY, Ts->bro, G, root);

}

#endif /* DUAL_SIMPLEX_PROCEDURE_SET_NEW_DISTANCE_H_ */
