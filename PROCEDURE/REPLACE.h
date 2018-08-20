/*
 * REPLACE.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_REPLACE_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_REPLACE_H_

void replace (Multi_Level_Bucket *MLB, V_set *set_of_vertex, int id_v, int prev_dist, int p, int k)
{
   /** This function repositions a node from one bucket to another
       when its label-distance is decreased.  */

//   printf("\n\n BEFORE THE REPLACE :::  actual_min_level=%d and active_bucket=%d \n\n", MLB->actual_level, MLB->LEVEL[MLB->actual_level].active_bucket);
//   system("pause");


   if (prev_dist==INT_MAX)
   {
      // Insert node in the structure
      insert_node_in_MLB(MLB, set_of_vertex, id_v, p);

   }
   else
   {

      xy_in_MLB *pos=find_position(MLB, prev_dist, p);
      // Find out the position of the node whose label-distance is decreased

      int new_dist=set_of_vertex->V[id_v].dist;

      int lower_bound=(float)MLB->LEVEL[pos->l].base_distance+(pos->b*(float)pow(p,pos->l));
      int upper_bound=(float)MLB->LEVEL[pos->l].base_distance+((pos->b+1)*(float)pow(p,pos->l))-1;

      if  ( ( new_dist < lower_bound ) )
      {

          // If, after the decrease the label-distance of the node is such that
          // it is not within the range of its current bucket

         // Delete the node from the actual bucket;
         delete_node_from_bucket(MLB, pos, id_v, p);

         /**************************************************************************************/
         /*************************** Find only new bucket position ****************************/
         /**************************************************************************************/
         /**/int range=MLB->LEVEL[pos->l].upper_distance-MLB->LEVEL[pos->l].base_distance+1; /**/
         /**/float x=(float)new_dist-MLB->LEVEL[pos->l].base_distance;                              /**/
         /**/float f=(float)x/range;                                                                /**/
         /**/int new_bucket=floor(f*p);                                                      /**/
         /**************************************************************************************/
         /**************************************************************************************/

         /**************************************************************************************/
         /************************** Try to replace the node in the same level *****************/
         /**************************************************************************************/
         /**/if (new_bucket > MLB->LEVEL[pos->l].active_bucket)                              /**/
         /**/{                                                                               /**/

  //              printf("\n 1) IL node %d viene riposizionato in [%d,%d]\n", id_v, pos->l, pos->b);

         /**/// If it can be replace in the same level, it will be done                      /**/
         /**/   pos->b=new_bucket;                                                           /**/
         /**/   add_in_bucket(MLB, set_of_vertex, pos, id_v, p);                             /**/
         /**/                                                                                /**/
         /**/   if (MLB->LEVEL[pos->l].active_bucket > pos->b)                               /**/
         /**/      MLB->LEVEL[pos->l].active_bucket=pos->b;                                  /**/

//   printf("\n\n AFTER THE REPLACE :::  actual_min_level=%d and active_bucket=%d \n\n", MLB->actual_level, MLB->LEVEL[MLB->actual_level].active_bucket);
//   system("pause");


         /**/                                                                                /**/
         /**/   pos=NULL;                                                                    /**/
         /**/   free(pos);                                                                   /**/
         /**/                                                                                /**/
         /**/   return;                                                                      /**/
         /**/}                                                                               /**/
         /**************************************************************************************/
         /**************************************************************************************/

         pos->l=-1;

         // Otherwise, the node will be replaced in lower levels
         while (1)
         {

            if (pos->l < k)
            {
            // if you have not reached the zero level

               pos->l=pos->l+1;
               // go down one level

               if (new_dist <= MLB->LEVEL[pos->l].upper_distance)
               {

                  /**************************************************************************************/
                  /*************************** Find only new bucket position ****************************/
                  /**************************************************************************************/
                  /**/range=MLB->LEVEL[pos->l].upper_distance-MLB->LEVEL[pos->l].base_distance+1;     /**/
                  /**/x=(float)new_dist-MLB->LEVEL[pos->l].base_distance;                             /**/
                  /**/f=(float)x/range;                                                               /**/
                  /**/int new_bucket=floor(f*p);                                                      /**/                                                /**/
                  /**************************************************************************************/
                  /**************************************************************************************/

                  // ADD THE NODE IN THE ACTUAL LEVEL
                  /**************************************************************************************/
                  /**************************************************************************************/
                  /**/                                                                                /**/
                  /**/   pos->b=new_bucket;                                                           /**/


                  /**/   add_in_bucket(MLB, set_of_vertex, pos, id_v, p);                             /**/
                  /**/                                                                                /**/

//                printf("\n 2) IL node %d viene riposizionato in [%d,%d]\n", id_v, pos->l, pos->b);

                  /**/   if (MLB->actual_level>pos->l) MLB->actual_level=pos->l;                      /**/

                  /**/   if (MLB->LEVEL[pos->l].active_bucket > pos->b)
                  /**/      MLB->LEVEL[pos->l].active_bucket=pos->b;

//   printf("\n\n AFTER THE REPLACE :::  actual_min_level=%d and active_bucket=%d \n\n", MLB->actual_level, MLB->LEVEL[MLB->actual_level].active_bucket);
//   system("pause");

                  /**/                                                                                /**/
                  /**/   pos=NULL;                                                                    /**/
                  /**/   free(pos);                                                                   /**/
                  /**/                                                                                /**/
                  /**/   return;                                                                      /**/
                  /**/                                                                                /**/
                  /**************************************************************************************/
                  /**************************************************************************************/

               }

            }

         }

      }

      else if ( new_dist >= lower_bound && new_dist <= upper_bound )
      {

         // Delete the node from the actual bucket;
         delete_node_from_bucket(MLB, pos, id_v, p);

         // Add the node in the actual bucket;
         add_in_bucket(MLB, set_of_vertex, pos, id_v, p);

//                printf("\n 3) IL node %d viene riposizionato in [%d,%d]\n", id_v, pos->l, pos->b);

            if (MLB->LEVEL[pos->l].active_bucket > pos->b)
               MLB->LEVEL[pos->l].active_bucket=pos->b;

//   printf("\n\n AFTER THE REPLACE :::  actual_min_level=%d and active_bucket=%d \n\n", MLB->actual_level, MLB->LEVEL[MLB->actual_level].active_bucket);
//   system("pause");

         pos=NULL;

         free(pos);

         return;

      }

   }

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_REPLACE_H_ */
