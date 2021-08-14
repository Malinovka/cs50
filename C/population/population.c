#include <stdio.h>

int main() {

    int start_pop_size;
    int end_pop_size;
    int years = 0;

// Prompt the user for a starting population size, a number that is greater than or equal to 9.
    do {
        printf("Enter a starting population (9 minimum): ");
        scanf("%d", &start_pop_size);
    }   while (start_pop_size < 9);

// Prompt the user for an ending population size greater than or equal to the starting population size.
    do {
        printf("Enter an ending population size (%d minimum): ", start_pop_size);
        scanf("%d", &end_pop_size);
    }   while (end_pop_size < start_pop_size);

//Calculate the (int) number of years required for the population to reach at least the size of the end value.
    while (start_pop_size < end_pop_size) {
        start_pop_size = start_pop_size + (start_pop_size / 3) - (start_pop_size /4);
        years++;
    }

//Print the number of years required for the llama population to reach end size.
    printf("Years: %d\n", years);
}