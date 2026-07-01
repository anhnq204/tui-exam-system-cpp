#include "question.h"
#include <iostream>
#include <algorithm>   // std::find
#include <stdexcept>

Question::Question() : correctIndex_(0) {
    options_.resize(4);  // init with 4 empty options
}


Question::Question(const std::string& text, const std::vector<std::string>& opts, int correct)
    : text_(text), options_(opts), correctIndex_(correct) {
    if (options_.size() != 4)
        throw std::invalid_argument("Question must have exactly 4 options!\n\n");
    if (correctIndex_ < 0 || correctIndex_ >= 4)
        throw std::invalid_argument("Correct index must be 0..3!\n\n");
}

/*
getters
*/
std::string Question::getText() const {
    return text_;
}

const std::vector<std::string>& Question::getOptions() const {
    return options_;
}

int Question::getCorrectIndex() const {
    return correctIndex_;
}

void Question::shuffleOptions(std::mt19937& rng) {

    std::string correctAnswer = options_[correctIndex_];

    std::shuffle(options_.begin(), options_.end(), rng);

    auto it = std::find(options_.begin(), options_.end(), correctAnswer);
    if (it != options_.end()) {
        correctIndex_ = static_cast<int>(it - options_.begin());
    } else {
        correctIndex_ = 0;
    }
}

void Question::print(int questionNumber) const {
    std::cout << "\nQuestion " << questionNumber << ": " << text_ << "\n";
    char label = 'A';
    for (const auto& opt : options_) {
        std::cout << "   " << label++ << ". " << opt << "\n";
    }
}