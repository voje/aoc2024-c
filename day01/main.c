#include <stdio.h>
#include <ctype.h>
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
    // left[nextL] = atoi(token);
    // nextL++;

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
    return nextL - 1;
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
    return res;
}

int main() {

    int res = day01a(example);
    assert(res == 11);
    printf("Example result: %d (assert passed)\n", res); 

    // Day01 a 
    FILE *f = fopen("./inputs/a.txt", "r");
    if (f == NULL) {
        printf("Can't open file\n");
        return OOPS;
    }
    // Get file size
    size_t fileSize;
    fseek(f, 0, SEEK_END);
    fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);
    printf("Input file size is: %zu b\n", fileSize);

    char inputA[fileSize];
    size_t r = fread(inputA, 1, fileSize, f);
    printf("Read: %zu b\n", r);

    res = day01a(inputA);
    printf("Day01/a result: %d\n", res);

    // If I cange variable name res, result changes.
    // If I add 'resa', both the previous res and resa change to a wrong
    // result.
    // C is fun...
    int resa = day01a(inputA);
    printf("Day01/a result: %d\n", resa);

    return 0;
}
