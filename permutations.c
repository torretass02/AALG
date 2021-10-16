/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>
#include <stddef.h>
/*#define NDEBUG*/
#include <assert.h>


/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup) {
  assert(inf <= sup);
  return (((sup-inf+1.0)*rand())/(RAND_MAX+1.0))+inf;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N){
  int i, aux, r;
  int *perm = NULL;

  assert(N>=0);

  perm = (int*)malloc(N*sizeof(int));
  
  if(perm == NULL){
    free(perm);
    return NULL;
  }

  for(i=0;i<N;i++){
    perm[i] = i+1;
  }

  for(i=0;i<N;i++){
    r=random_num(i,N-1);
    aux=perm[i];
    perm[i]=perm[r];
    perm[r]=aux;
  }

  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N) {
  int i, j;
  int** perm = NULL;

  assert(n_perms>=0);
  assert(N>=0);

  perm = (int**)malloc(n_perms*sizeof(int*)); 

  if(perm == NULL){
    return NULL;
  }

  for(i=0; i<n_perms; i++){
    perm[i]=generate_perm(N);
    if(perm[i]==NULL){
      for(j=0;j<=i;j++){
        free(perm[j]);
      }
      free(perm);
      return NULL;
    }
  }

  return perm;
}
