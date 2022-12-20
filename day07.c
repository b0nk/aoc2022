#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 50
#define MAX_FOLDERS 50
#define MAX_FILENAME 100
#define MAX_FOLDER_SIZE 100000
#define STORAGE_SPACE 70000000
#define UPDATE_SIZE 30000000


typedef struct {
	int size;
	char name[MAX_FILENAME];
} File;

typedef struct Folder {
	char name[MAX_FILENAME];
	struct Folder *parent; 
	int total_size;
	int n_files;
	File *files[MAX_FILES];
	int n_folders;
	struct Folder *folders[MAX_FOLDERS];
} Folder;

Folder* create_folder(Folder* parent, char* name){
	Folder* d = malloc(sizeof(Folder));
	strcpy(d->name, name);
	d->parent = parent;
	d->n_files = 0;
	d->n_folders = 0;
	d->total_size = 0;

	if(parent != NULL){
		parent->folders[parent->n_folders] = d;
		parent->n_folders++;
	}

	return d;
}

File* create_file(char* name, int size) {
	File* f = (File*)malloc(sizeof(File));
	f->size = size;
	strcpy(f->name,name);
	return f;
}

void update_parents(Folder* cursor, int size){
	if(cursor == NULL) {
		return;
	}
	cursor->total_size = cursor->total_size + size;
	update_parents(cursor->parent, size);
}

void add_file_to_folder(Folder* folder, File* file) {
	folder->files[folder->n_files] = file;
	folder->n_files = folder->n_files + 1;
	folder->total_size = folder->total_size + file->size;
	update_parents(folder->parent, file->size);
}

Folder* change_dir(Folder* cursor, char* destination){
	if(strcmp(destination, "/") == 0){
		while(cursor->parent != NULL){
			cursor = cursor->parent;
		}
		return cursor;
	}
	if(strcmp(destination, "..") == 0){
		return cursor->parent;
	}
	for(int i = 0; i < cursor->n_folders; i++){
		if(strcmp(cursor->folders[i]->name, destination) == 0){
			return cursor->folders[i];
		}
	}
}

void calculate_folder_sizes(Folder* cursor, Folder* list[], int* count, int limit){
	for(int i = 0; i <= cursor->n_folders - 1; i++){
		calculate_folder_sizes(cursor->folders[i], list, count, limit);
	}

	if(cursor->total_size <= limit){
		list[*count] = cursor;
		*count += 1;
	}
}

void calculate_needed_space(Folder* cursor, Folder* list[], int* count, int limit){
	for(int i = 0; i <= cursor->n_folders - 1; i++){
		calculate_needed_space(cursor->folders[i], list, count, limit);
	}

	if(cursor->total_size >= limit){
		list[*count] = cursor;
		*count += 1;
	}
}

int is_digit(char c){
	return c >= 48 && c <= 57;
}

int main(int argc, char* argv){

	Folder* root = create_folder(NULL, "/");
	Folder* cursor = root;

	char* command;
	char* arg;

	char line[BUFSIZ];

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		if(line[0] == '$'){
			command = strtok(strdup(&line[2]), " ");
			if(strcmp(command, "ls") == 0){
				continue;
			}
			if(strcmp(command, "cd") == 0){
				arg = strtok(strtok(&line[4], " "), "\n");
				cursor = change_dir(cursor, arg);
			}
		}
		else if(is_digit(line[0])){
			char* col1 = strtok(line, " ");
			char* col2 = strtok(NULL, "\n");
			File* f = create_file(col2, atoi(col1));
			add_file_to_folder(cursor, f);
		}
		else{
			strtok(line, " ");
			char* col2 = strtok(NULL, "\n");
			Folder* f = create_folder(cursor, col2);
		}
	}

	int sum = 0;
	int list_n = 0;
	Folder* list[50];

	calculate_folder_sizes(root, list, &list_n, MAX_FOLDER_SIZE);

	for(int i = 0; i < list_n; i++){
		sum += list[i]->total_size;
	}

	int free = STORAGE_SPACE - root->total_size;
	int target = UPDATE_SIZE - free;

	list_n = 0;

	calculate_needed_space(root, list, &list_n, target);

	int result = STORAGE_SPACE;
	for(int i = 0; i < list_n; i++){
		if(list[i]->total_size < result){
			result = list[i]->total_size;
		}
	}

	printf("part1: %d\n", sum);
	printf("part2: %d\n", result);

	return 0;
}
