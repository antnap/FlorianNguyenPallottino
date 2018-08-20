/*
 * BUILD-ARRAY-OF-BUCKET.h
 *
 *  Created on: 11 lug 2016
 *      Author: antonio
 */

#ifndef DIJKSTRA_PROCEDURE_MANAGEMENT_BUILD_ARRAY_OF_BUCKET_H_
#define DIJKSTRA_PROCEDURE_MANAGEMENT_BUILD_ARRAY_OF_BUCKET_H_

bucket_record *build_array_of_bucket(int p)
{

     bucket_record *b=malloc(p*sizeof(bucket_record));

     int i;

     for (i=0; i<p; i++)
     {
        b[i].bucket=(head_list *)malloc(sizeof(head_list));
        b[i].bucket=NULL;
     }

     return b;

}


#endif /* DIJKSTRA_PROCEDURE_MANAGEMENT_BUILD_ARRAY_OF_BUCKET_H_ */
