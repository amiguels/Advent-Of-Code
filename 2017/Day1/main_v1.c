#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t read_input(char **data){
    if( *data != NULL ){
        return 0;
    }
    *data = (char *)malloc(0);

    char c = '0';
    uint32_t n_read = 0;

    while( (c = fgetc(stdin)) != '\n' ){
        n_read++;
        *data = (char*)realloc(*data, n_read * sizeof(char) );
        (*data)[n_read-1] = c;
    }

    return n_read;
}

uint32_t get_next_index(uint32_t curr_index, uint32_t arr_size){
    return (curr_index+1)%arr_size;
}

uint32_t get_sum(char *data, uint32_t size){
    uint32_t next_index, sum = 0;

    for (uint32_t i = 0; i < size; i++) {
        next_index = get_next_index(i, size);

        if (data[i] == data[next_index]) {
            sum += data[i] - '0';
        }
    }

    return sum;
}

int main(void){
   char *data = NULL;

   uint32_t n_chars = read_input(&data);
   printf("%d\n", get_sum(data, n_chars) );
}
