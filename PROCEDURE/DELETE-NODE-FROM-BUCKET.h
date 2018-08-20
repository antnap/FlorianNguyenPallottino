/*
 * DELETE-NODE-FROM-BUCKET.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_DELETE_NODE_FROM_BUCKET_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_DELETE_NODE_FROM_BUCKET_H_

void delete_node_from_bucket(Multi_Level_Bucket *MLB, xy_in_MLB *pos, int id_v, int p)
{
   /**
      This function delete a node from a bucket;
   */

   /** The node that will be cancelled from a bucket, can be in three
      different position:
             - First: it's the first element of the list;
                   - Special case, if the list become NULL, it will be necessary delete the
                     bucket, in this case it could be necessary update the active bucket.
                     If, after the deletetion of the node, the number node in the level become
                     equal to zero, it will be necessary delete all the level.
             - Second: it's the last element of the list;
             - Third: it's in the middle of the list;
   */

   // DECREASE THE NUMBER OF NODES IN THE LEVEL
   /**************************************************************************************/
   /**************************************************************************************/
   /**/MLB->LEVEL[pos->l].num_nodes=MLB->LEVEL[pos->l].num_nodes-1;                    /**/
   /**************************************************************************************/
   /**************************************************************************************/

   list_node *temp=MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L;

   while(1)
   {
      if (temp->v==id_v) break;

      temp=temp->next;
   }

/*   if (pos->l==3 && pos->b==1)
   {
      printf("\n*********************** \n");
      printf("*********************** \n");
      list_node *t1=MLB->LEVEL[3].array_bucket_pointer[1].bucket->L;
      while(t1!=NULL)
      {
         printf(" %d ", t1->v);
         t1=t1->next;
      }
      printf("\n*********************** \n");
      printf("*********************** \n");
   }
*/

   /******************************************************************************************/
   /*****************************   FIRST  ***************************************************/
   /********** the node must be cancelled from the first position ****************************/
   /******************************************************************************************/
   /**/if (temp->prev==NULL)                                                               /**/
   /**/{                                                                                   /**/
   /**/    if (temp->next==NULL)                                                           /**/
   /**/    {                                                                               /**/
   /**/       // ***SPECIAL CASE*** THE LIST BECOME NULL                                   /**/
   /**/       MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L=NULL;              /**/
   /**/       free(temp);                                                                  /**/
   /**/                                                                                    /**/
   /**/       // DELETE THE BUCKET!!!                                                      /**/
   /**/       head_list *hl=MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket;        /**/
   /**/       MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket=NULL;                 /**/
   /**/       free(hl);                                                                    /**/
   /**/                                                                                    /**/
   /**/       // DELETE ALL THE LEVEL IF IT BECOME NULL                                    /**/
   /**/       if (MLB->LEVEL[pos->l].num_nodes==0)                                         /**/
   /**/       {                                                                            /**/
   /**/          MLB->LEVEL[pos->l].active_bucket=p;                                       /**/
   /**/          bucket_record *br=MLB->LEVEL[pos->l].array_bucket_pointer;                /**/
   /**/          MLB->LEVEL[pos->l].array_bucket_pointer=NULL;                             /**/
   /**/          free(br);                                                                 /**/
   /**/       }                                                                            /**/
   /**/       // OTHERWISE, SINCE THE BUCKET IS EMPTY BUT NOT THE LEVEL, IT IS NECESSARY   /**/
   /**/       // TO FIND A NEW ACTIVE BUCKET                                               /**/
   /**/       else                                                                         /**/
   /**/       {                                                                            /**/
   /**/          if (pos->b == MLB->LEVEL[pos->l].active_bucket)                           /**/
   /**/          {                                                                         /**/
   /**/             int i=pos->b;                                                          /**/
   /**/             while(1)                                                               /**/
   /**/             {                                                                      /**/
   /**/                if (MLB->LEVEL[pos->l].array_bucket_pointer[i].bucket!=NULL)        /**/
   /**/                {                                                                   /**/
   /**/                   MLB->LEVEL[pos->l].active_bucket=i;                              /**/
   /**/                   break;                                                           /**/
   /**/                }                                                                   /**/
   /**/                i=i+1;                                                              /**/
   /**/             }                                                                      /**/
   /**/          }                                                                         /**/
   /**/        }                                                                           /**/
   /**/        return;                                                                     /**/
   /**/    }                                                                               /**/
   /**/                                                                                    /**/
   /**/   MLB->LEVEL[pos->l].array_bucket_pointer[pos->b].bucket->L=temp->next;            /**/
   /**/   temp->next->prev=NULL;                                                           /**/
   /**/   free(temp);                                                                      /**/
   /**/   return;                                                                          /**/
   /**/}                                                                                   /**/
   /******************************************************************************************/
   /******************************************************************************************/

   /*******************************************************************************/
   /*****************************   SECOND  ***************************************/
   /********** the node must be cancelled from the last position ******************/
   /*******************************************************************************/
   /**/if (temp->next==NULL)                                                    /**/
   /**/{                                                                        /**/
   /**/   temp->prev->next=NULL;                                                /**/
   /**/   temp->prev=NULL;                                                      /**/
   /**/   free(temp);                                                           /**/
   /**/   return;                                                               /**/
   /**/}                                                                        /**/
   /*******************************************************************************/
   /*******************************************************************************/

   /*******************************************************************************/
   /*****************************   THIRD  ****************************************/
   /********** the node must be cancelled from a middle position ******************/
   /*******************************************************************************/
   /**/temp->prev->next=temp->next;                                             /**/
   /**/temp->next->prev=temp->prev;                                             /**/
   /**/temp->next=NULL;                                                         /**/
   /**/temp->prev=NULL;                                                         /**/
   /**/free(temp);                                                              /**/
   /**/return;                                                                  /**/
   /*******************************************************************************/
   /*******************************************************************************/

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_DELETE_NODE_FROM_BUCKET_H_ */
