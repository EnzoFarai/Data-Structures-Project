#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 12
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
        // Section 1: Floor and Ceiling
        {"What is ⌊3.7⌋?", 
         {"3", "4", "3.5", "0"}, 
         0, 1,
         "The floor function returns the greatest integer ≤ x. For 3.7, it's 3."},
         
        {"What is ⌈-1.2⌉?", 
         {"-2", "-1", "0", "1"}, 
         1, 1,
         "The ceiling function returns the smallest integer ≥ x. For -1.2, it's -1."},

        // Section 2: Remainder
        {"What is 17 MOD 5?", 
         {"0", "2", "3", "5"}, 
         1, 2,
         "17 ÷ 5 = 3 with remainder 2."},
         
        {"Which describes a MOD m?", 
         {"Quotient of a/m", 
          "Remainder when a is divided by m", 
          "Greatest divisor of a", 
          "Least common multiple"}, 
         1, 2,
         "MOD returns the integer remainder after division."},

        // Section 3: Exponential
        {"What is 2⁴?", 
         {"8", "16", "6", "32"}, 
         1, 3,
         "2⁴ = 2×2×2×2 = 16."},
         
        {"Which represents exponential growth?", 
         {"f(x) = x²", 
          "f(x) = 2ˣ", 
          "f(x) = log(x)", 
          "f(x) = x + 1"}, 
         1, 3,
         "Exponential functions have the form kⁿ, where the variable is the exponent."},

        // Section 4: Logarithmic
        {"What is log₂8?", 
         {"2", "3", "4", "1"}, 
         1, 4,
         "2³ = 8, so log₂8 = 3."},
         
        {"Which is true for any base n?", 
         {"logₙ1 = 0", 
          "logₙn = 0", 
          "logₙ0 = 1", 
          "logₙ(-1) = n"}, 
         0, 4,
         "By definition, logₙ1 = 0 because n⁰ = 1 for any n."},

        // Section 5: Notations
        {"What does ∑(i=1 to 4) i represent?", 
         {"1×2×3×4", 
          "1+2+3+4", 
          "4!", 
          "1²+2²+3²+4²"}, 
         1, 5,
         "Sigma (∑) denotes summation: 1+2+3+4 = 10."},
         
        {"Which set notation represents positive even integers?", 
         {"{x | x ∈ ℤ, x > 0}", 
          "{x | x ∈ ℤ, x = 2k, k ∈ ℤ⁺}", 
          "{1, 3, 5, ...}", 
          "{x | x ≤ 0}"}, 
         1, 5,
         "Correct notation specifies even numbers (x = 2k) and positivity (k ∈ ℤ⁺)."},

        // Section 6: Applications
        {"Which function is used to analyze algorithm complexity?", 
         {"Floor", 
          "Sigma (∑)", 
          "MOD", 
          "Exponential"}, 
         1, 6,
         "Sigma notation sums operations (e.g., loop iterations) in complexity analysis."},
         
        {"What does f(S) = |S| represent?", 
         {"Exponential growth of set S", 
          "Cardinality (size) of set S", 
          "Sum of elements in S", 
          "Power set of S"}, 
         1, 6,
         "|S| denotes the number of elements in set S."}
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

    printf("=== MATHEMATICAL NOTATION AND FUNCTIONS QUIZ ===\n");
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
