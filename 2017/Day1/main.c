#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t read_input(FILE* input, char **data){
    if( *data != NULL ){
        return 0;
    }

    size_t s = 0;
    return getline(data, &s, input)-1;
}

uint32_t get_nth_next_index(uint32_t curr_index, uint32_t arr_size, uint32_t step){
    return (curr_index+step)%arr_size;
}

uint32_t get_sum(char *data, uint32_t size, uint32_t step){
    uint32_t sum = 0;

    for (uint32_t i = 0; i < size; i++) {
        if (data[i] == data[ get_nth_next_index(i, size, step) ]) {
            sum += data[i] - '0';
        }
    }

    return sum;
}

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Must pass a valid input file.\n");
        return 0;
    }
    FILE* input = fopen(argv[1], "r");

   char *data = NULL;

   uint32_t n_chars = read_input(input, &data);
   printf("Part 1: %d\n", get_sum(data, n_chars, 1) );
   printf("Part 2: %d\n", get_sum(data, n_chars, n_chars/2) );

   free(data);
   return 0;
}
