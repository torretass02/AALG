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
/*#define NDEBUG*/


/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime) {
  int i, **perms, *ob, totalob;
  clock_t start, end;  

  perms=generate_permutations(n_perms,N);

  ob=(int*) malloc(n_perms*sizeof(int));
  if(!ob){
    return ERR;
  }

  start=clock();

  for(i=0;i<n_perms;i++){
    ob[i]=metodo(perms[i],0,N-1);
  }
  end=clock();

  ptime->min_ob=ob[0];
  ptime->max_ob=ob[0];

  for(i=totalob=0;i<n_perms;i++){
    if(ptime->min_ob<ob[i]) ptime->min_ob=ob[i];
    if(ptime->max_ob>ob[i]) ptime->max_ob=ob[i];
    totalob+=ob[i];
  }

  ptime->N=N;
  ptime->n_elems=n_perms;
  ptime->time = (double) (end-start)/n_perms/CLOCKS_PER_SEC;
  ptime->average_ob=(double) totalob/n_perms;

  free(ob);
  
  for(i=0;i<n_perms;i++){
    free(perms[i]);
  }

  free(perms);
  return OK;
}

short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms){
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
    if(average_sorting_time(method,n_perms,t,&time[i])==ERR){
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

short save_time_table(char* file, PTIME_AA ptime, int n_times){
  FILE *f=NULL;
  int i;

  f=fopen(file,"w");
  if(!f){
    return ERR;
  }

  for(i=0;i<n_times;i++){
   fprintf(f, " %d  %f  %f  %d  %d\n",ptime[i].N, ptime[i].time,ptime[i].average_ob,ptime[i].max_ob,ptime[i].min_ob);
  }

  fclose(f);
  return OK;
}