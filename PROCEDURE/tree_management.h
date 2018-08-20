/*
 * tree_management.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_TREE_MANAGEMENT_H_
#define DUAL_SIMPLEX_PROCEDURE_TREE_MANAGEMENT_H_

typedef struct tree_informations
{
   int id;
   int num_child;
   struct double_linked_list_element *child;
} T_info;

typedef struct tree
{
   int id;
   struct tree *child;
   struct tree *bro;
} T;

T_info *build_tree_informations(V_set *VERTICES, list_node *N_z, int n)
{
   int i;
   T_info *T_i=(T_info *)malloc((n+1)*sizeof(T_info));
   for (i=1; i<=n; i++)
   {
      T_i[i].num_child=0;
      T_i[i].child=NULL;
   }
   list_node *temp=N_z;
   while (temp!=NULL)
   {
      T_i[temp->v].id=temp->v;
      if (VERTICES->V[temp->v].pred!=0)
      {
         T_i[VERTICES->V[temp->v].pred].num_child++;
         list_node *new_node=(list_node *)malloc(sizeof(list_node));
         new_node->v=temp->v;
         new_node->prev=NULL;
         new_node->next=NULL;
         if (T_i[VERTICES->V[temp->v].pred].child==NULL)
         {
            T_i[VERTICES->V[temp->v].pred].child=new_node;
         }
         else
         {
            new_node->next=T_i[VERTICES->V[temp->v].pred].child;
            T_i[VERTICES->V[temp->v].pred].child->prev=new_node;
            T_i[VERTICES->V[temp->v].pred].child=new_node;
         }
         new_node=NULL;
         free(new_node);
     }
     temp=temp->next;
   }
   return T_i;
}

T_info *build_tree_info(V_set *VERTICES, list_node *N_z, list_node *N_z_negate, int n)
{
   int i;
   T_info *T_i=(T_info *)malloc((n+1)*sizeof(T_info));
   for (i=1; i<=n; i++)
   {
      T_i[i].num_child=0;
      T_i[i].child=NULL;
   }
   list_node *temp=N_z;
   while (temp!=NULL)
   {
      T_i[temp->v].id=temp->v;
      if (VERTICES->V[temp->v].pred!=0)
      {
         T_i[VERTICES->V[temp->v].pred].num_child++;
         list_node *new_node=(list_node *)malloc(sizeof(list_node));
         new_node->v=temp->v;
         new_node->prev=NULL;
         new_node->next=NULL;
         if (T_i[VERTICES->V[temp->v].pred].child==NULL)
         {
            T_i[VERTICES->V[temp->v].pred].child=new_node;
         }
         else
         {
            new_node->next=T_i[VERTICES->V[temp->v].pred].child;
            T_i[VERTICES->V[temp->v].pred].child->prev=new_node;
            T_i[VERTICES->V[temp->v].pred].child=new_node;
         }
         new_node=NULL;
         free(new_node);
     }
     temp=temp->next;
   }

   temp=N_z_negate;
   while (temp!=NULL)
   {
      T_i[temp->v].id=temp->v;
      if (VERTICES->V[temp->v].pred!=0)
      {
         T_i[VERTICES->V[temp->v].pred].num_child++;
         list_node *new_node=(list_node *)malloc(sizeof(list_node));
         new_node->v=temp->v;
         new_node->prev=NULL;
         new_node->next=NULL;
         if (T_i[VERTICES->V[temp->v].pred].child==NULL)
         {
            T_i[VERTICES->V[temp->v].pred].child=new_node;
         }
         else
         {
            new_node->next=T_i[VERTICES->V[temp->v].pred].child;
            T_i[VERTICES->V[temp->v].pred].child->prev=new_node;
            T_i[VERTICES->V[temp->v].pred].child=new_node;
         }
         new_node=NULL;
         free(new_node);
     }
     temp=temp->next;
   }
   return T_i;
}


void TH(T *TREE)
{
   if(TREE==NULL)return;

   printf(" %d ", TREE->id);

   TH(TREE->child);
   TH(TREE->bro);
}

void postorder(T *TREE)
{
   TH(TREE->child);

   if(TREE==NULL)return;

   printf(" %d ", TREE->id);

   TH(TREE->bro);
}


T *searchInTree(T *TREE, int node)
{
   if (TREE==NULL) return NULL;
   if (TREE->id==node) return TREE;
   T *t=searchInTree(TREE->child, node);
   if (t==NULL)
      t=searchInTree(TREE->bro, node);
   return t;
}

T *createTreeNode(int node)
{
   T *newnode=(T*)malloc(sizeof(T));
   newnode->child=NULL;
   newnode->bro=NULL;
   newnode->id=node;
   return newnode;
}


/**
T *buildTree(T_info *T_i, list_node *N_z, list_node *N_z_n, V_set *VERTICES)
{

   T *root=NULL;

   list_node *temp=N_z;
   list_node *temp2=N_z_n;

   while (temp!=NULL)
   {
      T *newnode=searchInTree(root, temp->v);
      if (newnode==NULL)
         newnode=createTreeNode(temp->v);

      T *parent=newnode;
      int j;
      list_node *aux;
      if (T_i[temp->v].num_child>0)
      {
         aux=T_i[temp->v].child;
         parent->child=createTreeNode(aux->v);
         parent=parent->child;
         aux=aux->next;
      }
      for (j=2; j<=T_i[temp->v].num_child; j++)
      {
         parent->bro=createTreeNode(aux->v);
         parent=parent->bro;
         aux=aux->next;
      }
      if (root==NULL)
         root=newnode;

      temp=temp->next;
      newnode=NULL;free(newnode);
      aux=NULL; free(aux);
      parent=NULL; free(parent);

   }

   while (temp2!=NULL)
   {
      T *newnode=searchInTree(root, temp2->v);
      if (newnode==NULL)
         newnode=createTreeNode(temp2->v);

      T *parent=newnode;
      int j;
      list_node *aux;
      if (T_i[temp2->v].num_child>0)
      {
         aux=T_i[temp2->v].child;
         parent->child=createTreeNode(aux->v);
         parent=parent->child;
         aux=aux->next;
      }
      for (j=2; j<=T_i[temp2->v].num_child; j++)
      {
         parent->bro=createTreeNode(aux->v);
         parent=parent->bro;
         aux=aux->next;
      }
      if (root==NULL)
         root=newnode;

      temp2=temp2->next;
      newnode=NULL;free(newnode);
      aux=NULL; free(aux);
      parent=NULL; free(parent);

   }

   return root;

}
*/

/*
T *buildTree(T_info *T_i, V_set *VERTICES)
{

   T *root=NULL;

   int i=n;

   while (i>0)
   {
      T *newnode=searchInTree(root, VERTICES->V[i].id);
      if (newnode==NULL)
         newnode=createTreeNode(VERTICES->V[i].id);

         printf("\n newnode=%d \n", newnode->id);

      T *parent=newnode;
      int j;
      list_node *aux;
      if (T_i[VERTICES->V[i].id].num_child>0)
      {
         aux=T_i[VERTICES->V[i].id].child;
         parent->child=createTreeNode(aux->v);
         parent=parent->child;
         aux=aux->next;
      }
      for (j=2; j<=T_i[VERTICES->V[i].id].num_child; j++)
      {
         parent->bro=createTreeNode(aux->v);
         parent=parent->bro;
         aux=aux->next;
      }
      if (root==NULL)
         root=newnode;

      newnode=NULL;free(newnode);
      aux=NULL; free(aux);
      parent=NULL; free(parent);

      system("pause");

      i--;

   }

   return root;

}

*/


T *buildSubTree(T *root, T_info *T_i, V_set *VERTICES, int i)
{

      T *newnode=searchInTree(root, VERTICES->V[i].id);
      if (newnode==NULL)
         newnode=createTreeNode(VERTICES->V[i].id);

      T *parent=newnode;
      int j;
      list_node *aux;
      if (T_i[VERTICES->V[i].id].num_child>0)
      {
         aux=T_i[VERTICES->V[i].id].child;
         parent->child=createTreeNode(aux->v);
         parent=parent->child;
         aux=aux->next;
      }
      for (j=2; j<=T_i[VERTICES->V[i].id].num_child; j++)
      {
         parent->bro=createTreeNode(aux->v);
         parent=parent->bro;
         aux=aux->next;
      }


      return newnode;

}

void add_sub_trees(T *TREE, T_info *T_i, V_set *VERTICES, int *added)
{

   if(TREE==NULL)return;

   if (added[TREE->id]==0)
   {
      TREE=buildSubTree(TREE, T_i, VERTICES, TREE->id);
      added[TREE->id]=1;
   }

   add_sub_trees(TREE->child, T_i, VERTICES, added);

   add_sub_trees(TREE->bro, T_i, VERTICES, added);

}

T *buildTree(T_info *T_i, V_set *VERTICES, int r, int n)
{

   T *TREE=NULL;

   int i;
   int *added=(int *)malloc((n+1)*sizeof(int));
   for (i=1; i<=n; i++) added[i]=0;

   TREE=buildSubTree(TREE, T_i, VERTICES, r);

   added[r]=1;

   T *temp=TREE;

   add_sub_trees(temp, T_i, VERTICES, added);

   return TREE;
}

/*
T *buildTree(T_info *T_i, V_set *VERTICES, int r)
{

   T *root=NULL;

   int i=r;

      T *newnode=searchInTree(root, VERTICES->V[i].id);
      if (newnode==NULL)
         newnode=createTreeNode(VERTICES->V[i].id);

         printf("\n newnode=%d \n", newnode->id);

      T *parent=newnode;
      int j;
      list_node *aux;
      if (T_i[VERTICES->V[i].id].num_child>0)
      {
         aux=T_i[VERTICES->V[i].id].child;
         parent->child=createTreeNode(aux->v);
         parent=parent->child;
         aux=aux->next;
      }
      for (j=2; j<=T_i[VERTICES->V[i].id].num_child; j++)
      {
         parent->bro=createTreeNode(aux->v);
         parent=parent->bro;
         aux=aux->next;
      }
      root=newnode;

      newnode=NULL;free(newnode);
      aux=NULL; free(aux);
      parent=NULL; free(parent);

   while (1)
   {

   }


   return root;

}


int *build_tree_vector(int n, V_set *VERTICES)
{
   int *F=(int *)malloc(((n*n)+1)*sizeof(int));

   int i;

   for (i=1; i<=n*n; i++) F[i]=0;

   for (i=1; i<=n; i++)
   {
      if (VERTICES->V[i].pred!=0)
      {
         int pos=((VERTICES->V[i].pred*n)-n)+i;
         F[pos]=VERTICES->V[i].pred;
      }
   }

   return F;
}

int *build_tree_vector_new_source(list_node *l, int n, V_set *VERTICES)
{

   int *F=(int *)malloc(((n*n)+1)*sizeof(int));

   int i;

   for (i=1; i<=n*n; i++) F[i]=0;

   list_node *temp=l->next;

   while(temp!=NULL)
   {
      int pos=((VERTICES->V[temp->v].pred*n)-n)+temp->v;
      F[pos]=VERTICES->V[temp->v].pred;
      temp=temp->next;
   }

   temp=NULL;
   free(temp);

   return F;

}
/**
int *build_T_z_from_heap(int *T_z, int i, minHeap *hp, int n)
{
    if(LCHILD(i) < hp->size) {
        build_T_z_from_heap(T_z, LCHILD(i), N_s_neg_tree);
    }
    int pos=((VERTICES[hp->elem[i]->id].pred*n)-n)+hp->elem[i]->id;
    T_z[pos]=VERTICES[hp->elem[i]->id].pred;
    if(RCHILD(i) < hp->size) {
        build_T_z_from_heap(T_z, RCHILD(i), N_s_neg_tree);
    }
    return T_z;
}

int *build_T_z(int *T_z, minHeap *hp, int n)
{
   return build_T_z_from_heap(T_z, 0, hp, n);
}
*/

#endif /* DUAL_SIMPLEX_PROCEDURE_TREE_MANAGEMENT_H_ */
