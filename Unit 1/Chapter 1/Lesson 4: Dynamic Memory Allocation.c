#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_QUESTIONS 10

typedef struct {
    char question[256];
    char options[4][64];
    int correct_answer; // Index of the correct option (0-3)
} QuizQuestion;

typedef struct {
    QuizQuestion questions[NUM_QUESTIONS];
    int incorrect_answers[NUM_QUESTIONS]; // Tracks incorrect answers
    int total_incorrect;
    int correct_first_attempt;
    time_t start_time;
    time_t end_time;
} Quiz;

void initializeQuiz(Quiz *quiz) {
    QuizQuestion q1 = {"What is dynamic memory allocation?", 
                       {"Allocating memory at compile time.", "Allocating memory during runtime.", "Allocating memory during program design.", "Allocating memory during operating system boot."}, 
                       1};
    QuizQuestion q2 = {"Which function in C is used to allocate a block of memory dynamically?", 
                       {"malloc()", "calloc()", "realloc()", "All of the above"}, 
                       3};
    QuizQuestion q3 = {"What does the `free()` function do in C?", 
                       {"Allocates memory.", "Initializes memory to zero.", "Deallocates previously allocated memory.", "Resizes allocated memory."}, 
                       2};
    QuizQuestion q4 = {"In C++, which operator is used to allocate memory dynamically for a single object?", 
                       {"malloc", "new", "calloc", "alloc"}, 
                       1};
    QuizQuestion q5 = {"What is the correct way to deallocate memory allocated with `new` for an array in C++?", 
                       {"delete ptr;", "free(ptr);", "delete[] ptr;", "release(ptr);"}, 
                       2};
    QuizQuestion q6 = {"Which of the following is a potential issue when using dynamic memory allocation?", 
                       {"Memory leaks", "Dangling pointers", "Fragmentation", "All of the above"}, 
                       3};
    QuizQuestion q7 = {"What is the purpose of the `realloc()` function in C?", 
                       {"To allocate memory for an array.", "To free allocated memory.", "To resize previously allocated memory blocks.", "To initialize allocated memory to zero."}, 
                       2};
    QuizQuestion q8 = {"In the provided C code example, what will happen if `malloc()` fails to allocate memory?", 
                       {"The program will continue execution.", "The program will print \"Memory not allocated.\" and terminate.", "The program will throw an exception.", "The program will automatically retry allocation."}, 
                       1};
    QuizQuestion q9 = {"Why is dynamic memory allocation important in data structures like linked lists?", 
                       {"It allows for a fixed amount of memory usage.", "It enables the creation of data structures with sizes that can change during runtime.", "It simplifies memory management by the compiler.", "It prevents memory fragmentation."}, 
                       1};
    QuizQuestion q10 = {"What is the output of the following C code snippet?\n\nint* ptr;\nptr = (int*)malloc(3 * sizeof(int));\nfor (int i = 0; i < 3; ++i) {\n    ptr[i] = i + 1;\n}\nprintf(\"%d\", *(ptr + 1));\nfree(ptr);", 
                        {"1", "2", "3", "Undefined behavior"}, 
                        1};

    quiz->questions[0] = q1;
    quiz->questions[1] = q2;
    quiz->questions[2] = q3;
    quiz->questions[3] = q4;
    quiz->questions[4] = q5;
    quiz->questions[5] = q6;
    quiz->questions[6] = q7;
    quiz->questions[7] = q8;
    quiz->questions[8] = q9;
    quiz->questions[9] = q10;

    quiz->total_incorrect = 0;
    quiz->correct_first_attempt = 0;
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

    printf("Welcome to the Dynamic Memory Allocation Quiz!\n");
    printf("You will be asked %d questions. Good luck!\n\n", NUM_QUESTIONS);

    quiz->start_time = time(NULL);

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("Question %d: %s\n", i + 1, quiz->questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'a' + j, quiz->questions[i].options[j]);
        }

        char user_answer;
        printf("Your answer: ");
        scanf(" %c", &user_answer);

        int user_choice = user_answer - 'a';
        if (user_choice == quiz->questions[i].correct_answer) {
            quiz->correct_first_attempt++;
        } else {
            quiz->incorrect_answers[i] = 1;
            quiz->total_incorrect++;
            printf("Incorrect! The correct answer is: %c) %s\n\n", 'a' + quiz->questions[i].correct_answer, quiz->questions[i].options[quiz->questions[i].correct_answer]);
        }
    }

    quiz->end_time = time(NULL);

    // Display results
    printf("\nQuiz Results:\n");
    printf("Total Correct Answers on First Attempt: %d\n", quiz->correct_first_attempt);
    printf("Total Incorrect Answers: %d\n", quiz->total_incorrect);
    printf("Percentage Correct on First Attempt: %.2f%%\n", (float)quiz->correct_first_attempt / NUM_QUESTIONS * 100);
    printf("Time Taken: %.2f seconds\n", difftime(quiz->end_time, quiz->start_time));

    // Repeat incorrect questions
    if (quiz->total_incorrect > 0) {
        printf("\nReviewing Incorrect Questions:\n");
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (quiz->incorrect_answers[i]) {
                printf("Question: %s\n", quiz->questions[i].question);
                printf("Correct Answer: %c) %s\n\n", 'a' + quiz->questions[i].correct_answer, quiz->questions[i].options[quiz->questions[i].correct_answer]);
            }
        }
    }
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    runQuiz(&quiz);
    return 0;
}
