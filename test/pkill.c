#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void* other_thread(void *data)
{
    while(1){
        printf("hai berlian\n");
        sleep(1);
    }
}



int main()
{
    pthread_t thread_saya;
    int kode_status;

    kode_status = pthread_create(&thread_saya, NULL, other_thread, (void*)NULL);
    sleep(10);
    pthread_cancel(thread_saya);
    sleep(5);
    return 0;
}