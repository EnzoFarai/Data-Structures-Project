#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define NUM_QUESTIONS 10
#define MAX_OPTIONS 4
#define LIVES 5
#define OPTION_LEN 100  // Increased from 64 to accommodate longer options
#define EXPLANATION_LEN 300  // Increased from 256 for longer explanations

typedef struct {
    char question[256];
    char options[MAX_OPTIONS][OPTION_LEN];
    char correct_answer;
    char explanation[EXPLANATION_LEN];
} QuizQuestion;

void displayGrade(int score) {
    float percentage = (float)score / NUM_QUESTIONS * 100;
    printf("\n\n=== Quiz Results ===\n");
    printf("Final Score: %d/%d (%.1f%%)\n", score, NUM_QUESTIONS, percentage);
    
    // Grading
    printf("Grade: ");
    if (percentage >= 95) {
        printf("A+\nQuote: \"Outstanding performance! You're a queue expert!\"");
    } else if (percentage >= 90) {
        printf("A-\nQuote: \"Excellent work! You've mastered queue applications!\"");
    } else if (percentage >= 85) {
        printf("B+\nQuote: \"Great job! You understand queues very well!\"");
    } else if (percentage >= 80) {
        printf("B-\nQuote: \"Good work! Just a little more practice needed!\"");
    } else if (percentage >= 75) {
        printf("C+\nQuote: \"Not bad! Review some queue concepts and try again!\"");
    } else if (percentage >= 70) {
        printf("C-\nQuote: \"Keep trying! You're getting there with queues!\"");
    } else if (percentage >= 65) {
        printf("D+\nQuote: \"You passed, but consider reviewing queue basics!\"");
    } else if (percentage >= 60) {
        printf("D-\nQuote: \"You made it, but queues need more attention!\"");
    } else if (percentage >= 55) {
        printf("E+\nQuote: \"You completed it! Time to study queue applications!\"");
    } else if (percentage >= 50) {
        printf("E-\nQuote: \"You finished! Focus on learning queue uses!\"");
    } else {
        printf("F\nQuote: \"Don't give up! Review queue concepts and try again!\"");
    }
}

int main() {
    printf("=== Welcome to the Queue Applications Quiz! ===\n");
    printf("You'll be tested on %d questions about queue data structures.\n", NUM_QUESTIONS);
    printf("You have %d lives. Lose them all and the game ends early!\n\n", LIVES);
    
    // Initialize quiz questions with adjusted string lengths
    QuizQuestion quiz[NUM_QUESTIONS] = {
        {
            "Which of the following queues uses the FIFO (First In First Out) principle?",
            {"Circular Queue", "Simple Queue", "Priority Queue", "Double-Ended Queue"},
            'b',
            "A simple queue strictly follows the FIFO rule, where insertion occurs at the rear and removal occurs at the front."
        },
        {
            "In which of the following scenarios is a circular queue primarily used?",
            {"Load balancing in operating systems", "Traffic light management", "Sorting of data", "Message buffering"},
            'b',
            "Circular queues are used in traffic systems to control traffic lights, ensuring they switch in a circular manner."
        },
        {
            "What is the main advantage of using a priority queue over a simple queue?",
            {"Follows FIFO principle", "Processes based on priority", "No ordering", "Insert at rear"},
            'b',
            "In a priority queue, elements are processed based on priority rather than following FIFO."
        },
        {
            "Which best describes a double-ended queue (Deque)?",
            {"Insert/remove from one end", "Insert/remove from both ends", "Allows sorting", "Circular removal"},
            'b',
            "A Deque allows both insertion and removal of elements from both ends."
        },
        {
            "Which is a correct application of queues in operating systems?",
            {"Buffering print jobs", "Sorting files", "Memory fragmentation", "Caching files"},
            'a',
            "Queues manage print job order, where each job is queued in the order received."
        },
        {
            "How does a circular queue differ from a simple queue?",
            {"Better overflow handling", "No front/rear pointers", "Insert/remove anywhere", "Circular link"},
            'd',
            "A circular queue connects last element to first, utilizing memory better."
        },
        {
            "Which is an application of queues in networking?",
            {"Managing router packets", "Sorting network data", "Filtering by priority", "Compressing packets"},
            'a',
            "Queues hold packets in routers to ensure proper data delivery."
        },
        {
            "Where would a queue help manage waiting lists for shared resources?",
            {"MP3 playlists", "Web server requests", "Disk scheduling", "Traffic lights"},
            'c',
            "Queues handle waiting lists for devices like disks in OS."
        },
        {
            "What happens when a queue has too many elements?",
            {"Underflow", "Priority inversion", "Overflow", "Fragmentation"},
            'c',
            "Queue overflow occurs when adding to a full fixed-size queue."
        },
        {
            "Which is a queue application in traffic management?",
            {"Traffic light sequence", "Vehicle speed sorting", "Vehicle type filtering", "Emergency priority"},
            'a',
            "Queues control sequential activation of traffic lights."
        }
    };
    
    int lives = LIVES;
    int score = 0;
    char answer;
    
    for (int i = 0; i < NUM_QUESTIONS && lives > 0; i++) {
        printf("\nQuestion %d/%d: %s\n", i+1, NUM_QUESTIONS, quiz[i].question);
        for (int j = 0; j < MAX_OPTIONS; j++) {
            printf("%c) %s\n", 'a' + j, quiz[i].options[j]);
        }
        
        printf("Your answer (a-d): ");
        scanf(" %c", &answer);
        answer = tolower(answer);
        
        if (answer == quiz[i].correct_answer) {
            printf("✅ Correct!\n");
            score++;
        } else {
            printf("❌ Incorrect!\n");
            lives--;
            printf("Lives remaining: %d\n", lives);
        }
        
        printf("Explanation: %s\n", quiz[i].explanation);
    }
    
    if (lives == 0) {
        printf("\n\n=== Game Over! You've run out of lives! ===\n");
    }
    
    displayGrade(score);
    
    return 0;
}
