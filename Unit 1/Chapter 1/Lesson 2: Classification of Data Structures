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
    QuizQuestion q1 = {"What are the two main categories of data structures?", 
                       {"Primitive and Non-Primitive", "Static and Dynamic", "Linear and Non-Linear", "Sequential and Random"}, 
                       0};
    QuizQuestion q2 = {"Which of the following is a characteristic of Primitive Data Structures?", 
                       {"They are derived from Non-Primitive Data Structures.", "They can be directly operated upon by machine-level instructions.", "They are always dynamic in nature.", "They include structures like arrays and linked lists."}, 
                       1};
    QuizQuestion q3 = {"What distinguishes Non-Primitive Data Structures from Primitive Data Structures?", 
                       {"They store a single value.", "They are derived from Primitive Data Structures and can store a collection of values.", "They are directly operated upon by machine-level instructions.", "They are always static in nature."}, 
                       1};
    QuizQuestion q4 = {"Which of the following is an example of a Linear Data Structure?", 
                       {"Tree", "Graph", "Array", "Hash Table"}, 
                       2};
    QuizQuestion q5 = {"How do Static Data Structures differ from Dynamic Data Structures?", 
                       {"Static Data Structures can change in size during runtime.", "Dynamic Data Structures have a fixed size determined at compile-time.", "Static Data Structures have a fixed size determined at compile-time.", "Dynamic Data Structures are always linear."}, 
                       2};
    QuizQuestion q6 = {"Which data structure would be most appropriate for implementing an undo feature in a text editor?", 
                       {"Queue", "Stack", "Array", "Graph"}, 
                       1};
    QuizQuestion q7 = {"In a Queue data structure, where does the insertion of elements occur?", 
                       {"Front end", "Rear end", "Both ends", "Middle"}, 
                       1};
    QuizQuestion q8 = {"Which Non-Linear Data Structure is commonly used to represent hierarchical relationships?", 
                       {"Array", "Linked List", "Tree", "Stack"}, 
                       2};
    QuizQuestion q9 = {"What is a key characteristic of Graph Data Structures?", 
                       {"They store data in a sequential manner.", "They consist of a set of vertices connected by edges.", "They follow the Last In, First Out (LIFO) principle.", "They have a fixed size."}, 
                       1};
    QuizQuestion q10 = {"Which of the following statements is true regarding Linked Lists?", 
                        {"They have a fixed size.", "Memory is allocated at compile-time.", "Each element points to the next, allowing for dynamic memory allocation.", "Elements are stored in contiguous memory locations."}, 
                        2};

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
    srand(time(NULL)); // Seed the random number generator
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Generate a random index
        QuizQuestion temp = questions[i]; // Swap questions[i] and questions[j]
        questions[i] = questions[j];
        questions[j] = temp;
    }
}

void runQuiz(Quiz *quiz) {
    shuffleQuestions(quiz->questions, NUM_QUESTIONS); // Shuffle questions before starting

    printf("Welcome to the Data Structures Quiz!\n");
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
