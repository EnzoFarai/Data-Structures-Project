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
        {"What is the primary purpose of a data structure?", 
         {"To replace programming languages", 
          "To organize data for efficient access and modification", 
          "To increase hardware manufacturing speed", 
          "To delete data permanently"}, 
         1,
         "Data structures optimise how data is stored and retrieved, reducing time and space complexity for operations."},
         
        // Question 2
        {"Which of these is NOT a benefit of using data structures?", 
         {"Faster data processing", 
          "Reduced memory usage", 
          "Increased code complexity", 
          "Easier data modification"}, 
         2,
         "Proper data structures simplify code and improve efficiency in programs, rather than add complexity."},
         
        // Question 3
        {"Which data structure optimizes memory usage?", 
         {"Linked lists only", 
          "Graphs and stacks", 
          "Fixed-size arrays", 
          "Queues and trees"}, 
         0,
         "Linked lists dynamically allocate memory per element, avoiding pre-allocated empty slots (unlike fixed-size arrays)."},
         
        // Question 4
        {"What are the core needs addressed by data structures?", 
         {"Real-time processing and efficient data management", 
          "Eliminating all algorithms", 
          "Increasing code redundancy", 
          "Slowing down systems"}, 
         0,
         "Data structures enable real-time systems (e.g., live navigation, trading) and organized data handling."}
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

    printf("=== DATA STRUCTURES QUIZ ===\n");
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

