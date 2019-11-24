#include <stdio.h>
int main() {
unsigned int a = 5;
unsigned int mask = 0xFF;
unsigned int c = a&mask;
printf("%d\n", c);
}
