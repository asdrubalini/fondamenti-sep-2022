#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <string.h>

void process_line(char *input, char *line) {
    size_t input_len, line_len;
    int i;
    char current_input_char, current_line_char;
    uint16_t diffs_count;

    input_len = strlen(input);
    line_len = strlen(line);

    if (input_len != line_len) {
        // nothing to do
        return;
    }

    diffs_count = 0;
    for (i = 0 ; i < input_len - 1; i++) {
        current_input_char = input[i];
        current_line_char = line[i];

        if (current_input_char != current_line_char) {
            diffs_count++;
        }
    }

    if (diffs_count == 1) {
        printf("%s", line);
    }
}

int main() {
    char input[35 + 1];
    FILE *dict_file;
    ssize_t read;
    char *current_line;
    size_t len = 0;

    printf("inserisci la stringa di input: ");
    fgets(input, sizeof(input), stdin);

    // curl -o dizionario.txt https://raw.githubusercontent.com/napolux/paroleitaliane/master/paroleitaliane/60000_parole_italiane.txt
    dict_file = fopen("./dizionario.txt", "r");
    if (dict_file == NULL) {
        perror("impossibile aprire il file dizionario.txt\n");
        return 1;
    }

    while ((read = getline(&current_line, &len, dict_file) != -1)) {
        if (read > 0) {
            process_line(input, current_line);
        }
    }

    free(current_line);

    return 0;
}
