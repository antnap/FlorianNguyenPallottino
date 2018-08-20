/*
 * MLB_data_structures.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef MLB_DATA_STRUCTURES_H_
#define MLB_DATA_STRUCTURES_H_


/**

    Header with the main basic data-structures used in the algorithm

*/

typedef struct vertex_graph
{
   int id;
   int dist;
   int pred;
   int tt;
   int label;
   BASIC_NODE *f;
   int in_Nz;
   int in_NsNeg;
   struct double_linked_list_head_pointer *adj;
   int numchild;

   /**
       This record represents a vertex of the graph. In the fields of this
       structure we have: the id of the vertex; its distance from the source
       vertex (we consider the case of Dijkstra algorithm); its predecessor in a
       shortest-path (compute by a shortest-path algorithm) from the source to itself;
       an adiancent list that contains all the v vertices that are in its
       Forward Star set;
   */

} node;


typedef struct vertex_set
{
   /**
      This array contains the index of all vertices in the graph. For each element of the array we have
      a pointer to a struct of type vertex_graph.
   */
   struct vertex_graph *V;
} V_set;


typedef struct double_linked_list_element
{
   int v;
   struct double_linked_list_element *prev;
   struct double_linked_list_element *next;
} list_node;


typedef struct double_linked_list_head_pointer
{
  struct double_linked_list_element *L;

  /**

     L is the pointer of the head of the double linked list;

     example:

                                   double
                                   linked
                                    list
                                   element

                                      1  <---------|   2  <---------|   3
                          Nil <---- ____           | _______        | _______
                                 |  |   | n|      |  |   | n|      |  |   | n|
                                 |  | e | e|      |  | e | e|      |  | e | e|
      L                          | p| l | x|      | p| l | x|      | p| l | x|
      |                          | r| e | t|      | r| e | t|      | r| e | t|
      |                          | e| m |  |      | e| m |  |      | e| m |  |
      |                          |_v|___|_ |      |_v|___|_ |      |_v|___|_ |
      |-----------------------------> 1   |----------> 2   |----------> 3   |--------> ...


      each element of the linked list has three fields, the first is a pointer
      to the previous element in the linked list, the third is a pointer to the
      next element in the linked list and the second element is a pointer to
      a vertex_graph record. A double linked list element is descibed in the
      next record.

  */

} head_list;


typedef struct a_bucket_record
{
   struct  double_linked_list_head_pointer *bucket;

   /**
      This record refers to one bucket array, in which each element of the array
      represents a pointer to a structure of type "double linked list".
      In this way for each level 0<=i<=k-1, we have an p-dimensional array.

          LEVEL

            |               <-------------- BUCKETS ---------------->
            |
            V
                                0      1     2                   p-1
          ______             ______ ______ ______              ______
         |      |           |      |      |      |            |      |
     k-1 |   o------------->|      |      |      |............|      |
         |______|           |______|______|______|            |______|
         |      |           |      |      |      |            |      |
     k-2 |   o------------->|      |      |      |............|      |
         |______|           |______|______|______|            |______|

             .                  .      .      .                   .
             .                  .      .      .                   .
             .                  .      .      .                   .
          ______             ______ ______ ______              ______
         |      |           |      |      |      |            |      |
      i  |   o------------->|      |      |      |............|      |
         |______|           |______|______|______|            |______|

             .                  .      .      .                   .
             .                  .      .      .                   .
             .                  .      .      .                   .
          ______             ______ ______ ______              ______
         |      |           |      |      |      |            |      |
      1  |   o------------->|      |      |      |............|      |
         |______|           |______|______|______|            |______|
         |      |           |      |      |      |            |      |
      0  |   o------------->|      |      |      |............|      |
         |______|           |______|______|______|            |______|

   */

} bucket_record;


typedef struct level_record_of_the_structure
{
   struct a_bucket_record *array_bucket_pointer;

   /**

       This data structure represents the level of the M-L-buckets.
       Eache level is a pointer to a structure of type bucket-array.

   */

   int active_bucket;
                           /**
                               for each level, active_bucket is a value that
                               define which bucket in the level is the first
                               that it isn't empty.
                               For instance, at level i for each bucket j such
                               that 0<=j<active_bucket(i), these ones are all
                               empty.
                           */

   int base_distance;
                           /**
                              this variabile says the min value of label distance
                              that might be present in the referenced level.
                           */

   int upper_distance;
                           /**
                              similar to the previous varible but, this indicates
                              the maximum value of label distance that might be
                              present in the referenced level.
                           */

    int num_nodes;
                           /**
                              it indicates the number of nodes that are actually
                              contained in the referenced level.
                           */

} level_record;



typedef struct multi_level_bucket_data_structure
{

   /**
      A pointer that maintains all the Multi-Level Bucket Data structures.
   */

   struct level_record_of_the_structure *LEVEL;

   int actual_level;

} Multi_Level_Bucket;


typedef struct position_in_multi_level_bucket
{
   /**
   This structure contains the coordinates, level and bucket, to access the
   Multi Level Bucket
   */
   int l;
   int b;
} xy_in_MLB;

typedef struct double_vertex_set
{
   struct double_linked_list_element *N_s;
   struct double_linked_list_element *N_s_negate;
   int N_s_number;
   int N_s_negate_number;
} Ns_NotNs;


#endif /* MLB_DATA_STRUCTURES_H_ */
