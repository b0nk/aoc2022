#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_SIZE 99


int is_visible(int t_map[MAP_SIZE][MAP_SIZE], int x, int y){
	int tree = t_map[x][y];
	int hidden_directions = 0;

	for(int i = x - 1; i >= 0; i--){
		if(tree <= t_map[i][y]){
			hidden_directions++;
			break;
		}
	}
	for(int i = x + 1; i < MAP_SIZE; i++){
		if(tree <= t_map[i][y]){
			hidden_directions++;
			break;
		}
	}
	for(int i = y - 1; i >= 0; i--){
		if(tree <= t_map[x][i]){
			hidden_directions++;
			break;
		}
	}
	for(int i = y + 1; i < MAP_SIZE; i++){
		if(tree <= t_map[x][i]){
			hidden_directions++;
			break;
		}
	}
	if(hidden_directions < 4){
		return 1;
	}
	return 0;
}

void count_visible_trees(int t_map[MAP_SIZE][MAP_SIZE], int* v){
	for(int i = 1; i < MAP_SIZE - 1; i++){
		for(int j = 1; j < MAP_SIZE - 1; j++){
			if(is_visible(t_map, i, j)){
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
		int length = strlen(line);
		for(int i = 0; i < length; i++){
			tree_map[l][i] = line[i] - '0';
		}
		l++;
	}

	fclose(fp);
	free(line);

	int visible = MAP_SIZE * 4 - 4;

	count_visible_trees(tree_map, &visible);

	printf("part1: %d\n", visible);

	return 0;
}
