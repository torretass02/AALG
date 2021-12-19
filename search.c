/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"
#include "sorting.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max){
  int i;

  for(i = 0; i < n_keys; i++) keys[i] = 1 + (i % max);

  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max){
  int i;

  for(i = 0; i < n_keys; i++) 
  {
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  }

  return;
}

PDICT init_dictionary (int size, char order){

	PDICT dictionary = NULL;

  /*assert(size >= 0);

  if(!order) return NULL;*/

  dictionary  = (PDICT)malloc(sizeof(DICT));
  if(!dictionary) return NULL;

  dictionary->table = (int*)malloc(size*sizeof(int));
  if(!dictionary->table){
    free_dictionary(dictionary);
    return NULL;
  }

  dictionary->n_data=0;
  dictionary->order=order;
  dictionary->size=size;

  return dictionary;
}

void free_dictionary(PDICT pdict){
  if(!pdict) return;

	free(pdict->table);
  free(pdict);
  
}

int insert_dictionary(PDICT pdict, int key){
  int j, A, ob=0;

  if(!pdict) return ERR;

  assert(pdict->size != pdict->n_data);

	if(pdict->order == NOT_SORTED){
    pdict->table[pdict->n_data] = key;
    pdict->n_data++;
  }
  else{
    pdict->table[pdict->n_data] = key;
    A = pdict->table[pdict->n_data];
    j=pdict->n_data-1;
    while(j>=0 && pdict->table[j]>A){
      ob++;
      pdict->table[j+1]=pdict->table[j];
      j--; 
    }
    pdict->table[j+1]=A;
    pdict->n_data++;
  }
  return ob;
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys){
	int i, ob=0;

  if(!pdict || !keys || !n_keys) return ERR;
  
  for(i=0; i<n_keys; i++){
    ob += insert_dictionary(pdict, keys[i]);
    assert (ob != ERR);
  }
  return ob;
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method){

  if(!pdict || !ppos || !method) return ERR;

  return method(pdict->table, 0, pdict->size, key, ppos);
}


int bin_search(int *table,int F,int L,int key, int *ppos){
  int m, ob=0;

  assert(F >= 0);

  if (!table || !ppos) return ERR;

	while(F<=L){
    m=(F+L)/2;
    ob++;
    if(table[m]==key){
      *ppos=m;
      return ob;
    }
    else if(key<table[m]){
      L=m-1;
    }
    else{
      F=m+1;
    }
  }
  *ppos = NOT_FOUND;
  return ob;
}

int lin_search(int *table,int F,int L,int key, int *ppos){
  int i, ob=0;

  assert(F >= 0);

  if(!table || !ppos) return ERR;


	for(i=F; i<L; i++){
    ob++;
    if(table[i]==key){
      *ppos = i;
      return ob;
    }
  }
  *ppos = NOT_FOUND;
  return ob;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos){
  int i, ob=0;

  assert(F >= 0);

  if(!table || !ppos) return ERR;

  for(i=F; i<=L; i++){
    ob++;
    if(table[i]==key){
      if(i!=0){
        swap(&table[i], &table[i-1]);
        *ppos = i;
        return ob;
      }
      else{
        *ppos = i;
        return ob;
      }
    }
  }
  *ppos = NOT_FOUND;
  return NOT_FOUND;
}
