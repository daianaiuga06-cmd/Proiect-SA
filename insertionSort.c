//Pornește de la al doilea element și îl compară cu elementele din stânga.
//Mută elementele mai mari cu o poziție spre dreapta și inserează elementul la poziția corectă.
//Repetă procesul până când toate elementele sunt sortate.
//Este eficient pentru liste mici sau aproape sortate.
//Complexitate:
//Best case (aproape sortat): O(n)
//Worst case: O(n²)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "sortari.h"
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
//FUNCTIA DE SORTARE PRIN INSERARE
void insertionSort(int arr[], long long n){
    for(long long i = 1; i < n; i++){
        int key = arr[i];
        long long j = i - 1;

        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
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
    insertionSort(arr,n);
    clock_t end =clock();

    printf("\n\n\n\n ARRAY SORTAT \n\n\n\n");
    printArray(arr,n);

    printf("Timp soratare: %f secunde\n",(double)(end-start)/CLOCKS_PER_SEC);

    free(arr);
    return 0;
}