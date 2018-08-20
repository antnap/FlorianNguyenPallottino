/*
 * STEP3.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_STEP3_H_
#define DUAL_SIMPLEX_PROCEDURE_STEP3_H_

BASIC_NODE *f;
int min=INT_MAX;

void set_label_in_N_z(T *Tz, V_set *VERTICES, int z)
{

   if (Tz==NULL)return;

   if (VERTICES->V[Tz->id].in_Nz==0)
   {
      VERTICES->V[Tz->id].label=VERTICES->V[z].label;
      VERTICES->V[Tz->id].in_Nz=1;
   }

   set_label_in_N_z(Tz->child, VERTICES, z);

   set_label_in_N_z(Tz->bro, VERTICES, z);

}

void _setLabelInNz ( T *Tz, V_set *VERTICES, int z ) {

   if ( Tz == NULL ) {
	   return;
   }

   if ( VERTICES->V[Tz->id].in_Nz == 0 ) {

	   VERTICES->V[Tz->id].label = VERTICES->V[z].label;
	   VERTICES->V[Tz->id].dist = VERTICES->V[z].dist;
	   VERTICES->V[Tz->id].in_Nz = 1;

   }

   _setLabelInNz ( Tz->child, VERTICES, z );
   _setLabelInNz( Tz->bro, VERTICES, z );

}


int min_label_value=INT_MAX;


void find_label_value(T* Tz, GRAPH *G, V_set *VERTICES, int node, int z)
{

   int j;

   if (Tz==NULL) return;

	 int arc_cost = INT_MAX;
	 int tail = Tz->id;
	 int head = node;
	 int indexHead = -1;

	 for ( j = 0; j < G->deg_[ tail ]; ++j ) {
		 if ( G->FS[ tail ][ j ]->j == head ) {
			 arc_cost = G->FS[ tail ][ j ]->w_ij;
			 indexHead = j;
			 break;
		 }
	 }


      if ( arc_cost != 0 && arc_cost != INT_MAX)
      {

         int compare_value = arc_cost + VERTICES->V[Tz->id].tt-VERTICES->V[node].tt+VERTICES->V[z].label;

         if (min_label_value > compare_value)
         {

            min_label_value=compare_value;

            f = &(*G->FS[ tail ][ indexHead ]);

         }

      }

   find_label_value(Tz->child, G, VERTICES, node, z);

   find_label_value(Tz->bro, G, VERTICES, node, z);

}

void set_notNs_label_less_Nz(minHeap *notNs, T* Tz, V_set *VERTICES, GRAPH *G, int z, int n)
{

   int i, j;

   for (i=0; i<notNs->size; i++)
   {

      if (VERTICES->V[notNs->elem[i]->id].in_Nz==0)
      {

    	 int arc_cost = INT_MAX;
    	 int tail = Tz->id;
    	 int head = notNs->elem[i]->id;
    	 BASIC_NODE *arc = NULL;

    	 for ( j = 0; j < G->deg_[ tail ]; ++j ) {
    		 if ( G->FS[ tail ][ j ]->j == head ) {
    			 arc_cost = G->FS[ tail ][ j ]->w_ij;
    			 arc = &(*G->FS[ tail ][ j ]);
    			 break;
    		 }
    	 }

         if ( arc_cost !=0 && arc_cost !=INT_MAX)
         {

            int compare_value = arc_cost + VERTICES->V[ tail ].tt-VERTICES->V[ head ].tt+VERTICES->V[z].label;

            if (VERTICES->V[ head ].label > compare_value)
            {

               VERTICES->V[ head ].label=compare_value;

               VERTICES->V[ head ].f = &(*arc);

               //fprintf(stderr, "1) label %d set -> (%d, %d) \n", head, arc->i, arc->j);
               //fprintf(stderr, "1) label %d set -> (%d, %d) \n", head, VERTICES->V[ head ].f->i, VERTICES->V[ head ].f->j);

               notNs->elem[i]->label=compare_value;

            }

         }

         find_label_value(Tz->child, G, VERTICES, head, z);

         if (min_label_value < VERTICES->V[ head ].label)
         {

            VERTICES->V[ head ].label=min_label_value;

            VERTICES->V[ head ].f = &(*f);

            //fprintf(stderr, "2) label %d set \n", head);

            notNs->elem[i]->label=min_label_value;

         }

         min_label_value=INT_MAX;
         //f = NULL;

      }

   }

//   for ( int s = 1; s <= G->n; ++s ) {
//       if ( VERTICES->V[ s ].f != NULL ) {
//      	 fprintf(stderr, " head %d has arc\n", s);
//      	 fprintf(stderr, " is this (%d, %d)\n ", VERTICES->V[ s ].f->i, VERTICES->V[ s ].f->j);
//       }
//   }

}

void _setLabelInNsNEG ( Multi_Level_Bucket *NsNEG, T* Tz, V_set *VERTICES, GRAPH *G, int z, int n, int p ){

   int i, j;

   for ( i = 1; i <= G->n; i++ )
   {

      if (VERTICES->V[ i ].in_Nz == 0 ) {

    	 int arc_cost = INT_MAX;
    	 int tail = Tz->id;
    	 int head = i;
    	 BASIC_NODE *arc = NULL;

    	 for ( j = 0; j < G->deg_[ tail ]; ++j ) {
    		 if ( G->FS[ tail ][ j ]->j == head ) {
    			 arc_cost = G->FS[ tail ][ j ]->w_ij;
    			 arc = &(*G->FS[ tail ][ j ]);
    			 break;
    		 }
    	 }

         if ( arc_cost !=0 && arc_cost !=INT_MAX)
         {

            int compare_value = arc_cost + VERTICES->V[ tail ].tt-VERTICES->V[ head ].tt+VERTICES->V[z].label;

            if (VERTICES->V[ head ].label > compare_value)
            {

               VERTICES->V[ head ].label = compare_value;
               VERTICES->V[ head ].dist = compare_value;
               VERTICES->V[ head ].f = &(*arc);

               insert_node_in_MLB( NsNEG, VERTICES, head, p );

            }

         }

         find_label_value( Tz->child, G, VERTICES, head, z );

         if (min_label_value < VERTICES->V[ head ].label)
         {

            VERTICES->V[ head ].label = min_label_value;
            VERTICES->V[ head ].dist = min_label_value;
            VERTICES->V[ head ].f = &(*f);

            insert_node_in_MLB( NsNEG, VERTICES, head, p );

         }

         min_label_value = INT_MAX;
         //f = NULL;

      }

   }

}


T *z_parent=NULL;
T *z_node=NULL;
T *z_node_prev=NULL;

void pred_z_in_TREE(T *TREE, int z)
{
   if (TREE==NULL)return;

   T *parent=TREE;

   if (parent->id==z) { z_parent=parent; return; }
   T *temp=parent->child;
   T *node_prev=NULL;
   while(temp!=NULL)
   {
      if (temp->id==z)
      {
         z_parent=parent;

         z_node=temp;

         z_node_prev=node_prev;

         return;

      }
      node_prev=temp;
      temp=temp->bro;
   }

   pred_z_in_TREE(TREE->child, z);
   pred_z_in_TREE(TREE->bro, z);
}

void add_Tz_to_Ts(T *T_z_pred, T *T_z)
{

   // T_k_pred haven't a child
   if (T_z_pred->child==NULL)
   {
      T_z_pred->child=T_z;
   }
   else
   {
      T_z->bro=T_z_pred->child;
      T_z_pred->child=T_z;
   }
   return;
}


void update_TREE_and_TREEs(T *TREE, T *TREE_s, int z, BASIC_NODE *f, int n)
{

	if (z==TREE_s->id)
	{

		pred_z_in_TREE(TREE, z);

		if (z_parent->id==z)
		{
			z_node=TREE;
			TREE=NULL;
			//       end=1;
		}
		else
		{
			// k is the first brother or the only
			if (z_node_prev==NULL)
			{
				z_parent->child=z_node->bro;
				z_node->bro=NULL;
			}
			// k is the "last" brother
			else if (z_node->bro==NULL && z_node_prev!=NULL)
			{
				z_node_prev->bro=NULL;
			}
			// k is a brother in the middle
			else
			{
				z_node_prev->bro=z_node->bro;
				z_node->bro=NULL;
			}
		}

	}
	else
	{

		pred_z_in_TREE(TREE, z);

		if (z_parent->id==z)
		{

			z_node=TREE;
			TREE=NULL;
			//       end=1;

		}
		else
		{

			// k is the first brother or the only
			if (z_node_prev==NULL)
			{
				z_parent->child=z_node->bro;
				z_node->bro=NULL;
			}
			// k is the "last" brother
			else if (z_node->bro==NULL && z_node_prev!=NULL)
			{
				z_node_prev->bro=NULL;
			}
			// k is a brother in the middle
			else
			{
				z_node_prev->bro=z_node->bro;
				z_node->bro=NULL;
			}

		}

		int pred_z_in_Ts= f->i ;

		if (pred_z_in_Ts==0) {
			add_Tz_to_Ts(TREE_s, z_node);
		}
		else {
//			fprintf(stderr, " else STEP 3 -init \n");
			T *searched = searchInTree(TREE_s, pred_z_in_Ts);
			if ( searched == NULL ) {
				fprintf(stderr, " To search %d - IT IS NULL \n", pred_z_in_Ts);
			}
//			fprintf(stderr, " else STEP 3 -middle \n");
			add_Tz_to_Ts(searchInTree(TREE_s, pred_z_in_Ts), z_node);
//			fprintf(stderr, " else STEP 3 -end \n");
		}

	}

}

void delete_Nz_from_notNs(minHeap *N_s_neg_tree, T *Tz)
{

   if (Tz==NULL) return;

   int i;
   for (i=0; i<N_s_neg_tree->size; i++)
   {
      if (N_s_neg_tree->elem[i]->id==Tz->id)
      {
         h_node *temp=N_s_neg_tree->elem[i];
         N_s_neg_tree->elem[i]->label = INT_MAX;
         N_s_neg_tree->elem[i]=N_s_neg_tree->elem[N_s_neg_tree->size-1];
         N_s_neg_tree->elem[N_s_neg_tree->size-1]=NULL;
         free(temp);
         N_s_neg_tree->size--;
         heapify(N_s_neg_tree, i);
         break;
      }
   }

   delete_Nz_from_notNs(N_s_neg_tree, Tz->child);

   delete_Nz_from_notNs(N_s_neg_tree, Tz->bro);

}

#endif /* DUAL_SIMPLEX_PROCEDURE_STEP3_H_ */
