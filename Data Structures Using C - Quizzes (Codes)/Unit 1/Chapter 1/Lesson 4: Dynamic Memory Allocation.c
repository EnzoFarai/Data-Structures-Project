#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 12
#define MAX_QUESTION_LEN 512
#define MAX_OPTION_LEN 100
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
        // Section 1: Fundamentals
        {"What is the key difference between static and dynamic memory allocation?", 
         {"Static allocation occurs at runtime", 
          "Dynamic allocation occurs at compile time", 
          "Dynamic allocation occurs at runtime", 
          "Static allocation uses heap memory"}, 
         2, 1,
         "Dynamic allocation allows memory size to be determined during program execution, unlike static allocation."},
         
        {"Which memory segment is used for dynamic memory allocation?", 
         {"Stack", 
          "Heap", 
          "Register", 
          "Cache"}, 
         1, 1,
         "The heap provides flexible memory that can be allocated/released at runtime."},

        // Section 2: C Memory Functions
        {"What does malloc() return if memory allocation fails?", 
         {"A zero-initialized block", 
          "NULL", 
          "Garbage values", 
          "The last valid address"}, 
         1, 2,
         "Always check ptr == NULL after malloc() to handle allocation failures."},
         
        {"Which function initializes allocated memory to zero?", 
         {"malloc()", 
          "calloc()", 
          "realloc()", 
          "free()"}, 
         1, 2,
         "calloc(num, size) allocates and zero-initializes memory for arrays."},
         
        {"What is the purpose of realloc()?", 
         {"To free memory", 
          "To resize an existing memory block", 
          "To initialize pointers", 
          "To check memory leaks"}, 
         1, 2,
         "realloc(ptr, new_size) adjusts previously allocated memory blocks."},
         
        {"Why is free() critical in dynamic memory management?", 
         {"It initializes memory", 
          "It prevents memory leaks", 
          "It resizes memory", 
          "It converts pointers to integers"}, 
         1, 2,
         "Forgetting free() leads to memory leaks by leaving heap memory unreachable."},

        // Section 3: Practical Applications
        {"Which data structure most commonly relies on dynamic memory allocation?", 
         {"Static arrays", 
          "Linked lists", 
          "Fixed-size queues", 
          "Primitive variables"}, 
         1, 3,
         "Linked lists dynamically allocate nodes as needed via pointers."},
         
        {"What happens if you dereference a pointer after calling free() on it?", 
         {"Safe operation", 
          "Dangling pointer error", 
          "Memory is reallocated", 
          "The program terminates gracefully"}, 
         1, 3,
         "Dereferencing freed memory causes undefined behavior (dangling pointer)."},
         
        {"Which scenario requires dynamic memory allocation?", 
         {"Storing 10 integers with a fixed size", 
          "Creating an array whose size is determined at runtime", 
          "Declaring a global variable", 
          "Using stack memory for local variables"}, 
         1, 3,
         "Dynamic allocation is essential when size requirements are unknown at compile time."},

        // Section 4: Code Analysis
        {"What does this code snippet do?\nint *ptr = (int*)malloc(5 * sizeof(int));", 
         {"Allocates stack memory for 5 integers", 
          "Allocates heap memory for 5 integers", 
          "Frees memory for 5 integers", 
          "Declares a static array"}, 
         1, 4,
         "malloc() allocates heap memory for 5 uninitialized integers."},
         
        {"What is missing from this code to avoid a memory leak?\nint *arr = (int*)calloc(10, sizeof(int));\n// ...use arr...", 
         {"realloc(arr, 20)", 
          "free(arr)", 
          "arr = NULL", 
          "Nothing"}, 
         1, 4,
         "free(arr) must be called to release heap memory."},
         
        {"Which line correctly resizes a dynamically allocated array?\nint *ptr = malloc(10 * sizeof(int));\n// Resize to 20 integers:", 
         {"ptr = realloc(10, 20);", 
          "ptr = realloc(ptr, 20 * sizeof(int));", 
          "realloc(ptr, 10);", 
          "free(ptr); malloc(20);"}, 
         1, 4,
         "realloc() takes the original pointer and new size in bytes."}
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

    printf("=== DYNAMIC MEMORY ALLOCATION QUIZ ===\n");
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
