#include "login.h"

Login::Login() {
	int userInput;
	while (1) {
		cout << "Select login or register (1: Login / 2: Register)" << endl;
		cout << ">>> ";
		cin >> userInput;
		try {
			if (0 < userInput && userInput < 3)
				break;
			else
				throw exception("Invalid Input");
		}
		catch (exception error) {
			cout << "Invalid Input" << endl;
		}		
	}
}

void Login::login() {

}