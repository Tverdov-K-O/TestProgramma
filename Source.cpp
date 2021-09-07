#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <archives/binary.hpp>
#include <sstream>
#include <types/vector.hpp>
#include <types/string.hpp>
#include <unordered_map>
#include <Windows.h>
#include "Classes.h"
#include "Foo.h"




using namespace std;


int main() {
	setlocale(LC_ALL, "");

        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        load();
        while (true) {
            string input = getInput("1. Войти\n2. Регистрация\n");
            if (input == "1") {
                loginMenu();
            }
            else if (input == "2") {
                registrationMenu();
            }
        }


    



	system("pause");
}