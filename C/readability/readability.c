#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int calculate_grade(string);

int main() {
    // Prompt user for text string
    string input = get_string("Enter text: ");

    // Check grade
    int grade = calculate_grade(input);

    // Print result
    if (grade < 1) {
        printf("Before Grade 1\n");
    }
    else if (grade > 1 && grade < 16) {
        printf("Grade %d\n", grade);
    }
    else {
        printf("Grade 16+\n");
    }
}


int calculate_grade(string text) {
    float letters = 0;
    float words = 1;
    float sentences = 0;

    for (int i = 0, n = strlen(text) ; i < n ; i++) {
        //Checks each character and increments the affected counter
        if (isalpha(text[i])) {
            letters++;
        }
        else if (text[i] == ' ') {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            sentences++;
        }
    }
    // Coleman-Liau formula
    return round(0.0588 * (letters/words)*100 - 0.296 * (sentences/words)*100 - 15.8);
}