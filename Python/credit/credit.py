import sys

# Get user input
number = str(input("Enter credit card number: "))

# If it's not a number, exit invalid
if not str.isdigit(number):
    sys.exit("INVALID")

# Get first two digits of number and convert to int
prefix = int(number[:2])

# Check if prefix and string length match a company or else exit invalid
while True:
    if prefix == 34 or prefix == 37:
        if len(number) == 15:
            company = "AMEX"
            break

    elif prefix >= 51 and prefix <= 55:
        if len(number) == 16:
            company = "MASTERCARD"
            break

    elif int(prefix/10) == 4:
        if len(number) == 13 or len(number) == 16:
            company = "VISA"
            break

    else:
        sys.exit("INVALID")

# Calculate if card is valid
total = 0

for i in range(len(number) - 2, -1, -2):
    product = int(number[i]) * 2
    if product > 9:
        total += product - 9
    else:
        total += product

for i in range(len(number) - 1, -1, -2):
    total += int(number[i])

# Print company if valid
if total % 10 == 0:
    print(company)
else:
    sys.exit("INVALID")