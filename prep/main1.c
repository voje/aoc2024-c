#include <stdio.h>
#include <stdlib.h>

const size_t BUFF_SIZE = 10 * sizeof(char);

char** readLines(char* filepath) {
    printf("%s\n", "start");
    FILE* fptr;
    fptr = fopen("./input.txt", "r");

    size_t capLines = 10;
    size_t lenLines = 0;
    char **lines = malloc(capLines * sizeof(char*));

    size_t llen = 0;
    size_t lsize = BUFF_SIZE;
    lines[lenLines] = malloc(lsize);
    char* line = lines[lenLines];

    char ch;
    int read = 1;
    while(read) {
        ch = fgetc(fptr);
        // printf("\033[0;32m%c\033[0m[%x] ", ch, ch);

        if (ch == EOF) {
            read = 0;
        }

        if (ch == '\n' || ch == EOF) {
            ch = '\0';
        }

        if (llen >= lsize) {
            lsize += BUFF_SIZE;
            lines[lenLines] = realloc(line, lsize);
            line = lines[lenLines];
        }

        line[llen] = ch;

        if (line[llen] == '\0') {
            // printf("%s\n", line);

            // Reset line
            lenLines++;
            lsize = BUFF_SIZE;
            llen = 0;

            lines[lenLines] = malloc(lsize);
            line = lines[lenLines];
        } else {
            llen++;
        }
    }

    fclose(fptr);
    printf("%s\n", "end");

    return lines;
}

int main() {
    char** lines = readLines("input.txt");

    printf("sizeof lines: %zu\n", sizeof(lines));

    for (size_t i=0; i<sizeof(lines); i++) {
        // printf("%zu | %s\n", i, lines[i]);
    }
    free(lines);
}
