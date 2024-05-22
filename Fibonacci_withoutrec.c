
#include <stdio.h>
int main()
{
    int n, a = 0, b = 1, c;
    printf("Enter the number of elements in fibonacci series\n");
    scanf("%d", &n);
    printf("0,1");
    for (int i = 0; i < n - 2; i++)
    {
        c = a + b;
        a = b;
        b = c;
        printf(",%d", c);
    }
    return 0;
}