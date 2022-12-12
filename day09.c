#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VISITED 10000

int is_new_position(int tail_x, int tail_y, int* ut_positions, char* visited[]){
	size_t l = sizeof(char) * 10;
	char* position = malloc(l);
	for(int i = 0; i <= *ut_positions - 1; i++){
		snprintf(position, l, "%d,%d", tail_x, tail_y);
		if(strcmp(position, visited[i]) == 0){
			return 0;
		}
	}
	return 1;
}

int is_adjacent(int* head_x, int* head_y, int* tail_x, int* tail_y){
	return (*head_x == *tail_x && *head_y == *tail_y) ||

			(*head_x == *tail_x + 1 && *head_y == *tail_y) ||
			(*head_x == *tail_x - 1 && *head_y == *tail_y) ||
			(*head_y == *tail_y + 1 && *head_x == *tail_x) ||
			(*head_y == *tail_y - 1 && *head_x == *tail_x) ||

			(*head_x == *tail_x + 1 && *head_y == *tail_y + 1) ||
			(*head_x == *tail_x - 1 && *head_y == *tail_y - 1) ||
			(*head_x == *tail_x + 1 && *head_y == *tail_y - 1) ||
			(*head_x == *tail_x - 1 && *head_y == *tail_y + 1);
}

void move_rope(char dir, int steps, int* head_x, int* head_y, int* tail_x, int* tail_y, int* ut_positions, char* visited[]){
	size_t l = sizeof(char) * 10;
	for(int i = 0; i < steps; i++){
		switch(dir){
			case 'U':
				*head_y += 1;
				if(!is_adjacent(head_x, head_y, tail_x, tail_y)){
					*tail_x = *head_x;
					*tail_y += 1;
				}
			break;

			case 'D':
				*head_y -= 1;
				if(!is_adjacent(head_x, head_y, tail_x, tail_y)){
					*tail_x = *head_x;
					*tail_y -= 1;
				}
			break;

			case 'L':
				*head_x -= 1;
				if(!is_adjacent(head_x, head_y, tail_x, tail_y)){
					*tail_y = *head_y;
					*tail_x -= 1;
				}
			break;

			case 'R':
				*head_x += 1;
				if(!is_adjacent(head_x, head_y, tail_x, tail_y)){
					*tail_y = *head_y;
					*tail_x += 1;
				}
			break;
		}
		if(is_new_position(*tail_x, *tail_y, ut_positions, visited)){
			snprintf(visited[*ut_positions], l, "%d,%d", *tail_x, *tail_y);
			*ut_positions += 1;
		}
	}
}

int main(int argc, char* argv){

	int unique_tail_positions = 0;
	int head_x = 0, head_y = 0, tail_x = 0, tail_y = 0;
	char* visited[MAX_VISITED];
	size_t l = sizeof(char) * 10;

	for(int i = 0; i < MAX_VISITED; i++){
		visited[i] = malloc(l);
	}

	snprintf(visited[unique_tail_positions], l, "%d,%d", tail_x, tail_y);
	unique_tail_positions += 1;

	char* line = NULL;
	size_t len = 0;

	char* filename = "inputday09";
	FILE* fp = fopen(filename, "r");

	while(getline(&line, &len, fp) != -1) {
		char dir = line[0];
		int steps = atoi(strtok(&line[1], "\n"));
		move_rope(dir, steps, &head_x, &head_y, &tail_x, &tail_y, &unique_tail_positions, visited);
	}

	fclose(fp);
	free(line);

	printf("part1: %d\n", unique_tail_positions);

	return 0;
}
