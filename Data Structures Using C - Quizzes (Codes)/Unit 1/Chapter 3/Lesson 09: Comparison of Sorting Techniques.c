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
        {"Which sorting algorithms have O(n²) worst-case time complexity?", 
         {"Bubble, Selection, and Insertion sorts", 
          "Merge and Quick sorts", 
          "Only Bubble sort", 
          "Only Selection sort"}, 
         0, 1,
         "These three simple sorts all exhibit quadratic time in worst cases."},
         
        {"Which algorithm maintains O(n log n) time complexity in all cases?", 
         {"Quick sort", 
          "Insertion sort", 
          "Merge sort", 
          "Bubble sort"}, 
         2, 1,
         "Merge sort's divide-and-conquer guarantees n log n performance."},

        // Section 2: Space Complexity
        {"Which sorting algorithm has O(1) space complexity?", 
         {"Merge sort", 
          "Quick sort (iterative)", 
          "Insertion sort", 
          "All of the above"}, 
         2, 2,
         "Insertion sort is in-place, needing only constant extra space."},
         
        {"Why does merge sort require O(n) space?", 
         {"For recursive call stacks", 
          "For temporary arrays during merging", 
          "For storing pivot elements", 
          "For multiple passes over data"}, 
         1, 2,
         "It needs auxiliary space to merge sorted subarrays."},

        // Section 3: Best-Case
        {"Which sort performs at O(n) when input is already sorted?", 
         {"Selection sort", 
          "Bubble sort", 
          "Quick sort (naive)", 
          "Merge sort"}, 
         1, 3,
         "Bubble sort can detect sorted arrays in one pass with optimization."},
         
        {"Insertion sort outperforms merge sort for:", 
         {"Large random datasets", 
          "Small or nearly-sorted arrays", 
          "Reverse-sorted data", 
          "Parallel processing"}, 
         1, 3,
         "Its adaptive nature makes it efficient for nearly-ordered data."},

        // Section 4: Selection
        {"When memory is extremely limited, which sort is preferable?", 
         {"Merge sort", 
          "Selection sort", 
          "Quick sort (recursive)", 
          "Bubble sort"}, 
         1, 4,
         "Selection sort's O(1) space makes it suitable for constrained environments."},
         
        {"For stable sorting of large datasets, choose:", 
         {"Quick sort", 
          "Merge sort", 
          "Selection sort", 
          "Insertion sort"}, 
         1, 4,
         "Merge sort provides stable, guaranteed O(n log n) performance."},

        // Section 5: Tradeoffs
        {"Which factor is most important when choosing between quick and merge sort?", 
         {"Code simplicity", 
          "Worst-case time guarantees", 
          "Number of swaps", 
          "Recursion depth"}, 
         1, 5,
         "Merge sort's consistent n log n vs quick sort's potential n² worst-case."},
         
        {"The main advantage of insertion sort over bubble sort is:", 
         {"Better best-case performance", 
          "Fewer total element writes", 
          "Lower space complexity", 
          "Easier implementation"}, 
         1, 5,
         "Insertion sort typically performs fewer writes/swaps than bubble sort."}
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

    printf("\n=== SORTING COMPARISONS QUIZ ===\n");
    printf("=== (Time/Space Complexity, Algorithm Selection) ===\n\n");
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
    printf("=== Thank you for comparing sorting algorithms! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Sorting Comparisons Quiz!\n");
    printf("This quiz covers time/space complexity tradeoffs and algorithm selection.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
