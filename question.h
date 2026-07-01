#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <vector>
#include <random>

class Question {
private:
    std::string text_;              
    std::vector<std::string> options_; 
    int correctIndex_;              // correct answer's index (0-3)

public:

    Question();

    Question(const std::string& text, const std::vector<std::string>& opts, int correct);

    std::string getText() const;
    const std::vector<std::string>& getOptions() const;
    int getCorrectIndex() const;

    void shuffleOptions(std::mt19937& rng);

    void print(int questionNumber) const;
};

#endif