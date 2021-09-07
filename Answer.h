#pragma once
#include"Question.h"
#include"Test.h"
#include"Section.h"
#include"Result.h"
#include"UserAdmin.h"
#include"Menu.h"

// класс представляющий собою один из возможных ответов на вопрос(Question)
class Answer {
private:
    int id;
    string txt;
    bool isTrueAnswer;
public:
    Answer() {

    }

    Answer(int id, string txt, bool isTrueAnswer) {
        this->id = id;
        this->txt = txt;
        this->isTrueAnswer = isTrueAnswer;
    }

    int getId() {
        return id;
    }

    string getTxt() {
        return txt;
    }

    bool checkIsCorrectAnswer() {
        return isTrueAnswer;
    }

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(id, txt, isTrueAnswer);
    }


};

