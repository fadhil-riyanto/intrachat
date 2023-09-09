#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signalrecv(int sig_number)
{
    printf("%d we goot signal", sig_number);
    (void) signal(SIGINT, SIG_DFL);
    
}


int main(int argc, char *argv[])
{
    (void) signal(SIGINT, signalrecv);


    sleep(1);

}