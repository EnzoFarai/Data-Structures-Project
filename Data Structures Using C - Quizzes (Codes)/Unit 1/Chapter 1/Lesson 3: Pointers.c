#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 15
#define MAX_QUESTION_LEN 256
#define MAX_OPTION_LEN 100
#define MAX_EXPLANATION_LEN 256

typedef struct {
    char question[MAX_QUESTION_LEN];
    char options[4][MAX_OPTION_LEN];
    int correct_answer;
    char explanation[MAX_EXPLANATION_LEN];
    int section; // To group by sections
} QuizQuestion;

typedef struct {
    QuizQuestion questions[NUM_QUESTIONS];
    int correct_first_attempt;
    int incorrect_answers[NUM_QUESTIONS];
    time_t start_time, end_time;
} Quiz;

void initializeQuiz(Quiz *quiz) {
    QuizQuestion initial_questions[NUM_QUESTIONS] = {
        // Section 1: Pointer Basics
        {"What is a pointer?", 
         {"A variable that stores a data value", 
          "A variable that stores a memory address", 
          "A function that allocates memory", 
          "A data type like int or char"}, 
         1, 1,
         "A pointer holds the memory address of another variable, enabling indirect access to data."},
         
        {"How is a pointer declared in C?", 
         {"pointer int var", 
          "var *int", 
          "datatype *var_name", 
          "*datatype var"}, 
         2, 1,
         "The syntax uses * (e.g., int *ptr;)."},
         
        {"What does the & operator do?", 
         {"Dereferences a pointer", 
          "Returns the memory address of a variable", 
          "Allocates dynamic memory", 
          "Frees allocated memory"}, 
         1, 1,
         "& fetches the address of a variable (e.g., ptr = &a;)."},
         
        {"What does the * operator do when used with a pointer?", 
         {"Declares a pointer", 
          "Accesses the value stored at the pointer's address", 
          "Allocates heap memory", 
          "Returns the pointer's own address"}, 
         1, 1,
         "*ptr retrieves the value at the address stored in ptr."},

        // Section 2: Dynamic Memory Allocation
        {"Which function allocates memory without initializing it?", 
         {"calloc()", 
          "malloc()", 
          "realloc()", 
          "free()"}, 
         1, 2,
         "malloc() allocates raw memory, while calloc() initializes to zero."},
         
        {"What does realloc() do?", 
         {"Frees memory", 
          "Resizes an existing memory block", 
          "Initializes memory to zero", 
          "Converts pointers to integers"}, 
         1, 2,
         "realloc() adjusts the size of a previously allocated memory block."},
         
        {"Which function deallocates memory?", 
         {"release()", 
          "delete()", 
          "free()", 
          "clear()"}, 
         2, 2,
         "free() returns memory to the heap to prevent leaks."},
         
        {"What happens if you dereference a NULL pointer?", 
         {"The program runs normally", 
          "Undefined behavior (e.g., crash)", 
          "Memory is automatically allocated", 
          "The pointer is initialized to zero"}, 
         1, 2,
         "Dereferencing NULL causes undefined behavior, often a segmentation fault."},

        // Section 3: Applications & Pitfalls
        {"Which data structure relies heavily on pointers?", 
         {"Static arrays", 
          "Linked lists", 
          "Primitive data types", 
          "Fixed-size queues"}, 
         1, 3,
         "Linked lists use pointers to connect nodes dynamically."},
         
        {"What is a dangling pointer?", 
         {"A pointer that is NULL", 
          "A pointer to freed memory", 
          "A pointer to a static variable", 
          "A pointer to another pointer"}, 
         1, 3,
         "Dangling pointers reference deallocated memory, causing errors."},
         
        {"What is a memory leak?", 
         {"Allocating too little memory", 
          "Forgetting to free allocated memory", 
          "Using uninitialized pointers", 
          "Accessing out-of-bounds array indices"}, 
         1, 3,
         "Memory leaks occur when dynamically allocated memory isn't freed."},
         
        {"Which pointer application enables modifying pointer values in functions?", 
         {"Single pointers", 
          "Pointers to pointers", 
          "Function pointers", 
          "Array pointers"}, 
         1, 3,
         "Double pointers (int **ptr) allow functions to modify pointer addresses."},

        // Section 4: Practical Scenarios
        {"What is the output of this code?\nint a = 5;\nint *ptr = &a;\nprintf(\"%d\", *ptr);", 
         {"Address of a", 
          "5", 
          "Address of ptr", 
          "Garbage value"}, 
         1, 4,
         "*ptr dereferences the address of a, printing its value (5)."},
         
        {"Which function dynamically allocates memory for an array of 10 integers?", 
         {"malloc(10);", 
          "malloc(10 * sizeof(int));", 
          "calloc(10);", 
          "realloc(ptr, 10);"}, 
         1, 4,
         "malloc() requires the total byte size (10 * sizeof(int))."},
         
        {"What does calloc() initialize allocated memory to?", 
         {"Garbage values", 
          "NULL", 
          "0", 
          "1"}, 
         2, 4,
         "Unlike malloc(), calloc() zero-initializes memory."}
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

    printf("=== POINTERS QUIZ ===\n");
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
