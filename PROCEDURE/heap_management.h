/*
 * heap_management.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_HEAP_MANAGEMENT_H_
#define DUAL_SIMPLEX_PROCEDURE_HEAP_MANAGEMENT_H_

#define LCHILD(x) 2 * x + 1
#define RCHILD(x) 2 * x + 2
#define PARENT(x) x/2

typedef struct h_node
{
   int id;
   int label;
   int edge_label;
} h_node;

typedef struct minHeap
{
   int size;
   h_node **elem;
} minHeap;

void insert_heap_node(minHeap *hp, int id, int l, int edge)
{
   if (hp->size)
   {
      hp->elem=realloc(hp->elem, (hp->size+1) * sizeof(h_node*));
   }
   else
   {
      hp->elem=malloc(sizeof(h_node*));
   }

   h_node *nd;
   nd=(h_node *)malloc(sizeof(h_node));
   nd->id=id;
   nd->label=l;
   nd->edge_label=edge;

   int i=(hp->size)++;

   while (i && nd->label < hp->elem[PARENT(i)]->label)
   {
      hp->elem[i] = hp->elem[PARENT(i)];
      i=PARENT(i);
   }
   hp->elem[i]=nd;
}

void swap(h_node *n1, h_node *n2)
{
   h_node *temp=n1;
   n1=n2;
   n2=temp;
}

void heapify(minHeap *hp, int i) {

    int smallest = (LCHILD(i) < hp->size && hp->elem[LCHILD(i)]->label < hp->elem[i]->label) ? LCHILD(i) : i ;
    if(RCHILD(i) < hp->size && hp->elem[RCHILD(i)]->label < hp->elem[smallest]->label) {
        smallest = RCHILD(i) ;
    }

    if(smallest != i) {

//        swap(hp->elem[i], hp->elem[smallest]);
        h_node *nd=hp->elem[i];
        hp->elem[i]=hp->elem[smallest];
        hp->elem[smallest]=nd;
        nd=NULL; free(nd);
        heapify(hp, smallest) ;
    }

}

/**
void heapify(minHeap *hp, int i)
{
   int k=i
   if (2*i+1<hp->size && hp->elem[2*i+1]->label < hp->elem[k]->label);
 then k=2j+1
 if 2j = n and A[2j] < A[k]
 then k=2j
 if k ? j
 then t=A[j], A[j]=A[k], A[k]=t
 Min_Heapify(A,k,n)
}
*/

void inorderTraversal(minHeap *hp, int i) {
    if(LCHILD(i) < hp->size) {
        inorderTraversal(hp, LCHILD(i)) ;
    }
    printf("%d ", hp->elem[i]->label) ;
    if(RCHILD(i) < hp->size) {
        inorderTraversal(hp, RCHILD(i)) ;
    }
}

minHeap *buildMinHeap(minHeap *hp, list_node *N_s_negate, V_set *VERTICES, int size) {

    list_node *temp=N_s_negate;

    hp=(minHeap *)malloc(sizeof(minHeap));
    hp->size=0;
    hp->elem=(h_node **)malloc(size*sizeof(h_node *));
    int i;
    for (i=0; i<size; i++) hp->elem[i]=NULL;

    for(i=0; temp!=NULL; temp=temp->next, i++)
    {
        h_node *nd=(h_node *)malloc(sizeof(h_node));
        nd->id = temp->v;
        nd->label=VERTICES->V[temp->v].label;
        nd->edge_label=0;
        if (hp->elem[i]==NULL) hp->elem[i]=(h_node*)malloc(sizeof(h_node));
        hp->elem[i]=nd;
        hp->size++;
    }

    // Making sure that heap property is also satisfied
    for(i = (hp->size - 1) / 2; i >= 0; i--) {
        heapify(hp, i);
    }

    return hp;

}

#endif /* DUAL_SIMPLEX_PROCEDURE_HEAP_MANAGEMENT_H_ */
