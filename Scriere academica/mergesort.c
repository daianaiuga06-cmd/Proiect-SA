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

// Salvare în fișier (primele 1000 elemente + rest)
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
    int *temp = malloc(n * sizeof(int));

    if(!arr || !original || !temp) {
        printf("Memorie insuficienta!\n");
        free(arr); free(original); free(temp);
        return 1;
    }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s", tip);

    if(strcmp(tip,"random")==0) gen_random(arr, n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr, n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr, n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr, n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr, n);
    else { printf("Tip invalid!\n"); free(arr); free(original); free(temp); return 1; }

    memcpy(original, arr, n * sizeof(int));

    clock_t start = clock();
    mergeSort(arr, temp, 0, n - 1);
    clock_t end = clock();

    printf("Timp MergeSort: %f secunde\n", (double)(end - start)/CLOCKS_PER_SEC);

    saveToFile("datetest.txt", original, arr, n, "MergeSort");

    free(arr); free(original); free(temp);
    return 0;
}