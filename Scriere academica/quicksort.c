#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    long long swaps = n * 0.05;
    for(long long i = 0; i < swaps; i++) {
        long long a = rand() % n;
        long long b = rand() % n;
        int tmp = arr[a]; arr[a] = arr[b]; arr[b] = tmp;
    }
}
void gen_flat(int arr[], long long n) {
    int values[] = {1,2,3,4,5};
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

void quicksort(int arr[], long long low, long long high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Salvare în fișier
void saveToFile(const char *filename, int original[], int sorted[], long long n, const char *sortName) {
    FILE *f = fopen(filename, "w");
    if(!f) { printf("Eroare la deschiderea fisierului!\n"); return; }

    long long limit = (n <= 100) ? n : 100;

    fprintf(f, "Algoritm: %s\n\n", sortName);

    fprintf(f, "Lista initiala:\n");
    for(long long i = 0; i < limit; i++) fprintf(f, "%d ", original[i]);
    if(n > 100) fprintf(f, "... (inca %lld elemente)", n - 100);
    fprintf(f, "\n\n");

    fprintf(f, "Lista sortata:\n");
    for(long long i = 0; i < limit; i++) fprintf(f, "%d ", sorted[i]);
    if(n > 100) fprintf(f, "... (inca %lld elemente)", n - 100);
    fprintf(f, "\n");

    fclose(f);
}

int main() {
    srand(time(NULL));

    long long n;
    printf("Introduceti numarul de elemente: ");
    scanf("%lld", &n);

    int *arr = malloc(n * sizeof(int));
    int *original = malloc(n * sizeof(int));
    if(!arr || !original) { printf("Memorie insuficienta!\n"); free(arr); free(original); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s", tip);

    if(strcmp(tip,"random")==0) gen_random(arr, n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr, n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr, n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr, n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr, n);
    else { printf("Tip invalid!\n"); free(arr); free(original); return 1; }

    memcpy(original, arr, n * sizeof(int));

    clock_t start = clock();
    quicksort(arr, 0, n - 1); // corect: 0..n-1
    clock_t end = clock();

    printf("Timp QuickSort: %f secunde\n", (double)(end - start)/CLOCKS_PER_SEC);

    saveToFile("datetest.txt", original, arr, n, "QuickSort");

    free(arr);
    free(original);
    return 0;
}