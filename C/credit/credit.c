#include <stdio.h>
#include <cs50.h>

string company_check(long);
int validity_check(long);

int main() {

    long credit_num;
    string company;

    //Prompt user for non-negative credit card number.
    do {
        credit_num = get_long("Enter credit card number: ");
    }   while (credit_num <= 0);

    //Check if number matches a companys prefix and length.
    company = company_check(credit_num);
    if (company == 0) {
        printf("INVALID\n");
        return 0;
    }

    //Check if number passes validity algorithm.
    if (validity_check(credit_num) == 1) {
        printf("%s", company);
    }
    else {
        printf("INVALID\n");
    }
}

string company_check(long cc_num) {
    int count = 0;

    //Cut number down to first two digits, and count number of digits.
    while (cc_num >= 100) {
        cc_num /= 10;
        count++;
    }
    //Add the first two digits and return if number is too small or too large.
    count += 2;
    if (count < 13 || count > 16) {
        return 0;
    }

    //Compare the digits and the count for any company match. If there is no match it'll be invalid.
    if ((cc_num == 34 || cc_num == 37) && count == 15) {
        return "AMEX\n";
    }
    else if ((cc_num >= 51 && cc_num <= 55) && count == 16) {
        return "MASTERCARD\n";
    }
    else if (cc_num/10 == 4 && (count == 13 || count == 16)) {
        return "VISA\n";
    }
    else {
        return 0;
    }
}

int validity_check(long cc_num) {
    int multiplied_by_two;
    int total_sum = 0;

    //Cycle through each digit and either add to total immediately or multiply and then add.
    do {
        //Add current digit to total
        total_sum += cc_num % 10;
        //If there's more digits, continue to the multiply step
        if (cc_num > 9) {
            //Reduce credit card by one digit
            cc_num /= 10;
            multiplied_by_two = (cc_num % 10) * 2;
            //If there's more than two digits in the product then subtract 9
            if (multiplied_by_two > 9) {
                total_sum += multiplied_by_two % 10 - 9;
            }
            else {
                total_sum += multiplied_by_two % 10;
            }
            //Break if there are no more digits left after this step
            if (cc_num < 10) {
                break;
            }
        }
        //Break if there are no more digits left after this step
        if (cc_num < 10) {
            break;
        }
        //Reduce credit card by one digit
        cc_num /= 10;

    }   while (cc_num > 0);

    //If the last digit of the sum is 0 it's valid
    if (total_sum % 10 == 0) {
        return 1;
    }
    else {
        return 0;
    }
}