#include "Color.h"

void setColor(int key) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), key);
}

void printSystem() {
	setColor(14);
	cout << "[System] ";
	setColor(15);
}

void printNum(int value) {
	setColor(10);
	cout << value;
	setColor(15);
}

