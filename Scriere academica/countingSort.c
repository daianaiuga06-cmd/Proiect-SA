#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

// GENERATOARE DE LISTE
void gen_random(int arr[], long long n){
    for(long long i=0;i<n;i++) arr[i]=rand()%10000000;
}
void gen_sortat(int arr[], long long n){
    for(long long i=0;i<n;i++) arr[i]=i;
}
void gen_invers(int arr[], long long n){
    for(long long i=0;i<n;i++) arr[i]=n-i;
}
void gen_aproape_sortat(int arr[], long long n){
    for(long long i=0;i<n;i++) arr[i]=i;
    long long swaps=n*0.05;
    for(long long i=0;i<swaps;i++){
        long long a=rand()%n;
        long long b=rand()%n;
        int tmp=arr[a]; arr[a]=arr[b]; arr[b]=tmp;
    }
}
void gen_flat(int arr[], long long n){
    int values[]={1,2,3,4,5};
    for(long long i=0;i<n;i++) arr[i]=values[rand()%5];
}

// COUNTING SORT
void countingSort(int arr[], long long n){
    if(n<=0) return;

    int max = arr[0];
    for(long long i=1;i<n;i++) if(arr[i]>max) max=arr[i];

    int *count = malloc((max+1)*sizeof(int));
    if(!count){ printf("Memorie insuficienta!\n"); return; }

    for(int i=0;i<=max;i++) count[i]=0;
    for(long long i=0;i<n;i++) count[arr[i]]++;

    long long index=0;
    for(int i=0;i<=max;i++){
        while(count[i]>0){
            arr[index++]=i;
            count[i]--;
        }
    }
    free(count);
}

// AFISARE
void printArray(int arr[], long long n){
    long long limit=1000;
    for(long long i=0;i<(n<limit?n:limit);i++) printf("%d ", arr[i]);
    if(n>limit) printf("... (%lld elemente total)\n", n);
    else printf("\n");
}

// SALVARE IN FISIER
void saveToFile(const char *filename, int original[], int sorted[], long long n, const char *sortName){
    FILE *f=fopen(filename,"w");
    if(!f){ printf("Eroare la deschiderea fisierului!\n"); return; }
    long long limit=(n<=100)?n:100;

    fprintf(f,"Algoritm: %s\n\n", sortName);
    fprintf(f,"Lista initiala:\n");
    for(long long i=0;i<limit;i++) fprintf(f,"%d ", original[i]);
    if(n>100) fprintf(f,"... (inca %lld elemente)", n-100);
    fprintf(f,"\n\n");

    fprintf(f,"Lista sortata:\n");
    for(long long i=0;i<limit;i++) fprintf(f,"%d ", sorted[i]);
    if(n>100) fprintf(f,"... (inca %lld elemente)", n-100);
    fprintf(f,"\n");

    fclose(f);
}

// MAIN
int main(){
    srand(time(NULL));

    long long n;
    printf("Introduceti numarul de elemente: ");
    scanf("%lld",&n);

    int *arr=malloc(n*sizeof(int));
    int *original=malloc(n*sizeof(int));
    if(!arr || !original){ printf("Memorie insuficienta!\n"); free(arr); free(original); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s",tip);

    if(strcmp(tip,"random")==0) gen_random(arr,n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(arr,n);
    else if(strcmp(tip,"invers")==0) gen_invers(arr,n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(arr,n);
    else if(strcmp(tip,"flat")==0) gen_flat(arr,n);
    else { printf("Tip invalid!\n"); free(arr); free(original); return 1; }

    memcpy(original, arr, n*sizeof(int));

    clock_t start=clock();
    countingSort(arr,n);
    clock_t end=clock();

    printf("Timp CountingSort: %f secunde\n", (double)(end-start)/CLOCKS_PER_SEC);

    saveToFile("datetest.txt", original, arr, n, "CountingSort");

    free(arr);
    free(original);
    return 0;
}