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
        // Section 1: Time Complexity
        {"What does O(1) time complexity indicate?", 
         {"Runtime grows linearly with input", 
          "Runtime remains constant", 
          "Runtime grows exponentially", 
          "Runtime halves with each operation"}, 
         1, 1,
         "O(1) means the algorithm takes the same time regardless of input size (e.g., accessing an array's first element)."},
         
        {"Binary search has O(log n) complexity because it:", 
         {"Processes all elements sequentially", 
          "Divides the search space in half each iteration", 
          "Uses nested loops", 
          "Requires sorting the input first"}, 
         1, 1,
         "Halving the search space at each step leads to logarithmic growth."},

        // Section 2: Space Complexity
        {"What is the space complexity of creating an n×n matrix?", 
         {"O(1)", 
          "O(n)", 
          "O(n²)", 
          "O(log n)"}, 
         2, 2,
         "Storing n² elements requires quadratic space."},
         
        {"Which algorithm uses O(1) auxiliary space?", 
         {"Merge sort", 
          "Bubble sort", 
          "Quick sort", 
          "Binary search tree"}, 
         1, 2,
         "Bubble sort only needs a constant amount of extra space for temporary variables."},

        // Section 3: Case Analysis
        {"In linear search, the best case occurs when:", 
         {"The target is absent", 
          "The target is at the first position", 
          "The array is unsorted", 
          "The target is at the last position"}, 
         1, 3,
         "Only one comparison is needed if the target is found immediately."},
         
        {"Why is worst-case analysis important?", 
         {"It shows optimal performance", 
          "It guarantees upper performance limits", 
          "It ignores large inputs", 
          "It measures average memory usage"}, 
         1, 3,
         "Worst-case analysis ensures the algorithm won't exceed a certain runtime for any input."},

        // Section 4: Practical Applications
        {"Which time complexity is typical for efficient sorting algorithms?", 
         {"O(n)", 
          "O(n log n)", 
          "O(n²)", 
          "O(2ⁿ)"}, 
         1, 4,
         "Algorithms like merge sort and heapsort achieve O(n log n) complexity."},
         
        {"Recursive Fibonacci has O(2ⁿ) time complexity due to:", 
         {"Constant-time operations", 
          "Repeated calculations of subproblems", 
          "Linear memory usage", 
          "Single loop iterations"}, 
         1, 4,
         "The recursive tree branches exponentially, recalculating values."},

        // Section 5: Comparative Analysis
        {"Which is faster for large inputs: O(n) or O(n²)?", 
         {"O(n)", 
          "O(n²)", 
          "They are equal", 
          "Depends on hardware"}, 
         0, 5,
         "Linear time scales better than quadratic as input grows."},
         
        {"What is the space complexity of recursive Fibonacci?", 
         {"O(1)", 
          "O(n)", 
          "O(n²)", 
          "O(2ⁿ)"}, 
         1, 5,
         "The call stack depth grows linearly with input size n."}
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

    printf("\n=== ALGORITHM COMPLEXITY QUIZ ===\n");
    printf("=== (Time/Space Complexity Analysis) ===\n\n");
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
    printf("=== Thank you for testing your algorithm complexity knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Algorithm Complexity Quiz!\n");
    printf("This quiz covers time and space complexity analysis.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
