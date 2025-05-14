#include <stdio.h>

int main(void) {
    size_t n = 44 * sizeof(char);
    printf("%zu\n", n);
    printf("%zx\n", n);
    printf("%zd\n", n);

    return 0;
}
