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

// Bubble Sort
void bubbleSort(int arr[], long long n) {
    for(long long i = 0; i < n - 1; i++) {
        for(long long j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

// Afisare array
void printArray(int arr[], long long n) {
    long long limit = 1000;
    if(n <= 1000) {
        for(long long i = 0; i < n; i++)
            printf("%d ", arr[i]);
    } else {
        for(long long i = 0; i < limit; i++)
            printf("%d ", arr[i]);
        printf("... (%lld elemente total)", n);
    }
    printf("\n");
}

// Salvare în fișier
void saveToFile(const char *filename, int original[], int sorted[], long long n) {
    FILE *f = fopen(filename, "w");
    if(!f) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    long long limit = (n <= 100) ? n : 100;

    fprintf(f, "Algoritm: BubbleSort\n\n");

    // Lista inițială
    fprintf(f, "Lista initiala:\n");
    for(long long i = 0; i < limit; i++)
        fprintf(f, "%d ", original[i]);
    if(n > 100)
        fprintf(f, "... (%lld elemente ramase)", n - 100);
    fprintf(f, "\n\n");

    // Lista sortată
    fprintf(f, "Lista sortata:\n");
    for(long long i = 0; i < limit; i++)
        fprintf(f, "%d ", sorted[i]);
    if(n > 100)
        fprintf(f, "... (%lld elemente ramase)", n - 100);
    fprintf(f, "\n");

    fclose(f);
}

int main() {
    srand(time(NULL));

    long long n;
    printf("Introduceti numarul de elemente: ");
    scanf("%lld", &n);

    int *arr = malloc(n * sizeof(int));
    if(!arr) { printf("Memorie insuficienta!\n"); return 1; }

    int *original = malloc(n * sizeof(int));
    if(!original) { printf("Memorie insuficienta!\n"); free(arr); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s", tip);

    if(strcmp(tip,"random")==0) gen_random(arr, n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr, n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr, n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr, n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr, n);
    else { printf("Tip invalid!\n"); free(arr); free(original); return 1; }

    // Salvăm copia inițială
    memcpy(original, arr, n * sizeof(int));

    // Sortare Bubble
    clock_t start = clock();
    bubbleSort(arr, n);
    clock_t end = clock();

    printf("Timp BubbleSort: %f secunde\n", (double)(end - start)/CLOCKS_PER_SEC);


    // Salvare în fișier
    saveToFile("datetest.txt", original, arr, n);

    free(arr);
    free(original);
    return 0;
}