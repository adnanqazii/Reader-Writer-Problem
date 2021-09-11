#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define MAX 1000

void reader();
void writer();


int main(void)
{
	key_t key = 1234;

	sem_t *rw_mutex;
	sem_t *mutex;
	char *mname = "mutex";
	char *rname = "write";
	int val = 1;
	if(sem_unlink(mname)==-1) {
		printf("sum_unlink\n");
	}
	if(sem_unlink(rname)==-1) {
		printf("sum_unlink\n");
	}
	int shmid;
	if ((shmid = shmget(key, sizeof(int), 0)) ==-1)
	{
		perror("shmget");
		exit(-1);
	}
	if(shmctl(shmid, IPC_RMID, NULL)==-1) {
		perror("shmctl\n");
		exit(-1);
	}
}
