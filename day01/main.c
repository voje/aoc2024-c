#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

const int OOPS = 1;

const char *example = "3   4\n"
"4   3\n"
"2   5\n"
"1   3\n"
"3   9\n"
"3   3\n";

void printArr(const int* arr, size_t size) {
    for (size_t i=0; i<size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

size_t getSize(const char *input) {
    size_t size = 0;
    for (int i=0;;i++) {
        if (input[i] == '\0') {
            break;
        } else if (input[i] == '\n') {
            size++;
        }
    }
    return size;
}

int readInput(const char *input, int* left, int* right) {
    size_t nextL = 0;
    size_t nextR = 0;

    char* token;
    char *iinput = strdup(input);

    token = strtok(iinput, " \n");

    while (token != NULL) {
        #ifdef DEBUG
        printf("Token: %s\n", token);
        #endif

        if (nextL == nextR) {
            left[nextL] = atoi(token);
            nextL++;
            #ifdef DEBUG
            printf("L ");
            printArr(left, nextL);
            #endif
        } else {
            right[nextR] = atoi(token);
            nextR++;
            #ifdef DEBUG
            printf("R ");
            printArr(right, nextL);
            #endif
        }

        token = strtok(NULL, " \n");
    }

    free(token);
    free(iinput);
    return nextL;
}

int comp(const void* a, const void *b) {
    int aa = *((int*)a);
    int bb = *((int*)b);
    return (aa > bb); 
}

int day01a(const char* input) {
    size_t outLen = 100000;  // init size
    int* left = calloc(outLen, sizeof(int));
    int* right = calloc(outLen, sizeof(int));
    outLen = readInput(input, left, right);

    #ifdef DEBUG
    printArr(left, outLen);
    printArr(right, outLen);
    #endif

    // Sort both arrays
    qsort(left, outLen, sizeof(*left), comp);
    qsort(right, outLen, sizeof(*right), comp);

    #ifdef DEBUG
    printf("Sorted\n");
    printArr(left, outLen);
    printArr(right, outLen);
    #endif

    // Calculate da01a result
    int res = 0;
    for (size_t i=0; i<outLen; i++) {
        res += abs(left[i] - right[i]);
    }

    free(left);
    free(right);
    return res;
}

int day01b(const char* input) {
    size_t outLen = 100000;  // init size
    int* left = calloc(outLen, sizeof(int));
    int* right = calloc(outLen, sizeof(int));
    outLen = readInput(input, left, right);

    #ifdef DEBUG
    printArr(left, outLen);
    printArr(right, outLen);
    #endif

    int max = 0;
    for (size_t i=0; i<outLen; i++) {
        if (right[i] > max) { max = right[i]; }
    }

    int *occurrences = calloc(max+1, sizeof(int));
    for (size_t i=0; i<outLen; i++) {
        occurrences[right[i]]++;
    }

    #ifdef DEBUG
    printf("Occurrences\n");
    printArr(occurrences, max+1);
    #endif

    // Calculate da01b result
    int res = 0;
    for (size_t i=0; i<outLen; i++) {
        res += left[i] * occurrences[left[i]];
    }

    free(left);
    free(right);
    free(occurrences);
    return res;
}

int main() {
    // Read input
    FILE *f = fopen("./inputs/a.txt", "r");
    if (f == NULL) {
        printf("Can't open file\n");
        return OOPS;
    }
    size_t fileSize;
    fseek(f, 0, SEEK_END);
    fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    printf("Input file size is: %zu b\n", fileSize);
    char inputA[fileSize];
    size_t r = fread(inputA, 1, fileSize, f);
    fclose(f);

    printf("Part1\n------------\n");
    assert(day01a(example) == 11);
    assert(day01a(inputA) == 1938424);
    printf("Day01/a result: %d\n", day01a(inputA));

    printf("Part2\n------------\n");
    assert(day01b(example) == 31);
    assert(day01b(inputA) == 22014209);
    printf("Day01/b result: %d\n", day01b(inputA));

    return 0;
}
