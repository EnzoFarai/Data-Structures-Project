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
        // Section 1: Array Traversal
        {"What is the time complexity of traversing an array of size n?", 
         {"O(1)", 
          "O(log n)", 
          "O(n)", 
          "O(n²)"}, 
         2, 1,
         "Each element must be visited exactly once, resulting in linear time."},
         
        {"How are elements typically accessed during traversal?", 
         {"Random indices", 
          "Sequential indices", 
          "Only even indices", 
          "Via hash values"}, 
         1, 1,
         "Traversal sequentially accesses elements from index 0 to n-1."},

        // Section 2: Insertion Operations
        {"What is the worst-case time complexity of inserting at the beginning of an array?", 
         {"O(1)", 
          "O(n)", 
          "O(log n)", 
          "O(n log n)"}, 
         1, 2,
         "All elements must be shifted right, requiring n operations."},
         
        {"Which code correctly inserts 'x' at position 'pos' in array 'arr'?", 
         "for(int i=pos; i<n; i++) arr[i+1]=arr[i];\narr[pos]=x;", 
         "for(int i=n-1; i>=pos; i--) arr[i+1]=arr[i];\narr[pos]=x;", 
         "arr[pos] = x;", 
         "arr[n] = x;"}, 
         1, 2,
         "Elements must be shifted right-to-left to avoid overwriting."},

        // Section 3: Deletion Operations
        {"Deleting from the middle of an array requires:", 
         {"Shifting all subsequent elements left", 
          "Randomizing remaining elements", 
          "Setting the value to NULL", 
          "No additional operations"}, 
         0, 3,
         "Gaps must be filled by shifting elements left."},
         
        {"What is the time complexity to delete the last element?", 
         {"O(1)", 
          "O(n)", 
          "O(log n)", 
          "O(n²)"}, 
         0, 3,
         "No shifting is needed when removing the last element."},

        // Section 4: Practical Applications
        {"Which operation is essential for implementing a stack using arrays?", 
         {"Reverse traversal", 
          "Insertion/deletion at the end", 
          "Matrix multiplication", 
          "Recursive splitting"}, 
         1, 4,
         "Stacks require efficient push/pop operations at the array's end."},
         
        {"What makes arrays suitable for implementing queues?", 
         {"Constant-time random access", 
          "Efficient insertion/deletion at both ends", 
          "Fixed-size memory allocation", 
          "Automatic sorting"}, 
         2, 4,
         "Though circular arrays are often used to optimize queue operations."},

        // Section 5: Edge Cases
        {"What happens if you insert into a full array?", 
         {"Automatic resizing", 
          "Memory corruption", 
          "Operation fails", 
          "Random element overwrite"}, 
         2, 5,
         "Static arrays cannot grow; dynamic arrays would require reallocation."},
         
        {"After deleting element at index 2 from [10,20,30,40], the array becomes:", 
         {"[10,20,40]", 
          "[10,30,40]", 
          "[10,20,40,0]", 
          "[10,20,40,40]"}, 
         3, 5,
         "Elements shift left, but original size is preserved (last value duplicated)."}
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

    printf("\n=== ARRAY OPERATIONS QUIZ ===\n");
    printf("=== (Traversal, Insertion, Deletion, Applications) ===\n\n");
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
    printf("=== Thank you for testing your array operations knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Array Operations Quiz!\n");
    printf("This quiz covers traversal, insertion, deletion, and practical applications.\n");
    printf("You'll be presented with %d questions across 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
