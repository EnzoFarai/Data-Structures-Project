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
        // Section 1: Array Fundamentals
        {"What is the key characteristic of array elements?", 
         {"They must be of different data types", 
          "They are stored in non-contiguous memory", 
          "They share the same data type", 
          "They cannot be modified after declaration"}, 
         2, 1,
         "Arrays store homogeneous elements (same data type) in contiguous memory locations."},
         
        {"Why do arrays provide O(1) random access?", 
         {"Because they use hash tables", 
          "Due to pointer arithmetic with fixed offsets", 
          "They require binary search", 
          "Elements are sorted automatically"}, 
         1, 1,
         "Address calculation uses base pointer + (index × element size) for direct access."},

        // Section 2: 1D Arrays
        {"How is the 3rd element accessed in a 1D array `arr`?", 
         {"arr(3)", 
          "arr[2]", 
          "arr[3]", 
          "arr{3}"}, 
         1, 2,
         "Array indices start at 0, so index 2 refers to the 3rd element."},
         
        {"What happens if you initialize `int nums[] = {10,20,30};`?", 
         {"Compilation error", 
          "Creates a 3-element array", 
          "Creates an empty array", 
          "Allocates memory for 10 elements"}, 
         1, 2,
         "The size is inferred as 3 from the initialization list."},

        // Section 3: 2D Arrays
        {"How is a 2D array element at row 1, column 2 accessed?", 
         {"arr[1,2]", 
          "arr[1][2]", 
          "arr[2][1]", 
          "arr(1)(2)"}, 
         1, 3,
         "C/C++ uses separate brackets for each dimension."},
         
        {"What does `int grid[2][3]` declare?", 
         {"6-element 1D array", 
          "2-row, 3-column matrix", 
          "3-row, 2-column matrix", 
          "Jagged array"}, 
         1, 3,
         "First dimension is rows, second is columns."},

        // Section 4: Array Operations
        {"What is the time complexity to update an array element?", 
         {"O(n)", 
          "O(log n)", 
          "O(1)", 
          "O(n²)"}, 
         2, 4,
         "Direct access via index allows constant-time updates."},
         
        {"Which operation is NOT typically supported natively by arrays?", 
         {"Element insertion at index", 
          "Element deletion", 
          "Dynamic resizing", 
          "Value modification"}, 
         2, 4,
         "Arrays have fixed size; resizing requires creating a new array."},

        // Section 5: Memory Representation
        {"How are 2D arrays stored in memory?", 
         {"As linked lists", 
          "In row-major order", 
          "In column-major order", 
          "As binary trees"}, 
         1, 5,
         "Elements are stored row-wise in contiguous memory."},
         
        {"What is the index range for an array of size N?", 
         {"1 to N", 
          "0 to N-1", 
          "0 to N", 
          "1 to N+1"}, 
         1, 5,
         "C/C++ arrays use zero-based indexing."}
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

    printf("\n=== ARRAYS QUIZ ===\n");
    printf("=== (1D Arrays, 2D Arrays, Memory Representation) ===\n\n");
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
    printf("=== Thank you for testing your array knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Arrays Quiz!\n");
    printf("This quiz covers 1D arrays, 2D arrays, and memory representation.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
