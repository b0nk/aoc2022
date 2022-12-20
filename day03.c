#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_priority(char c){
	int prio = (int)c;

	if(prio <= 90){
		return prio - 38;
	}
	return prio - 96;
}

char get_shared_item(char* container){
	char item;
	int found = 0;
	int length = strlen(container) - 1;

	for(int i = 0; found == 0 && i <= length/2; i++){
		for(int j = length; j >= length/2; j--){
			if(container[i] == container[j]){
				item = container[i];
				found = 1;
				break;
			}
		}
	}
	return item;
}

char get_common_item(char* group_items){
	int length = 0;
	char* line;
	char* next_line;
	char* save_ptr;
	char* tmp = strdup(group_items);

	line = strtok_r(group_items, "\n", &save_ptr);
	length = strlen(line);
	for(int i = 0; i < length; i++){
		char c = line[i];
		next_line = strtok_r(NULL, "\n", &save_ptr);
		if(strchr(next_line, c) != NULL){
			next_line = strtok_r(NULL, "\n", &save_ptr);
			if(strchr(next_line, c) != NULL){
				return c;
			}
		}
		group_items = strdup(tmp);
		line = strtok_r(group_items, "\n", &save_ptr);
	}
}

int main(int argc, char* argv){

	char shared;
	int priority = 0;
	int priority_p2 = 0;
	int counter = 0;
	char* grouped = (char*)malloc(sizeof(char) * 1000);

	char line[BUFSIZ];

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		shared = get_shared_item(line);
		priority += get_priority(shared);

		if(counter == 0 || counter % 3 != 0) {
			strcat(grouped, line);
		} else {
			shared = get_common_item(grouped);
			priority_p2 += get_priority(shared);
			strcpy(grouped, line);
		}
		counter++;
	}

	if(counter % 3 == 0){
		shared = get_common_item(grouped);
		priority_p2 += get_priority(shared);
	}

	printf("part1: %d\n", priority);
	printf("part2: %d\n", priority_p2);

	return 0;
}
