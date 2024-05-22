
#include <stdio.h>
void fibonacciSeries(int n)
{
    static int a = 0, b = 1, c;
    if (n > 0)
    {
        c = a + b;
        a = b;
        b = c;
        printf(",%d", c);
        fibonacciSeries(n - 1);
    }
}
int main()
{
    int n;
    printf("Enter number of elements in fibonacci series\n");
    scanf("%d", &n);
    printf("0,1");
    fibonacciSeries(n - 2);
    return 0;
}