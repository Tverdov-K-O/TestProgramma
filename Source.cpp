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
            system("cls");
            int input;
            cout << "     |-Меню-|" << endl;
            cout << "------------------" << endl;
            cout << " 1 -> Вход" << endl;
            cout << " 2 -> Регистрация" << endl;
            cout << " 3 -> Выход" << endl;
            cout << "------------------" << endl;
            cout << "Действие: "; cin >> input;
            switch (input)
            {
            default: break;
            case 1: loginMenu(); break;
            case 2: registrationMenu(); break;
            case 3: exit(0);
            }
        }


        //string input = getInput("1. Войти\n2. Регистрация\n");

    



	system("pause");
}