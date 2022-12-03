#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv){

	char* filename = "inputday01";
	FILE *fp = fopen(filename, "r");

	char *line = NULL;
	size_t len = 0;

	int current_max, current_sum, value = 0;

	while(getline(&line, &len, fp) != -1) {
		if((char) *line == '\n'){
			if(current_sum > current_max){
				current_max = current_sum;
			}
			current_sum = 0;
		}
		else{
			value = atoi(line);
			current_sum += value;
		}
	}

	fclose(fp);
	free(line);

	printf("result: %d\n", current_max);

	return 0;
}
