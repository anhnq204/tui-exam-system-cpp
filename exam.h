#ifndef EXAM_H
#define EXAM_H

#include "vector.h"
#include "question.h"
#include <string>
#include <random>

class Exam {
private:
    Vector<Question> allQuestions;    // all quests imported from file
    Vector<Question> examQuestions;   // set of k questions
    Vector<int> userAnswers;          // candidate's chosen answers

public:
    bool loadQuestions(const std::string& filename);

    void generateExam(int k, std::mt19937& rng);

    void takeExam();

    int calculateScore() const;

    void displayResult() const;

    const Vector<Question>& getExamQuestions() const { return examQuestions; }
    const Vector<int>& getUserAnswers() const { return userAnswers; }
};

#endif