#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRENGTH_SIZE 6

void increment_cycle(int* cycle, int* rax, int* next_print, int* strength_list[], int* count){
	*cycle += 1;
	if(*cycle == *next_print){
		*strength_list[*count] = *cycle * *rax;
		*count += 1;
		*next_print += 40;
	}
}

int main(int argc, char* argv){

	int rax = 1;
	int arg;
	int cycle = 0;
	int next_print = 20;
	int strength_count = 0;
	int* strength_list[STRENGTH_SIZE];

	for(int i = 0; i < STRENGTH_SIZE; i++){
		strength_list[i] = malloc(sizeof(int));
	}

	char* line = NULL;
	size_t len = 0;

	char* filename = "inputday10";
	FILE* fp = fopen(filename, "r");

	while(getline(&line, &len, fp) != -1) {
		if(line[0] == 'n'){
			increment_cycle(&cycle, &rax, &next_print, strength_list, &strength_count);
		}
		else{
			increment_cycle(&cycle, &rax, &next_print, strength_list, &strength_count);
			increment_cycle(&cycle, &rax, &next_print, strength_list, &strength_count);
			arg = atoi(&line[4]);
			rax += arg;
		}
	}

	fclose(fp);
	free(line);

	int strength_sum = 0;
	for(int i = 0; i < strength_count; i++){
		strength_sum += *strength_list[i];
	}

	printf("part1: %d\n", strength_sum);

	return 0;
}
