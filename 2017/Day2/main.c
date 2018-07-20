#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool read_line(FILE* input, uint32_t *diff){
    if( input == NULL ){
        return false;
    }

    char* data = NULL;
    size_t s = 0;
    uint32_t n_chars = getline(&data, &s, input);
    if ( n_chars == 0) {
        free(data);
        return false;
    }

    char delim[] = "\t ";
    uint32_t min = UINT32_MAX, max = 0, val;

    char *token = strtok(data, delim);
    if( token == NULL ){
        free(data);
        return false;
    }

    do{
        val = atoi(token);
        if( val < min) {
            min = val;
        }
        if( val > max ){
            max = val;
        }
    } while( (token = strtok(NULL, delim)) != NULL);


    *diff = max - min;

    free(data);
    return true;
}


int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Must pass a valid input file.\n");
        return 0;
    }
    FILE* input = fopen(argv[1], "r");

    uint32_t val, sum = 0;
    while( read_line(input, &val) ){
        sum += val;
    }

    printf("%d\n", sum);

}
