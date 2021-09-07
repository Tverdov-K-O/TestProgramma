#pragma once
using namespace std;

// ����� �������������� ����� ���� �� ��������� ������� �� ������(Question)

class Answer {

    int id;
    string txt;
    bool isTrueAnswer;
public:
    Answer() {}
    Answer(int id, string txt, bool isTrueAnswer) 
    {
        this->id = id;
        this->txt = txt;
        this->isTrueAnswer = isTrueAnswer;
    }

    int getId() { return id; }

    string getTxt() { return txt; }

    bool checkIsCorrectAnswer() { return isTrueAnswer; }

    template<class Archive>
    void serialize(Archive& archive) { archive(id, txt, isTrueAnswer); }


};




// ����� �������������� ����� ���� �� ��������� �������� � �����(Test)
class Question {

    int id;
    string title;
    vector<Answer> possibleAnswers;
public:
    Question() {}
    Question(int id, string title, vector<Answer> possibleAnswers) 
    {
        this->id = id;
        this->title = title;
        this->possibleAnswers = possibleAnswers;
    }

    Question(int id, string title) 
    {
        this->id = id;
        this->title = title;
    }
    vector<Answer>& getPossibleAnswers() { return possibleAnswers; }
    int getId() { return id; }
    string getTitle() { return title; }
    void delAnswer(int id);
    void appendAnswer(Answer answer) { possibleAnswers.push_back(answer); }
    template<class Archive>
    void serialize(Archive& archive) { archive(id, title, possibleAnswers); }
};

void Question::delAnswer(int id)
{
    int index = 0;
    for (Answer answer : possibleAnswers)
    {
        if (answer.getId() == id) 
        {
            possibleAnswers.erase(possibleAnswers.begin() + index);
            break;
        }
        index++;
    }
}


// ����� �������������� ����� ���� �� ��������� ������ � �������(Section)
class Test {

    int id;
    string name;
    vector<Question> questions;
public:
    Test() {}
    Test(int id, string name, vector<Question> questions) 
    {
        this->id = id;
        this->name = name;
        this->questions = questions;
    }
    Test(int id, string name) 
    {
        this->id = id;
        this->name = name;
        this->questions = questions;
    }

    string getName() { return name; }
    int getId() { return id; }
    vector<Question>& getQuestions() { return questions; }
    void delQuestion(int id);
    void appendQuestion(Question question) { questions.push_back(question); }
    template<class Archive>
    void serialize(Archive& archive) { archive(id, name, questions); }
};

void Test::delQuestion(int id)
{
    int index = 0;
    for (Question question : questions) 
    {
        if (question.getId() == id) 
        {
            questions.erase(questions.begin() + index);
            break;
        }
        index++;
    }
}


// ����� �������������� ����� ���������,������
class Section {

    int id;
    string name;
    vector<Test> tests;
public:
    Section() {}
    Section(int id, string name, vector<Test> tests) 
    {
        this->id = id;
        this->name = name;
        this->tests = tests;
    }
    Section(int id, string name) 
    {
        this->id = id;
        this->name = name;
    }

    string getName() { return name; }
    int getId() { return id; }
    vector<Test>& getTests() { return tests; }
    void delTest(int id);
    void appendTest(Test test) { tests.push_back(test); }
    template<class Archive>
    void serialize(Archive& archive){ archive(id, name, tests); }

};

void Section::delTest(int id)
{
    int index = 0;
    for (Test test : tests) 
    {
        if (test.getId() == id) 
        {
            tests.erase(tests.begin() + index);
            break;
        }
        index++;
    }
}



// ����� �������������� ����� ��������� ����������� �����
class Result {

    int testId;
    string testName;
    int answersCount;
    int correctAnswersCount;

public:
    Result() {}
    Result(int testId, string testName, int answersCount, int correctAnswersCount) 
    {
        this->testId = testId;
        this->testName = testName;
        this->answersCount = answersCount;
        this->correctAnswersCount = correctAnswersCount;
    }

    string getTestName() { return testName; }
    int getTestId() { return testId; }
    double getResult() { return correctAnswersCount / answersCount; }
    template<class Archive>
    void serialize(Archive& archive) { archive(testId, testName, answersCount, correctAnswersCount); }

};

// ������ ��������� �����
enum Role {
    ADMIN,
    USER
};

// ������� ��� ����������� ������ � ������
hash<string> hasher;

// ����� �������������� ����� ������������ (������,����������)
class User {

    size_t usernameHash;
    size_t passwordHash;
    string fullName;
    string address;
    string phoneNumber;
    vector<Result> results;
    Role role;

public:
    User() {}
    User(string username, string password, string fullName, string address, string phoneNumber, Role role) 
    {
        this->usernameHash = hasher(username);
        this->passwordHash = hasher(password);
        this->fullName = fullName;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = role;
    }
    User(string username, string password, string fullName, string address, string phoneNumber) 
    {
        this->usernameHash = hasher(username);
        this->passwordHash = hasher(password);
        this->fullName = fullName;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->role = Role(USER);
    }

    bool testCompleStatus(int test_id);
    string getFullName() { return fullName; }
    vector<Result> getResults() { return results; }
    void appendResult(Result result) { results.push_back(result); }
    void printInfo() { cout << fullName << endl << address << endl << phoneNumber << endl; }
    size_t getUsername() { return usernameHash; }
    bool check_Username(string username);
    bool check_Password(string password);
    bool is_Admin();
    template<class Archive>
    void serialize(Archive& archive){ archive(usernameHash, passwordHash, fullName, address, phoneNumber, role); }

};

bool User::testCompleStatus(int test_id)
{
    for (Result result : results)
    {
        if (result.getTestId() == test_id)
        {
            return true;
        }
    }
    return false;
}

inline bool User::check_Username(string username)
{
    if (hasher(username) == usernameHash)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool User::check_Password(string password)
{
    if (hasher(password) == passwordHash)
    {
        return true;
    }
    else
    {
        return false;
    }
}

inline bool User::is_Admin()
{
    if (role == ADMIN)
    {
        return true;
    }
    else
    {
        return false;
    }
}
