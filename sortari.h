#ifndef SORTARI_H
#define SORTARI_H

// Generatoare de liste

void gen_random(int arr[], long long n);
void gen_sortat(int arr[], long long n);
void gen_invers(int arr[], long long n);
void gen_aproape_sortat(int arr[], long long n);
void gen_flat(int arr[], long long n);

// Sortări
void bublesort(int arr[], long long n);
void countingSort(int arr[], long long n);
void insertionSort(int arr[], long long n);
void mergesort(int arr[], long long n);
void quickSort(int arr[], long long n);
void radixSort(int arr[], long long n);
void selectionSort(int arr[], long long n);
void shakerSort(int arr[], long long n);

// Funcție utilitară
void printArray(int arr[], long long n);

#endif