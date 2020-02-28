#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

using namespace std;

void writer_process(int shmid) {
    // shmat to attach to shared memory
    char *str = (char *)shmat(shmid, (void *)0, 0);

    cout << "Write Data : ";
    gets(str);

    printf("Data written in memory: %s\n", str);

    //detach from shared memory
    shmdt(str);
}

int main() {
    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    cout << "shmid: " << shmid << endl;

    int pid = fork();

    if (pid == 0) {
        // Child process
        const char *shmid_str = to_string(shmid).c_str();
        execl("./reader_process", "reader_process", shmid_str);
        return (1);
    } else if (pid > 0) {
        // Parent process
        writer_process(shmid);

        int wait_pid;
        if ((wait_pid = wait(NULL)) < 0) {
            cout << "wait failed?" << endl;
            // destroy the shared memory
            shmctl(shmid, IPC_RMID, NULL);
            return 1;
        }
        // destroy the shared memory
        shmctl(shmid, IPC_RMID, NULL);

        // If the memory is not destroyed here, another process can attach to it even after this process terminates
    } else {
        // Error
        return 1;
    }

    return 0;
}
