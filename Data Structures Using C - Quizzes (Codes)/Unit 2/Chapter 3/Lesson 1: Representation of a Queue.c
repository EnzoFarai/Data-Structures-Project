#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 6
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
        {"Which principle best describes queue operations?", 
         {"Last-In-First-Out (LIFO)", 
          "First-In-First-Out (FIFO)", 
          "Random Access", 
          "Priority-Based"}, 
         1, 1,
         "Queues strictly follow FIFO where the first element inserted is the first removed, like a ticket line."},
         
        {"What do the FRONT and REAR pointers indicate in a queue?", 
         {"FRONT tracks newest element, REAR tracks oldest", 
          "FRONT tracks insertion point, REAR tracks removal point", 
          "FRONT tracks first element, REAR tracks last element", 
          "FRONT tracks empty slots, REAR tracks filled slots"}, 
         2, 1,
         "FRONT points to the oldest element (removal point) while REAR points to the newest (insertion point)."},

        {"How is an empty queue represented in array implementation?", 
         {"FRONT = 0, REAR = MAXSIZE-1", 
          "FRONT = -1, REAR = -1", 
          "FRONT = NULL, REAR = NULL", 
          "FRONT = REAR = 0"}, 
         1, 1,
         "-1 values for both pointers indicate no elements exist."},

        {"What is a key advantage of linked list queue representation?", 
         {"Fixed memory allocation", 
          "Constant-time random access", 
          "No predefined size limitation", 
          "Better cache locality"}, 
         2, 1,
         "Linked lists dynamically allocate nodes, eliminating fixed capacity constraints."},

        {"Which operation adds elements to the queue?", 
         {"Dequeue", 
          "Peek", 
          "Enqueue", 
          "isFull"}, 
         2, 1,
         "Enqueue inserts elements exclusively at the REAR position."},

        {"What happens when REAR reaches MAXSIZE-1 in array implementation?", 
         {"Automatic array doubling", 
          "Queue underflow", 
          "Queue overflow", 
          "Pointer reset to 0"}, 
         2, 1,
         "The queue is full and cannot accept more elements."}
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

    printf("\n=== QUEUE FUNDAMENTALS QUIZ ===\n");
    printf("=== (FIFO Principle, Implementation) ===\n\n");
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
    printf("=== Thank you for testing your queue fundamentals knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Queue Fundamentals Quiz!\n");
    printf("This quiz covers FIFO principle, FRONT/REAR pointers, and implementations.\n");
    printf("You'll be presented with %d questions.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
