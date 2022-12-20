#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PACKET 4
#define MESSAGE 14

int has_duplicate(char* seq){
	size_t l = strlen(seq);
	for(int i = 0; i < l; i++){
		for(int j = i + 1; j < l; j++){
			if(seq[i] == seq[j]){
				return 1;
			}
		}
	}
	return 0;
}

int find_data(char* str, int type){
	int res = 0;
	size_t length = strlen(str) - 1;
	char* seq = malloc(sizeof(char) * type);

	for(int i = 0; i < length; i++){
		seq = strncpy(seq, &str[i], type);
		if(strlen(seq) < type){
			break;
		}
		if(!has_duplicate(seq)){
			res = i + type;
			break;
		}
	}
	return res;
}

int main(int argc, char* argv){

	int marker_pos = 0;
	int msg_pos = 0;

	char line[BUFSIZ];

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		marker_pos = find_data(line, PACKET);
		msg_pos = find_data(line, MESSAGE);
	}

	printf("part1: %d\n", marker_pos);
	printf("part2: %d\n", msg_pos);

	return 0;
}
