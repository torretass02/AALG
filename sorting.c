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
#include <assert.h>
/*#define NDEBUG*/


/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

int BubbleSort(int* array, int ip, int iu) {
  int i, j, ob;

  assert(ip>0 || iu>0);

  ob=0;
  for(i=iu;i>ip;i--){
    for(j=ip;j<iu;j++){
      if(array[j]>array[j+1]){
        swap(&array[j], &array[j+1]);
      }
      ob++;
    }
  }
  return ob;
}

int BubbleSortFlag(int* array, int ip, int iu) {
  int i=iu, j, flag = 1, ob;

  assert(ip>0 || iu>0);

  ob=0;

  while(flag==1 && i>=ip+1){
    flag = 0;
    for(j=ip;j<iu;j++){
      if(array[j]>array[j+1]){
        swap(&array[j], &array[j+1]);
        flag=1;
      }
      ob++;
    }
    i--;
  }
  return ob;
}