#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>



#include <fcntl.h>

#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
	key_t key = 1234;
	int shmid;
	int *read_count;
	// char sentence[20];
	// fgets(sentence, sizeof(sentence), stdin);
	if ((shmid = shmget(key, sizeof(int), IPC_CREAT | 0666)) < -1)
	{
		perror("shmget");
		exit(-1);
	}
	if ((read_count = shmat(shmid, NULL, 0)) == (int *)-1)
	{
		perror("shmat");
		exit(-1);
	}
	*read_count = 0;
}