#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#define SHMSZ 27
#define N 20

void main(){
	int sharedMemoId;
	key_t k;


	char *s;
	int *sharedMemo;

	k = 5674;

	if((sharedMemoId = shmget(k, N * sizeof(int), 0666)) < 0){
		printf("shmget() couldn't successfully get the requested shared memory");
		exit(1);
	}

	if((sharedMemo = shmat(sharedMemoId, NULL, 0)) == (char *) -1){
		printf("shmat() couldn't successfully attach segment");
		exit(1);
	}
	
	for(int i = 0; i < N ;i++){
		if(sharedMemo[i] != NULL){
			printf("%d - %d\n", i, sharedMemo[i]);
		}
	}
	
	int pos = 0;
	while(pos >= 0 && pos < N){
		printf("Enter position to consume : ");
		scanf("%d", &pos);
		
		if(pos >= 0 && pos < N){
			sharedMemo[pos] = NULL;
		}

		for(int i = 0; i < N;i++){
			if(sharedMemo[i] != NULL){
				printf("%d - %d\n", i,sharedMemo[i]);
			}
		}
	}

	printf("Exiting \n");
	exit(0);
}
