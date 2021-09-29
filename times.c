/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.c"
#include <time.h>
#include <stdlib.h>
#include <limits.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime){
  int i, minob = INT_MAX, maxob = INT_MIN, ob, num_ob=0;
  int** perms = generate_permutations(n_perms, N);
  clock_t start, end, total;

  if (perms == NULL){
    free(perms);
    return ERR;
  }
  
  start = clock();
  for(i=0; i<n_perms; i++){
    ob = metodo(perms[i], 0, N-1);
    if(ob<minob){
      minob = ob;
    }
    else if(ob>maxob){
      maxob = ob;
    }
    num_ob+=ob;
  }
  end = clock();
  total = (double)(end-start)/CLOCKS_PER_SEC;

  ptime->max_ob = maxob;
  ptime->min_ob = minob;
  ptime->N = N;
  ptime->n_elems = n_perms;
  ptime->time = total;
  ptime->average_ob = num_ob/n_perms;
  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms){

}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times){

}


