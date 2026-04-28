
#include <stdio.h>
#include <string.h>

#define N 10

typedef struct {
    char b[N];
    int h;
    int t;
    int c;
} X;

void f0(X *x) {
    x->h = 0;
    x->t = 0;
    x->c = 0;
}

int f1(X *x) {
    return x->c == N;
}

int f2(X *x) {
    return x->c == 0;
}

void f3(X *x, char v) {
    if (f1(x)) {
        printf("Buffer Overflow\n");
        return;
    }
    x->b[x->t] = v;
    x->t = (x->t + 1) % N;
    x->c++;
}

char f4(X *x) {
    if (f2(x)) {
        printf("Buffer Underflow\n");
        return '\0';
    }
    char v = x->b[x->h];
    x->h = (x->h + 1) % N;
    x->c--;
    return v;
}

int main() {
    X x;
    f0(&x);

    char s[50];
    scanf("%s", s);

    strcat(s, "CE-ESY");

    for (int i = 0; i < strlen(s); i++) {
        f3(&x, s[i]);
    }

    while (!f2(&x)) {
        printf("%c", f4(&x));
    }

    printf("\n");

    if (f2(&x)) {
        printf("Buffer is now empty.\n");
    }

    return 0;
}
