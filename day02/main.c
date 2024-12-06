#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// #define DEBUG

const size_t LINE_LEN = 100;

const char *exampleA = "7 6 4 2 1\n"
"1 2 7 8 9\n"
"9 7 6 2 1\n"
"1 3 2 4 5\n"
"8 6 4 4 1\n"
"1 3 6 7 9\n\0";

// Pop nth element from array, out needs to be preallocated
void popNth(int* orig, size_t origLen, size_t nth, int* out) {
    size_t newIdx = 0;
    for (size_t i=0; i<origLen; i++) {
        if (i != nth) {
            out[newIdx] = orig[i];
            newIdx++;
        }
    }
}

// Parse one line
int partA(int* line, size_t size) {
    int prefix = (line[0] > line[1]) * 2 - 1;
    #ifdef DEBUG
    printf("Prefix: %d\n", prefix);
    for (size_t i=0; i<size; i++) {
        printf("%d ", line[i]);
    }
    printf("\n");
    #endif

    for (size_t i=0; i<size - 1; i++) {
        int diff = (line[i] - line[i+1]) * prefix;
        
        #ifdef DEBUG
        printf("Diff: %d\n", diff);
        #endif

        if (diff < 1 || diff > 3) {
            return 0;
        }
    }
    return 1;
}

// Parse one line
int partB(int* line, size_t size) {
    if (partA(line, size) == 1) { return 1; }

    for (size_t i=0; i<size; i++) {
        int* skipped = malloc((size - 1 ) * sizeof(int));
        popNth(line, size, i, skipped);
        if (partA(skipped, size - 1) == 1) {
            free(skipped);
            return 1;
        }
        free(skipped);
    }
    return 0;
}

int iterInput(const char* input, int(*f)(int*, size_t)) {
    int res = 0;

    int line[LINE_LEN];
    size_t lsize = 0;
    char number[LINE_LEN]; 
    size_t nidx = 0;
    
    for(size_t i=0;; i++) {
        char c = input[i];

        if (c >= '0' && c <= '9') {
            number[nidx] = c; 
            nidx++;
        } else if (c == ' ' || c == '\n') {
            // End of number
            number[nidx] = '\0';
            line[lsize] = atoi(number);
            lsize++;
            nidx = 0;
        }

        if (c == '\n') {
            // End of line
            res += f(line, lsize);
            #ifdef DEBUG
            printf("%d\n", res);
            #endif
            lsize = 0;
        } else if (c == '\0') {
            // Stop reading
            break;
        }
    }

    return res;
}

int main() {
    // Example a
    assert(iterInput(exampleA, partA) == 2);
    assert(iterInput(exampleA, partB) == 4);

    // Read a.txt
    FILE *f = fopen("./inputs/a.txt", "r");
    char *buff;
    size_t bufflen;
    if (f) {
        fseek(f, 0, SEEK_END);
        bufflen = ftell(f); 
        fseek(f, 0, SEEK_SET);
        buff = malloc(bufflen * sizeof(char) + 1);
        fread(buff, 1, bufflen, f);
        buff[bufflen] = '\0';
        fclose(f);
    }

    assert(iterInput(buff, partA) == 442);
    assert(iterInput(buff, partB) == 493);

    free(buff);
    return 0;
}
