#include "Engine.h"
#include <iostream>
int main()
{
	Engine::getInstance()->app(100, 50, "Test", true);
	system("pause");
	return 0;
}