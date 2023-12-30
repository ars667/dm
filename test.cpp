#include <stdio.h>
#include "Natural.h"

int main()
{
    Natural num1("90000000000000000000000000000000000000");
    Natural num2("356");
    Natural num3 = num1/num2;
    num3.print();
    return 0;
}