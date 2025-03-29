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
        // Section 1: Fundamentals
        {"What keyword is used to declare a structure in C?", 
         {"class", 
          "object", 
          "struct", 
          "typedef"}, 
         2, 1,
         "The 'struct' keyword defines a new composite data type."},
         
        {"How do you access member 'age' in structure variable 'person'?", 
         {"person->age", 
          "person.age", 
          "person[age]", 
          "person::age"}, 
         1, 1,
         "Dot notation accesses members of non-pointer structure variables."},

        // Section 2: Declaration
        {"What is missing in this structure declaration?\nstruct student { char name[50]; int id; };", 
         {"Structure name", 
          "Member functions", 
          "Structure variable", 
          "Nothing is missing"}, 
         2, 2,
         "The declaration is valid but doesn't create variables."},
         
        {"Which correctly initializes a structure?\nstruct point { int x; int y; };", 
         {"point p = {5, 10};", 
          "struct point p = {5, 10};", 
          "p.x = 5; p.y = 10; (without declaration)", 
          "point->x = 5; point->y = 10;"}, 
         1, 2,
         "Must use 'struct point' in C unless typedef'd."},

        // Section 3: Self-Reference
        {"What makes a structure self-referential?", 
         {"Containing pointers to its own type", 
          "Having recursive member functions", 
          "Including nested structures", 
          "Using dynamic memory allocation"}, 
         0, 3,
         "Contains pointers to the same structure type (e.g., linked list nodes)."},
         
        {"In a doubly-linked list node structure, how many self-referential pointers?", 
         {"0", 
          "1", 
          "2", 
          "Variable"}, 
         2, 3,
         "Needs both 'next' and 'prev' pointers."},

        // Section 4: Applications
        {"Why are structures essential for linked lists?", 
         {"They allow function overloading", 
          "They group data and link to next node", 
          "They automatically resize memory", 
          "They enable operator overloading"}, 
         1, 4,
         "Combine node data with self-referential pointers."},
         
        {"Which operation is invalid on structures?", 
         {"Assignment (struct1 = struct2)", 
          "Arithmetic (e.g., struct1 + struct2)", 
          "Member access (struct.member)", 
          "Pointer dereferencing (struct_ptr->member)"}, 
         1, 4,
         "Arithmetic operations aren't defined for entire structures."},

        // Section 5: Memory
        {"What is the size of this structure?\nstruct example { char c; int i; };", 
         {"sizeof(char) + sizeof(int)", 
          "Often 8 bytes due to padding", 
          "Always 5 bytes", 
          "Depends on optimization level"}, 
         1, 5,
         "Padding aligns members to memory boundaries."},
         
        {"How do you create an array of structures?\nstruct book { char title[50]; float price; };", 
         {"book array[10];", 
          "struct book library[10];", 
          "book* library = malloc(10);", 
          "struct book* library[10];"}, 
         1, 5,
         "In C, arrays require the 'struct' keyword unless typedef'd."}
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

    printf("\n=== STRUCTURES QUIZ ===\n");
    printf("=== (Declaration, Memory, Applications) ===\n\n");
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
    printf("=== Thank you for testing your structures knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Structures Quiz!\n");
    printf("This quiz covers declaration, memory layout, and applications.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
