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
    QuizQuestion q1 = {"What is a data structure?", {"A programming language", "A way to organize and store data efficiently", "A method of software testing", "A type of computer hardware"}, 1};
    QuizQuestion q2 = {"Which of the following is NOT a benefit of using data structures?", {"Efficient data management", "Increased memory usage", "Better problem-solving capability", "Scalability for large applications"}, 1};
    QuizQuestion q3 = {"What is an example of an application where arrays are commonly used?", {"Implementing undo operations", "Image processing", "Network routing", "Social media friend recommendations"}, 1};
    QuizQuestion q4 = {"Why are linked lists preferred over arrays in dynamic memory allocation?", {"They are easier to implement", "They require less memory", "They allow efficient insertion and deletion", "They are faster for searching data"}, 2};
    QuizQuestion q5 = {"Which data structure is best suited for handling real-time task scheduling?", {"Stack", "Queue", "Graph", "Array"}, 1};
    QuizQuestion q6 = {"What is the time complexity of searching in a hash table (on average)?", {"O(n)", "O(log n)", "O(1)", "O(n²)"}, 2};
    QuizQuestion q7 = {"Which data structure is typically used for implementing undo functionality in text editors?", {"Stack", "Queue", "Linked List", "Tree"}, 0};
    QuizQuestion q8 = {"Which data structure is commonly used in graph traversal algorithms like Dijkstra’s shortest path?", {"Queue", "Stack", "Heap", "Hash Table"}, 2};
    QuizQuestion q9 = {"How does a tree data structure help in organizing hierarchical data?", {"It stores data sequentially", "It represents relationships in a parent-child format", "It only allows fixed-size data storage", "It follows a last-in, first-out (LIFO) principle"}, 1};
    QuizQuestion q10 = {"Which data structure is most efficient for storing frequently accessed data in a cache system?", {"Array", "Stack", "Hash Table", "Queue"}, 2};

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
