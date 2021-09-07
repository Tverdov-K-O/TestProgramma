#pragma once

using namespace std;



vector<Section> sections;
vector<User> users;

// загружает данные из файлов
void load() {
    {
        {
            std::ifstream file("users.bin", std::ios::binary);
            if (file.is_open()) {
                cereal::BinaryInputArchive ar(file);
                ar(users);
            }

        }
        {
            std::ifstream file("sections.bin", std::ios::binary);
            if (file.is_open()) {
                cereal::BinaryInputArchive ar(file);
                ar(sections);
            }

        }
    }
}

// сохраняет данные в файлы
void save() {
    {
        {
            std::ofstream file("users.bin", std::ios::binary);
            cereal::BinaryOutputArchive ar(file);
            ar(users);
        }
        {
            std::ofstream file("sections.bin", std::ios::binary);
            cereal::BinaryOutputArchive ar(file);
            ar(sections);
        }
    }
}

// функция для получения ввода пользователя
string getInput(string message) {
    string input;
    do
    {
        system("cls");
        cout << message;
        getline(cin, input);
    } while (input.length() == 0);
    return input;
}

// консольное меню управления вопросом
void questionMenu(Question* question) {
    while (true) {
        string answersList = " Список возможных ответов:\n";
        for (Answer answer : question->getPossibleAnswers()) {
            answersList += " " + answer.getTxt() + " id: " + to_string(answer.getId());
            if (answer.checkIsCorrectAnswer()) {
                answersList += " [ПРАВИЛЬНЫЙ ОТВЕТ]";
            }
            answersList += "\n";
        }
        string input = getInput(answersList + "1. Добавить новый ответ\n2. Удалить ответ\nN. Выход\n");
        if (input == "1") {
            string txt = getInput("Введите новый ответ\n");
            cout << "Введите id нового ответа" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            input = getInput("Это правильный ответ?\n1. Да!\nN. Нет!\n");
            bool flag;
            if (input == "1") {
                flag = true;
            }
            else {
                flag = false;
            }
            Answer answer(id, txt, flag);
            question->appendAnswer(answer);
        }
        else if (input == "2") {
            cout << "Введите id удаляемого ответа" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            question->delAnswer(id);
        }
        else {
            cout << input;
            return;
        }
    }
}

// консольное меню управления тестом 
Test testMenu(Test test) {
    while (true) {
        string questionsList = " Список вопросов:\n";
        for (Question question : test.getQuestions()) {
            questionsList += " " + question.getTitle() + " id: " + to_string(question.getId()) + "\n";
        }
        string input = getInput(questionsList + "1. Добавить новый вопрос\n2. Удалить вопрос\n3. Управление вопросами\nN. Выход\n");
        if (input == "1") {
            string name = getInput("Введите новый вопрос\n");
            cout << "Введите id нового вопроса" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            Question question(id, name);
            test.appendQuestion(question);
        }
        else if (input == "2") {
            cout << "Введите id удаляемого вопроса" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            test.delQuestion(id);
        }
        else if (input == "3") {
            cout << "Введите id вопроса" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            for (Question& question : test.getQuestions()) {
                if (question.getId() == id) {
                    questionMenu(&question);
                }
            }
        }
        else {
            return test;
        }
    }
}

void sectionMenu(Section* section) {
    while (true) {
        string testsList = " Список тестов:\n";
        for (Test test : section->getTests()) {
            testsList += " " + test.getName() + " id: " + to_string(test.getId()) + "\n";
        }
        string input = getInput(testsList + "1. Добавить новый тест\n2. Удалить тест\n3. Управление тестом\nN. Выход\n");
        if (input == "1") {
            string name = getInput("Введите название нового теста\n");
            cout << "Введите id нового теста" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            Test test(id, name);
            section->appendTest(test);

        }
        else if (input == "2") {
            cout << "Введите id удаляемого теста" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            section->delTest(id);

        }
        else if (input == "3") {
            cout << "Введите id теста" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            int index = 0;
            Test newTest;
            for (Test& test : section->getTests()) {
                if (test.getId() == id) {
                    newTest = testMenu(test);
                    section->delTest(id);
                    section->appendTest(newTest);
                }
                index++;
            }

        }
        else {
            return;
        }
    }
}

void registrationMenu() {
    while (true) {
        string username = getInput("Введите логин: \n");
        for (User user : users) {
            if (user.check_Username(username)) {
                getInput("Данный логин уже занят,попробуйте другой\nВведите любой символ для выхода\n");
                return;
            }
        }
        string password = getInput("Введите пароль: \n");
        string fullName = getInput("Введите Ф.И.О: \n");
        string address = getInput("Введите адрес проживания: \n");
        string phoneNumber = getInput("Введите номер телефона в формате +380..\n");
        Role role;

        while (true) {
            string input = getInput("1. Обычный пользователь\n2. Администратор\n");
            if (input == "1") {
                role = USER;
                break;
            }
            else if (input == "2") {
                role = ADMIN;
                break;
            }
        }

        User user(username, password, fullName, address, phoneNumber, role);
        users.push_back(user);
        save();
        return;
    }
}

void usersControlMenu() {
    while (true) {
        string usersList;
        usersList += " Список пользователей:\n";
        int index = 0;
        for (User user : users) {
            usersList += " " + to_string(index) + ". " + user.getFullName() + "\n";
            index++;
        }
        string input = getInput(usersList + "1. Добавить нового пользователя\n2. Удалить пользователя\n3. Результаты тестов всех пользователей\nN. Выход\n");
        if (input == "1") {
            registrationMenu();
        }
        else if (input == "2") {
            int index;
            cout << "Введите порядковый номер пользователя в списке" << endl;
            cin >> index;
            index;
            cin.ignore();
            if (cin.fail() || index < 0 || index >= users.size())
            {
                cin.clear();
                continue;
            }
            else {
                users.erase(users.begin());
                save();
                continue;
            }
            

        }
        else if (input == "3") {
            string output;
            for (User user : users) {
                output += user.getFullName() + ":";
                for (Result result : user.getResults()) {
                    output += " " + result.getTestName() + ", результат " + to_string(result.getResult() * 100) + "%\n";
                }
            }
            getInput(output + "\nВведите любой символ для выхода\n");
        }
        else {
            return;
        }
    }
}

void adminMenu() {
    while (true) {
        string input = getInput("1. Управление разделами\n2. Пользователи\n3. Сохранить\nN. Выйти\n");
        if (input == "1") {
            while (true) {
                string sectionsList;
                sectionsList += " Список разделов: \n";
                for (Section section : sections) {
                    sectionsList += " " + section.getName() + " id: " + to_string(section.getId()) + "\n";
                }
                string input = getInput(sectionsList + "1. Добавить новый раздел\n2. Удалить раздел\n3. Управление разделом\nN. Выход\n");
                if (input == "1") {
                    string name = getInput("Введите название нового раздела\n");
                    cout << "Введите id нового раздела" << endl;
                    int id;
                    cin >> id;
                    cin.ignore();
                    if (cin.fail())
                    {
                        cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛОr" << endl;
                        cin.clear();
                        continue;
                    }
                    Section newSection(id, name);
                    sections.push_back(newSection);
                }
                else if (input == "2") {
                    cout << "Введите id удаляемого раздела" << endl;
                    int id;
                    cin >> id;
                    cin.ignore();
                    if (cin.fail())
                    {
                        cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                        cin.clear();
                        continue;
                    }
                    int index = 0;
                    for (Section section : sections) {
                        if (section.getId() == id) {
                            sections.erase(sections.begin() + index);
                            break;
                        }
                        index++;
                    }
                }
                else if (input == "3") {
                    cout << "Введите id раздела" << endl;
                    int id;
                    cin >> id;
                    cin.ignore();
                    if (cin.fail())
                    {
                        cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                        cin.clear();
                        continue;
                    }
                    for (Section& section : sections) {
                        if (section.getId() == id) {
                            sectionMenu(&section);
                        }
                    }
                }
                else {
                    break;
                }
            }
        }
        else if (input == "2") {
            usersControlMenu();
        }
        else if (input == "3") {
            save();
        }
        else
            break;
    }
}

Result testRun(Test test) {
    int correctAnswers = 0;
    for (Question question : test.getQuestions()) {
        string possibleAnswersList;
        for (Answer answer : question.getPossibleAnswers()) {
            possibleAnswersList += " " + answer.getTxt() + " id " + to_string(answer.getId()) + "\n";
        }
        string input = getInput(question.getTitle() + "\nВозможные варианты ответов:\n" + possibleAnswersList + "В качестве ответа, введите id\n");
        for (Answer answer : question.getPossibleAnswers()) {
            if (answer.checkIsCorrectAnswer() && to_string(answer.getId()) == input) {
                correctAnswers++;
            }
        }
    }
    Result result(test.getId(), test.getName(), test.getQuestions().size(), correctAnswers);
    return result;
}




void userMenu(User* currentUser) {
    while (true) {

        string input = getInput("1. Пройти тестирование\n2. Мои результаты\n");
        if (input == "1") {
            string sectionsList;
            sectionsList += " Список разделов:\n";
            for (Section section : sections) {
                sectionsList += " " + section.getName() + " id: " + to_string(section.getId()) + "\n";
            }
            input = getInput("Выберите раздел (id)\n" + sectionsList);
            for (Section section : sections) {
                if (to_string(section.getId()) == input) {
                    string testsList = " Список доступных тестов:\n";
                    for (Test test : section.getTests()) {
                        testsList += " " + test.getName() + " id: " + to_string(test.getId()) + "\n";
                    }
                    input = getInput("Выберите тест (id)\n" + testsList);
                    for (Test test : section.getTests()) {
                        if (to_string(test.getId()) == input) {
                            if (!currentUser->testCompleStatus(test.getId())) {
                                currentUser->appendResult(testRun(test));

                            }
                            else {
                                getInput("Вы уже проходили данный тест\nВведите любой символ для выхода\n");
                            }
                        }
                    }

                }
            }
            save();
        }
        else if (input == "2") {
            string resultsList;
            for (Result result : currentUser->getResults()) {
                resultsList += " " + result.getTestName() + ", результат " + to_string(result.getResult() * 100) + "%\n";// нужно доделать результат тестирования 
            }
            getInput(resultsList + "Введите любой символ для выхода\n");
        }

    }
}

void loginMenu() {
    while (true) {
        cout << "Введите логин" << endl;
        string username = getInput("Введите логин\n");
        cout << "Введите пароль" << endl;
        string password = getInput("Введите пароль\n");
        for (User& user : users) {
            if (user.check_Username(username) && user.check_Password(password)) {
                if (user.is_Admin()) {
                    adminMenu();
                }
                else {
                    userMenu(&user);
                }
            }
        }
        return;
    }
}