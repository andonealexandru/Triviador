#include <iostream>
#include <Validator.h>
int main()
{
    Validator valid;
    std::cout<<valid.IsNumeric("123");
    return 0;
}