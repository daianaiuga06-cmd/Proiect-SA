#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sortari.h"

int main() {
    char *tipuri[] = {"random", "sortat", "invers", "aproape", "flat"};
    long long seturi[] = {10, 50, 100, 1000};

    char *sortariNume[] = {"BubbleSort","CountingSort","InsertionSort","MergeSort","QuickSort","RadixSort","SelectionSort","ShakerSort"};
    void (*sortariFunc[])(int*, long long) = {bublesort, countingSort, insertionSort, mergesort, quickSort, radixSort, selectionSort, shakerSort};

    int num_sortari = 8;
    int num_tipuri = 5;
    int num_seturi = 4;

    for(int s=0; s<num_seturi; s++) {
        long long n = seturi[s];
        printf("\nSet de date: %lld elemente\n", n);
        printf("Sortare\t\tTip lista\tTimp(secunde)\n");
        printf("-----------------------------------------\n");

        for(int sort=0; sort<num_sortari; sort++) {
            for(int t=0; t<num_tipuri; t++) {
                int *arr = malloc(n * sizeof(int));
                if(!arr) { printf("Memorie insuficienta!\n"); return 1; }

                if(strcmp(tipuri[t],"random")==0) gen_random(arr,n);
                else if(strcmp(tipuri[t],"sortat")==0) gen_sortat(arr,n);
                else if(strcmp(tipuri[t],"invers")==0) gen_invers(arr,n);
                else if(strcmp(tipuri[t],"aproape")==0) gen_aproape_sortat(arr,n);
                else if(strcmp(tipuri[t],"flat")==0) gen_flat(arr,n);

                clock_t start = clock();
                sortariFunc[sort](arr,n);
                clock_t end = clock();
                double timp = (double)(end - start)/CLOCKS_PER_SEC;

                printf("%-12s\t%-10s\t%.5f\n", sortariNume[sort], tipuri[t], timp);
                free(arr);
            }
        }
    }

    return 0;
}