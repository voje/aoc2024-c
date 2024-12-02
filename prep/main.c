#include "string.h"
#include "stdlib.h"
#include "stdio.h"

char* readLine(FILE *f) {
    size_t buff_size = 256;
    char* buff = malloc(buff_size);
    size_t offset = 0;
    size_t llen = 0;
    while (fgets(buff + offset, buff_size, f)) {
        llen = strlen(buff);
        printf("%s\n", buff);
        if (buff[llen - 1] == '\n' || feof(f)) {
            printf("%s\n", "breaking");
            break;
        }
        buff[llen - 1] = ' ';
        offset += buff_size;
        buff = realloc(buff, buff_size + offset);
    }
    if (llen == 0) { return NULL; }
    return buff;
}

char** readLines(char* filepath) {
    FILE* f;
    f = fopen(filepath, "r");
    if (!f) {
        char* errMsg;
        sprintf(errMsg, "Failed to open file: %s", filepath);
        perror(errMsg);
    }

    size_t nlines = 256;
    char** lines = malloc(nlines * sizeof(char *));
    while (1) {
        printf("%s\n", "aa"); 
        char* line = readLine(f);
        if (line == NULL) {
            break;
        }
        printf("%s", "rrr"); 
    }
    return NULL;
}

int main() {
    printf("%s\n", "derp");
    readLines("./input.txt");
    return 0;
}
