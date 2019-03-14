
#include "pch.h"
#include <iostream>


#include "../headers/FunctionPtr.hpp"

void func(int s)
{
	std::cout << s << std::endl;
}

void func2()
{
	std::cout << "2" << std::endl;
}



int main()
{
	FunctionPtr<void(int)> FP = func;
	FunctionPtr<void(void)> FP2 = []() { std::cout << "Message \n"; };
	FunctionPtr<void(void)> FP3 = []() { std::cout << "Message2 \n"; };

	std::swap(FP3, FP2);
	FP2();

	system("pause");
	return 0;
}

