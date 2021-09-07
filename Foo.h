#pragma once

using namespace std;



vector<Section> sections;
vector<User> users;

// ��������� ������ �� ������
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

// ��������� ������ � �����
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

// ������� ��� ��������� ����� ������������
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

// ���������� ���� ���������� ��������
void questionMenu(Question* question) {
    while (true) {
        string answersList = " ������ ��������� �������:\n";
        for (Answer answer : question->getPossibleAnswers()) {
            answersList += " " + answer.getTxt() + " id: " + to_string(answer.getId());
            if (answer.checkIsCorrectAnswer()) {
                answersList += " [���������� �����]";
            }
            answersList += "\n";
        }
        string input = getInput(answersList + "1. �������� ����� �����\n2. ������� �����\nN. �����\n");
        if (input == "1") {
            string txt = getInput("������� ����� �����\n");
            cout << "������� id ������ ������" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
                cin.clear();
                continue;
            }
            input = getInput("��� ���������� �����?\n1. ��!\nN. ���!\n");
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
            cout << "������� id ���������� ������" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
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

// ���������� ���� ���������� ������ 
Test testMenu(Test test) {
    while (true) {
        string questionsList = " ������ ��������:\n";
        for (Question question : test.getQuestions()) {
            questionsList += " " + question.getTitle() + " id: " + to_string(question.getId()) + "\n";
        }
        string input = getInput(questionsList + "1. �������� ����� ������\n2. ������� ������\n3. ���������� ���������\nN. �����\n");
        if (input == "1") {
            string name = getInput("������� ����� ������\n");
            cout << "������� id ������ �������" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
                cin.clear();
                continue;
            }
            Question question(id, name);
            test.appendQuestion(question);
        }
        else if (input == "2") {
            cout << "������� id ���������� �������" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
                cin.clear();
                continue;
            }
            test.delQuestion(id);
        }
        else if (input == "3") {
            cout << "������� id �������" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
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
        string testsList = " ������ ������:\n";
        for (Test test : section->getTests()) {
            testsList += " " + test.getName() + " id: " + to_string(test.getId()) + "\n";
        }
        string input = getInput(testsList + "1. �������� ����� ����\n2. ������� ����\n3. ���������� ������\nN. �����\n");
        if (input == "1") {
            string name = getInput("������� �������� ������ �����\n");
            cout << "������� id ������ �����" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
                cin.clear();
                continue;
            }
            Test test(id, name);
            section->appendTest(test);

        }
        else if (input == "2") {
            cout << "������� id ���������� �����" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
                cin.clear();
                continue;
            }
            section->delTest(id);

        }
        else if (input == "3") {
            cout << "������� id �����" << endl;
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
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
        string username = getInput("������� �����: \n");
        for (User user : users) {
            if (user.check_Username(username)) {
                getInput("������ ����� ��� �����,���������� ������\n������� ����� ������ ��� ������\n");
                return;
            }
        }
        string password = getInput("������� ������: \n");
        string fullName = getInput("������� �.�.�: \n");
        string address = getInput("������� ����� ����������: \n");
        string phoneNumber = getInput("������� ����� �������� � ������� +380..\n");
        Role role;

        while (true) {
            string input = getInput("1. ������� ������������\n2. �������������\n");
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
        usersList += " ������ �������������:\n";
        int index = 0;
        for (User user : users) {
            usersList += " " + to_string(index) + ". " + user.getFullName() + "\n";
            index++;
        }
        string input = getInput(usersList + "1. �������� ������ ������������\n2. ������� ������������\n3. ���������� ������ ���� �������������\nN. �����\n");
        if (input == "1") {
            registrationMenu();
        }
        else if (input == "2") {
            int index;
            cout << "������� ���������� ����� ������������ � ������" << endl;
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
                    output += " " + result.getTestName() + ", ��������� " + to_string(result.getResult() * 100) + "%\n";
                }
            }
            getInput(output + "\n������� ����� ������ ��� ������\n");
        }
        else {
            return;
        }
    }
}

void adminMenu() {
    while (true) {
        string input = getInput("1. ���������� ���������\n2. ������������\n3. ���������\nN. �����\n");
        if (input == "1") {
            while (true) {
                string sectionsList;
                sectionsList += " ������ ��������: \n";
                for (Section section : sections) {
                    sectionsList += " " + section.getName() + " id: " + to_string(section.getId()) + "\n";
                }
                string input = getInput(sectionsList + "1. �������� ����� ������\n2. ������� ������\n3. ���������� ��������\nN. �����\n");
                if (input == "1") {
                    string name = getInput("������� �������� ������ �������\n");
                    cout << "������� id ������ �������" << endl;
                    int id;
                    cin >> id;
                    cin.ignore();
                    if (cin.fail())
                    {
                        cout << "������ -- �� ����� �� �����r" << endl;
                        cin.clear();
                        continue;
                    }
                    Section newSection(id, name);
                    sections.push_back(newSection);
                }
                else if (input == "2") {
                    cout << "������� id ���������� �������" << endl;
                    int id;
                    cin >> id;
                    cin.ignore();
                    if (cin.fail())
                    {
                        cout << "������ -- �� ����� �� �����" << endl;
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
                    cout << "������� id �������" << endl;
                    int id;
                    cin >> id;
                    cin.ignore();
                    if (cin.fail())
                    {
                        cout << "������ -- �� ����� �� �����" << endl;
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
        string input = getInput(question.getTitle() + "\n��������� �������� �������:\n" + possibleAnswersList + "� �������� ������, ������� id\n");
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

        string input = getInput("1. ������ ������������\n2. ��� ����������\n");
        if (input == "1") {
            string sectionsList;
            sectionsList += " ������ ��������:\n";
            for (Section section : sections) {
                sectionsList += " " + section.getName() + " id: " + to_string(section.getId()) + "\n";
            }
            input = getInput("�������� ������ (id)\n" + sectionsList);
            for (Section section : sections) {
                if (to_string(section.getId()) == input) {
                    string testsList = " ������ ��������� ������:\n";
                    for (Test test : section.getTests()) {
                        testsList += " " + test.getName() + " id: " + to_string(test.getId()) + "\n";
                    }
                    input = getInput("�������� ���� (id)\n" + testsList);
                    for (Test test : section.getTests()) {
                        if (to_string(test.getId()) == input) {
                            if (!currentUser->testCompleStatus(test.getId())) {
                                currentUser->appendResult(testRun(test));

                            }
                            else {
                                getInput("�� ��� ��������� ������ ����\n������� ����� ������ ��� ������\n");
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
                resultsList += " " + result.getTestName() + ", ��������� " + to_string(result.getResult() * 100) + "%\n";// ����� �������� ��������� ������������ 
            }
            getInput(resultsList + "������� ����� ������ ��� ������\n");
        }

    }
}

void loginMenu() {
    while (true) {
        cout << "������� �����" << endl;
        string username = getInput("������� �����\n");
        cout << "������� ������" << endl;
        string password = getInput("������� ������\n");
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