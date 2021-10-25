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
#include <stdio.h>
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

int mergesort(int* tabla, int ip, int iu){
 int m,ob,ob_aux,ob_aux2;

  if(!tabla||ip<0||iu<0||ip>iu){
    return ERR;
  }

  if(ip==iu){
    return 0;
  }

  m=(ip+iu)/2;
  
  ob=1;
  ob+=mergesort(tabla,ip,m);
  if(ob==NULL){
    return ERR;
  }

  ob_aux=1;
  ob_aux+=mergesort(tabla,m+1,iu);
  if(ob_aux==NULL){
    return ERR;
  }

  ob_aux2=1;
  ob_aux2+= merge(tabla,ip,iu,m);
  if(ob_aux2==NULL){
    return ERR;
  }

  return ob+ob_aux+ob_aux2;
}

void copy(int* aux, int* t, int p, int u){
  int i=p;
  aux-=p;
  while(i<=u){
    t[i]=aux[i];
    i++;
  }
}

int merge(int* tabla, int ip, int iu, int imedio){
  int* tablaaux = NULL;
  int i, j, k, ob=0;
  i = ip;
  j = imedio+1;

  tablaaux=(int*)malloc((iu-ip+1)*sizeof(int));

  k = 0;

   while(i<=imedio && j<=iu){
    if(tabla[i]<tabla[j]){
      tablaaux[k]=tabla[i];
      i++;
      ob++;
    }
    else{
     tablaaux[k]=tabla[j];
     j++;
     ob++;
    }
    k++;
  }
  if(i>imedio){
    while(j<=iu){
      tablaaux[k]=tabla[j];
      j++;
      k++;
    }
  }
  else if(j>iu){
    while(i<=imedio){
      tablaaux[k]=tabla[i];
      i++;
      k++;
    }
  }
  copy(tablaaux, tabla, ip, iu);
  free(tablaaux);
  return ob;
}
