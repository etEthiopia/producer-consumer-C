#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define SHMSZ 27
#define N 20

void main(){
	char c;
	int sharedMemoId;


	key_t k;


	int *sharedMemo;
	char *s;

	k = 5674;
	if((sharedMemoId = shmget(k, N * sizeof(int), IPC_CREAT | 0666)) < 0){
		printf("shmget() couldn't successfully get the requested shared memory");
		exit(1);
	}

	if((sharedMemo = shmat(sharedMemoId, NULL, 0)) == (char *) - 1) {
		printf("shmat() couldn't successfully attach segment");
		exit(1);
	}
	
	

	int pos = 0;
	while(pos >= 0 && pos < 10){
		for(int i = 0; i < N;i++){
			if(sharedMemo[i] != NULL){
				printf("%d - %d\n", i,sharedMemo[i]);
			}
		}
		printf("Enter position to update value : ");
		scanf("%d", &pos);
		int value;
		printf("Enter the the new value: ");
		scanf("%d", &value);
		sharedMemo[pos] = value;
	}
	
	exit(0);
}
