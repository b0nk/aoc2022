#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VISITED 10000
#define ROPE_LENGTH 9

typedef struct {
	int x;
	int y;
} Knot;

Knot* create_knot(){
	Knot* k = (Knot*)malloc(sizeof(Knot));
	k->x = 0;
	k->y = 0;
	return k;
}

void add_to_visited(Knot* tail, Knot* visited[], int* unique_tail_positions){
	for(int i = 0; i <= *unique_tail_positions - 1; i++){
		if(visited[i]->x == tail->x && visited[i]->y == tail->y){
			return;
		}
	}
	memcpy(visited[*unique_tail_positions], tail, sizeof(Knot));
	*unique_tail_positions += 1;
}

void move_head(Knot* head, char dir){
	switch(dir){
		case 'U':
			head->y += 1;
		break;

		case 'D':
			head->y -= 1;
		break;

		case 'L':
			head->x -= 1;
		break;

		case 'R':
			head->x += 1;
		break;
	}
}

void move_tail(Knot* head, Knot* tail){
	int diff_x = head->x - tail->x;
	int diff_y = head->y - tail->y;

	if(abs(diff_x) == 2 || abs(diff_y) == 2){
		if(diff_x < 0){
			tail->x -= 1;
		}
		else if(diff_x > 0){
			tail->x += 1;
		}
		if(diff_y < 0){
			tail->y -= 1;
		}
		else if(diff_y > 0){
			tail->y += 1;
		}
	}
}

int main(int argc, char* argv){

	int unique_tail_positions = 0, unique_rope_positions = 0;
	Knot* head = create_knot();
	Knot* tail = create_knot();
	Knot* visited[MAX_VISITED];
	Knot* rope[ROPE_LENGTH];
	Knot* rope_traveled[MAX_VISITED];

	for(int i = 0; i < MAX_VISITED; i++){
		visited[i] = malloc(sizeof(Knot));
	}
	for(int i = 0; i < ROPE_LENGTH; i++){
		rope[i] = malloc(sizeof(Knot));
	}
	for(int i = 0; i < MAX_VISITED; i++){
		rope_traveled[i] = malloc(sizeof(Knot));
	}

	memcpy(visited[unique_tail_positions], tail, sizeof(Knot));
	unique_tail_positions += 1;

	char* line = NULL;
	size_t len = 0;

	char* filename = "inputday09";
	FILE* fp = fopen(filename, "r");

	while(getline(&line, &len, fp) != -1) {
		char dir = line[0];
		int steps = atoi(strtok(&line[1], "\n"));
		for(int i = 0; i < steps; i++){
			move_head(head, dir);
			move_tail(head, tail);
			move_tail(head, rope[0]);
			add_to_visited(tail, visited, &unique_tail_positions);
			for(int j = 1; j < ROPE_LENGTH; j++){
				move_tail(rope[j-1], rope[j]);
			}
			add_to_visited(rope[ROPE_LENGTH-1], rope_traveled, &unique_rope_positions);
		}
	}

	fclose(fp);
	free(line);

	printf("part1: %d\n", unique_tail_positions);
	printf("part2: %d\n", unique_rope_positions);

	return 0;
}
