import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)
    persons_str_counts_csv = sys.argv[1]
    dna_sequencies_txt = sys.argv[2]

    # Read database file into a variable
    with open(persons_str_counts_csv, "r") as file:
        reader = csv.DictReader(file)
        STRs = reader.fieldnames[1:]
        persons_str_counts = [person for person in reader]
    # Converts counts to ints
    for person in persons_str_counts:
        for dna_STR in STRs:
            person[dna_STR] = int(person[dna_STR])

    # Read DNA sequence file into a variable
    with open(dna_sequencies_txt, "r") as file:
        dna_sequence = file.readline().strip("\n ")

    # Find longest match of each STR in DNA sequence
    longest_STRs_match = {}
    for dna_STR in STRs:
        longest_STRs_match.update({dna_STR: longest_match(dna_sequence, dna_STR)})

    # Check database for matching profiles
    for person in persons_str_counts:
        for dna_STR in STRs:
            if person[dna_STR] != longest_STRs_match[dna_STR]:
                break
        else:
            print(person['name'])
            break
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
