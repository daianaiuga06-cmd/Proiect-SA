//Împarte array-ul în două jumătăți.
//Sortează recursiv fiecare jumătate.
//Combină cele două jumătăți sortate într-un array final sortat.
//Complexitate: O(n log n) în toate cazurile.
//Este stabil și foarte eficient pentru liste mari.
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

// MergeSort
void merge(int arr[], int temp[], long long left, long long mid, long long right) {
    long long i = left, j = mid + 1, k = left;

    while(i <= mid && j <= right) {
        if(arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while(i <= mid) temp[k++] = arr[i++];
    while(j <= right) temp[k++] = arr[j++];
    for(i = left; i <= right; i++)
        arr[i] = temp[i];
}

void mergeSort(int arr[], int temp[], long long left, long long right) {
    if(left >= right) return;
    long long mid = (left + right) / 2;
    mergeSort(arr, temp, left, mid);
    mergeSort(arr, temp, mid + 1, right);
    merge(arr, temp, left, mid, right);
}

// Afisare array 
void printArray(int arr[], long long n) {
    long long limit = 1000;
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
    int *temp = malloc(n * sizeof(int));
    if(!arr || !temp) { printf("Memorie insuficienta!\n"); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s", tip);

    if(strcmp(tip,"random")==0) gen_random(arr, n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr, n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr, n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr, n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr, n);
    else { printf("Tip invalid!\n"); free(arr); free(temp); return 1; }

    printf("\n\n\n\nARRAY NESORTAT:\n\n\n\n");
    printArray(arr, n);

    clock_t start = clock();
    mergeSort(arr, temp, 0, n - 1);
    clock_t end = clock();

    printf("\n\n\n\nARRAY SORTAT:\n\n\n\n");
    printArray(arr, n);

    printf("Timp sortare: %f secunde\n", (double)(end - start)/CLOCKS_PER_SEC);

    free(arr);
    free(temp);
    return 0;
}