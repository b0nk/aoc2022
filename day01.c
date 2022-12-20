#include <stdio.h>
#include <stdlib.h>

#define LENGTH 3

void initialize_top(int top[]){
	for(int i = 0; i < LENGTH; i++){
		top[i] = 0;
	}
}

void process_top(int v, int top[]){
	for(int i = 0; i < LENGTH; i++){
		if(v > top[i]){
			for(int j = LENGTH; j > i; j--){
				top[j] = top[j-1];
			}
			top[i] = v;
			break;
		}
	}
}

int main(int argc, char* argv){

	int current_max, current_sum, current_value, top_total = 0;
	int top[LENGTH];

	initialize_top(top);

	char line[BUFSIZ];

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		if(line[0] == '\n'){
			if(current_sum > current_max){
				current_max = current_sum;
				process_top(current_max, top);
			}
			current_sum = 0;
		}
		else{
			current_value = atoi(line);
			current_sum += current_value;
		}
	}

	for(int i = 0; i < LENGTH; i++){
		top_total += top[i];
	}

	printf("part1: %d\n", current_max);
	printf("part2: %d\n", top_total);

	return 0;
}
