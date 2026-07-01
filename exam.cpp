#include "exam.h"
#include <fstream>
#include <iostream>
#include <algorithm>   // std::shuffle, std::find
#include <stdexcept>
#include <cctype>      // std::toupper

/*
read exam's questions from file
satisfy the following format:
line 1: question's text
line 2-5: the 4 anwsers text
line 6: ordinal number of the correct answer (1, 2, 3, or 4)
*/
bool Exam::loadQuestions(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "ERROR: Cannot open file: " << filename << std::endl;
        return false;
    }

    allQuestions.clear(); // flush old data

    std::string line;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::string questionText = line;

        std::vector<std::string> options(4);
        for (int i = 0; i < 4; ++i) {
            if (!std::getline(fin, options[i])) {
                std::cerr << "ERROR: Missing answer for the question: " << questionText << std::endl;
                return false;
            }
        }

        std::string correctStr;
        if (!std::getline(fin, correctStr)) {
            std::cerr << "ERROR: Missing correct answer for the question: " << questionText << std::endl;
            return false;
        }

        int correct = 0;
        try {
            correct = std::stoi(correctStr) - 1;
        } catch (...) {
            std::cerr << "ERROR: Correct answer was not an integer at question: " << questionText << std::endl;
            return false;
        }

        if (correct < 0 || correct > 3) {
            std::cerr << "ERROR: Correct answer index is invalid at question: " << questionText << std::endl;
            return false;
        }

        allQuestions.push_back(Question(questionText, options, correct));
    }

    fin.close();
    std::cout << "Successfully loaded " << allQuestions.size() << " questions.\n";
    return true;
}

void Exam::generateExam(int k, std::mt19937& rng) {
    if (k > static_cast<int>(allQuestions.size())) {
        std::cerr << "WARNING: The requested number of questions (" << k 
                  << ") exceeds the available questions in the questions bank (" << allQuestions.size() 
                  << "). Taking all of them.\n";
        k = static_cast<int>(allQuestions.size());
    }

    std::vector<int> indices(allQuestions.size());
    for (size_t i = 0; i < allQuestions.size(); ++i)
        indices[i] = static_cast<int>(i);
    std::shuffle(indices.begin(), indices.end(), rng);
    indices.resize(k);

    examQuestions.clear();
    userAnswers.clear();

    for (int idx : indices) {
        Question q = allQuestions[idx];   
        q.shuffleOptions(rng);           
        examQuestions.push_back(q);
        userAnswers.push_back(-1);        
    }
}

void Exam::takeExam() {
    if (examQuestions.empty()) {
        std::cout << "No exam has been generated. Please call generateExam() first!\n";
        return;
    }

    std::cout << "\n========== BEGIN EXAM ==========\n";
    for (size_t i = 0; i < examQuestions.size(); ++i) {

        examQuestions[i].print(static_cast<int>(i + 1));

        char choice;
        std::cout << "Choose the correct answer (A/B/C/D): ";
        std::cin >> choice;
        choice = std::toupper(choice);

        int ans = -1;
        if (choice >= 'A' && choice <= 'D') {
            ans = choice - 'A';
        } else {
            std::cout << "Invalid answer. Skipping this question!\n";
        }
        userAnswers[i] = ans;
    }
    std::cout << "========== THE END ==========\n\n";
}

int Exam::calculateScore() const {
    if (examQuestions.size() != userAnswers.size()) {
        std::cerr << "ERROR: The number of questions and answers does not match.\n";
        return 0;
    }

    int score = 0;
    for (size_t i = 0; i < examQuestions.size(); ++i) {
        if (userAnswers[i] == examQuestions[i].getCorrectIndex())
            ++score;
    }
    return score;
}

void Exam::displayResult() const {
    int total = static_cast<int>(examQuestions.size());
    if (total == 0) {
        std::cout << "No exam has been generated yet!\n";
        return;
    }

    int correct = calculateScore();
    std::cout << "You answered " << correct << " out of " << total << " questions correctly.\n";
    double mark = static_cast<double>(correct) / total * 10.0;
    std::cout << "Score: " << mark << "/10\n";
}