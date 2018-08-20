/*
 * manageMLB.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_MANAGEMLB_H_
#define DUAL_SIMPLEX_MANAGEMLB_H_

/**

   Header with Functions for "creation" and "management" of Multi-Level Bucket

*/



int defineNumberOfLevels(int n, int m, int Cmax)
{

   /**
      Based on empirical results, this function tries to find the appropriate
      number of levels of the Multi-Level-Bucket. Its heuristics is based on:
             - n   : number of vertices;
             - m   : number of edges;
             - Cmax: i.e. max weight in the graph;
   */


    double k=ceil(2*log(Cmax)/log(log(Cmax)));

    return (int)k;

}

int defineBucketsNumberForLevel(int Cmax, int k)
{

    /**
       Input :
             - Cmax : max weight, of an edge, in the graph;
             - k    : levels number of the Multi-Level Bucket

       Output :
              - p   : buckets number for levele of the Multi-Level Bucket.
                      For each level 0<=i<=k-1 the structure has "p" buckets,
                      each bucket is labeled with an index 0<=j<=p-1.
    */

    return ceil((float)pow(Cmax,(float)1/k));

}

level_record *allocateLevels(int k, int p)
{
   /**
    This function build the levels of the structures and assigns their initial
    values. In particular, this function builds:
      - an k-dimensional array with k bucket_level elements. Each of these
        elements contains:
           - a bucket_array pointer, i.e. a pointer of an array of buckets
             elements;
           - a base_distance variable;
           - an upper_distance variable;
           - a num_nodes_variable;

      FOR MORE DETAILS ABOUTS THE STRUCTURES, REFER TO THE HEADER FILE
      "MLB_data_structures.h", in the folder "Header".
    */

    level_record *LEVELS=(level_record *)malloc(k*sizeof(level_record));
    // Allocates k bucket_level elements;

    int i;

    for (i=0; i<k; i++)
    {

       LEVELS[i].array_bucket_pointer=NULL;
       // Set to NULL the pointer to array of buckets

       LEVELS[i].active_bucket=p;
       // At firts, all the bucket arraies are empty, so, for each levels,
       // no one bucket is active.

       LEVELS[i].base_distance=0;
       // At first all base distance are equal to zero


       LEVELS[i].upper_distance=(LEVELS[i].base_distance+(float)pow(p, i+1))-1;
       // The upper level is set to, Ui <- Bi + p^(i+1)-1;

       LEVELS[i].num_nodes=0;
       // Since all the buckets are empty, the levels do not contain any node.

    }

    return LEVELS;

}

#endif /* DUAL_SIMPLEX_MANAGEMLB_H_ */
