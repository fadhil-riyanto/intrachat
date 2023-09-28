
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* threadrn(void *pointer)
{
    int *a = *(int*)pointer;
    printf("hello from thread %d\n", *a);
    return 0;
}

int main()
{
    int ret;
    int data = 999;
    printf("hello from main\n");
    pthread_t thread;
    ret = pthread_create(&thread, NULL, threadrn, (void*)777);

    printf("pthread ret %d\n", ret);
    sleep(1);
    pthread_cancel(thread);
    pthread_join(thread, NULL);
    return 0;
}