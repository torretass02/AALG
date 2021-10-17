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

  assert(ip>=0||iu>=0);

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
  int i, comps, sorted = 0, ob = 0;	
	comps = (iu-1) - 1;

  assert(ip>=0||iu>=0);

	while ( !sorted ){
		sorted = 1;	
		for(i = ip;i < comps;i++){
			if(array[i] > array[i + 1]){
        swap(&array[i], &array[i+1]);
				sorted = 0;
			}
      ob++;
		}	
		comps--;
	}
  return ob;
}
