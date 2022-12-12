#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 99


int is_visible_with_score(int t_map[MAP_SIZE][MAP_SIZE], int x, int y, int* score){
	int tree = t_map[x][y];
	int hidden_directions = 0;
	int current_score, north_score, south_score, west_score, east_score;

	for(int i = x - 1, j = 1; i >= 0; i--, j++){
		north_score = j;
		if(tree <= t_map[i][y]){
			hidden_directions++;
			break;
		}
	}
	for(int i = x + 1, j = 1; i < MAP_SIZE; i++, j++){
		south_score = j;
		if(tree <= t_map[i][y]){
			hidden_directions++;
			break;
		}
	}
	for(int i = y - 1, j = 1; i >= 0; i--, j++){
		west_score = j;
		if(tree <= t_map[x][i]){
			hidden_directions++;
			break;
		}
	}
	for(int i = y + 1, j = 1; i < MAP_SIZE; i++, j++){
		east_score = j;
		if(tree <= t_map[x][i]){
			hidden_directions++;
			break;
		}
	}

	current_score = north_score * south_score * east_score * west_score;
	if(current_score > *score){
		*score = current_score;
	}
	if(hidden_directions < 4){
		return 1;
	}
	return 0;
}

void count_visible_trees_and_score(int t_map[MAP_SIZE][MAP_SIZE], int* v, int* score){
	for(int i = 1; i < MAP_SIZE - 1; i++){
		for(int j = 1; j < MAP_SIZE - 1; j++){
			if(is_visible_with_score(t_map, i, j, score)){
				*v += 1;
			}
		}
	}
}

int main(int argc, char* argv){

	int tree_map[MAP_SIZE][MAP_SIZE];
	int l = 0;

	char* line = NULL;
	size_t len = 0;

	char* filename = "inputday08";
	FILE* fp = fopen(filename, "r");

	while(getline(&line, &len, fp) != -1) {
		for(int i = 0; i < MAP_SIZE; i++){
			tree_map[l][i] = line[i] - '0';
		}
		l++;
	}

	fclose(fp);
	free(line);

	int visible = MAP_SIZE * 4 - 4;
	int high_score = 1;

	count_visible_trees_and_score(tree_map, &visible, &high_score);

	printf("part1: %d\n", visible);
	printf("part2: %d\n", high_score);

	return 0;
}
