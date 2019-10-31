#include "io.h"
#include "algorithm.h"
#include "util.h"
int main() {
    int a = doComputation(5, 7.0);
    int b = 5;
    max(a, b);
    logDebug('!');
    return 0;
}
int doComputation(int a, double b) {
    int c = max(3, 4);
    logDebug('d');
    (void)a;
    (void)b;
    return c;
}
