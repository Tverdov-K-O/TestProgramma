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
    bool flag = true;
    while (input.length() == 0) 
    {
        if(flag)
            cout << message;
        getline(cin, input);
        flag = false;
    }
    return input;
}


    //system("cls");
    

// консольное меню управления вопросом
void questionMenu(Question* question) {
    while (true) {
        system("cls");
        string answersList = " Список возможных ответов:\n";
        for (Answer answer : question->getPossibleAnswers()) {
            answersList += "id: " + to_string(answer.getId()) + " " + answer.getTxt();
            if (answer.checkIsCorrectAnswer()) {
                answersList += " [ПРАВИЛЬНЫЙ ОТВЕТ]";
            }
            answersList += "\n";
        }
        cout << "    -Управление ответом-" << endl;
        cout << "----------------------------" << endl;
        string input = getInput(answersList + "----------------------------\n1 -> Добавить новый ответ\n2 -> Удалить ответ\nN -> Выход\n----------------------------\nДействие: ");
        if (input == "1") {
            string txt = getInput("Введите новый ответ: ");
            cout << "Введите id нового ответа: ";
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            input = getInput("Это правильный ответ?\n1 -> Да!\n2 -> Нет!\n");
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
            cout << "Введите id удаляемого ответа: ";
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
        system("cls");
        string questionsList = " Список вопросов:\n";
        for (Question question : test.getQuestions()) {
            questionsList += " id:" + to_string(question.getId())+ " " + question.getTitle() + "\n";
        }
        cout << "     -Управление тестом-" << endl;
        cout << "      " << test.getName() << endl;
        cout << "----------------------------" << endl;
        string input = getInput(questionsList + "----------------------------\n1 -> Добавить новый вопрос\n2 -> Удалить вопрос\n3 -> Управление вопросами\nN -> Выход\n----------------------------\nДействие: ");
        if (input == "1") {
            string name = getInput("Введите новый вопрос: ");
            cout << "Введите id нового вопроса: ";
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
            cout << "Введите id удаляемого вопроса: ";
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
            cout << "Введите id вопроса: ";
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
        system("cls");
        string testsList = " Список тестов:\n";
        for (Test test : section->getTests()) {
            testsList += " id: " + to_string(test.getId())+ "\t" + test.getName() +"\n";
        }
        cout << "    -Управление разделом-" << endl;
        cout << "           "<<section->getName() << endl;
        cout << "-------------------------------" << endl;
        string input = getInput(testsList + "-------------------------------\n1 -> Добавить новый тест\n2 -> Удалить тест\n3 -> Управление тестом\nN -> Выход\n-------------------------------\nДействие: ");
        if (input == "1") {
            string name = getInput("Введите название нового теста: ");
            cout << "Введите id нового теста: " << endl;
            int id; cin >> id; cin.ignore();
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
            cout << "Введите id удаляемого теста: ";
            int id; cin >> id;cin.ignore();
            if (cin.fail())
            {
                cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                cin.clear();
                continue;
            }
            section->delTest(id);

        }
        else if (input == "3") {
            cout << "Введите id теста: " << endl;
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
        system("cls");
        cout << "   |-Регистрация-| " << endl;
        cout << "---------------------" << endl;
        string username = getInput("Логин: ");
        for (User user : users) {
            if (user.check_Username(username)) {
                getInput("Данный логин уже занят,попробуйте другой\nВведите любой символ для выхода\n");
                return;
            }
        }
        string password = getInput("Пароль: ");
        string fullName = getInput("Ф.И.О: ");
        string address = getInput("Aдрес проживания: ");
        string phoneNumber = getInput("Номер телефона в формате +38 ");
        Role role;

        while (true) {
            system("cls");
            cout << "           |-Роль-|" << endl;
            cout << "------------------------------" << endl;
            cout << "1 -> Обычный пользователь" << endl;
            cout << "2 -> Администратор" << endl;
            cout << "------------------------------" << endl;
            string input = getInput("Выбор: ");
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
        system("cls");
        string usersList;
        usersList += "    -Список пользователей-\n-----------------------------------------\n";
        int index = 0;
        for (User user : users) {
            usersList += " " + to_string(index) + ". " + user.getFullName() + "\n";
            index++;
        }
        string input = getInput(usersList + "-----------------------------------------\n1 -> Добавить нового пользователя\n2 -> Удалить пользователя\n3 -> Результаты тестов всех пользователей\nN -> Выход\n-----------------------------------------\nДействие: ");
        if (input == "1") {
            registrationMenu();
        }
        else if (input == "2") {
            int index;
            cout << "Введите номер пользователя: ";
            cin >> index;
            cin.ignore();
            if (cin.fail() || index < 0 || index >= users.size())
            {
                cin.clear();
                continue;
            }
            else {
                users.erase(users.begin() + index);
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
        system("cls");
        string input;
        cout << "   -Меню Администратора-" << endl;
        cout << "---------------------------" << endl;
        cout << "1 -> Управление разделами" << endl;
        cout << "2 -> Пользователи" << endl;
        cout << "3 -> Сохранить" << endl;
        cout << "N -> Выйти" << endl;
        cout << "---------------------------" << endl;
        cout << "Действие: "; getline(cin, input);
        if (input == "1") 
        {
            
            while (true) 
            {
                system("cls");
                string sectionsList;
                cout << "   -Управление разделами-" << endl;
                cout << "---------------------------" << endl;
                sectionsList += " Список разделов: \n";
                for (Section section : sections) 
                {
                    sectionsList += " id: " + to_string(section.getId())+ "\t" + section.getName() + "\n";
                }
                cout << sectionsList;
                cout << "---------------------------" << endl;
                cout << "1 -> Добавить новый раздел "<< endl;
                cout << "2 -> Удалить раздел" << endl;
                cout << "3 -> Управление разделом" << endl;
                cout << "N -> Выход" << endl;
                cout << "---------------------------" << endl;
                cout << "Действие: ";
                input.clear();
                getline(cin, input);
                if (input == "1") 
                {
                    cout << "   -Добавление нового раздела-" << endl;
                    cout << "---------------------------------" << endl;
                    string name = getInput("Название нового раздела: ");
                    cout << "ID нового раздела: ";
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
                else if (input == "2") 
                {
                    cout << "Введите id удаляемого раздела: " << endl;
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
                    for (Section section : sections) 
                    {
                        if (section.getId() == id) 
                        {
                            sections.erase(sections.begin() + index);
                            break;
                        }
                        index++;
                    }
                }
                else if (input == "3") 
                {
                    cout << "Введите id раздела: ";
                    int id;
                    cin >> id;
                    cin.ignore();
                    if (cin.fail())
                    {
                        cout << "ОШИБКА -- ВЫ ВВЕЛИ НЕ ЧИСЛО" << endl;
                        cin.clear();
                        continue;
                    }
                    for (Section& section : sections) 
                    {
                        if (section.getId() == id) 
                        {
                            sectionMenu(&section);
                        }
                    }
                }
                else 
                {
                    break;
                }
            }
        }
        else if (input == "2") 
        {
            usersControlMenu();
        }
        else if (input == "3") 
        {
            save();
        }
        else
            break;
    }
}

Result testRun(Test test)
{
    int correctAnswers = 0;
    system("cls");
    for (Question question : test.getQuestions()) 
    {
        string possibleAnswersList;
        for (Answer answer : question.getPossibleAnswers()) 
        {
            system("cls");
            possibleAnswersList += " id " + to_string(answer.getId()) + "\t"+ answer.getTxt() + "\n";
        }
        string input = getInput(question.getTitle()+ "\n------------------------------" + "\nВозможные варианты ответов:\n" + possibleAnswersList + "В качестве ответа, введите (id)\n------------------------------\n id: ");
        for (Answer answer : question.getPossibleAnswers()) {
            if (answer.checkIsCorrectAnswer() && to_string(answer.getId()) == input) 
            {
                correctAnswers++;
            }
        }
    }
    Result result(test.getId(), test.getName(), test.getQuestions().size(), correctAnswers);
    return result;
}




void userMenu(User* currentUser) 
{
    load();
    while (true) 
    {
        system("cls");
        cout << "   -Программа тестирования-" << endl;
        cout << "------------------------------" << endl;
        string input = getInput("1 -> Пройти тестирование\n2 -> Мои результаты\n3 -> Персональные данные\nN -> Выход\n------------------------------\nДействие: ");
        if (input == "1") 
        {
            system("cls");
            string sectionsList;
            sectionsList += " Список разделов:\n";
            cout << "\t-Тестирование-" << endl;
            cout << "------------------------------" << endl;
            for (Section section : sections)
                {
                    sectionsList += " id: " + to_string(section.getId()) + "\t" + section.getName() + "\n";
                }
            system("cls");
            input = getInput("Выберите раздел (id)\n" + sectionsList + " N -> Выход\n------------------------------\n id: ");
            for (Section section : sections) 
            {
                if (to_string(section.getId()) == input) 
                {
                    string testsList = " Список доступных тестов:\n";
                    for (Test test : section.getTests())
                    {
                        testsList += " " + test.getName() + " id: " + to_string(test.getId()) + "\n";
                    }
                    input = getInput("------------------------------\nВыберите тест (id)\n------------------------------\n" + testsList + "------------------------------\n id: ");
                    for (Test test : section.getTests()) 
                    {
                        if (to_string(test.getId()) == input) 
                        {
                            if (!currentUser->testCompleStatus(test.getId())) 
                            {
                                currentUser->appendResult(testRun(test));
                            }
                            else 
                            {
                                cout << "Вы уже проходили данный тест!" << endl;
                                system("pause");
                             
                            }
                            
                        }
                        
                    }

                }
            }
            save();
        }
        else if (input == "2") {
            string resultsList;
            for (Result result : currentUser->getResults()) 
            {
                resultsList += " -" + result.getTestName() + "-\t|результат| = " + to_string(result.getResult()) + "%\n";
            }
            cout << resultsList << "------------------------------" << endl;
            system("pause");
        }
        else if(input == "3")
        {
            currentUser->getPersonalData();
        }
        else 
        {
            break;
        }
    }
    save();
}

void loginMenu() 
{
    while (true) 
    {
        system("cls");
        cout << "   |-Вход-|" << endl;
        cout << "--------------" << endl;
        string username = getInput("Логин : ");
        string password = getInput("Пароль: ");
        bool flag = true;
        for (User& user : users) 
        {
            if (user.check_Username(username) && user.check_Password(password)) 
            {
                if (user.is_Admin()) 
                {
                    adminMenu();
                    flag = false;
                }
                else 
                {
                    userMenu(&user);
                    flag = false;
                }
            }
        }
        if (flag) 
        {
        cout << "Неверный логин или пароль!" << endl;
        cout << "Возможно учетной записи не существует!" << endl;
        system("pause");
        }
        return;
    }
}
