import csv
import re
import sys

def main():

    # Exit if incorrect number of arguments present
    if len(sys.argv) != 3:
        sys.exit("Missing arguments. Expected input: python dna.py database.csv sequence.txt")

    # Open files and read to memory
    with open(sys.argv[1], "r") as file:
        reader = csv.DictReader(file)
        keys = reader.fieldnames
        # Create a list of dictionaries containing our dna data, and create a set of keys to reference later
        dna_data = []
        for row in reader:
            d = {}
            for key in keys:
                d[key] = row[key]
            dna_data.append(d)

    # Read the dna sequence to a string
    with open(sys.argv[2], "r") as file:
        sequence = file.read().replace("\n", "")

    # Count the max repetitions of each STR
    keys.pop(0)
    person = {}
    for key in keys:
        person[key] = count_matches(key, sequence)

    # Compare our person to each person in the dna data, print a name if it matches
    for d in dna_data:
        match = 1
        for key in keys:
            if person[key] != d[key]:
                match = 0
        if match == 1:
            print(d["name"])
            sys.exit()

    print("No match")
    sys.exit()

# Compares a substring to another string and counts the max repetitions
def count_matches(STR, string):

    max_count = 0
    for i in range(len(string)):
        # Check if the substring matches the current selection
        if string[i : i + len(STR)] == STR:
            counter = 0
            # Count up until a match is no longer found
            while string[i + counter * len(STR) : i + (counter * len(STR)) + len(STR)] == STR:
                counter += 1
            # Update max_count
            if counter > max_count:
                max_count = counter

    return str(max_count)

if __name__ == "__main__":
    main()