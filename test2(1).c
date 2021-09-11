#include <linux/kernel.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>


void reader();
void writer();

int main(void)
{
	int check;
	long int s = syscall(442);
	printf("System Call: %ld\n",s);
	

	printf("Enter 1 to read file\n");
	printf("Enter 2 to Write file\n");
	printf("Enter 0 to exit\n");
	scanf("%d",&check);
	getchar();

	if(check == 1){
		key_t key = 1234;
	int shmid;
	int *read_count;
	sem_t *rw_mutex;
	sem_t *mutex;
	
	char *mname = "mutex";
	char *rname = "write";
	int val = 1;
	rw_mutex = sem_open(rname, O_CREAT, 0666, val);
	mutex = sem_open(mname, O_CREAT, 0666, val);
	
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
	
	sem_wait(mutex);
	(*read_count)++;
	if ((*read_count) == 1)
	{
		int a=1;
		sem_getvalue(rw_mutex, &a);
		if (a == 0)
		{
			printf("reader:waiting for writers to finish\n");
		}
		sem_wait(rw_mutex);
		if(a==0) {
			printf("reader:finished waiting for writers\n");
		}
	}

	sem_post(mutex);

	char ch;
	FILE *fp;
	fp = fopen("Test.txt", "r");

	if (fp == NULL)
	{
		perror("Error while opening the file.\n");
		exit(1);
	}

	printf("reader:The contents of file are:\n");

	while ((ch = fgetc(fp)) != EOF)
	{
		printf("%c", ch);
	}
	printf("\n");
	fclose(fp);
	sem_wait(mutex);
	(*read_count)--;
	if ((*read_count) == 0)
	{
		sem_post(rw_mutex);
	}
	sem_post(mutex);
	sem_close(mutex);
	sem_close(rw_mutex);
	}
	
	else if(check == 2){
		key_t key = 1234;
	int shmid;
	sem_t *rw_mutex;

	char *rname = "write";
	int val = 1;
	rw_mutex = sem_open(rname, O_CREAT, 0666, val);
	int a=1;
	sem_getvalue(rw_mutex, &a);
	if (a == 0)
	{
		printf("writer:waiting for readers/writers to finish\n");
	}
	sem_wait(rw_mutex);
	if(a==0) {
		printf("writer:finished waiting for  readers/writers\n");
	}
	char sentence[1000];
	FILE *fptr;
	fptr = fopen("Test.txt", "a");

	if (fptr == NULL)
	{
		printf("Error!");
		exit(1);
	}
	printf("writer:Enter to write(append)  to file:\n");
	
	fgets(sentence, sizeof(sentence), stdin);
	fprintf(fptr, "%s", sentence);
	fclose(fptr);
	sem_post(rw_mutex);
	sem_close(rw_mutex);
	}

	else{
		printf("Exiting\n");
		exit(1);
	}
}

