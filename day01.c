#include <stdio.h>
#include <stdlib.h>

#define LENGTH 3
int top3[LENGTH];

void initialize_top3(){
	for(int i = 0; i < LENGTH; i++){
		top3[i] = 0;
	}
}

void process_top3(int v){
	for(int i = 0; i < LENGTH; i++){
		if(v > top3[i]){
			for(int j = LENGTH; j > i; j--){
				top3[j] = top3[j-1];
			}
			top3[i] = v;
			break;
		}
	}
}

int main(int argc, char* argv){

	int current_max, current_sum, current_value = 0;

	initialize_top3();

	char* line = NULL;
	size_t len = 0;

	char* filename = "inputday01";
	FILE* fp = fopen(filename, "r");

	while(getline(&line, &len, fp) != -1) {
		if((char) *line == '\n'){
			if(current_sum > current_max){
				current_max = current_sum;
				process_top3(current_max);
			}
			current_sum = 0;
		}
		else{
			current_value = atoi(line);
			current_sum += current_value;
		}
	}

	fclose(fp);
	free(line);

	int top3_total = 0;

	for(int i = 0; i < LENGTH; i++){
		top3_total += top3[i];
	}

	printf("max: %d\n", current_max);
	printf("top 3 summed: %d\n", top3_total);

	return 0;
}