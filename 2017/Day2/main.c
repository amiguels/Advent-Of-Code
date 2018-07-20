#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

uint32_t read_input(FILE* input, char **data){
    if( *data != NULL ){
        return 0;
    }

    size_t s = 0;
    ssize_t len = getline(data, &s, input);

    return len < 0 ? 0 : len;
}

uint32_t get_extreme_diff(char *input, uint32_t len){
    char* data = (char*) malloc( len * sizeof(char) );
    strcpy(data, input);

    char delim[] = "\t ";
    uint32_t min = UINT32_MAX, max = 0, val;

    char *token = strtok(data, delim);
    if( token == NULL ){
        return 0;
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

    return max - min;
}

uint32_t get_multiples_diff(char *input, uint32_t len){
    char* data = (char*) malloc( len * sizeof(char) );
    strcpy(data, input);

    char delim[] = "\t ";
    uint32_t *vals = (uint32_t*) malloc(0);
    uint32_t size = 0;

    char *token = strtok(data, delim);
    if( token == NULL ){
        return 0;
    }

    do{
        size++;
        vals = (uint32_t*) realloc( vals, size * sizeof(uint32_t) );
        vals[size-1] = atoi(token);
    } while( (token = strtok(NULL, delim)) != NULL);

    for (uint32_t i = 0; i < size; i++) {
        for (uint32_t k = 0; k < size; k++) {
            if (i == k || vals[i] < vals[k]) {
                continue;
            }

            if ( vals[i] % vals[k] == 0) {
                return vals[i] / vals[k];
            }
        }
    }
    return 0;
}


int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Must pass a valid input file.\n");
        return 0;
    }

    FILE* input = fopen(argv[1], "r");
    if( input == NULL ){
        printf("Must pass a valid input file.\n");
        return 0;
    }

    char *data = NULL;
    uint32_t n_chars, extremes_diff_sum = 0, multiples_diff_sum = 0;

    while( (n_chars = read_input(input, &data)) != 0 ){
        extremes_diff_sum += get_extreme_diff(data, n_chars);
        multiples_diff_sum += get_multiples_diff(data, n_chars);
        free(data);
        data = NULL;
    }

    printf("Sum of extremes diff: %d\n", extremes_diff_sum);
    printf("Sum of multiples diff: %d\n", multiples_diff_sum);

    return 0;
}
