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
    QuizQuestion q1 = {"What is a pointer in programming?", 
                       {"A variable that stores a value.", "A variable that stores the memory address of another variable.", "A function that returns a value.", "A data type for storing strings."}, 
                       1};
    QuizQuestion q2 = {"Which operator is used to declare a pointer variable in C?", 
                       {"&", "*", "%", "#"}, 
                       1};
    QuizQuestion q3 = {"How do you assign the address of a variable to a pointer?", 
                       {"Using the dereference operator (*).", "Using the address-of operator (&).", "Using the modulus operator (%).", "Using the assignment operator (=)."}, 
                       1};
    QuizQuestion q4 = {"What will the following C code output?\n\n#include <stdio.h>\nint main() {\n    int a = 10;\n    int* ptr = &a;\n    printf(\"%d\\n\", *ptr);\n    return 0;\n}", 
                       {"10", "Address of a", "0", "Undefined behavior"}, 
                       0};
    QuizQuestion q5 = {"Which of the following is NOT an advantage of using pointers?", 
                       {"Efficient array manipulation", "Dynamic memory allocation", "Simplified syntax", "Ability to create complex data structures"}, 
                       2};
    QuizQuestion q6 = {"What is a potential issue when using pointers?", 
                       {"Dereferencing a null or uninitialized pointer.", "Pointers cannot store addresses.", "Pointers are slower than variables.", "Pointers cannot be used in functions."}, 
                       0};
    QuizQuestion q7 = {"In the context of dynamic memory allocation in C, what does the `malloc` function do?", 
                       {"Allocates a specified number of bytes in memory.", "Frees allocated memory.", "Initializes memory to zero.", "Resizes allocated memory."}, 
                       0};
    QuizQuestion q8 = {"Which function is used to deallocate memory that was previously allocated using `malloc` in C?", 
                       {"delete", "free", "release", "dealloc"}, 
                       1};
    QuizQuestion q9 = {"What is the purpose of the `realloc` function in C?", 
                       {"To allocate memory for an array.", "To free allocated memory.", "To resize previously allocated memory blocks.", "To initialize allocated memory to zero."}, 
                       2};
    QuizQuestion q10 = {"In C++, which operator is used for dynamic memory allocation?", 
                        {"malloc", "new", "alloc", "create"}, 
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

    printf("Welcome to the Pointers Quiz!\n");
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
