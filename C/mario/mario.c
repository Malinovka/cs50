#include <stdio.h>

int main() {

    void print_char_loop(char, int);

    int height;

    //Prompt user to enter int from 1 to 8 inclusive
    do {
        printf("Enter a number from 1 to 8: ");
        scanf("%d", &height);

    }   while (height < 1 || height > 8);

    //Print two pyramids, spaced two blocks apart
    for (int spaces = height - 1; spaces >= 0; spaces--) {
        print_char_loop(' ', spaces);
        print_char_loop('#', height - spaces);
        print_char_loop(' ', 2);
        print_char_loop('#', height - spaces);
        printf("\n");
    }
}

//Prints 'c' character 'n' number of times
void print_char_loop(char c, int n) {
    while (n > 0) {
        printf("%c", c);
        n--;
    }
}