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
        {"What is the key operation in quick sort?", 
         {"Merging sorted subarrays", 
          "Selecting the median element", 
          "Partitioning around a pivot", 
          "Swapping adjacent elements"}, 
         2, 1,
         "Quick sort works by partitioning the array around a pivot element."},
         
        {"Which element is commonly chosen as the pivot?", 
         {"Always the first element", 
          "Always the middle element", 
          "Can be first, last, or random", 
          "The largest element"}, 
         2, 1,
         "Pivot selection can vary, though often the last element is used."},

        // Section 2: Partitioning
        {"What does the partition function return?", 
         {"The pivot value", 
          "The index of the pivot's correct position", 
          "The number of swaps performed", 
          "The size of the left subarray"}, 
         1, 2,
         "The partition returns the final index where the pivot is placed."},
         
        {"During partitioning, elements smaller than the pivot are moved:", 
         {"To the right of the pivot", 
          "To the left of the pivot", 
          "To a separate array", 
          "To random positions"}, 
         1, 2,
         "Smaller elements go left, larger elements go right of the pivot."},

        // Section 3: Time Complexity
        {"What is quick sort's average-case time complexity?", 
         {"O(n)", 
          "O(n log n)", 
          "O(n²)", 
          "O(log n)"}, 
         1, 3,
         "Average-case performance is O(n log n) with good pivot choices."},
         
        {"When does quick sort exhibit O(n²) worst-case behavior?", 
         {"When the array is already sorted", 
          "When using random pivot selection", 
          "For small arrays", 
          "When elements are unique"}, 
         0, 3,
         "Worst-case occurs with poor pivot choices (e.g., sorted array with first/last pivot)."},

        // Section 4: Space Complexity
        {"What is quick sort's space complexity?", 
         {"O(1)", 
          "O(log n)", 
          "O(n)", 
          "O(n log n)"}, 
         1, 4,
         "Space is used for the recursive call stack (log n for balanced partitions)."},
         
        {"Why is quick sort called 'in-place'?", 
         {"It doesn't use recursion", 
          "It requires O(1) extra space", 
          "It sorts within the original array", 
          "It's always faster than merge sort"}, 
         2, 4,
         "Quick sort modifies the original array with minimal extra space."},

        // Section 5: Practical
        {"How can worst-case performance be avoided?", 
         {"By using insertion sort for small subarrays", 
          "By choosing a random pivot", 
          "By always selecting the first element", 
          "By limiting recursion depth"}, 
         1, 5,
         "Randomized pivot selection reduces likelihood of worst-case scenarios."},
         
        {"Compared to merge sort, quick sort is typically:", 
         {"More stable", 
          "Faster in practice", 
          "More memory-intensive", 
          "Slower for large datasets"}, 
         1, 5,
         "Quick sort often has better constants and cache performance."}
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

    printf("\n=== QUICK SORT QUIZ ===\n");
    printf("=== (Partitioning, Complexity, Optimizations) ===\n\n");
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
    printf("=== Thank you for testing your quick sort knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Quick Sort Quiz!\n");
    printf("This quiz covers partitioning, complexity analysis, and optimizations.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
