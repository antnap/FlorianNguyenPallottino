/*
 * dealloc_all.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_DEALLOC_ALL_H_
#define DUAL_SIMPLEX_PROCEDURE_DEALLOC_ALL_H_

void dealloc_Multi_Level_Bucket(Multi_Level_Bucket *MLB, int p, int k)
{
 int i,j;

 if (MLB->LEVEL!=NULL)
 {
  for (i=0;i<k;i++)
  {
   if (MLB->LEVEL[i].array_bucket_pointer!=NULL)
   {
    for (j=0;j<p;j++)
    {
      if (MLB->LEVEL[i].array_bucket_pointer[j].bucket!=NULL)
      {
       if (MLB->LEVEL[i].array_bucket_pointer[j].bucket->L!=NULL)
       {
        while(MLB->LEVEL[i].array_bucket_pointer[j].bucket->L!=NULL)
        {
         list_node *temp=MLB->LEVEL[i].array_bucket_pointer[j].bucket->L;
         MLB->LEVEL[i].array_bucket_pointer[j].bucket->L=temp->next;
         temp->next=NULL;
         temp->prev=NULL;
         free(temp);
        }
       }
      }
     head_list *temp=MLB->LEVEL[i].array_bucket_pointer[j].bucket;
     MLB->LEVEL[i].array_bucket_pointer[j].bucket=NULL;
     free(temp);
    }
    bucket_record *temp=MLB->LEVEL[i].array_bucket_pointer;
    MLB->LEVEL[i].array_bucket_pointer=NULL;
    free(temp);
   }
  }
  level_record *temp=MLB->LEVEL;
  MLB->LEVEL=NULL;
  free(temp);
 }

 free(MLB);

 return;

}

void dealloc_VERTICES(V_set *VERTICES, int n)
{

 int i;
 for (i=1; i<=n; i++)
 {
  if (VERTICES->V[i].adj!=NULL)
  {
   if (VERTICES->V[i].adj->L!=NULL)
   {
    while (VERTICES->V[i].adj->L!=NULL)
    {
     list_node *temp=VERTICES->V[i].adj->L;
     VERTICES->V[i].adj->L=temp->next;
     temp->next!=NULL;
     temp->prev!=NULL;
     free(temp);
    }
    list_node *temp=VERTICES->V[i].adj->L;
    VERTICES->V[i].adj->L=NULL;
    free(temp);
   }
   head_list *temp=temp=VERTICES->V[i].adj;
   VERTICES->V[i].adj=NULL;
   free(temp);
  }
 }

 node *temp=VERTICES->V;
 VERTICES->V=NULL;
 free(temp);

 free(VERTICES);

 return;

}

void dealloc_Bidimensional_Matrix(int **M, int n, int m)
{

   int i;

   for (i=1; i<=n; i++)
      free(M[i]);

   free(M);

   return;

}

void dealloc_all_Bidimensional_Matrix(int **M1, int **M2, int **M3, int n, int m)
{

   int i;

   for (i=1; i<=n; i++)
   {
      free(M1[i]);
      free(M2[i]);
      free(M3[i]);
   }

   free(M1);
   free(M2);
   free(M3);

   return;

}


void dealloc_NsNotNs(Ns_NotNs *LLL)
{
   if (LLL->N_s!=NULL)
   {
      while(LLL->N_s!=NULL)
      {
         list_node *temp=LLL->N_s;
         LLL->N_s=temp->next;
         temp->next=NULL;
         temp->prev=NULL;
         free(temp);
      }
      list_node *temp=LLL->N_s;
      LLL->N_s=NULL;
      free(temp);
   }
   if (LLL->N_s_negate!=NULL)
   {
      while(LLL->N_s_negate!=NULL)
      {
         list_node *temp=LLL->N_s_negate;
         LLL->N_s_negate=temp->next;
         temp->next=NULL;
         temp->prev=NULL;
         free(temp);
      }
      list_node *temp=LLL->N_s_negate;
      LLL->N_s_negate=NULL;
      free(temp);
   }
   free(LLL);

   return;

}


void dealloc_EDGELISTS(EDGELIST *EL1, EDGELIST *EL2, EDGELIST *EL3, EDGELIST *EL4, EDGELIST *EL5, int n)
{

   int i;
   for (i=1; i<=n*n; i++)
   {

      if (EL1!=NULL)
      {
      EDGENODE *temp=EL1->EDGES[i];
      EL1->EDGES[i]=NULL;
      free(temp);
      }

      if (EL2!=NULL)
      {
      EDGENODE *temp=EL2->EDGES[i];
      EL2->EDGES[i]=NULL;
      free(temp);
      }

      if (EL3!=NULL)
      {
      EDGENODE *temp=EL3->EDGES[i];
      EL3->EDGES[i]=NULL;
      free(temp);
      }

      if (EL4!=NULL)
      {
      EDGENODE *temp=EL4->EDGES[i];
      EL4->EDGES[i]=NULL;
      free(temp);
      }

/*      temp=EL5->EDGES[i];
      EL5->EDGES[i]=NULL;
      free(temp);*/

   }

   if (EL1!=NULL)
   {
   EDGENODE **temp=EL1->EDGES;
   EL1->EDGES=NULL;
   free(temp);
   }

   if (EL2!=NULL)
   {
   EDGENODE **temp=EL2->EDGES;
   EL2->EDGES=NULL;
   free(temp);
   }

   if (EL3!=NULL)
   {
   EDGENODE **temp=EL3->EDGES;
   EL3->EDGES=NULL;
   free(temp);
   }

   if (EL4!=NULL)
   {
   EDGENODE **temp=EL4->EDGES;
   EL4->EDGES=NULL;
   free(temp);
   }

   if (EL5!=NULL)
   {
   EDGENODE **temp=EL5->EDGES;
   EL5->EDGES=NULL;
   free(temp);
   }

   free(EL1);
   free(EL2);
   free(EL3);
   free(EL4);
   free(EL5);

   return;

}

void dealloc_Tinfo(T_info *Ti, T_info *Ti2, int n)
{

   int i;
   for (i=1; i<=n; i++)
   {
      while (Ti[i].child!=NULL)
      {
         list_node *temp=Ti[i].child;
         Ti[i].child=temp->next;
         temp->next=NULL;
         temp->prev=NULL;
         free(temp);
      }
   }

   free(Ti);

   return;

}

void dealloc_TREE(T *TREE)
{

   if (TREE==NULL)return;

   free(TREE);

   dealloc_TREE(TREE->child);

   dealloc_TREE(TREE->bro);

}

void dealloc_heap(minHeap *MH, int n)
{

   int i;

   for (i=0; i<MH->size; i++)
   {
      if (MH->elem!=NULL)
      {
         h_node *temp=MH->elem[i];
         MH->elem[i]=NULL;
         free(temp);
      }
   }

   h_node **temp=MH->elem;
   MH->elem=NULL;
   free(temp);

   free(MH);

}

#endif /* DUAL_SIMPLEX_PROCEDURE_DEALLOC_ALL_H_ */
