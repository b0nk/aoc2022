#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_ITEMS 100
#define N_MONKEYS 8
#define ROUNDS 20
#define ROUNDS_P2 10000
#define TOP_MONKEYS 2

typedef struct {
	uint64_t items[MAX_ITEMS];
	int n_items;
	char operation;
	uint64_t op_value;
	uint64_t test_divisible;
	int monkey_true;
	int monkey_false;
	int inspected;
} Monkey;

Monkey create_monkey(){
	Monkey* m = malloc(sizeof(Monkey));
	m->n_items = 0;
	m->inspected = 0;
	for(int i = 0; i < MAX_ITEMS; i++){
		m->items[i] = 0;
	}
	return *m;
}

void add_items_to_monkey(Monkey* m, char* list){
	char* tok = strtok(list, ",");
	while(tok != NULL){
		int element = atoi(tok);
		m->items[m->n_items] = element;
		m->n_items += 1;
		tok = strtok(NULL, ",");
	}
}

void add_operation_to_monkey(Monkey* m, char* operation){
	char op = operation[5];
	int value = atoi(&operation[6]);
	m->operation = op;
	m->op_value = value;
}

void add_condition_to_monkey(Monkey* m, char* cond){
	int value = atoi(cond);
	m->test_divisible = value;
}

void add_target_to_monkey(Monkey* m, char* target, int true_cond){
	int value = atoi(target);
	if(true_cond){
		m->monkey_true = value;
	}
	else{
		m->monkey_false = value;
	}
}

uint64_t get_worry(uint64_t item, char op, uint64_t value){
	if(op == '+'){
		return item + value;
	}
	if(value == 0){
		return item * item;
	}
	return item * value;
}

int pass_test(uint64_t v, uint64_t div){
	return v % div == 0;
}

void throw_item(Monkey* src, Monkey* target, uint64_t bored){
	for(int i = target->n_items; i > 0; i--){
		target->items[i] = target->items[i-1];
	}
	target->items[0] = bored;
	target->n_items += 1;
}

void play_rounds(int rounds, Monkey monkeys[], int part1, uint64_t common_multiple){
	for(int i = 0; i < rounds; i++){
		for(int j = 0; j < N_MONKEYS; j++){
			Monkey* curr = &monkeys[j];
			for(int k = 0; k < curr->n_items; k++){
				int item = curr->items[k];
				char op = curr->operation;
				uint64_t op_value = curr->op_value;
				uint64_t worry = get_worry(item, op, op_value);
				uint64_t bored;
				if(part1){
					bored = worry / 3;
				}
				else{
					bored = worry % common_multiple;
				}
				if(pass_test(bored, curr->test_divisible)){
					throw_item(curr, &monkeys[curr->monkey_true], bored);
				}
				else {
					throw_item(curr, &monkeys[curr->monkey_false], bored);
				}
				curr->items[k] = 0;
			}
			curr->inspected += curr->n_items;
			curr->n_items = 0;
		}
	}
}

void process_top(uint64_t top[], int v){
	for(int i = 0; i < TOP_MONKEYS; i++){
		if(v > top[i]){
			for(int j = TOP_MONKEYS; j > i; j--){
				top[j] = top[j-1];
			}
			top[i] = v;
			break;
		}
	}
}

int main(int argc, char* argv){

	Monkey monkeys[N_MONKEYS];
	Monkey monkeys_p2[N_MONKEYS];
	int monkey_idx = -1;

	for(int i = 0; i < N_MONKEYS; i++){
		monkeys[i] = create_monkey();
	}

	uint64_t top_inspections[TOP_MONKEYS];
	for(int i = 0; i < TOP_MONKEYS; i++){
		top_inspections[i] = 0;
	}

	char line[BUFSIZ];

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		if(line[0] == '\n'){
			continue;
		}
		if(line[0] == 'M'){
			monkey_idx++;
		}
		else if(line[2] == 'S'){
			strtok(line, ":");
			char* list = strtok(NULL, ":");
			add_items_to_monkey(&monkeys[monkey_idx], list);
		}
		else if(line[2] == 'O'){
			strtok(line, "=");
			char* operation = strtok(NULL, "=");
			add_operation_to_monkey(&monkeys[monkey_idx], operation);
		}
		else if(line[2] == 'T'){
			strtok(line, "y");
			char* div = strtok(NULL, "y");
			add_condition_to_monkey(&monkeys[monkey_idx], div);
		}
		else if(line[7] == 't'){
			strtok(line, "y");
			char* target_monkey = strtok(NULL, "y");
			add_target_to_monkey(&monkeys[monkey_idx], target_monkey, 1);
		}
		else if(line[7] == 'f'){
			strtok(line, "y");
			char* target_monkey = strtok(NULL, "y");
			add_target_to_monkey(&monkeys[monkey_idx], target_monkey, 0);
		}
	}

	memcpy(monkeys_p2, monkeys, sizeof(monkeys));
	
	uint64_t common_multiple = 1;
	for (int i = 0; i < N_MONKEYS; i++){
		common_multiple *= monkeys[i].test_divisible;
	}

	play_rounds(ROUNDS, monkeys, 1, common_multiple);

	for(int i = 0; i < N_MONKEYS; i++){
		int inspected = monkeys[i].inspected;
		process_top(top_inspections, inspected);
	}

	uint64_t result = 1;
	for(int i = 0; i < TOP_MONKEYS; i++){
		result *= top_inspections[i];
	}

	printf("part1: %"PRIu64"\n", result);

	play_rounds(ROUNDS_P2, monkeys_p2, 0, common_multiple);

	for(int i = 0; i < TOP_MONKEYS; i++){
		top_inspections[i] = 0;
	}

	for(int i = 0; i < N_MONKEYS; i++){
		int inspected = monkeys_p2[i].inspected;
		process_top(top_inspections, inspected);
	}

	result = 1;
	for(int i = 0; i < TOP_MONKEYS; i++){
		result *= top_inspections[i];
	}

	printf("part2: %"PRIu64"\n", result);

	return 0;
}
