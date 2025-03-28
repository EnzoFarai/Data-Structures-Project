#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 4
#define MAX_QUESTION_LEN 256
#define MAX_OPTION_LEN 100
#define MAX_EXPLANATION_LEN 256

typedef struct {
    char question[MAX_QUESTION_LEN];
    char options[4][MAX_OPTION_LEN];
    int correct_answer;
    char explanation[MAX_EXPLANATION_LEN];
} QuizQuestion;

typedef struct {
    QuizQuestion questions[NUM_QUESTIONS];
    int correct_first_attempt;
    int incorrect_answers[NUM_QUESTIONS];
    time_t start_time, end_time;
} Quiz;

void initializeQuiz(Quiz *quiz) {
    QuizQuestion initial_questions[NUM_QUESTIONS] = {
        // Question 1
        {"Which of these is a primitive data structure?", 
         {"Array", 
          "Integer", 
          "Linked List", 
          "Graph"}, 
         1,
         "Integers are basic, indivisible types directly manipulated by machine instructions."},
         
        // Question 2
        {"What characterizes primitive data structures?", 
         {"They can be divided into smaller units", 
          "They're directly operated by machine instructions", 
          "They require dynamic memory allocation", 
          "They store heterogeneous data"}, 
         1,
         "Primitive types (e.g., int, char) are natively processed by the CPU."},
         
        // Question 3
        {"Non-primitive data structures are classified as:", 
         {"Static and Dynamic", 
          "Linear and Non-Linear", 
          "Homogeneous and Heterogeneous", 
          "Sequential and Random"}, 
         1,
         "They’re categorized by data arrangement (sequential vs. hierarchical)."},
         
        // Question 4
        {"Arrays are called static structures because:", 
         {"Their size is fixed at compile time", 
          "They use contiguous memory", 
          "They store homogeneous data", 
          "They can’t be modified"}, 
         0,
         "Array sizes are predefined and unchangeable during runtime."}
    };
    
    memcpy(quiz->questions, initial_questions, sizeof(initial_questions));
    quiz->correct_first_attempt = 0;
    memset(quiz->incorrect_answers, 0, sizeof(quiz->incorrect_answers));
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

    printf("=== PRIMITIVE & NON-PRIMITIVE DATA STRUCTURES QUIZ ===\n");
    printf("Total Questions: %d\n\n", NUM_QUESTIONS);

    quiz->start_time = time(NULL);

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("\nQuestion %d: %s\n", i + 1, quiz->questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'a' + j, quiz->questions[i].options[j]);
        }

        printf("Your answer (a-d): ");
        char user_answer;
        scanf(" %c", &user_answer);
        
        int user_choice = tolower(user_answer) - 'a';
        if (user_choice == quiz->questions[i].correct_answer) {
            printf("✅ Correct!\nExplanation: %s\n", quiz->questions[i].explanation);
            quiz->correct_first_attempt++;
        } else {
            printf("❌ Incorrect!\nCorrect answer: %c) %s\n", 
                  'a' + quiz->questions[i].correct_answer, 
                  quiz->questions[i].options[quiz->questions[i].correct_answer]);
            printf("Explanation: %s\n", quiz->questions[i].explanation);
            quiz->incorrect_answers[i] = 1;
        }
    }

    quiz->end_time = time(NULL);
    double time_taken = difftime(quiz->end_time, quiz->start_time);
    int minutes = (int)time_taken / 60;
    int seconds = (int)time_taken % 60;

    printf("\n=== RESULTS ===\n");
    printf("Score: %d/%d (%.1f%%)\n", 
           quiz->correct_first_attempt, NUM_QUESTIONS, 
           (float)quiz->correct_first_attempt / NUM_QUESTIONS * 100);
    printf("Time: %d min %d sec\n", minutes, seconds);

    if (quiz->correct_first_attempt < NUM_QUESTIONS) {
        printf("\n=== INCORRECT ANSWERS ===\n");
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (quiz->incorrect_answers[i]) {
                printf("\nQ%d: %s\n", i + 1, quiz->questions[i].question);
                printf("Correct: %c) %s\n", 
                      'a' + quiz->questions[i].correct_answer,
                      quiz->questions[i].options[quiz->questions[i].correct_answer]);
            }
        }
    }
    printf("\n=== QUIZ COMPLETE ===\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    runQuiz(&quiz);
    return 0;
}
