#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/times.h>
#include <math.h>
#include <ftw.h>
#include <sys/stat.h>
#include <string.h>

static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;

const char arr[] = "work";

const int M = strlen(arr);

int k = 1;

pthread_t *thread;

char **a;

int list(const char *name, const struct stat *status, int type);

void *run(void *arg);

int main(int argc, char * argv[]) {
    int i;
    a=(char **)malloc(k * sizeof(char*));
    if(argc==0)
      return -1;
    if (ftw(argv[1], list, 20) == -1) {
        return -1;
    }
    thread=(pthread_t *)malloc(k * sizeof(pthread_t));
    int *h;
    h=(int *)malloc(k * sizeof(int));
    for(i=0; i<k; i++)
       h[i]=i;
    for(i=0; i<k-1; i++) {
       int res=pthread_create(&thread[i], NULL, &run, &h[i]);
       if (res!=0) {
       perror("Can't create thread");
       exit(1); } }
    for(i=0; i<k-1; i++)
       pthread_join(thread[i], NULL);
    return 0;
}

int list(const char *name, const struct stat *status, int type) {
    status=0;
    if(type == FTW_NS || type == FTW_DNR || type == FTW_D) {
        return 0;
    }
    if(type == FTW_F) {
      a[k-1]=strdup(name);
      k++;
      a=(char **)realloc(a, k * sizeof(char*)); }
    return 0;
}

void *run(void *arg){
     int arg1=*((int*)arg);
     FILE *in;
     pthread_mutex_lock(&mutex);
     in=fopen(a[arg1],"r");
     if(!in) {
         perror("eRROR");
     }
     pthread_mutex_unlock(&mutex);
     int i,j=0,n;
     char *q, t=0;
     q=(char *)malloc(j * sizeof(char));
     for(; fscanf(in,"%c",&t)==1; j++) {
        q=(char *)realloc(q, (j+1) * sizeof(char));
        q[j]=t; }
     n = j;
     for(i = 0, j = 0; ((i + M) < n) && (j < M); i++)
        if(arr[0]==q[i])
            for(j = 1; (j < M) && (j != -1); j++)
                if(arr[j] != q[(i+j)])
                    j = -2;
     pthread_mutex_lock(&mutex);
     if(j == M)
       printf("%s Yes %d \n", a[arg1], arg1);
     else
       printf("%s No %d \n", a[arg1], arg1);
     pthread_mutex_unlock(&mutex);
     return NULL;
}
