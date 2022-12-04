#include <stdio.h>
#include <stdlib.h>

#define HAND_SIZE 3

#define ROCK 1
#define PAPER 2
#define SCISSORS 3

#define WIN 6
#define DRAW 3
#define LOSS 0

const char* hand1[HAND_SIZE] = {"A", "B", "C"};
const char* hand2[HAND_SIZE] = {"X", "Y", "Z"};
const int scores[HAND_SIZE] = {1, 2, 3};

int get_position(char c, const char* hand[HAND_SIZE]){
	for(int i = 0; i < HAND_SIZE; i++){
		if(c == *hand[i]){
			return i+1;
		}
	}
}

int rps(char c1, char c2){
	int v1 = get_position(c1, hand1);
	int v2 = get_position(c2, hand2);

	if(v1 == v2) {
		return DRAW + scores[v2-1];
	}

	if((v1 == ROCK && v2 == PAPER) || (v1 == PAPER && v2 == SCISSORS) || (v1 == SCISSORS && v2 == ROCK)) {
		return WIN + scores[v2-1];
	}
	else{
		return LOSS + scores[v2-1];
	}
}

int rps2(char c1, char c2){
	int v1 = get_position(c1, hand1);

	if(c2 == 'X'){
		if(v1 == ROCK){
			return SCISSORS + LOSS;
		}
		if(v1 == SCISSORS){
			return PAPER + LOSS;
		}
		return ROCK + LOSS;
	}
	if(c2 == 'Y'){
		return DRAW + scores[v1-1];
	}
	if(v1 == ROCK){
		return PAPER + WIN;
	}
	if(v1 == SCISSORS){
		return ROCK + WIN;
	}
	return SCISSORS + WIN;
}

int main(int argc, char* argv){

	char col1, col2;
	int score1, score2 = 0;

	char* line = NULL;
	size_t len = 0;

	char* filename = "inputday02";
	FILE* fp = fopen(filename, "r");

	while(getline(&line, &len, fp) != -1) {
		col1 = line[0];
		col2 = line[2];
		score1 += rps(col1, col2);
		score2 += rps2(col1, col2);
	}

	fclose(fp);
	free(line);

	printf("score1: %d\n", score1);
	printf("score2: %d\n", score2);

	return 0;
}
