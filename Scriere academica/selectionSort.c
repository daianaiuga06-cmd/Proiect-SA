#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Generatoare de liste
void gen_random(int arr[], long long n) {
    for(long long i=0; i<n; i++)
        arr[i] = rand() % 10000000;
}

void gen_sortat(int arr[], long long n) {
    for(long long i=0; i<n; i++)
        arr[i] = i;
}

void gen_invers(int arr[], long long n) {
    for(long long i=0; i<n; i++)
        arr[i] = n - i;
}

void gen_aproape_sortat(int arr[], long long n) {
    for(long long i=0; i<n; i++)
        arr[i] = i;
    long long swaps = n * 0.05;
    for(long long i=0; i<swaps; i++){
        long long a = rand()%n;
        long long b = rand()%n;
        int tmp = arr[a]; arr[a] = arr[b]; arr[b] = tmp;
    }
}

void gen_flat(int arr[], long long n){
    int values[]={1,2,3,4,5};
    for(long long i=0; i<n; i++)
        arr[i] = values[rand()%5];
}

// Selection Sort
void selectionSort(int arr[], long long n){
    for(long long i=0; i<n-1; i++){
        long long minIndex = i;
        for(long long j=i+1; j<n; j++){
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        if(minIndex != i){
            int tmp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = tmp;
        }
    }
}

// Afisare array
void printArray(int arr[], long long n){
    long long limit = 1000;
    if(n <= limit){
        for(long long i=0; i<n; i++)
            printf("%d ", arr[i]);
    } else {
        for(long long i=0; i<limit; i++)
            printf("%d ", arr[i]);
        printf("... (%lld elemente total)", n);
    }
    printf("\n");
}

// Salvare în fișier
void saveToFile(const char *filename, int original[], int sorted[], long long n){
    FILE *f = fopen(filename, "w");
    if(!f){ printf("Eroare la deschiderea fisierului!\n"); return; }

    long long limit = (n<=100) ? n : 100;

    fprintf(f, "Algoritm: SelectionSort\n\n");

    // Lista initiala
    fprintf(f, "Lista initiala:\n");
    for(long long i=0; i<limit; i++)
        fprintf(f, "%d ", original[i]);
    if(n>100) fprintf(f, "... (%lld elemente ramase)", n-100);
    fprintf(f, "\n\n");

    // Lista sortata
    fprintf(f, "Lista sortata:\n");
    for(long long i=0; i<limit; i++)
        fprintf(f, "%d ", sorted[i]);
    if(n>100) fprintf(f, "... (%lld elemente ramase)", n-100);
    fprintf(f, "\n");

    fclose(f);
}

int main(){
    srand(time(NULL));

    long long n;
    printf("Introduceti numarul de elemente: ");
    scanf("%lld",&n);

    int *arr = malloc(n*sizeof(int));
    if(!arr){ printf("Memorie insuficienta!\n"); return 1; }

    int *original = malloc(n*sizeof(int));
    if(!original){ printf("Memorie insuficienta!\n"); free(arr); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s",tip);

    if(strcmp(tip,"random")==0) gen_random(arr,n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr,n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr,n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr,n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr,n);
    else { printf("Tip invalid\n"); free(arr); free(original); return 1; }

    memcpy(original, arr, n*sizeof(int));

    printf("\nArray nesortat:\n");
    printArray(arr,n);

    clock_t start = clock();
    selectionSort(arr,n);
    clock_t end = clock();

    printf("\nArray sortat:\n");
    printArray(arr,n);

    printf("\nTimp sortare: %f secunde\n", (double)(end-start)/CLOCKS_PER_SEC);

    saveToFile("datetest.txt", original, arr, n);

    free(arr);
    free(original);
    return 0;
}