//Alege un element numit pivot.
//Reorganizează lista astfel încât:
//toate elementele mai mici decât pivotul să fie în stânga
//toate elementele mai mari să fie în dreapta
//Apoi aplică recursiv QuickSort pe sublistele din stânga și dreapta pivotului.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sortari.h"

// Generatoare de liste
void gen_random(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = rand() % 10000000;
}

void gen_sortat(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = i;
}

void gen_invers(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = n - i;
}

void gen_aproape_sortat(int arr[], long long n) {
    for(long long i = 0; i < n; i++)
        arr[i] = i;
    long long swaps = n * 0.05; // 5% elemente nelalocul lor
    for(long long i = 0; i < swaps; i++) {
        long long a = rand() % n;
        long long b = rand() % n;
        int tmp = arr[a]; arr[a] = arr[b]; arr[b] = tmp;
    }
}

void gen_flat(int arr[], long long n) {
    int values[] = {1, 2, 3, 4, 5};
    for(long long i = 0; i < n; i++)
        arr[i] = values[rand() % 5];
}

// QuickSort
void swap(int *a, int *b) { int tmp = *a; *a = *b; *b = tmp; }

int partition(int arr[], long long low, long long high) {
    int pivot = arr[high];
    long long i = low - 1;
    for(long long j = low; j < high; j++)
        if(arr[j] < pivot) { i++; swap(&arr[i], &arr[j]); }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], long long low, long long high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Afisare array 
void printArray(long long n, int arr[]) {
    long long limit = 1000; // limita de afișare
    if(n <= 100000) {
        for(long long i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("\n");
    } else {
        for(long long i = 0; i < limit; i++) printf("%d ", arr[i]);
        printf("... (%lld elemente total)\n", n);
    }
}

int main() {
    srand(time(NULL));

    long long n;
    printf("Introduceti numarul de elemente: ");
    scanf("%lld", &n);

    int *arr = malloc(n * sizeof(int));
    if(!arr) { printf("Memorie insuficienta!\n"); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s", tip);

    if(strcmp(tip,"random")==0) gen_random(arr, n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr, n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr, n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr, n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr, n);
    else { printf("Tip invalid!\n"); free(arr); return 1; }

    printf("\n\n\n\nARRAY NESORTAT:\n\n\n\n");
    printArray(n, arr);

    clock_t start = clock();
    quickSort(arr, 0, n - 1);
    clock_t end = clock();

    printf("\n\n\n\nARRAY SORTAT:\n\n\n\n");
    printArray(n, arr);

    printf("Timp sortare: %f secunde\n", (double)(end - start)/CLOCKS_PER_SEC);

    free(arr);
    return 0;
}