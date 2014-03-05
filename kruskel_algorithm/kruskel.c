/**
 * Usage: ./KRUSKEL  <vertices> <edges>
 **/

#include <stdio.h>

int graph[100][100];

int main(int argc, char **argv) {
	int e, v;
	
	if(argc < 3) {
		printf("\nERROR!! \nUsage: %s <vertices> <edges>\n");
		exit(1);
	}

	sscanf(argv[1], "%d", &v);
	sscanf(argv[2], "%d", &e);
	makeGraphSet(v, e);
	return 0;
}
