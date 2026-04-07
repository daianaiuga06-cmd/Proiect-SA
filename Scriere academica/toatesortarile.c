#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ================= Generatoare de liste =================
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
    for(long long i = 0; i < n; i++) arr[i] = i;
    long long swaps = n * 0.05;
    for(long long i = 0; i < swaps; i++) {
        long long a = rand() % n;
        long long b = rand() % n;
        int tmp = arr[a]; arr[a] = arr[b]; arr[b] = tmp;
    }
}

void gen_flat(int arr[], long long n) {
    int values[] = {1,2,3,4,5};
    for(long long i = 0; i < n; i++) arr[i] = values[rand() % 5];
}

// ================= Sortari lente cu timeout =================
double bubbleSortTimeout(int arr[], long long n, double max_seconds) {
    clock_t start = clock();
    for(long long i = 0; i < n - 1; i++) {
        for(long long j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j]; arr[j] = arr[j+1]; arr[j+1] = tmp;
            }
            if((double)(clock() - start)/CLOCKS_PER_SEC > max_seconds) return -1;
        }
    }
    return (double)(clock() - start)/CLOCKS_PER_SEC;
}

double insertionSortTimeout(int arr[], long long n, double max_seconds) {
    clock_t start = clock();
    for(long long i = 1; i < n; i++){
        int key = arr[i];
        long long j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j+1] = arr[j];
            j--;
            if((double)(clock() - start)/CLOCKS_PER_SEC > max_seconds) return -1;
        }
        arr[j+1] = key;
    }
    return (double)(clock() - start)/CLOCKS_PER_SEC;
}

double selectionSortTimeout(int arr[], long long n, double max_seconds){
    clock_t start = clock();
    for(long long i = 0; i < n; i++){
        long long minIndex = i;
        for(long long j = i+1; j < n; j++) {
            if(arr[j] < arr[minIndex]) minIndex = j;
            if((double)(clock() - start)/CLOCKS_PER_SEC > max_seconds) return -1;
        }
        if(minIndex != i){
            int tmp = arr[i]; arr[i] = arr[minIndex]; arr[minIndex] = tmp;
        }
    }
    return (double)(clock() - start)/CLOCKS_PER_SEC;
}

double shakerSortTimeout(int arr[], long long n, double max_seconds){
    clock_t start = clock();
    long long left = 0, right = n-1;
    int swapped = 1;
    while(swapped){
        swapped = 0;
        for(long long i = left; i < right; i++){
            if(arr[i] > arr[i+1]){
                int tmp = arr[i]; arr[i] = arr[i+1]; arr[i+1] = tmp;
                swapped = 1;
            }
            if((double)(clock() - start)/CLOCKS_PER_SEC > max_seconds) return -1;
        }
        if(!swapped) break;
        right--;
        swapped = 0;
        for(long long i = right; i > left; i--){
            if(arr[i] < arr[i-1]){
                int tmp = arr[i]; arr[i] = arr[i-1]; arr[i-1] = tmp;
                swapped = 1;
            }
            if((double)(clock() - start)/CLOCKS_PER_SEC > max_seconds) return -1;
        }
        left++;
    }
    return (double)(clock() - start)/CLOCKS_PER_SEC;
}

// ================= Sortari rapide =================
void countingSort(int arr[], long long n){
    if(n <= 0) return;
    int max = arr[0];
    for(long long i = 1; i < n; i++) if(arr[i] > max) max = arr[i];
    int *count = malloc((max+1)*sizeof(int));
    if(!count){ printf("Memorie insuficienta!\n"); return; }
    for(int i = 0; i <= max; i++) count[i] = 0;
    for(long long i = 0; i < n; i++) count[arr[i]]++;
    long long idx = 0;
    for(int i = 0; i <= max; i++){
        while(count[i]-- > 0) arr[idx++] = i;
    }
    free(count);
}

void merge(int arr[], int temp[], long long left, long long mid, long long right){
    long long i=left, j=mid+1, k=left;
    while(i<=mid && j<=right) temp[k++] = (arr[i]<=arr[j])? arr[i++] : arr[j++];
    while(i<=mid) temp[k++] = arr[i++];
    while(j<=right) temp[k++] = arr[j++];
    for(i=left;i<=right;i++) arr[i]=temp[i];
}

void mergeSort(int arr[], int temp[], long long left, long long right){
    if(left>=right) return;
    long long mid=(left+right)/2;
    mergeSort(arr,temp,left,mid);
    mergeSort(arr,temp,mid+1,right);
    merge(arr,temp,left,mid,right);
}

void swap(int *a,int *b){ int tmp=*a; *a=*b; *b=tmp; }

// QuickSort cu pivot random
int partitionRandom(int arr[], long long low, long long high){
    long long pivotIndex = low + rand() % (high - low + 1);
    swap(&arr[pivotIndex], &arr[high]);
    int pivot = arr[high];
    long long i = low - 1;
    for(long long j = low; j < high; j++)
        if(arr[j] < pivot) { i++; swap(&arr[i], &arr[j]); }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}

void quicksortRandom(int arr[], long long low, long long high){
    if(low < high){
        int pi = partitionRandom(arr, low, high);
        quicksortRandom(arr, low, pi-1);
        quicksortRandom(arr, pi+1, high);
    }
}

// RadixSort optimizat cu buffer prealocat
void countingSortForRadix(int arr[], long long n, int exp, int output[]){
    int count[10]={0};
    for(long long i=0;i<n;i++) count[(arr[i]/exp)%10]++;
    for(int i=1;i<10;i++) count[i]+=count[i-1];
    for(long long i=n-1;i>=0;i--){
        int digit=(arr[i]/exp)%10;
        output[count[digit]-1]=arr[i];
        count[digit]--;
    }
    for(long long i=0;i<n;i++) arr[i]=output[i];
}

void radixSort(int arr[], long long n){
    int max=arr[0];
    for(long long i=1;i<n;i++) if(arr[i]>max) max=arr[i];
    int *output=malloc(n*sizeof(int));
    for(int exp=1;max/exp>0;exp*=10) countingSortForRadix(arr,n,exp,output);
    free(output);
}

// ================= MAIN =================
int main(){
    srand(time(NULL));
    long long n;
    printf("Introduceti numarul de elemente: ");
    scanf("%lld",&n);

    int *original=malloc(n*sizeof(int));
    if(!original){ printf("Memorie insuficienta!\n"); return 1; }

    char tip[20];
    printf("Tip lista (random/sortat/invers/aproape/flat): ");
    scanf("%s",tip);

    if(strcmp(tip,"random")==0) gen_random(original,n);
    else if(strcmp(tip,"sortat")==0) gen_sortat(original,n);
    else if(strcmp(tip,"invers")==0) gen_invers(original,n);
    else if(strcmp(tip,"aproape")==0) gen_aproape_sortat(original,n);
    else if(strcmp(tip,"flat")==0) gen_flat(original,n);
    else { printf("Tip invalid!\n"); free(original); return 1; }

    double timeout=20.0;
    printf("\n--- REZULTATE TIMP SORTARI ---\n\n");

    #define RUN_SORT(name, func) { \
        int *v=malloc(n*sizeof(int)); memcpy(v,original,n*sizeof(int)); \
        double t = func; \
        if(t<0) printf(name ": depasit timeout %.3f sec\n",timeout); \
        else printf(name ": %.3f sec\n",t); \
        free(v); \
    }

    RUN_SORT("BubbleSort", bubbleSortTimeout(v,n,timeout));
    RUN_SORT("InsertionSort", insertionSortTimeout(v,n,timeout));
    RUN_SORT("SelectionSort", selectionSortTimeout(v,n,timeout));
    RUN_SORT("ShakerSort", shakerSortTimeout(v,n,timeout));

    // Sortari rapide (fara timeout)
    {
        int *v=malloc(n*sizeof(int)); memcpy(v,original,n*sizeof(int));
        clock_t start=clock();
        countingSort(v,n);
        clock_t end=clock();
        double t=(double)(end-start)/CLOCKS_PER_SEC;
        printf("CountingSort: %.3f sec\n",t);
        free(v);
    }

    {
        int *v=malloc(n*sizeof(int)); int *temp=malloc(n*sizeof(int));
        memcpy(v,original,n*sizeof(int));
        clock_t start=clock();
        mergeSort(v,temp,0,n-1);
        clock_t end=clock();
        double t=(double)(end-start)/CLOCKS_PER_SEC;
        printf("MergeSort: %.3f sec\n",t);
        free(v); free(temp);
    }

    {
        int *v=malloc(n*sizeof(int)); memcpy(v,original,n*sizeof(int));
        clock_t start=clock();
        quicksortRandom(v,0,n-1);
        clock_t end=clock();
        double t=(double)(end-start)/CLOCKS_PER_SEC;
        printf("QuickSort: %.3f sec\n",t);
        free(v);
    }

    {
        int *v=malloc(n*sizeof(int)); memcpy(v,original,n*sizeof(int));
        clock_t start=clock();
        radixSort(v,n);
        clock_t end=clock();
        double t=(double)(end-start)/CLOCKS_PER_SEC;
        printf("RadixSort: %.3f sec\n",t);
        free(v);
    }

    free(original);
    return 0;
}