#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>

#define READ_COUNT_LIMIT 128
#define READ_BUFFER_SIZE 128

int stat(int64_t termine, int64_t *max, int64_t *min, double *avg) {
    // 64 bit ints so it is less likely for the user to input an invalid number

    int64_t *inputs = malloc(sizeof(int64_t) * READ_COUNT_LIMIT);
    int i;
    bool stop;
    int64_t sum;

    int read_count;
    char read_buffer[READ_BUFFER_SIZE];

    if (inputs == NULL) {
        printf("memory error\n");
        return 1;
    }

    stop = false;
    for (i = 0; i < READ_COUNT_LIMIT && !stop; i++) {
        printf("inserisci un valore: ");

        // hopefully prevent memory corruption bugs
        if (fgets(read_buffer, sizeof(read_buffer), stdin)) {
            if (sscanf(read_buffer, "%lld", &inputs[i]) != 1) {
                printf("read error");

                // discard result as it is not valid
                i--;
            }
        } else {
            printf("read error");
        }

        if (inputs[i] == termine) {
            stop = true;

            // "termine" is discarded by using i before inc
            read_count = i;
        }
    }

    if (!stop) {
        printf("hai raggiunto il limite di interi che puoi inserire\n");
    } else if (read_count == 0) {
        printf("non ho nessun valore con cui fare i calcoli\n");
        return 1;
    }

    *max = inputs[0];
    *min = inputs[0];
    sum = inputs[0];

    for (i = 1; i < read_count; i++) {
        int64_t current = inputs[i];

        if (current > *max) {
            *max = current;
        }

        if (current < *min) {
            *min = current;
        }

        sum += current;
    }

    *avg = (double) sum / (double) read_count;

    free(inputs);

    return 0;
}

int main() {
    int64_t max, min, stop;
    double avg;
    int code;

    char read_buffer[READ_BUFFER_SIZE];

    printf("inserisci il valore di stop: ");
    if (fgets(read_buffer, sizeof(read_buffer), stdin)) {
        if (sscanf(read_buffer, "%lld", &stop) != 1) {
            printf("read error\n");
            return 1;
        }
    } else {
        printf("read error\n");
        return 1;
    }

    code = stat(stop, &max, &min, &avg);


    if (code == 0) {
        printf("max: %lld, min: %lld, avg: %f\n", max, min, avg);
    } else {
        // function got an error, results is invalid memory
        return 1;
    }

    return 0;
}
