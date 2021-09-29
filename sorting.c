  /**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu) {
  int i, j;

  if(!array || ip<0 || iu<0){
    return ERR;
  }

  for(i=iu;i>ip;i--){
    for(j=ip;j<iu;j++){
      if(array[j]>array[j+1]){
        swap(&array[j], &array[j+1]);
      }
    }
  }
}

int BubbleSortFlag(int* array, int ip, int iu) {
  /* your code */
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


