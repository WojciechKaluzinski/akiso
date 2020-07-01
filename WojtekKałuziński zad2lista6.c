#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

typedef struct {
	int size;
	int** m1;
	int** m2;
	int** res;
} matrices;


int** alloc_matrix(int size, int fill) {
	srand(time(NULL));
	
	int** matrix = calloc(size, sizeof(int*));
	
	for (int i = 0; i < size; i++) {
		matrix[i] = calloc(size, sizeof(int));
		if (fill > 0) {
			for (int j = 0; j < size; j++){
                        	matrix[i][j] = rand() % fill;
                        }
                printf("\n");
		}
	}
        printf("\n");
	return matrix;
}


pthread_mutex_t mutex;
int curr_row = 0;

void* mult(void* vargp) {
	matrices* m = (matrices*) vargp;
	
	while (curr_row < m->size) {

		pthread_mutex_lock(&mutex);
		int row = curr_row;
		curr_row++;
		pthread_mutex_unlock(&mutex);
		
		for (int i = 0; i < m->size; i++) {
			for (int j = 0; j < m->size; j++) {
				m->res[row][i] |= (m->m1[row][j] & m->m2[j][i]);
				if (m->res[row][i] == 1) break;
			}
		}
	}


	pthread_exit(0);
}

int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("jako argumenty wpisz: [rozmiar macierzy] [ilość wątków]\n");
		return 1;
	}
	
	
	int size = atoi(argv[1]);
	int tnum = atoi(argv[2]);
	
	matrices m;
	
	m.size = size;
	
	m.m1 = alloc_matrix(size, 2);
	m.m2 = alloc_matrix(size, 2);
	m.res = alloc_matrix(size, 0);
	
	pthread_mutex_init(&mutex, NULL);
	pthread_t threadIds[tnum];

	
	for (int i = 0; i < tnum; i++) {
		printf("wątek %d zaczął\n", i);
		pthread_create(&threadIds[i], NULL, &mult, &m);
	}
	
	for (int i = 0; i < tnum; i++) {
		pthread_join(threadIds[i], NULL);
		printf("wątek %d skończył\n", i);
	}



   printf("\nmacierz 1:\n");
	for(int i=0;i<m.size;i++)
	{
		printf("\n");
		for(int j=0; j<m.size;j++)
		{	
			printf("%d ",m.m1[i][j]);
		}
	}

   printf("\nmacierz 2:\n");
	for(int i=0;i<m.size;i++)
	{
		printf("\n");
		for(int j=0; j<m.size;j++)
		{	
			printf("%d ",m.m2[i][j]);
		}
	}

         printf("\nResult matrix:\n");
	for(int i=0;i<m.size;i++)
	{
		printf("\n");
		for(int j=0; j<m.size;j++)
		{	
			printf("%d ",m.res[i][j]);
		}
	}
	
	pthread_mutex_destroy(&mutex);


	printf("\nkoniec, do widzenia :)\n");
	return 0;
}
