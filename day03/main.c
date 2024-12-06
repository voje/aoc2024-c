#include <assert.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

const char *exampleA = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";
const char *exampleB = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

enum ExprType {
    DO,
    DONT,
    MUL
};

typedef struct expr_ {
    char str[100];
    size_t pos;
    int res;
    enum ExprType type;
} Expr;

void printExpr(const Expr* e) {
    printf("%zu | %s | %d\n", e->pos, e->str, e->res); 
}

size_t findPattern(enum ExprType type, const char* pattern, const char* input, Expr *expr) {
    size_t exprIdx = 0;

    regex_t reg;
    if (regcomp(&reg, pattern, REG_EXTENDED) != 0) {
        printf("Error compiling regex");
        return 1;
    }

    int maxGroups = 1;
    regmatch_t groups[1];

    const char *cursor = input;
    const char *initCursor = input;
    while(regexec(&reg, cursor, maxGroups, groups, 0) == 0) {
        int start0 = groups[0].rm_so;
        int end0 = groups[0].rm_eo;
        char str[100];
        sprintf(str, "%.*s", end0 - start0, cursor + start0);
        printf("%s\n", str);

        expr[exprIdx].pos = cursor + start0 - initCursor;
        strcpy(expr[exprIdx].str, str);
        expr[exprIdx].res = 0;
        expr[exprIdx].type = type;

        exprIdx++;
        cursor += end0;
    }
    regfree(&reg);
    return exprIdx;
}

size_t findMul(const char* input, Expr *mulExpr) {
    size_t mulExprIdx = 0;

    regex_t mulreg;
    const char *pattern = "mul\\(([0-9]+),([0-9]+)\\)";
    if (regcomp(&mulreg, pattern, REG_EXTENDED) != 0) {
        printf("Error compiling regex");
        return 0;
    }

    int maxGroups = 3;
    regmatch_t groups[maxGroups];

    const char *cursor = input;
    const char *initCursor = input;
    while(regexec(&mulreg, cursor, maxGroups, groups, 0) == 0) {
        int start0 = groups[0].rm_so;
        int end0 = groups[0].rm_eo;
        char str[100];
        sprintf(str, "%.*s", end0 - start0, cursor + start0);
        printf("%s\n", str);

        int start1 = groups[1].rm_so;
        int end1 = groups[1].rm_eo;
        char arg1[100];
        sprintf(arg1, "%.*s\n", end1 - start1, cursor + start1);
        int iarg1 = atoi(arg1);

        int start2 = groups[2].rm_so;
        int end2 = groups[2].rm_eo;
        char arg2[100];
        sprintf(arg2, "%.*s\n", end2 - start2, cursor + start2);
        int iarg2 = atoi(arg2);

        int rres = iarg1 * iarg2;
        printf("%d * %d = %d\n", iarg1, iarg2, rres); 

        mulExpr[mulExprIdx].pos = cursor + start0 - initCursor;
        strcpy(mulExpr[mulExprIdx].str, str);
        mulExpr[mulExprIdx].res = iarg1 * iarg2;
        mulExpr[mulExprIdx].type = MUL;

        mulExprIdx++;
        cursor += end0;
    }
    regfree(&mulreg);
    return mulExprIdx;
}

int partA(const char* input) {
    Expr mulExpr[1000];
    size_t size = findMul(input, mulExpr);

    int res = 0;
    for (size_t i=0; i<size; i++) {
        printExpr(&mulExpr[i]);
        res += mulExpr[i].res;
    }
    return res;
}

int compFn(const void *a, const void *b) {
    size_t aa = ((Expr*)a)->pos;
    size_t bb = ((Expr*)b)->pos;
    if (aa > bb) return 1; 
    if (aa < bb) return -1; 
    return 0;
}

int partB(const char* input) {
    size_t size = 0;
    Expr expr[1000];
    size_t mulSize = findMul(input, expr);
    size += mulSize;

    const char *pattern = "do\\(\\)";
    size_t doSize = findPattern(DO, pattern, input, &expr[size]);
    size += doSize;

    pattern = "don't\\(\\)";
    size_t dontSize = findPattern(DONT, pattern, input, &expr[size]);
    size += dontSize;

    qsort(expr, size, sizeof(expr[0]), compFn);

    int res = 0;
    int doo = 1;
    for (size_t i=0; i<size; i++) {
        Expr ex = expr[i];
        printExpr(&ex);
        if (ex.type == DO) { doo = 1; }
        if (ex.type == DONT) { doo = 0; }

        if (doo && ex.type == MUL ) {
            res += ex.res;
        }
    }
    return res;
}

int main() {
    printf("Start\n");
    assert(partA(exampleA) == 161);
    assert(partB(exampleB) == 48);

    FILE *f = fopen("./inputs/a.txt", "r");
    if (f == NULL) {
        printf("Error reading file\n");
    }
    size_t bufflen;
    char *buff;
    fseek(f, 0, SEEK_END); 
    bufflen = ftell(f);
    fseek(f, 0, SEEK_SET); 
    buff = malloc((bufflen + 1) * sizeof(char));
    fread(buff, 1, bufflen, f);
    buff[bufflen] = '\0';

    // printf("%s\n", buff);

    assert(partA(buff) == 163931492);
    printf("%d\n", partB(buff));

    printf("End\n");
}
