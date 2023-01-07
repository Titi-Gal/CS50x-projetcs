from cs50 import get_string


def coleman_liau_index(letters, words, sentences):
    """Compute Coleman-Liau index."""
    return round(0.0588 * ((letters / words) * 100) - 0.296 * ((sentences / words) * 100) - 15.8)


def main():
    # Gets string from user
    text = get_string("Text: ").strip()

    sentences_separators = [".", "!", "?"]

    letters = 0
    words = 1  # Starts at 1 because there os no space after last word
    sentences = 0
    for character in text:

        # If letters count letter
        if character.isalpha():
            letters += 1
            continue

        # If is space count word
        if " " in character:
            words += 1
            continue

        # If is any of the separators count sentences
        for separator in sentences_separators:
            if separator in character:
                sentences += 1
                break

    grade = coleman_liau_index(letters, words, sentences)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f'Grade {grade}')


if __name__ == "__main__":
    main()

