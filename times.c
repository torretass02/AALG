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
#include "permutations.h"
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <assert.h>
#include "search.h"
/*#define NDEBUG*/


/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/

short average_search_time(pfunc_search method, pfunc_key_generator generator, char order, int N, int n_times, PTIME_AA ptime){
  int i, min_ob, max_ob, ob=0, search, pos;
  PDICT dictionary;
  int *perm=NULL, *table = NULL;

  clock_t start, end;

  ptime->n_elems=(N*n_times);
  ptime->N=N;

  dictionary = init_dictionary(N, order);

  perm = generate_perm(N);

  table = (int*) malloc((N*n_times)*sizeof(int));

  massive_insertion_dictionary(dictionary, perm, N);

  generator(table, N*n_times, N);

  start=clock();
  min_ob=INT_MAX;
  max_ob=0;
  for(i=0; i<n_times; i++){
    search=search_dictionary(dictionary, table[i], &pos, method);
    if(search<min_ob) min_ob=search;
    else if(search>max_ob) max_ob=search;
    ob+=search;
  }

  end=clock();

  ptime->max_ob = max_ob;
  ptime->min_ob = min_ob;
  ptime->average_ob=(double) ob/ptime->n_elems;
  ptime->time = (double) (end-start)/N/n_times/CLOCKS_PER_SEC;

  free_dictionary(dictionary);
  free(perm);
  free(table);

  return OK;
}

short generate_search_times(pfunc_search method, pfunc_key_generator generator, int order, char* file, int num_min, int num_max, int incr, int n_times){
  TIME_AA *time=NULL;
  int i,aux,t;

  assert(num_min <= num_max);
  assert(num_min>=0);

  if(!method||!file){
    return ERR;
  }

  aux=(num_max-num_min)/incr+1;
  time=(TIME_AA*)malloc((aux)*sizeof(TIME_AA));

  for(i=0,t=num_min;i<aux;i++,t+=incr){
    if(average_search_time(method, generator, order, t, n_times, &time[i])==ERR){
      return ERR;
    }
  }

  if(save_time_table(file, time,aux)==ERR){
    free(time);
    return ERR;
  }

  free(time);
  return OK;
}

short save_time_table(char* file, PTIME_AA time, int N){
FILE *f=NULL;
  int i;

  f=fopen(file,"w");
  if(!f){
    return ERR;
  }

  for(i=0; i<N; i++){
   fprintf(f, " %d  %f  %d  %f  %d\n",time[i].N, time[i].time,time[i].max_ob, time[i].average_ob, time[i].min_ob);
  }

  fclose(f);
  return OK;
}
