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
        {"What is the core operation in selection sort?", 
         {"Swapping adjacent elements", 
          "Repeatedly finding the minimum element", 
          "Dividing the array into subarrays", 
          "Merging sorted subarrays"}, 
         1, 1,
         "Selection sort works by finding the minimum element in the unsorted portion and placing it in its correct position."},
         
        {"How many passes are needed to sort an array of size n?", 
         {"n", 
          "n-1", 
          "log n", 
          "n²"}, 
         1, 1,
         "After n-1 passes, the last element is automatically in place."},

        // Section 2: Time Complexity
        {"What is the worst-case time complexity of selection sort?", 
         {"O(n)", 
          "O(n log n)", 
          "O(n²)", 
          "O(1)"}, 
         2, 2,
         "The nested loops result in quadratic time complexity regardless of input order."},
         
        {"Why does selection sort always take O(n²) time?", 
         {"It uses recursion", 
          "It compares all elements in every pass", 
          "It requires extra memory", 
          "It's an adaptive algorithm"}, 
         1, 2,
         "Even if the array is sorted, it still performs all comparisons."},

        // Section 3: Space Complexity
        {"What is the space complexity of selection sort?", 
         {"O(n)", 
          "O(log n)", 
          "O(1)", 
          "O(n²)"}, 
         2, 3,
         "It sorts in-place using only a constant amount of extra space."},
         
        {"Which statement about selection sort is TRUE?", 
         {"It's stable", 
          "It requires O(n) auxiliary space", 
          "It performs minimum swaps", 
          "It's the fastest sorting algorithm"}, 
         2, 3,
         "Selection sort makes at most n-1 swaps (one per pass)."},

        // Section 4: Practical Execution
        {"After the first pass on [64,25,12,22,11], the array becomes:", 
         {"[25,64,12,22,11]", 
          "[11,25,12,22,64]", 
          "[11,64,25,22,12]", 
          "[12,25,64,22,11]"}, 
         2, 4,
         "The minimum element (11) is swapped with the first element."},
         
        {"In selection sort, the sorted portion grows from the:", 
         {"Middle of the array", 
          "Left end", 
          "Right end", 
          "Random positions"}, 
         1, 4,
         "Each pass places the next smallest element at the leftmost unsorted position."},

        // Section 5: Comparisons
        {"Compared to bubble sort, selection sort:", 
         {"Makes more swaps", 
          "Is always faster", 
          "Makes fewer swaps", 
          "Is stable"}, 
         2, 5,
         "Bubble sort may swap multiple times per pass, while selection sort swaps once per pass."},
         
        {"When would selection sort be preferable?", 
         {"When memory is limited", 
          "When stability is required", 
          "For nearly sorted data", 
          "For large datasets"}, 
         0, 5,
         "Its O(1) space complexity makes it useful in memory-constrained environments."}
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

    printf("\n=== SELECTION SORT QUIZ ===\n");
    printf("=== (Fundamentals, Complexity, Comparisons) ===\n\n");
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
    printf("=== Thank you for testing your selection sort knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Selection Sort Quiz!\n");
    printf("This quiz covers fundamentals, time/space complexity, and comparisons.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
