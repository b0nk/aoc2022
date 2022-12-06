#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_contained_overlapped(char* c1, char* c2, int contained){

        char* ptr1;
        char* ptr2;
        char* c1min = strtok_r(c1, "-", &ptr1);
        char* c1max = strtok_r(NULL, "-", &ptr1);
        char* c2min = strtok_r(c2, "-", &ptr2);
        char* c2max = strtok_r(NULL, "-", &ptr2);

        int c1bottom = atoi(c1min);
        int c1top = atoi(c1max);
        int c2bottom = atoi(c2min);
        int c2top = atoi(c2max);

        if(contained){
                return (c1bottom >= c2bottom && c1top <= c2top) || (c2bottom >= c1bottom && c2top <= c1top);
        }
        return ((c1bottom <= c2top && c1bottom >= c2bottom) || (c2bottom <= c1top && c2bottom >= c1bottom)) ||
                ((c1top >= c2bottom && c1top <= c2top) || (c1top >= c2bottom && c1top <= c2top));
}

int main(int argc, char* argv){

        char* range1;
        char* range2;
        char* save_ptr;
        int contained = 0;
        int overlapped = 0;

        char* line = NULL;
        size_t len = 0;

        char* filename = "inputday04";
        FILE* fp = fopen(filename, "r");

        while(getline(&line, &len, fp) != -1) {
                range1 = strtok_r(line, ",", &save_ptr);
                range2 = strtok_r(NULL, "\n", &save_ptr);
                if(is_contained_overlapped(strdup(range1), strdup(range2), 1)){
                        contained++;
                }
                if(is_contained_overlapped(strdup(range1), strdup(range2), 0)){
                        overlapped++;
                }
        }

        fclose(fp);
        free(line);

        printf("part1: %d\n", contained);
        printf("part2: %d\n", overlapped);

        return 0;
}
