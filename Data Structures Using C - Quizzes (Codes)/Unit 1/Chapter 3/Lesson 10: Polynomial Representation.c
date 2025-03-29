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
        {"What are the two essential components of a polynomial term?", 
         {"Base and power", 
          "Coefficient and exponent", 
          "Variable and constant", 
          "Integer and float"}, 
         1, 1,
         "Each term has a coefficient (numeric multiplier) and exponent (power)."},
         
        {"Which polynomial type has exactly three terms?", 
         {"Monomial", 
          "Binomial", 
          "Trinomial", 
          "Quadrinomial"}, 
         2, 1,
         "Examples include 2x² + 3x + 1 (terms separated by +/−)."},

        // Section 2: Array Representation
        {"How is the polynomial 4x³ + 2x + 7 stored in an array?", 
         {"[4, 0, 2, 7]", 
          "[7, 2, 0, 4]", 
          "[4, 2, 7]", 
          "[3, 1, 0]"}, 
         0, 2,
         "Array indices correspond to exponents, with coefficients at positions."},
         
        {"What is the main limitation of array representation?", 
         {"Difficult to evaluate", 
          "Wastes space for sparse polynomials", 
          "Cannot handle negative exponents", 
          "Limited to single-variable polynomials"}, 
         1, 2,
         "Arrays allocate space for all exponents up to highest degree."},

        // Section 3: Linked List
        {"What does each node in a polynomial linked list store?", 
         {"Only the coefficient", 
          "Coefficient, exponent, and next pointer", 
          "Variable name and value", 
          "Degree and term count"}, 
         1, 3,
         "Nodes contain coefficient, exponent, and pointer to next term."},
         
        {"Why is linked list representation preferred for sparse polynomials?", 
         {"Faster evaluation", 
          "Only stores non-zero terms", 
          "Easier to multiply", 
          "Better cache performance"}, 
         1, 3,
         "It efficiently skips zero terms by storing only existing terms."},

        // Section 4: Operations
        {"When adding two polynomials using arrays, what determines the result's size?", 
         {"Sum of all coefficients", 
          "Highest degree among inputs", 
          "Number of non-zero terms", 
          "Always fixed size"}, 
         1, 4,
         "Result array must accommodate terms up to maximum input degree."},
         
        {"In linked list addition, what happens when exponents match?", 
         {"Terms are multiplied", 
          "Coefficients are added", 
          "The larger term is kept", 
          "A new node is always created"}, 
         1, 4,
         "Matching exponents trigger coefficient addition (e.g., 5x² + 3x² = 8x²)."},

        // Section 5: Evaluation
        {"What is the time complexity of evaluating a polynomial of degree n?", 
         {"O(1)", 
          "O(n)", 
          "O(n log n)", 
          "O(n²)"}, 
         1, 5,
         "Requires n multiplications and n additions (Horner's method can optimize)."},
         
        {"Which representation is more efficient for polynomial multiplication?", 
         {"Arrays due to random access", 
          "Linked lists due to dynamic sizing", 
          "Both are equally efficient", 
          "Depends on compiler optimizations"}, 
         0, 5,
         "Array indices allow direct access to terms, simplifying pairing."}
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

    printf("\n=== POLYNOMIAL REPRESENTATION QUIZ ===\n");
    printf("=== (Array vs Linked List, Operations) ===\n\n");
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
    printf("=== Thank you for testing your polynomial knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Polynomial Representation Quiz!\n");
    printf("This quiz covers array/linked list representations and operations.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
