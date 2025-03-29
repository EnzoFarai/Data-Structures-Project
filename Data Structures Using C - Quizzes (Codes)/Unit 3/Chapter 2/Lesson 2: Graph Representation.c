#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 5
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
        {"An adjacency matrix for a graph with n vertices has size:", 
         {"n × n", 
          "n × e (where e = edges)", 
          "n × 2", 
          "n log n"}, 
         0, 1,
         "It tracks connections between all vertex pairs."},
         
        {"In an adjacency list representation:", 
         {"Edges are stored in a separate array", 
          "Each vertex maintains a list of neighbors", 
          "Parallel edges are explicitly forbidden", 
          "Weights are ignored"}, 
         1, 1,
         "Adjacency lists use linked lists for neighbor tracking."},

        {"An incidence matrix uses -1 to indicate:", 
         {"An unconnected vertex", 
          "An incoming edge to a vertex", 
          "A weighted edge", 
          "A self-loop"}, 
         1, 1,
         "-1 marks an edge entering a vertex (directed graphs)."},

        {"Which representation is most space-efficient for sparse graphs?", 
         {"Adjacency matrix", 
          "Incidence matrix", 
          "Adjacency list", 
          "Edge array"}, 
         2, 1,
         "Adjacency lists avoid storing empty connections."},

        {"For a weighted graph, adjacency matrices store:", 
         {"Only 0s and 1s", 
          "Edge weights instead of 1s", 
          "Vertex degrees", 
          "Negative values for cycles"}, 
         1, 1,
         "Weights replace the binary indicators."}
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

    printf("\n=== GRAPH REPRESENTATION QUIZ ===\n");
    printf("=== (Adjacency Matrix, List, Incidence Matrix) ===\n\n");
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
    printf("=== Thank you for testing your graph representation knowledge! ===\n\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Graph Representation Quiz!\n");
    printf("This quiz covers adjacency matrices, lists, and incidence matrices.\n");
    printf("You'll be presented with %d questions.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
