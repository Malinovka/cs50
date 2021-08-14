import re
import sys

# Prompt user for text
text = str(input("Enter text: "))

# Split text into sentences
sentences = re.split(r'[\?\.\!]\s', text)

# Split text into words
words = text.split()

# Count number of letters
letters = 0
for i in range(len(text)):
    if text[i].isalnum():
        letters += 1

# Calculate grade
grade = round(0.0588 * (letters / len(words)) * 100 - 0.296 * (len(sentences) / len(words)) * 100 - 15.8)

# Print result
if grade < 1:
    print("Before Grade 1")

elif grade > 15:
    print("Grade 16+")

else:
    print(f"Grade {grade}")

