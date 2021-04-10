#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "AVL.h"

int main() {
	
	AVL a(10);

	while (true) {
		system("cls");
		std::cout << a;
		std::cout << std::endl
			<< "0. exit" << std::endl
			<< "1. add" << std::endl
			<< "2. del" << std::endl;
		int n;
		int val;
		std::cin >> n;
		try {
			switch (n)
			{
			case 0:
				return 0;
			case 1:
				std::cin >> val;
				a.add(val);
				break;
			case 2:
				std::cin >> val;
				a.del(val);
				break;
			default:
				break;
			}
		}
		catch (const char* s) {
			std::cout << s << std::endl;
			_getch();
		}
	}
}