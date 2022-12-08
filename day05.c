#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 100

char** stacks;
char** temp_stacks;
int n_stacks;

int is_digit(char c){
	return c >= 48 && c <= 57;
}

char* strrev(char* str) {
	if (!str || ! *str){
		return str;
	}

	int i = strlen(str) - 1, j = 0;
	char ch;

	while (i > j){
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
		i--;
		j++;
	}
	return str;
}

void add_to_stack(int x, int y, char c, char** s){
	for(int i = 0; i < y; i++){
		if(s[x][i] == '\0'){
			s[x][i] = ' ';
		}
	}
	s[x][y] = c;
	s[x][y+1] = '\0';
}

void convert_stack(){
	char c;
	for(int i = 0; i < n_stacks; i++){
		for(int j = n_stacks - 1; j >= 0; j--){
			c = temp_stacks[i][j];
			if(c == '\0'){
				continue;
			}
			add_to_stack(j, i, c, stacks);
		}
	}
	for(int k = 0; k < n_stacks; k++){
		stacks[k] = strrev(strtok(strdup(stacks[k]), " "));
	}
}

char* get_top_of_crates(){
	char* res = malloc(sizeof(char) * n_stacks);
	char c;
	for(int i = 0, j = 0; i < n_stacks; i++){
		c = stacks[i][strlen(stacks[i]) - 1];
		if(c != '\0'){
			res[j++] = c;
		}
	}
	return res;
}

void stack_operation(int qty, int from, int to){
	int pos = strlen(stacks[from]) - qty;
	char* carry = strrev(strdup(&stacks[from][pos]));
	char* tmp = malloc(sizeof(char) * STACK_SIZE);
	tmp = strncpy(tmp, stacks[from], pos);
	stacks[from] = tmp;
	tmp = strdup(strcat(stacks[to], carry));
	stacks[to] = tmp;
}


int main(int argc, char* argv){

	int j = 0;
	int n = 0;
	int qty = 0;
	int from = 0;
	int to = 0;
	int count = 0;

	temp_stacks = malloc(sizeof(*temp_stacks) * STACK_SIZE);
        for(int i = 0; i < STACK_SIZE; i++){
		temp_stacks[i] = malloc(sizeof(**temp_stacks) * STACK_SIZE);
        }

	int stack_line_length;
	char* n_stack_line;

	char element[3];

	char* line = NULL;
	size_t len = 0;

	char* filename = "inputday05";
	FILE* fp = fopen(filename, "r");

	while(getline(&line, &len, fp) != -1) {
		if(line[0] == 'm'){
			strtok(line, " ");
			qty = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			from = atoi(strtok(NULL, " "));
			strtok(NULL, " ");
			to = atoi(strtok(NULL, " "));
			stack_operation(qty, from - 1, to - 1);
		}
		else if(line[0] == '\n'){
			stacks = malloc(sizeof(*stacks) * n_stacks);
			for(int i = 0; i < n_stacks; i++){
				stacks[i] = malloc(sizeof(**stacks) * STACK_SIZE);
			}
			convert_stack();
			free(temp_stacks);
		}
		else {
			if(line[0] == ' ' && is_digit(line[1])){
				n_stack_line = strtok(line, " ");
				while(n_stack_line != NULL){
					n = atoi(n_stack_line);
					if(n > n_stacks){
						n_stacks = n;
					}
					n_stack_line = strtok(NULL, " ");
				}
			}
			else {
				while(strlen(line) >= 4){
					memcpy(element, line, 3);
					if(element[1] != ' '){
						add_to_stack(j, count, element[1], temp_stacks);
					}
					if(strlen(line) == 4){
						line = NULL;
						break;
					}
					count++;
					line = &line[4];
				}
				j++;
				count = 0;
			}
		}
	}

	char* top_of_crates = get_top_of_crates();

	fclose(fp);
	free(line);

	printf("part1: %s\n", top_of_crates);
	//printf("part2: %d\n", len);

	return 0;
}
