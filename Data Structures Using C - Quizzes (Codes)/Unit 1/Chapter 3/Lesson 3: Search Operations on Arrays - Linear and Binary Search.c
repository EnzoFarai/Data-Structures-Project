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
        // Section 1: Linear Search
        {"What is the worst-case time complexity of linear search?", 
         {"O(1)", 
          "O(log n)", 
          "O(n)", 
          "O(n²)"}, 
         2, 1,
         "In the worst case (element absent or at last position), all n elements must be checked."},
         
        {"When does linear search perform at O(1) time complexity?", 
         {"When the array is sorted", 
          "When the target is the first element", 
          "When using parallel processing", 
          "For arrays smaller than 10 elements"}, 
         1, 1,
         "Best-case occurs when the target is found at index 0."},

        // Section 2: Binary Search Requirements
        {"What precondition must be met for binary search?", 
         {"Array must be unsorted", 
          "Array must be sorted", 
          "Array must have duplicate values", 
          "Array size must be even"}, 
         1, 2,
         "Binary search relies on the sorted order to divide the search space."},
         
        {"Which statement about binary search is FALSE?", 
         {"It has O(log n) time complexity", 
          "It can only be implemented recursively", 
          "It requires random access capability", 
          "It's more efficient than linear search for large datasets"}, 
         1, 2,
         "Binary search can be implemented both iteratively and recursively."},

        // Section 3: Algorithm Comparisons
        {"For an array of 1024 elements, what is the maximum number of comparisons needed by binary search?", 
         {"10", 
          "100", 
          "512", 
          "1024"}, 
         0, 3,
         "2¹⁰ = 1024 ⇒ max 10 comparisons (log₂1024 = 10)."},
         
        {"When would linear search be preferred over binary search?", 
         {"For large sorted arrays", 
          "When the array is unsorted", 
          "When O(1) space is required", 
          "For multi-dimensional arrays"}, 
         1, 3,
         "Binary search cannot work on unsorted data without preprocessing."},

        // Section 4: Implementation Details
        {"What is the purpose of `mid = start + (end - start)/2` in binary search?", 
         {"To avoid integer overflow", 
          "To ensure mid is always even", 
          "To prioritize left half", 
          "To reduce constant factors"}, 
         0, 4,
         "This prevents potential overflow from `(start + end)/2`."},
         
        {"In the recursive binary search implementation, what condition terminates the recursion?", 
         {"`start > end`", 
          "`arr[mid] == key`", 
          "Both a and b", 
          "When memory is exhausted"}, 
         2, 4,
         "Either the element is found (`arr[mid]==key`) or the search space is exhausted (`start>end`)."},

        // Section 5: Practical Applications
        {"Which search method would a dictionary app most likely use?", 
         {"Linear search", 
          "Binary search", 
          "Bubble search", 
          "Hash-based search"}, 
         1, 5,
         "Dictionary words are stored sorted, making binary search ideal."},
         
        {"What is the space complexity of iterative binary search?", 
         {"O(n)", 
          "O(log n)", 
          "O(1)", 
          "O(n log n)"}, 
         2, 5,
         "Iterative version uses constant space (no call stack)."}
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

    printf("\n=== ARRAY SEARCH OPERATIONS QUIZ ===\n");
    printf("=== (Linear Search, Binary Search, Comparisons) ===\n\n");
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
    printf("=== Thank you for testing your array search knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Array Search Operations Quiz!\n");
    printf("This quiz covers linear search, binary search, and their comparisons.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
