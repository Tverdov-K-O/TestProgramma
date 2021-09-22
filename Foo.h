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
    

// ���������� ���� ���������� ��������
void questionMenu(Question* question) {
    while (true) {
        system("cls");
        string answersList = " ������ ��������� �������:\n";
        for (Answer answer : question->getPossibleAnswers()) {
            answersList += "id: " + to_string(answer.getId()) + " " + answer.getTxt();
            if (answer.checkIsCorrectAnswer()) {
                answersList += " [���������� �����]";
            }
            answersList += "\n";
        }
        cout << "    -���������� �������-" << endl;
        cout << "----------------------------" << endl;
        string input = getInput(answersList + "----------------------------\n1 -> �������� ����� �����\n2 -> ������� �����\nN -> �����\n----------------------------\n��������: ");
        if (input == "1") {
            string txt = getInput("������� ����� �����: ");
            cout << "������� id ������ ������: ";
            int id;
            cin >> id;
            cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
                cin.clear();
                continue;
            }
            input = getInput("��� ���������� �����?\n1 -> ��!\n2 -> ���!\n");
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
            cout << "������� id ���������� ������: ";
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
        system("cls");
        string questionsList = " ������ ��������:\n";
        for (Question question : test.getQuestions()) {
            questionsList += " id:" + to_string(question.getId())+ " " + question.getTitle() + "\n";
        }
        cout << "     -���������� ������-" << endl;
        cout << "      " << test.getName() << endl;
        cout << "----------------------------" << endl;
        string input = getInput(questionsList + "----------------------------\n1 -> �������� ����� ������\n2 -> ������� ������\n3 -> ���������� ���������\nN -> �����\n----------------------------\n��������: ");
        if (input == "1") {
            string name = getInput("������� ����� ������: ");
            cout << "������� id ������ �������: ";
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
            cout << "������� id ���������� �������: ";
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
            cout << "������� id �������: ";
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
        system("cls");
        string testsList = " ������ ������:\n";
        for (Test test : section->getTests()) {
            testsList += " " + test.getName() + "\tid: " + to_string(test.getId()) + "\n";
        }
        cout << "    -���������� ��������-" << endl;
        cout << "           "<<section->getName() << endl;
        cout << "-------------------------------" << endl;
        string input = getInput(testsList + "-------------------------------\n1 -> �������� ����� ����\n2 -> ������� ����\n3 -> ���������� ������\nN -> �����\n-------------------------------\n��������: ");
        if (input == "1") {
            string name = getInput("������� �������� ������ �����: ");
            cout << "������� id ������ �����: " << endl;
            int id; cin >> id; cin.ignore();
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
            cout << "������� id ���������� �����: ";
            int id; cin >> id;cin.ignore();
            if (cin.fail())
            {
                cout << "������ -- �� ����� �� �����" << endl;
                cin.clear();
                continue;
            }
            section->delTest(id);

        }
        else if (input == "3") {
            cout << "������� id �����: " << endl;
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
        system("cls");
        cout << "   |-�����������-| " << endl;
        cout << "---------------------" << endl;
        string username = getInput("�����: ");
        for (User user : users) {
            if (user.check_Username(username)) {
                getInput("������ ����� ��� �����,���������� ������\n������� ����� ������ ��� ������\n");
                return;
            }
        }
        string password = getInput("������: ");
        string fullName = getInput("�.�.�: ");
        string address = getInput("A���� ����������: ");
        string phoneNumber = getInput("����� �������� � ������� +38 ");
        Role role;

        while (true) {
            system("cls");
            cout << "           |-����-|" << endl;
            cout << "------------------------------" << endl;
            cout << "1 -> ������� ������������" << endl;
            cout << "2 -> �������������" << endl;
            cout << "------------------------------" << endl;
            string input = getInput("�����: ");
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
        usersList += "    -������ �������������-\n-----------------------------------------\n";
        int index = 0;
        for (User user : users) {
            usersList += " " + to_string(index) + ". " + user.getFullName() + "\n";
            index++;
        }
        string input = getInput(usersList + "-----------------------------------------\n1 -> �������� ������ ������������\n2 -> ������� ������������\n3 -> ���������� ������ ���� �������������\nN -> �����\n-----------------------------------------\n��������: ");
        if (input == "1") {
            registrationMenu();
        }
        else if (input == "2") {
            int index;
            cout << "������� ����� ������������: ";
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
        system("cls");
        string input;
        cout << "   -���� ��������������-" << endl;
        cout << "---------------------------" << endl;
        cout << "1 -> ���������� ���������" << endl;
        cout << "2 -> ������������" << endl;
        cout << "3 -> ���������" << endl;
        cout << "N -> �����" << endl;
        cout << "---------------------------" << endl;
        cout << "��������: "; getline(cin, input);
        if (input == "1") {
            
            while (true) {
                system("cls");
                string sectionsList;
                cout << "   -���������� ���������-" << endl;
                cout << "---------------------------" << endl;
                sectionsList += " ������ ��������: \n";
                for (Section section : sections) {
                    sectionsList += " " + section.getName() + "\tid: " + to_string(section.getId()) + "\n";
                }
                cout << sectionsList;
                cout << "---------------------------" << endl;
                cout << "1 -> �������� ����� ������ "<< endl;
                cout << "2 -> ������� ������" << endl;
                cout << "3 -> ���������� ��������" << endl;
                cout << "N -> �����" << endl;
                cout << "---------------------------" << endl;
                cout << "��������: ";
                input.clear();
                getline(cin, input);
                if (input == "1") {
                    cout << "   -���������� ������ �������-" << endl;
                    cout << "---------------------------------" << endl;
                    string name = getInput("�������� ������ �������: ");
                    cout << "ID ������ �������: ";
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
                    cout << "������� id ���������� �������: " << endl;
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
                    cout << "������� id �������: ";
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
    system("cls");
    for (Question question : test.getQuestions()) {
        string possibleAnswersList;
        for (Answer answer : question.getPossibleAnswers()) {
            system("cls");
            possibleAnswersList += " id " + to_string(answer.getId()) + "\t"+ answer.getTxt() + "\n";
        }
        string input = getInput(question.getTitle()+ "\n------------------------------" + "\n��������� �������� �������:\n" + possibleAnswersList + "� �������� ������, ������� (id)\n------------------------------\n id: ");
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
        system("cls");
        cout << "   -��������� ������������-" << endl;
        cout << "------------------------------" << endl;
        string input = getInput("1 -> ������ ������������\n2 -> ��� ����������\n3 -> ������������ ������\nN -> �����\n------------------------------\n��������: ");
        if (input == "1") {
            system("cls");
            string sectionsList;
            sectionsList += " ������ ��������:\n";
            cout << "\t-������������-" << endl;
            cout << "------------------------------" << endl;
            for (Section section : sections) {
                sectionsList += " " + section.getName() + "\tid: " + to_string(section.getId()) + "\n";
            }
            input = getInput("�������� ������ (id)\n" + sectionsList +"------------------------------\n id: ");
            for (Section section : sections) {
                if (to_string(section.getId()) == input) {
                    string testsList = " ������ ��������� ������:\n";
                    for (auto test : section.getTests()) {
                        testsList += " " + test.getName() + " id: " + to_string(test.getId()) + "\n";
                    }
                    input = getInput("------------------------------\n�������� ���� (id)\n------------------------------\n" + testsList + "\n------------------------------\n id: ");
                    bool flag = false;
                    for (Test test : section.getTests()) {
                        
                        if (to_string(test.getId()) == input && !flag) 
                        {
                            if (!currentUser->testCompleStatus(test.getId())) 
                            {
                                currentUser->appendResult(testRun(test));

                            }
                            else 
                            {
                                getInput("�� ��� ��������� ������ ����\n������� ����� ������ ��� ������\n");
                                flag == true;
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
                resultsList += " " + result.getTestName() + ", ��������� " + to_string(result.getResult()) + "%\n";
            }
            getInput(resultsList + "������� ����� ������ ��� ������\n");
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

void loginMenu() {
    while (true) {
        system("cls");
        cout << "   |-����-|" << endl;
        cout << "--------------" << endl;
        string username = getInput("����� : ");
        string password = getInput("������: ");
        bool flag = true;
        for (User& user : users) {
            if (user.check_Username(username) && user.check_Password(password)) {
                if (user.is_Admin()) {
                    adminMenu();
                    flag = false;
                }
                else {
                    userMenu(&user);
                    flag = false;
                }
            }
        }
        if (flag) 
        {
        cout << "�������� ����� ��� ������!" << endl;
        cout << "�������� ������� ������ �� ����������!" << endl;
        system("pause");
        }
        return;
    }
}
