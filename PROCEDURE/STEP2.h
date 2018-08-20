/*
 * STEP2.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_STEP2_H_
#define DUAL_SIMPLEX_PROCEDURE_STEP2_H_

int min_label=INT_MAX;
int head=0;

void compute_min_connecting_arc(minHeap *hp, int i)
{
//    if(LCHILD(i) < hp->size) {
//        compute_min_connecting_arc(hp, LCHILD(i));
//    }
//    if (min_label > hp->elem[i]->label)
//    {
//       min_label=hp->elem[i]->label;
//       head=hp->elem[i]->id;
//    }
//    if(RCHILD(i) < hp->size) {
//        compute_min_connecting_arc(hp, RCHILD(i));
//    }
    //if (hp->size==0){ int i; for (i=0; i<1000; i++) system("pause"); }
    head=hp->elem[0]->id;
}

BASIC_NODE *get_min_connecting_arc(minHeap *hp, int i, V_set *VERTICES)
{

   compute_min_connecting_arc(hp, i);
	if ( VERTICES->V[ head ].f == NULL ) {
		fprintf(stderr, " it's arc is NULL ");
	}

   return &(*VERTICES->V[head].f);

}

BASIC_NODE *getMinConnectingArc ( Multi_Level_Bucket *NsNEG, V_set *VERTICES, int k, int p ) {

	int min = extract_min_vertex( NsNEG, k, p, VERTICES );

	fprintf( stderr, " min = %d\n ", min );

	return &( *VERTICES->V[ min ].f );

}


int get_min_head_connecting_arc(V_set *VERTICES, int n)
{
   return head;
}

int get_min_label_N_s_negate(V_set *VERTICES)
{
   return VERTICES->V[head].label;
}

#endif /* DUAL_SIMPLEX_PROCEDURE_STEP2_H_ */
