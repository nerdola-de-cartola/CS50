from sys import argv
from os import read
from csv import DictReader


def main(argv):
    if len(argv) != 3:
        print("Usage: python dna.py data.cs> sequence.txt")
    else:
        # Load data base into memory
        data = []
        with open(argv[1]) as csvfile:
            reader = DictReader(csvfile)
            for row in reader:
                data.append(row)

        # Load the exmple sequence into memory
        with open(argv[2]) as txtfile:
            sequence = txtfile.read()

        # Keep track of what strs we are looking for
        strs = []
        for key, value in data[0].items():
            strs.append(key)
        strs.pop(0)

        # This dictionary represents the person in the txt file
        person = {}
        for s in strs:
            person[s] = countSequence(s, sequence)

        # Compare person with the database
        for p in data:
            # Boolean to crontrol the loop
            samePerson = True

            # Compare each person
            for s in strs:
                # If one of the sequences are diferent
                if int(p[s]) != person[s]:
                    samePerson = False
                    break

            # If matches all dna sequences
            if samePerson == True:
                print(p["name"])
                return

        # If no match dna has found
        print("No match")


def countSequence(substring, completeString):
    # Initialize variables
    maxCount = 0

    # Loops for each possible substring
    for i in range(len(completeString)):
        s = completeString[i:i + len(substring)]

        # If the current substring matches the str sequnce
        if s == substring:
            count = 1

            # Loops until the sequence is over
            for j in range(i + len(substring), len(completeString), len(substring)):
                t = completeString[j: j + len(substring)]
                if t == substring:
                    count += 1
                else:
                    break

            # Update the max count
            if count > maxCount:
                maxCount = count

    return maxCount


main(argv)