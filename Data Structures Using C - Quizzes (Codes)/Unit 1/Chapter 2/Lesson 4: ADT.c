#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 10
#define MAX_QUESTION_LEN 512
#define MAX_OPTION_LEN 128
#define MAX_EXPLANATION_LEN 512

typedef struct {
    char question[MAX_QUESTION_LEN];
    char options[4][MAX_OPTION_LEN];
    int correct_answer;
    char explanation[MAX_EXPLANATION_LEN];
    int section;
} QuizQuestion;

typedef struct {
    QuizQuestion questions[NUM_QUESTIONS];
    int correct_first_attempt;
    int incorrect_answers[NUM_QUESTIONS];
    time_t start_time, end_time;
} Quiz;

void initializeQuiz(Quiz *quiz) {
    QuizQuestion initial_questions[NUM_QUESTIONS] = {
        // Section 1: ADT Fundamentals
        {"What makes an ADT \"abstract\"?", 
         {"It uses complex mathematical operations", 
          "It hides implementation details while exposing operations", 
          "It only works with primitive data types", 
          "It cannot be implemented in code"}, 
         1, 1,
         "ADTs provide an implementation-independent interface, exposing what operations do rather than how they work."},
         
        {"Which feature is NOT characteristic of ADTs?", 
         {"Data encapsulation", 
          "Pre-defined implementation code", 
          "Operation abstraction", 
          "Robust error handling"}, 
         1, 1,
         "ADTs specify operations conceptually without providing pre-built implementations."},

        // Section 2: List ADT
        {"Which List ADT operation returns an element without removing it?", 
         {"insert()", 
          "remove()", 
          "get()", 
          "replace()"}, 
         2, 2,
         "get() accesses an element at a given position while preserving the list structure."},
         
        {"What does isEmpty() test in a List ADT?", 
         {"Memory allocation status", 
          "Presence of any elements", 
          "Data type consistency", 
          "Pointer validity"}, 
         1, 2,
         "isEmpty() checks if the list contains zero elements (size == 0)."},

        // Section 3: Stack ADT
        {"Which principle governs Stack ADT operations?", 
         {"FIFO (First-In-First-Out)", 
          "LIFO (Last-In-First-Out)", 
          "Random access", 
          "Priority ordering"}, 
         1, 3,
         "Stacks process elements in reverse order of insertion (like a plate stack)."},
         
        {"What does peek() do in a Stack ADT?", 
         {"Removes the top element", 
          "Returns the top element without removal", 
          "Reverses the stack order", 
          "Checks for stack overflow"}, 
         1, 3,
         "peek() allows viewing the top element while maintaining stack integrity."},

        // Section 4: Queue ADT
        {"Queue ADT follows which principle?", 
         {"LIFO", 
          "FIFO", 
          "Shortest-job-first", 
          "Round-robin"}, 
         1, 4,
         "Queues process elements in insertion order (like a ticket line)."},
         
        {"Which operation adds an element to a Queue ADT?", 
         {"pop()", 
          "dequeue()", 
          "push()", 
          "enqueue()"}, 
         3, 4,
         "enqueue() inserts elements at the rear (end) of the queue."},

        // Section 5: ADT Features
        {"How does ADT abstraction benefit programmers?", 
         {"By exposing memory addresses", 
          "By allowing focus on usage rather than implementation", 
          "By enforcing single programming languages", 
          "By eliminating all errors"}, 
         1, 5,
         "Abstraction lets programmers use data structures without knowing internal details."},
         
        {"Which ADT would best model a printer's job queue?", 
         {"List", 
          "Stack", 
          "Queue", 
          "Integer array"}, 
         2, 5,
         "Printers process jobs in FIFO order, matching Queue ADT behavior."}
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

    printf("\n=== ABSTRACT DATA TYPES QUIZ ===\n");
    printf("=== (ADT Fundamentals, Lists, Stacks, Queues) ===\n\n");
    printf("Total Questions: %d\n\n", NUM_QUESTIONS);

    quiz->start_time = time(NULL);

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("\nQuestion %d (Section %d): %s\n", 
              i + 1, quiz->questions[i].section, quiz->questions[i].question);
        
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'a' + j, quiz->questions[i].options[j]);
        }

        printf("Your answer (a-d): ");
        char user_answer;
        scanf(" %c", &user_answer);
        
        // Input validation
        user_answer = tolower(user_answer);
        while (user_answer < 'a' || user_answer > 'd') {
            printf("Invalid input. Please enter a-d: ");
            scanf(" %c", &user_answer);
            user_answer = tolower(user_answer);
        }
        
        int user_choice = user_answer - 'a';
        if (user_choice == quiz->questions[i].correct_answer) {
            printf("\n✅ Correct!\n\nExplanation: %s\n", quiz->questions[i].explanation);
            quiz->correct_first_attempt++;
        } else {
            printf("\n❌ Incorrect!\nCorrect answer: %c) %s\n", 
                  'a' + quiz->questions[i].correct_answer, 
                  quiz->questions[i].options[quiz->questions[i].correct_answer]);
            printf("\nExplanation: %s\n", quiz->questions[i].explanation);
            quiz->incorrect_answers[i] = 1;
        }
    }

    quiz->end_time = time(NULL);
    double time_taken = difftime(quiz->end_time, quiz->start_time);
    int minutes = (int)time_taken / 60;
    int seconds = (int)time_taken % 60;

    printf("\n=== FINAL RESULTS ===\n");
    printf("Correct Answers: %d/%d (%.1f%%)\n", 
           quiz->correct_first_attempt, NUM_QUESTIONS, 
           (float)quiz->correct_first_attempt / NUM_QUESTIONS * 100);
    printf("Time Taken: %d min %d sec\n", minutes, seconds);

    if (quiz->correct_first_attempt < NUM_QUESTIONS) {
        printf("\n=== QUESTIONS TO REVIEW ===\n");
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (quiz->incorrect_answers[i]) {
                printf("\nQ%d (Section %d): %s\n", 
                      i + 1, quiz->questions[i].section, quiz->questions[i].question);
                printf("Correct Answer: %c) %s\n", 
                      'a' + quiz->questions[i].correct_answer,
                      quiz->questions[i].options[quiz->questions[i].correct_answer]);
                printf("Explanation: %s\n", quiz->questions[i].explanation);
            }
        }
    }
    
    printf("\n=== QUIZ COMPLETE ===\n");
    printf("=== Thank you for testing your ADT knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Abstract Data Types Quiz!\n");
    printf("This quiz covers ADT fundamentals, Lists, Stacks, and Queues.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
