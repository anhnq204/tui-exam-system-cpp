# Multiple-Choice Exam System - CPP

This project implements a simple multiple-choice exam system in C++, including a custom vector data structure, a question class, an exam class, and functionalities to read questions from a text file, shuffle questions and answers, conduct an exam, and calculate scores.


## System Requirements

- C++ compiler supporting C++11 or later (e.g., g++, clang++, MSVC).
- Any operating system with command-line support (Windows, Linux, macOS).

## Compilation

### Using command line (g++ or clang++)

```bash
g++ -std=c++11 -o exam *.cpp
```
## Usage

1. Prepare a text file containing questions in the specified format (see below).

2. Run the program:
```bash
./exam
```
3. Enter the question file name.

4. Enter the number of questions (k) for the exam.

5. The program will display an exam with k randomly selected questions; the answer options of each question are shuffled.

6. For each question, type your answer as A, B, C, or D (case-insensitive). Invalid inputs will skip that question (no score).

7. After finishing, the program shows the number of correct answers and the score on a 10-point scale.

## Input File Format

The text file contains a list of questions. Each question consists of the following lines:
- Line 1: Question text (plain text).
- Line 2: Option A.
- Line 3: Option B.
- Line 4: Option C.
- Line 5: Option D.
- Line 6: The number of the correct answer (1, 2, 3 or 4 corresponding to A, B, C, D).

Questions are separated by one or more blank lines. Leading and trailing blank lines are ignored.

Example `questions.txt`:
```
What is the capital of Vietnam?
Hanoi
Ho Chi Minh City
Da Nang
Hue
1

Which country has the largest area in the world?
Russia
Canada
China
United States
1

What is the chemical symbol for Oxygen?
Oxygen
Hydrogen
Carbon
Nitrogen
1
```
