
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* threadrn(void *pointer)
{
    printf("hello from thread\n");
    return 0;
}

int main()
{
    int ret;
    printf("hello from main\n");
    pthread_t thread;
    ret = pthread_create(&thread, NULL, threadrn, (void*)9);

    printf("pthread ret %d\n", ret);
    sleep(1);
    pthread_cancel(thread);
    pthread_join(thread, NULL);
    return 0;
}