#include <iostream>
#include "Window.h"
int main() {
	std::cout << "Helloworld" << std::endl;
	Window* w = new Window();
	w->Create(1920,1080, "Helloworld");
	w->Run();
	return 1;
}