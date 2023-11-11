#include <pthread.h>
#include <stdio.h>

int mainvar = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* fn(void *nullptr)
{
    // unclocked
    // for(int a = 0; a < 10000; a++) {
    //     mainvar = mainvar + 1;
    // }

    // locked
    pthread_mutex_lock(&mutex);
    for(int a = 0; a < 10000; a++) {
        mainvar = mainvar + 1;
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    int n = 20;

    // sync
    // for(int a = 0; a < n; a++) {
    //     fn(NULL);
    // }
    // printf("%d current\n", mainvar);
    // return 0;

    
    // pthreaded
    pthread_t thread[n];

    for(int a = 0; a < n; a++) {
        pthread_create(&thread[a], NULL, fn, NULL);
    }

    for(int a = 0; a < n; a++) {
        pthread_join(thread[a], NULL);
    }
    

    printf("%d current\n", mainvar);
}