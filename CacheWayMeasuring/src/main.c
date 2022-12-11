#include <stdio.h>
#include <malloc.h>

#define START 1
#define STOP 32

#define ARRAY_SIZE_BYTES 16777216
#define ARRAY_SIZE (ARRAY_SIZE_BYTES / sizeof(int))

#define OFFSET 49152 // 48 KB

#define EPOCH 10

#define MIN(A, B) ((A) > (B) ? (B) : (A))

union Ticks{
    unsigned long long t64;
    struct s32 { long th, tl; } t32;
};

void init_array(unsigned int* array, unsigned int fragments_count){
    for (unsigned int i = 0; i < ARRAY_SIZE - OFFSET * (fragments_count - 1); i++){
        for (unsigned int j = 0; j < fragments_count - 1; j++){
            array[i + j * OFFSET] = i + (j + 1) * OFFSET;
        }

        array[i + OFFSET * (fragments_count - 1)] = i + 1;
    }
}
unsigned long long test(const unsigned int* array){
    unsigned int i, k;

    union Ticks start, end;

    asm volatile("rdtsc\n":"=a"(start.t32.th),"=d"(start.t32.tl));

    for (k = 0, i = 0; i < ARRAY_SIZE; i++){
        k = array[k];
    }

    asm volatile("rdtsc\n":"=a"(end.t32.th),"=d"(end.t32.tl));

    if (k == 1){
        printf("0_0\n");
    }

    return (end.t64 - start.t64) / ARRAY_SIZE;
}

int main(){
    unsigned int* array = malloc(ARRAY_SIZE_BYTES);

    FILE* file = fopen("../out", "w");

    for (unsigned int fragments_count = START; fragments_count <= STOP; fragments_count++){
        init_array(array, fragments_count);

        unsigned long long min_time = ULLONG_MAX;

        for (unsigned int j = 0; j < EPOCH; j++){
            const unsigned long long current_time = test(array);

            min_time = MIN(min_time, current_time);
        }

        fprintf(file, "%d %llu\n", fragments_count, min_time);
    }

    free(array);

    fclose(file);

    return 0;
}
