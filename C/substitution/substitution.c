#include <string.h>
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>

void generate_cipher(string);


string key;

int main(int argc, char * argv[]) {
    //Check that correct number of arguments entered
    if (argc != 2) {
        printf("Usage: ./substitution [26 char key]\n");
        return 1;
    }

    //Check validity of key
    key = argv[1];
    //Check length
    if (strlen(key) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //Check for all letters of alphabet
    for (int i = 'A'; i <= 'Z'; i++) {
        int count = 0;
        for (int n = 0; n < 26; n++) {
            if (i == toupper(key[n])) {
                count++;
            }
        }
        if (count != 1) {
            printf("Key must contain full alphabet with no duplicates.\n");
            return 1;
        }
    }
    //Prompt user for text input
    string plain_text = get_string("plaintext: ");
    //Generate and print cipher
    generate_cipher(plain_text);

}

void generate_cipher(string text) {
    string cipher_text = (char*) malloc(strlen(text));

    for (int i = 0, n = strlen(text) ; i < n ; i++) {
        if (isupper(text[i])) {
                 cipher_text[i] = toupper(key[text[i] - 'A']);
        }
        else if (islower(text[i])) {
                cipher_text[i] = tolower(key[text[i] - 'a']);
        }
        else {
            cipher_text[i] = text[i];
        }
    }
    printf("ciphertext: %s\n", cipher_text);
}
