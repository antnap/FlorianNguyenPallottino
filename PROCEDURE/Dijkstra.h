/*
 * Dijkstra.h
 *
 *  Created on: 23 apr 2016
 *      Author: antonio
 */

#ifndef DUAL_SIMPLEX_PROCEDURE_DIJKSTRA_H_
#define DUAL_SIMPLEX_PROCEDURE_DIJKSTRA_H_

void Dijkstra(V_set *VERTICES, Multi_Level_Bucket *MLB, int **W, int n, int m, int p, int k, int source)
{
   VERTICES->V[source].dist=0;
   VERTICES->V[source].pred=0;

   MLB->actual_level=0;

   insert_node_in_MLB(MLB, VERTICES, source, p);

   while (MLB->actual_level < k)
   {

      int u=search(MLB, k, p, VERTICES);
/*
      printf("\n\n Il minimo nodo estratto e' %d\n", u);

      printf("\n\n actual_level %d active_bucket=%d\n\n", MLB->actual_level, MLB->LEVEL[MLB->actual_level].active_bucket);
      system("pause");

      system("pause");*/

      if (u!=0)
      {

         list_node *adj_u=VERTICES->V[u].adj->L;

         while (adj_u!=NULL)
         {

            int alt=VERTICES->V[u].dist+W[u][adj_u->v];

            if (alt < VERTICES->V[adj_u->v].dist)
            {

/*               printf("\n\n La distanza del nodo adiacente a %d : %d viene aggiornata a %d ", u, adj_u->v, alt);

               system("pause");                    */

               int prev_dist=VERTICES->V[adj_u->v].dist;
               VERTICES->V[adj_u->v].dist=alt;
               VERTICES->V[adj_u->v].pred=u;

               replace (MLB, VERTICES, adj_u->v, prev_dist, p, k);

            }

            adj_u=adj_u->next;

         }

         adj_u=NULL;
         free(adj_u);

      }

   }

}

#endif /* DUAL_SIMPLEX_PROCEDURE_DIJKSTRA_H_ */
