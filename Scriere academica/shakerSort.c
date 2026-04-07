//Parcurgem lista de la stânga la dreapta, mutând cel mai mare element la sfârșit.
//Parcurgem lista de la dreapta la stânga, mutând cel mai mic element la început.
//Repetăm procesul până când lista este complet sortată.
//Complexitate: O(n²) în medie și în cel mai rău caz
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
//GENERATOARE DE LISTE
void gen_random(int arr[], long long n){
    for(long long i=0;i<n;i++)
        arr[i]=rand()%10000000;
}

void gen_sortat(int arr[], long long n){
    for(long long i=0;i<n;i++)
        arr[i]=i;
}

void gen_invers(int arr[], long long n){
    for(long long i=0;i<n;i++)
        arr[i]=n-i;

}

void gen_aproape_sortat(int arr[], long long n){
    for(long long i=0;i<n;i++)
        arr[i]=i;
    long long swaps=n*0.05;
    for(long long i=0;i<swaps;i++){
        long long a=rand()%n;
        long long b=rand()%n;
        int tmp=arr[a];arr[a]=arr[b];arr[b]=tmp;
    }

}
void gen_flat(int arr[], long long n){
    int values[]={1,2,3,4,5};
    for(long long i=0;i<n;i++)
        arr[i]=values[rand()%5];
}
//FUNCTIA DE SORTARE
void shakerSort(int arr[], long long n){
    long long left=0;
    long long right =n-1;
    int swapped=1;

    while(swapped){
        swapped=0;

        for(long long i=left;i<right;i++){
            if(arr[i]>arr[i+1]){
                int tmp=arr[i];
                arr[i]=arr[i+1];
                arr[i+1]=tmp;
                swapped=1;
              }
        }
        if(!swapped) break;
        right--;
        swapped=0;

        for(long long i=right;i>left;i--){
            if(arr[i]<arr[i-1]){
                int tmp=arr[i];
                arr[i]=arr[i-1];
                arr[i-1]=tmp;
                swapped=1;
            }
        }
        left++;
    }
}
//AFISARE
void printArray(int arr[], long long n){
    long long limit = 1000;

    if(n <= 100000){
        for(long long i = 0; i < n; i++)
            printf("%d ", arr[i]);
        printf("\n");
    } else {
        for(long long i = 0; i < limit; i++)
            printf("%d ", arr[i]);
        printf("... (%lld elemente total)\n", n);
    }
}
void saveToFile(const char *date, int original[], int sorted[], long long n) {
    FILE *f = fopen(date, "w");
    if(!f) {
        printf("Eroare la deschiderea fisierului!\n");
        return;
    }

    long long limit = (n <= 100) ? n : 100;

    // Lista initiala
    fprintf(f, "Lista initiala:\n");
    for(long long i = 0; i < limit; i++)
        fprintf(f, "%d ", original[i]);

    if(n > 100)
        fprintf(f, "... (inca %lld elemente)", n - 100);

    fprintf(f, "\n\n");

    // Lista sortata
    fprintf(f, "Lista sortata:\n");
    for(long long i = 0; i < limit; i++)
        fprintf(f, "%d ", sorted[i]);

    if(n > 100)
        fprintf(f, "... (inca %lld elemente)", n - 100);

    fprintf(f, "\n");

    fclose(f);
}
int main(){
    srand(time(NULL));

    long long n;
    printf("Introduceti numarul de elemente:");
    scanf("%lld",&n);

    int *arr=malloc(n*sizeof(int));
    if(!arr){
        printf("Memorie insuficienta!\n");
        return 1;
    }

    char tip[20];
    printf("Tip lista(random/sortat/invers/aproape/flat): ");
    scanf("%s",tip);

    if(strcmp(tip,"random")==0) gen_random(arr,n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr,n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr,n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr,n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr,n);
    else {printf("Tip invalid\n");
        free(arr);
        return 1;}
    printf("\n\n\n\n ARRAY NESORTAT \n\n\n\n");
    printArray(arr,n);

    clock_t start =clock();
    shakerSort(arr,n);
    clock_t end =clock();

    printf("\n\n\n\n ARRAY SORTAT \n\n\n\n");
    printArray(arr,n);

    printf("Timp soratare: %f secunde\n",(double)(end-start)/CLOCKS_PER_SEC);

    free(arr);
    return 0;
}