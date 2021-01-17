#include <iostream>
#include "Leviathan/Core/Window.h"
using namespace Leviathan;

int main() {
	std::cout << "Helloworld" << std::endl;
	Window* w = new Window(1920, 1080, "Helloworld");
	std::string str = w->GetTitle();
	w->Run();
	return 1;
}