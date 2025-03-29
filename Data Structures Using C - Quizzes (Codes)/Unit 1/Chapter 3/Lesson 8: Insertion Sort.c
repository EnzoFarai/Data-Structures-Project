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
        {"How does insertion sort conceptually work?", 
         {"By repeatedly finding minimum elements", 
          "By dividing the array into subarrays", 
          "By building a sorted portion one element at a time", 
          "By swapping adjacent elements"}, 
         2, 1,
         "Insertion sort maintains a growing sorted subarray, inserting each new element."},
         
        {"What real-world activity is insertion sort often compared to?", 
         {"Flipping pancakes", 
          "Sorting playing cards in hand", 
          "Arranging books on a shelf", 
          "Shuffling a deck"}, 
         1, 1,
         "Like organizing cards, it places elements among already-sorted ones."},

        // Section 2: Time Complexity
        {"What is insertion sort's best-case time complexity?", 
         {"O(n)", 
          "O(n log n)", 
          "O(n²)", 
          "O(1)"}, 
         0, 2,
         "When already sorted, each element only needs one comparison."},
         
        {"Why does insertion sort perform at O(n²) in worst-case?", 
         {"It requires multiple passes over the entire array", 
          "Each insertion may require shifting all sorted elements", 
          "It uses recursive calls", 
          "It needs to merge subarrays"}, 
         1, 2,
         "For reverse-sorted arrays, each new element must be shifted through the entire sorted portion."},

        // Section 3: Space Complexity
        {"What is insertion sort's space complexity?", 
         {"O(n)", 
          "O(log n)", 
          "O(1)", 
          "O(n²)"}, 
         2, 3,
         "It sorts in-place using only constant extra space."},
         
        {"Which statement about insertion sort's memory usage is TRUE?", 
         {"It requires auxiliary arrays", 
          "Its space usage grows with input size", 
          "It's an in-place algorithm", 
          "It needs O(n) stack space"}, 
         2, 3,
         "Only the original array is modified, with minimal extra variables."},

        // Section 4: Execution
        {"After the 3rd iteration for [5,2,4,6,1], the array becomes:", 
         {"[2,4,5,6,1]", 
          "[1,2,4,5,6]", 
          "[5,2,4,1,6]", 
          "[2,5,4,6,1]"}, 
         0, 4,
         "After processing the 3rd element (4), the sorted portion becomes [2,5] → [2,4,5]."},
         
        {"How many comparisons are needed to insert an element in a sorted subarray of size k?", 
         {"Exactly 1", 
          "At most k", 
          "Exactly k", 
          "k²"}, 
         1, 4,
         "In worst case, it may compare with all k sorted elements."},

        // Section 5: Applications
        {"When is insertion sort most efficient?", 
         {"For large random datasets", 
          "For small or nearly-sorted arrays", 
          "When stability isn't required", 
          "When memory is unlimited"}, 
         1, 5,
         "Its adaptive nature makes it efficient for small/nearly-sorted data."},
         
        {"Compared to bubble sort, insertion sort:", 
         {"Always makes more comparisons", 
          "Typically performs fewer writes", 
          "Has better worst-case complexity", 
          "Cannot sort in-place"}, 
         1, 5,
         "Insertion sort only writes when necessary during insertion."}
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

    printf("\n=== INSERTION SORT QUIZ ===\n");
    printf("=== (Fundamentals, Complexity, Practical Use) ===\n\n");
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
    printf("=== Thank you for testing your insertion sort knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Insertion Sort Quiz!\n");
    printf("This quiz covers adaptive sorting, in-place operations, and comparisons.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
