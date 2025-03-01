#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_QUESTIONS 14

typedef struct {
    char question[256];
    char options[4][64];
    int correct_answer; // Index of the correct option (0-3)
} QuizQuestion;

typedef struct {
    QuizQuestion questions[NUM_QUESTIONS];
    int incorrect_answers[NUM_QUESTIONS]; // Tracks incorrect answers
    int total_incorrect;
    int correct_first_attempt;
    time_t start_time;
    time_t end_time;
} Quiz;

void initializeQuiz(Quiz *quiz) {
    QuizQuestion q1 = {"What is the floor function of 4.7?", 
                       {"4", "5", "4.7", "5.7"}, 
                       0};
    QuizQuestion q2 = {"Calculate the ceiling function of -3.2.", 
                       {"-4", "-3", "-2", "-3.5"}, 
                       1};
    QuizQuestion q3 = {"What is the result of 15 MOD 4?", 
                       {"1", "2", "3", "4"}, 
                       2};
    QuizQuestion q4 = {"Evaluate 2^5.", 
                       {"10", "16", "32", "64"}, 
                       2};
    QuizQuestion q5 = {"Find the value of log₂(8).", 
                       {"2", "3", "4", "8"}, 
                       1};
    QuizQuestion q6 = {"Simplify the sigma notation ∑(i=1 to 4) i².", 
                       {"10", "20", "30", "40"}, 
                       2};
    QuizQuestion q7 = {"Which of the following represents a set of all positive even integers?", 
                       {"{x | x is an integer and x > 0}", "{x | x is an even integer}", "{x | x is a positive even integer}", "{x | x is an integer and x is odd}"}, 
                       2};
    QuizQuestion q8 = {"If f(x) = 3x + 2, what is f(4)?", 
                       {"10", "12", "14", "16"}, 
                       2};
    QuizQuestion q9 = {"Determine the floor function of -1.7.", 
                       {"-2", "-1", "1", "2"}, 
                       0};
    QuizQuestion q10 = {"What is the ceiling function of 2.3?", 
                        {"2", "3", "2.3", "4"}, 
                        1};
    QuizQuestion q11 = {"Calculate 7 MOD 5.", 
                        {"0", "1", "2", "3"}, 
                        2};
    QuizQuestion q12 = {"Evaluate 5^0.", 
                        {"0", "1", "5", "Undefined"}, 
                        1};
    QuizQuestion q13 = {"Find the value of log₁₀(1000).", 
                        {"2", "3", "4", "10"}, 
                        1};
    QuizQuestion q14 = {"Simplify the sigma notation ∑(i=1 to 3) (2i + 1).", 
                        {"6", "9", "12", "15"}, 
                        2};

    quiz->questions[0] = q1;
    quiz->questions[1] = q2;
    quiz->questions[2] = q3;
    quiz->questions[3] = q4;
    quiz->questions[4] = q5;
    quiz->questions[5] = q6;
    quiz->questions[6] = q7;
    quiz->questions[7] = q8;
    quiz->questions[8] = q9;
    quiz->questions[9] = q10;
    quiz->questions[10] = q11;
    quiz->questions[11] = q12;
    quiz->questions[12] = q13;
    quiz->questions[13] = q14;

    quiz->total_incorrect = 0;
    quiz->correct_first_attempt = 0;
}

void shuffleQuestions(QuizQuestion *questions, int n) {
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        QuizQuestion temp = questions[i];
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

void runQuiz(Quiz *quiz) {
    shuffleQuestions(quiz->questions, NUM_QUESTIONS);

    printf("Welcome to the Mathematical Notation and Functions Quiz!\n");
    printf("You will be asked %d questions. Good luck!\n\n", NUM_QUESTIONS);

    quiz->start_time = time(NULL);

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("Question %d: %s\n", i + 1, quiz->questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'a' + j, quiz->questions[i].options[j]);
        }

        char user_answer;
        printf("Your answer: ");
        scanf(" %c", &user_answer);

        int user_choice = user_answer - 'a';
        if (user_choice == quiz->questions[i].correct_answer) {
            quiz->correct_first_attempt++;
        } else {
            quiz->incorrect_answers[i] = 1;
            quiz->total_incorrect++;
            printf("Incorrect! The correct answer is: %c) %s\n\n", 'a' + quiz->questions[i].correct_answer, quiz->questions[i].options[quiz->questions[i].correct_answer]);
        }
    }

    quiz->end_time = time(NULL);

    // Display results
    printf("\nQuiz Results:\n");
    printf("Total Correct Answers on First Attempt: %d\n", quiz->correct_first_attempt);
    printf("Total Incorrect Answers: %d\n", quiz->total_incorrect);
    printf("Percentage Correct on First Attempt: %.2f%%\n", (float)quiz->correct_first_attempt / NUM_QUESTIONS * 100);
    printf("Time Taken: %.2f seconds\n", difftime(quiz->end_time, quiz->start_time));

    // Repeat incorrect questions
    if (quiz->total_incorrect > 0) {
        printf("\nReviewing Incorrect Questions:\n");
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (quiz->incorrect_answers[i]) {
                printf("Question: %s\n", quiz->questions[i].question);
                printf("Correct Answer: %c) %s\n\n", 'a' + quiz->questions[i].correct_answer, quiz->questions[i].options[quiz->questions[i].correct_answer]);
            }
        }
    }
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    runQuiz(&quiz);
    return 0;
}
