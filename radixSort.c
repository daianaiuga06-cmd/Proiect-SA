//Alegem poziția unei cifre (unități, zeci, sute etc.).
//Sortăm elementele în funcție de cifra respectivă, păstrând ordinea relativă.
//Repetăm pentru toate pozițiile cifrelor până lista e sortată complet.
//Complexitate: O(n × k), unde k = numărul de cifre
//Nu compară elementele direct, ci se bazează pe cifre
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
//FUNCTIA COUNTING
void countingSort(int arr[],long long n, int exp){
    int *output =malloc(n*sizeof(int));
    if(!output){
        printf("Memorie insuficienta!");
        return;
    }
    int count[10]={0};

    for(long long i=0;i<n;i++)
        count[(arr[i]/exp)%10]++;

    for(int i=1;i<10;i++)
        count[i]+= count[i-1];

    for(long long i=n-1;i>=0;i--){
        int digit=(arr[i]/exp)%10;
        output[count[digit]-1]=arr[i];
        count[digit]--;
    }
    for(long long i=0;i<n;i++)
        arr[i]=output[i];
    free(output);
}
//FUNCTIA REDIX
void radixSort(int arr[],long long n){
    int max=arr[0];
    for(long long i=1;i<n;i++)
        if(arr[i]>max) max=arr[i];

    for(int exp=1;max/exp>0;exp*=10)
        countingSort(arr,n,exp);

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
    radixSort(arr,n);
    clock_t end =clock();

    printf("\n\n\n\n ARRAY SORTAT \n\n\n\n");
    printArray(arr,n);

    printf("Timp soratare: %f secunde\n",(double)(end-start)/CLOCKS_PER_SEC);

    free(arr);
    return 0;
}