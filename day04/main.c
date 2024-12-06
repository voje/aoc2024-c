#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* exampleA = "MMMSXXMASM\n"
    "MSAMXMSMSA\n" 
    "AMXSXMAAMM\n"
    "MSAMASMSMX\n"
    "XMASAMXAMM\n"
    "XXAMMXXAMA\n"
    "SMSMSASXSS\n"
    "SAXAMASAAA\n"
    "MAMMMXMMMM\n"
    "MXMXAXMASX\n\0";

const char* XMAS = "XMAS\0";

const int YUP = -1;
const int YDOWN = 1;
const int XLEFT = -1;
const int XRIGHT = 1;

typedef struct {
    size_t height;
    size_t width;
    char **grid;
} Grid;

// Free the grid pointer after usage
Grid *toGrid(const char* input) {
    Grid *g = malloc(sizeof(Grid));

    size_t w = 0;
    for (;input[w] != '\n';w++);
    size_t h = 0;
    for (int i=0; input[i] != '\0'; i++) {
        if (input[i] == '\n') { h++; } 
    }
    printf("w: %zu, h: %zu\n", w, h);

    // Don't forget to free me
    g->grid = malloc(h * sizeof(char*));
    for (size_t i=0; i<h; i++) {
        g->grid[i] = malloc(w * sizeof(char));
    }

    size_t i = 0;
    size_t j = 0;
    for (size_t ii=0; input[ii] != '\0'; ii++) {
        char c = input[ii];
        if (c == '\n') {
            j = 0;
            i++;
        } else {
            g->grid[i][j] = c;
            // printf("%zu[%zu][%zu]%c\n", ii, i, j, c);
            j++;
        }
    }

    g->width = w;
    g->height = h;
    return g;
}

// Returns 1 if it finds XMAS
int findXmas(Grid *g, size_t x, int xGrad, size_t y, int yGrad, size_t xmasIdx) {
    if (XMAS[xmasIdx] == '\0') {
        // printf("Found one!\n");
        return 1;
    }
    if (x >= g->width || x < 0 || y >= g->height || y < 0) {
        // printf("Out of grid bounds!\n");
        return 0;
    }
    char c = g->grid[y][x];
    // printf("%zu %zu %c\n", x, y, g->grid[y][x]);
    if (c == XMAS[xmasIdx]) {
        return findXmas(g, x + xGrad, xGrad, y + yGrad, yGrad, ++xmasIdx);
    }
    return 0;
}

void printGrid(Grid *g) {
    for (size_t i=0; i<g->height; i++) {
        for (size_t j=0; j<g->width; j++) {
            printf("%c ", g->grid[i][j]); 
        }
        printf("\n");
    }
}

void freeGrid(Grid *g) {
    for (size_t i=0; i<g->height; i++) {
        free(g->grid[i]);
    }
    free(g->grid);
    free(g);
}

int partA(const char* input) {
    size_t w, h;
    Grid *g = toGrid(input);

    printGrid(g);

    int res = 0;
    for (size_t i=0; i<g->height; i++) {
        for (size_t j=0; j<g->width; j++) {
            res += findXmas(g, j, XLEFT, i, 0, 0);
            res += findXmas(g, j, XLEFT, i, YUP, 0);
            res += findXmas(g, j, 0, i, YUP, 0);
            res += findXmas(g, j, XRIGHT, i, YUP, 0);
            res += findXmas(g, j, XRIGHT, i, 0, 0);
            res += findXmas(g, j, XRIGHT, i, YDOWN, 0);
            res += findXmas(g, j, 0, i, YDOWN, 0);
            res += findXmas(g, j, XLEFT, i, YDOWN, 0);
        }
    }

    freeGrid(g);
    return res;
}

char getCharAt(Grid *g, size_t y, size_t x) {
    if (x >= g->width || x < 0 || y >= g->height || y < 0) {
        return '\0';
    }
    return g->grid[y][x];
}

int partB(const char* input) {
    size_t w, h;
    Grid *g = toGrid(input);

    printGrid(g);

    int res = 0;
    for (size_t i=0; i<g->height; i++) {
        for (size_t j=0; j<g->width; j++) {
            if (g->grid[i][j] != 'A') { continue; }
            else {
                int mas = 0;

                if (
                    (getCharAt(g, i + YUP, j + XLEFT) == 'M') &&
                    (getCharAt(g, i + YDOWN, j + XRIGHT) == 'S')
                ) { mas++; }
                else if (
                    (getCharAt(g, i + YUP, j + XLEFT) == 'S') &&
                    (getCharAt(g, i + YDOWN, j + XRIGHT) == 'M')
                ) { mas++; }

                if (
                    (getCharAt(g, i + YUP, j + XRIGHT) == 'M') &&
                    (getCharAt(g, i + YDOWN, j + XLEFT) == 'S')
                ) { mas++; }
                else if (
                    (getCharAt(g, i + YUP, j + XRIGHT) == 'S') &&
                    (getCharAt(g, i + YDOWN, j + XLEFT) == 'M')
                ) { mas++; }

                // printf("%zu, %zu, %d, %d\n", i, j, mm, ss);

                if (mas == 2) { res++; }
            }
        }
    }
    freeGrid(g);
    return res;
}

int main() {
    assert(partA(exampleA) == 18);
    assert(partB(exampleA) == 9);

    // Read input
    FILE *f = fopen("./inputs/a.txt", "r");
    size_t buffsize = 0;
    fseek(f, 0, SEEK_END);
    buffsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buff = malloc((buffsize + 1) * sizeof(char));
    fread(buff, 1, buffsize + 1, f);
    fclose(f);
    buff[buffsize] = '\0';
    
    assert(partA(buff) == 2434);
    printf("%d\n", partB(buff));

    free(buff);
    return 0;
}
