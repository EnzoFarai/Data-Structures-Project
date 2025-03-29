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
        {"What is the core principle behind merge sort?", 
         {"Swapping adjacent elements", 
          "Selecting minimum elements", 
          "Divide and conquer", 
          "Random partitioning"}, 
         2, 1,
         "Merge sort recursively divides the array into halves, sorts them, and merges the sorted halves."},
         
        {"Which operation is most critical in merge sort?", 
         {"Partitioning", 
          "Swapping", 
          "Merging sorted subarrays", 
          "Selecting pivots"}, 
         2, 1,
         "The merge operation combines two sorted subarrays into one sorted array."},

        // Section 2: Time Complexity
        {"What is the time complexity of merge sort?", 
         {"O(n)", 
          "O(n log n)", 
          "O(n²)", 
          "O(log n)"}, 
         1, 2,
         "The divide-and-conquer approach with merging yields n log n performance."},
         
        {"Why does merge sort maintain O(n log n) complexity in worst-case?", 
         {"It always divides arrays exactly in half", 
          "It uses randomization", 
          "It skips merging when possible", 
          "It's an in-place algorithm"}, 
         0, 2,
         "The logarithmic division depth and linear merging at each level guarantee n log n time."},

        // Section 3: Space Complexity
        {"What is the space complexity of standard merge sort?", 
         {"O(1)", 
          "O(log n)", 
          "O(n)", 
          "O(n²)"}, 
         2, 3,
         "Requires auxiliary space proportional to the input size for merging."},
         
        {"What causes merge sort's space requirement?", 
         {"Recursive call stack", 
          "Temporary arrays for merging", 
          "Multiple pivot storage", 
          "In-place swapping"}, 
         1, 3,
         "The merge operation needs temporary storage to combine subarrays."},

        // Section 4: Algorithm Execution
        {"When does the recursion in merge sort stop?", 
         {"When the array is reverse sorted", 
          "When subarrays contain 0 or 1 elements", 
          "After exactly log n divisions", 
          "When a swap flag is set"}, 
         1, 4,
         "Base case occurs when subarrays can't be divided further (size ≤ 1)."},
         
        {"What is the key step in the merge operation?", 
         {"Finding the median", 
          "Comparing elements from both subarrays", 
          "Randomly selecting elements", 
          "Swapping adjacent elements"}, 
         1, 4,
         "The merge compares elements from both halves to determine the next in order."},

        // Section 5: Comparisons
        {"Compared to quick sort, merge sort:", 
         {"Is faster in practice", 
          "Has better worst-case guarantees", 
          "Uses less memory", 
          "Is unstable"}, 
         1, 5,
         "Merge sort's O(n log n) worst-case contrasts with quick sort's O(n²) worst-case."},
         
        {"When would merge sort be preferred over insertion sort?", 
         {"For small datasets", 
          "When memory is extremely limited", 
          "For large datasets", 
          "When stability isn't required"}, 
         2, 5,
         "Merge sort's superior time complexity makes it better for large inputs despite higher space usage."}
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

    printf("\n=== MERGE SORT QUIZ ===\n");
    printf("=== (Divide-and-Conquer, Complexity, Applications) ===\n\n");
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
    printf("=== Thank you for testing your merge sort knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Merge Sort Quiz!\n");
    printf("This quiz covers divide-and-conquer, complexity analysis, and comparisons.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
