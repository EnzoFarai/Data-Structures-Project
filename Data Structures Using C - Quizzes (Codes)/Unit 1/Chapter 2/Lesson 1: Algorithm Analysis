#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 10
#define MAX_QUESTION_LEN 256
#define MAX_OPTION_LEN 100
#define MAX_EXPLANATION_LEN 256

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
        // Section 1: Algorithm Fundamentals
        {"Which characteristic ensures an algorithm will terminate?", 
         {"Input/Output", 
          "Finiteness", 
          "Language independence", 
          "Effectiveness"}, 
         1, 1,
         "Finiteness requires an algorithm to have a countable number of instructions that guarantee termination."},
         
        {"What makes an algorithm language-independent?", 
         {"It uses specific programming syntax", 
          "It can be implemented in any language with same results", 
          "It only works with machine code", 
          "It requires a particular compiler"}, 
         1, 1,
         "Language independence means the logic can be implemented across different programming languages."},

        // Section 2: Complexity Analysis
        {"What is the primary difference between performance and complexity?", 
         {"Performance measures exact runtime, complexity measures scaling", 
          "Complexity depends on hardware, performance doesn't", 
          "They are identical concepts", 
          "Performance analyzes memory, complexity analyzes time"}, 
         0, 2,
         "Performance is machine-dependent runtime, while complexity describes how resource needs grow with input size."},
         
        {"Which complexity type measures memory usage growth?", 
         {"Time complexity", 
          "Space complexity", 
          "Best-case complexity", 
          "Average-case complexity"}, 
         1, 2,
         "Space complexity analyzes memory requirements relative to input size."},

        // Section 3: Case Analysis
        {"In linear search, the best case occurs when:", 
         {"The target is absent", 
          "The target is at the first position", 
          "The target is at the last position", 
          "The array is unsorted"}, 
         1, 3,
         "Best case represents the optimal scenario (minimum operations)."},
         
        {"What does worst-case analysis provide?", 
         {"Minimum runtime guarantee", 
          "Upper bound on runtime", 
          "Average performance", 
          "Memory usage at best case"}, 
         1, 3,
         "Worst-case gives the maximum time an algorithm could take (e.g., O(n) for linear search)."},

        // Section 4: Big O Notation
        {"What does O(n²) indicate?", 
         {"Constant time", 
          "Linear time", 
          "Quadratic time", 
          "Logarithmic time"}, 
         2, 4,
         "O(n²) means runtime grows with the square of input size (e.g., nested loops)."},
         
        {"The space complexity of recursive Fibonacci is O(n) because:", 
         {"It stores all Fibonacci numbers", 
          "Call stack depth grows linearly with input", 
          "It uses constant memory", 
          "It has iterative implementation"}, 
         1, 4,
         "Each recursive call adds a stack frame, with maximum depth proportional to n."},

        // Section 5: Practical Analysis
        {"What is the time complexity of finding maximum in an array?", 
         {"O(1)", 
          "O(n)", 
          "O(log n)", 
          "O(n log n)"}, 
         1, 5,
         "It requires examining each element once (linear time)."},
         
        {"Why is average-case analysis useful?", 
         {"It gives exact runtime predictions", 
          "It describes expected performance for random inputs", 
          "It ignores all real-world factors", 
          "It only considers best scenarios"}, 
         1, 5,
         "Average-case helps understand typical behavior across varied inputs."}
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

    printf("=== ALGORITHM ANALYSIS QUIZ ===\n");
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
