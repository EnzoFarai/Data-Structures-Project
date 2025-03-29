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
        {"What is the core operation in bubble sort?", 
         {"Finding the minimum element", 
          "Recursively dividing the array", 
          "Comparing and swapping adjacent elements", 
          "Merging sorted subarrays"}, 
         2, 1,
         "Bubble sort repeatedly compares adjacent elements and swaps them if they're in the wrong order."},
         
        {"After each complete pass of bubble sort:", 
         {"The smallest element moves to the front", 
          "The largest element bubbles to its correct position", 
          "The array becomes completely sorted", 
          "Half the elements are in place"}, 
         1, 1,
         "Each pass places the next largest element at its final position at the end of the array."},

        // Section 2: Time Complexity
        {"What is the worst-case time complexity of bubble sort?", 
         {"O(n)", 
          "O(n log n)", 
          "O(n²)", 
          "O(1)"}, 
         2, 2,
         "The nested loops result in quadratic time complexity in all cases (except optimized versions)."},
         
        {"When does bubble sort perform at O(n) time complexity?", 
         {"When the array is reverse sorted", 
          "When the array is already sorted", 
          "For arrays smaller than 10 elements", 
          "Never"}, 
         1, 2,
         "With an optimization flag, it can detect a sorted array in one pass."},

        // Section 3: Space Complexity
        {"What is the space complexity of bubble sort?", 
         {"O(n)", 
          "O(log n)", 
          "O(1)", 
          "O(n²)"}, 
         2, 3,
         "It sorts in-place using only a constant amount of extra space for swapping."},
         
        {"Which statement about bubble sort is TRUE?", 
         {"It's the fastest sorting algorithm", 
          "It requires O(n) auxiliary space", 
          "It can be made stable", 
          "It performs minimum swaps"}, 
         2, 3,
         "Bubble sort is stable by nature as it only swaps adjacent equal elements."},

        // Section 4: Practical Execution
        {"After the first pass on [5,3,8,6,2], the array becomes:", 
         {"[3,5,6,2,8]", 
          "[2,3,5,6,8]", 
          "[5,3,8,2,6]", 
          "[3,5,8,6,2]"}, 
         0, 4,
         "8 bubbles up to the end after comparing/swapping adjacent pairs."},
         
        {"How many total comparisons occur for an array of size 5?", 
         {"5", 
          "10", 
          "15", 
          "20"}, 
         1, 4,
         "For n=5, comparisons = n(n-1)/2 = 10 (4+3+2+1)."},

        // Section 5: Optimizations
        {"What optimization can improve bubble sort's best-case performance?", 
         {"Using recursion", 
          "Adding a swap flag", 
          "Randomizing the array first", 
          "Sorting in parallel"}, 
         1, 5,
         "A flag detecting no swaps in a pass allows early termination (O(n) for sorted arrays)."},
         
        {"Compared to selection sort, bubble sort:", 
         {"Always makes fewer comparisons", 
          "Is always faster", 
          "Typically performs more swaps", 
          "Is stable"}, 
         2, 5,
         "Bubble sort may swap multiple times per pass, while selection sort swaps once per pass."}
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

    printf("\n=== BUBBLE SORT QUIZ ===\n");
    printf("=== (Fundamentals, Complexity, Optimizations) ===\n\n");
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
    printf("=== Thank you for testing your bubble sort knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Bubble Sort Quiz!\n");
    printf("This quiz covers fundamentals, time/space complexity, and optimizations.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
