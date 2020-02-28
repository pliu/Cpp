#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    sleep(3);

    int shmid = stoi(argv[1]);

    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);

    printf("Data read from memory: %s\n", str);

    //detach from shared memory
    shmdt(str);

    return 0;
}
