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

/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime){
  clock_t start_t, end_t, total_t;
  int i, minob, maxob, ob, totalob=0;
  int** perms=NULL;

  if(!metodo||n_perms<=0||N<=0||!ptime)
    return ERR;

  perms=generate_permutations(n_perms,N);
    if(perms==NULL){
      return ERR;
    }

  maxob=INT_MIN;
  minob=INT_MAX;

  start_t=clock();

  for(i=0;i<n_perms;i++){
    ob=metodo(perms[i],0,N-1);
    if(ob<minob) minob=ob;
    if(ob>maxob) maxob=ob;
    totalob+=ob;
  }

  end_t=clock();

  total_t=(double)(end_t-start_t)/n_perms;

  ptime->N=N;
  ptime->n_elems=n_perms;
  ptime->time=total_t;
  ptime->average_ob=(double)(totalob/n_perms);
  ptime->min_ob=minob;
  ptime->max_ob=maxob;

  for(i=0;i<n_perms;i++){
    free(perms[i]);
  }
  free(perms);

  return OK;
}


short generate_sorting_times(pfunc_sort method, char* file, int num_min, int num_max, int incr, int n_perms){
  TIME_AA *time=NULL;
  int i,aux,tam;

  if(!method||!file)
    return ERR;

  aux=(num_max-num_min)/incr+1;
  time=(TIME_AA*)malloc((aux)*sizeof(TIME_AA));
  if(time==NULL)
    return ERR;

  for(i=0,tam=num_min;i<aux;i++,tam+=incr){
    if(average_sorting_time(method,n_perms,tam,&time[i])==ERR){
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

  if(!file)
    return ERR;

  f=fopen(file,"w");
  if(f==NULL)
   return ERR;

  for(i=0;i<n_times;i++){
    fprintf(f," %d  %f  %f  %d  %d\n",ptime[i].N,ptime[i].time,ptime[i].average_ob,ptime[i].max_ob,ptime[i].min_ob);
  }

  fclose(f);
  return OK;
}


