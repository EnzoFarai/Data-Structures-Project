#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define NUM_QUESTIONS 10
#define MAX_QUESTION_LEN 256
#define MAX_OPTION_LEN 100
#define MAX_EXPLANATION_LEN 256

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
        {"What is the purpose of asymptotic notation?", 
         {"To calculate exact runtime of algorithms", 
          "To describe growth rates of algorithm complexity", 
          "To determine programming language efficiency", 
          "To measure hardware performance"}, 
         1, 1,
         "Asymptotic notation describes how an algorithm's resource requirements grow as input size increases, ignoring constant factors."},
         
        {"Which terms are ignored in asymptotic analysis?", 
         {"Most significant terms", 
          "Least significant terms", 
          "All logarithmic terms", 
          "Only constant terms"}, 
         1, 1,
         "For large inputs, lower-order terms (e.g., 2n in 5n² + 2n + 1) become negligible."},

        // Section 2: Big-O
        {"What does Big-O (O) represent?", 
         {"Average-case complexity", 
          "Lower bound of complexity", 
          "Upper bound/Worst-case complexity", 
          "Exact memory usage"}, 
         2, 2,
         "Big-O describes the maximum time/space an algorithm could take (e.g., O(n²))."},
         
        {"If f(n) = 4n³ + 2n + 7, its Big-O is:", 
         {"O(n)", 
          "O(n²)", 
          "O(n³)", 
          "O(1)"}, 
         2, 2,
         "The dominant term n³ determines the growth rate."},

        // Section 3: Big-Ω
        {"Big-Ω (Ω) describes:", 
         {"Best-case complexity/Lower bound", 
          "Worst-case complexity", 
          "Average memory usage", 
          "Fixed runtime"}, 
         0, 3,
         "Ω indicates the minimum resources needed (e.g., Ω(n) for linear search's best case)."},
         
        {"Which represents Ω(n) correctly?", 
         {"3n + 5 = Ω(n)", 
          "n² = Ω(n³)", 
          "log n = Ω(n)", 
          "2ⁿ = Ω(1)"}, 
         0, 3,
         "3n + 5 grows at least as fast as n (with C=1, n₀=1)."},

        // Section 4: Big-Θ
        {"Big-Θ (Θ) provides:", 
         {"Only upper bounds", 
          "Tight bounds/Average-case complexity", 
          "Only lower bounds", 
          "Exact runtime formula"}, 
         1, 4,
         "Θ describes both upper and lower bounds (e.g., 3n + 2 = Θ(n))."},
         
        {"For f(n) = 5n log n + 3n, Θ is:", 
         {"Θ(n)", 
          "Θ(n log n)", 
          "Θ(log n)", 
          "Θ(n²)"}, 
         1, 4,
         "n log n is the dominant term that bounds the function."},

        // Section 5: Practical Analysis
        {"An O(1) algorithm's runtime:", 
         {"Grows linearly with input", 
          "Remains constant", 
          "Grows quadratically", 
          "Depends on hardware"}, 
         1, 5,
         "O(1) indicates constant time, independent of input size."},
         
        {"Binary search has a worst-case complexity of:", 
         {"O(n)", 
          "O(log n)", 
          "O(n log n)", 
          "O(1)"}, 
         1, 5,
         "It halves the search space each iteration, giving logarithmic growth."}
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

    printf("\n=== ASYMPTOTIC NOTATIONS QUIZ ===\n");
    printf("=== Based on Lecture Topic 1.2.2 ===\n");
    printf("Total Questions: %d\n\n", NUM_QUESTIONS);

    quiz->start_time = time(NULL);

    for (int i = 0; i < NUM_QUESTIONS; i++) {
        printf("\nSection %d: Question %d\n", quiz->questions[i].section, i+1);
        printf("%s\n", quiz->questions[i].question);
        for (int j = 0; j < 4; j++) {
            printf("%c) %s\n", 'a' + j, quiz->questions[i].options[j]);
        }

        printf("Your answer (a-d): ");
        char user_answer;
        scanf(" %c", &user_answer);
        
        // Convert to lowercase and validate input
        user_answer = tolower(user_answer);
        while(user_answer < 'a' || user_answer > 'd') {
            printf("Invalid input. Please enter a-d: ");
            scanf(" %c", &user_answer);
            user_answer = tolower(user_answer);
        }
        
        int user_choice = user_answer - 'a';
        if (user_choice == quiz->questions[i].correct_answer) {
            printf("\n✅ Correct!\n");
            printf("Explanation: %s\n", quiz->questions[i].explanation);
            quiz->correct_first_attempt++;
        } else {
            printf("\n❌ Incorrect!\n");
            printf("Correct answer: %c) %s\n", 
                  'a' + quiz->questions[i].correct_answer, 
                  quiz->questions[i].options[quiz->questions[i].correct_answer]);
            printf("Explanation: %s\n", quiz->questions[i].explanation);
            quiz->incorrect_answers[i] = 1;
        }
    }

    quiz->end_time = time(NULL);
    double time_taken = difftime(quiz->end_time, quiz->start_time);
    int minutes = (int)time_taken / 60;
    int seconds = (int)time_taken % 60;

    printf("\n=== QUIZ RESULTS ===\n");
    printf("Final Score: %d/%d (%.1f%%)\n", 
           quiz->correct_first_attempt, NUM_QUESTIONS, 
           (float)quiz->correct_first_attempt / NUM_QUESTIONS * 100);
    printf("Time Taken: %d minutes %d seconds\n", minutes, seconds);

    // Detailed performance analysis
    printf("\nPerformance Analysis:\n");
    if (quiz->correct_first_attempt == NUM_QUESTIONS) {
        printf("Perfect score! You've mastered asymptotic notations.\n");
    } else if (quiz->correct_first_attempt >= NUM_QUESTIONS * 0.8) {
        printf("Excellent understanding! Review a few concepts.\n");
    } else if (quiz->correct_first_attempt >= NUM_QUESTIONS * 0.6) {
        printf("Good attempt. Focus on the following areas:\n");
    } else {
        printf("Needs improvement. Please review these concepts:\n");
    }

    if (quiz->correct_first_attempt < NUM_QUESTIONS) {
        printf("\n=== INCORRECT ANSWERS ===\n");
        for (int i = 0; i < NUM_QUESTIONS; i++) {
            if (quiz->incorrect_answers[i]) {
                printf("\nSection %d: Question %d\n", quiz->questions[i].section, i+1);
                printf("Question: %s\n", quiz->questions[i].question);
                printf("Your answer: %c) %s\n", 
                      'a' + quiz->questions[i].correct_answer,
                      quiz->questions[i].options[quiz->questions[i].correct_answer]);
                printf("Explanation: %s\n", quiz->questions[i].explanation);
            }
        }
    }
    
    printf("\n=== KEY TAKEAWAYS ===\n");
    printf("- Big-O (O): Worst-case/upper bound complexity\n");
    printf("- Big-Ω (Ω): Best-case/lower bound complexity\n");
    printf("- Big-Θ (Θ): Tight bounds complexity\n");
    printf("- Asymptotic analysis ignores constants and lower-order terms\n");
    
    printf("\n=== QUIZ COMPLETE ===\n");
}

int main() {
    Quiz quiz;
    initializeQuiz(&quiz);
    
    printf("Welcome to the Asymptotic Notations Quiz!\n");
    printf("This quiz tests your understanding of algorithm complexity analysis.\n");
    printf("There are %d questions divided into 5 sections.\n\n", NUM_QUESTIONS);
    
    runQuiz(&quiz);
    return 0;
}
