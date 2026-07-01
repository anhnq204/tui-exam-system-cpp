#include "exam.h"
#include <iostream>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());

    Exam exam;
    std::string filename;
    std::cout << "Enter file name: ";
    std::cin >> filename;

    if (!exam.loadQuestions(filename)) {
        return 1;
    }

    int k;
    std::cout << "Enter number of questions: ";
    std::cin >> k;

    exam.generateExam(k, rng);
    exam.takeExam();
    exam.displayResult();

    return 0;
}