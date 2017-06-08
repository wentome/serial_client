#include<stdio.h>
#include<test.h>
int main()
{   int b;
    printf("main\n");
    func1();
    b=func2(5);
    printf("func2 return %d\n",&b);
}
