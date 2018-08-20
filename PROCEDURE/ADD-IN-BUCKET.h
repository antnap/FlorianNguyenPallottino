/*
 * ADD-IN-BUCKET.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_ADD_IN_BUCKET_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_ADD_IN_BUCKET_H_

void add_in_bucket(Multi_Level_Bucket *MLB, V_set *set_of_vertex, xy_in_MLB *pos, int id_incoming_vertex, int p)
{

   /**
      INPUT:
            - MLB, is the pointer to the multi level bucket
            - set_of_vertex, the set of the vertices of the graph;
            - pos, is the position where the node will be inserted;
            - in_incoming_vertex, is the id of the node that will be inserted;
            - p is the number of bucket for level;
   */

   /************************************************************************************/
   /******************** Creation of the node that will be inserted ********************/
   /************************************************************************************/
   /**/list_node *n=(list_node *)malloc(sizeof(list_node));                          /**/
   /**/n->v=id_incoming_vertex;                                                      /**/
   /**/n->next=NULL;                                                                 /**/
   /**/n->prev=NULL;                                                                 /**/
   /************************************************************************************/
   /************************************************************************************/

   // IF THE LEVEL WHERE THE NODE WILL BE INSERTED IS EMPTY BUILD A NEW LEVEL
   /************************************************************************************/
   /**************************** BUILD NEW LEVEL ***************************************/
   /************************************************************************************/
   /**/if (MLB->LEVEL[pos->l].array_bucket_pointer==NULL)                            /**/
   /**/{                                                                             /**/
   /**/// if the level is empty then we must build the array of bucket               /**/
   /**/                                                                              /**/
   /**/   MLB->LEVEL[pos->l].array_bucket_pointer=build_array_of_bucket(p);          /**/
   /**/// The algorithm builds a p-dimensional bucket array at the level pos.l       /**/
   /**/}                                                                             /**/
   /************************************************************************************/
   /************************************************************************************/

   // IF THE BUCKET WHERE THE NODE WILL BE INSERTED IS EMPTY BUILD NEW BUCKET
   /******************************************************************************************************************/
   /************************************************** INSERTION OF THE FIRST NODE ***********************************/
   /******************************************************************************************************************/
   /**/if (MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket==NULL)                                           /**/
   /**/{                                                                                                           /**/
   /** First we check if the bucket is empty. If so the algorithm                                                   **/
   /** builds a new double linked list.                                                                             **/
   /**/   MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket=(head_list*)malloc(sizeof(head_list));            /**/
   /**/   MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L=n;                                             /**/
   /**/   n=NULL;                                                                                                  /**/
   /**/   free(n);                                                                                                 /**/
   /**/                                                                                                            /**/
   /**/   // INCREASE THE NUMBER OF NODE IN THE LEVEL AND UPDATE THE ACTIVE BUCKET IF NECESSARY                    /**/
   /**/   if (MLB->LEVEL[pos->l].active_bucket > pos->b)                                                           /**/
   /**/      MLB->LEVEL[pos->l].active_bucket=pos->b;                                                              /**/
   /**/   MLB->LEVEL[pos->l].num_nodes=MLB->LEVEL[pos->l].num_nodes+1;                                             /**/
   /**/                                                                                                            /**/
   /**/   return;                                                                                                  /**/
   /**/}                                                                                                           /**/
   /******************************************************************************************************************/
   /******************************************************************************************************************/

   /*********************************************************************************************************************/
   /******** Otherwise, it will be necessary to build a new node and append it to those already in the bucket ***********/
   /*********************************************************************************************************************/
   /*********************************************************************************************************************/

   list_node *temp=MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L;
   int inco_dist=set_of_vertex->V[id_incoming_vertex].dist;


   // Scan the list
   while (temp->next!=NULL)//  <------------------------------------------|
   {//                                                                    |
      /** Scanning can end in two cases:                                  |
             - I      : An element in the list is greater than v; --------|---|
             - II     : All the list is scanned. -------------------------|   |
      *///                                                                    |
      if (set_of_vertex->V[temp->v].dist >= inco_dist) break;//  <------------|
         temp=temp->next;

   }

   /** The element can be inserted in three different ways in the list:
          - First:  "ahead" if v is less than all;
          - Second: "at the end" if v is greater than all;
          - Third:  "in the middle", otherwise.
   */


   if (set_of_vertex->V[temp->v].dist >= inco_dist && temp->prev==NULL)     // First
   {
      MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L=n;
      n->next=temp;
      temp->prev=n;
      temp=NULL;free(temp);
      n=NULL;free(n);

      // INCREASE THE NUMBER OF NODE IN THE LEVEL
      MLB->LEVEL[pos->l].num_nodes=MLB->LEVEL[pos->l].num_nodes+1;

      return;
   }

   if (set_of_vertex->V[temp->v].dist < inco_dist && temp->next==NULL)      // Second
   {
      temp->next=n;
      n->prev=temp;
      temp=NULL;free(temp);
      n=NULL;free(n);

      // INCREASE THE NUMBER OF NODE IN THE LEVEL
      MLB->LEVEL[pos->l].num_nodes=MLB->LEVEL[pos->l].num_nodes+1;

      return;
   }

   n->next=temp;                                      // Third
   n->prev=temp->prev;
   temp->prev->next=n;
   temp->prev=n;
   temp=NULL;free(temp);
   n=NULL;free(n);

   // INCREASE THE NUMBER OF NODE IN THE LEVEL
   MLB->LEVEL[pos->l].num_nodes=MLB->LEVEL[pos->l].num_nodes+1;

   return;

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_ADD_IN_BUCKET_H_ */
