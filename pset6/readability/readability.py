from cs50 import get_string


def main():
    # Input from user
    text = get_string("Text: ")

    # Assigning variables
    l = calculateLetters(text)
    w = calculateWords(text)
    s = calculateSenteces(text)
    index = colemanLiau(l, w, s)

    # Print the correct message
    if index <= 1:
        message = f"Before Grade 1"
    elif index >= 16:
        message = f"Grade 16+"
    else:
        message = f"Grade {index}"

    print(message)


# Return the number of letters in a text
def calculateLetters(text):
    lettersCount = 0

    for char in text:
        if char.isalpha():
            lettersCount += 1
    print(lettersCount)
    return lettersCount


# Return the number of words in a text
def calculateWords(text):
    wordsCount = 1

    for char in text:
        if char == " ":
            wordsCount += 1
    print(wordsCount)
    return wordsCount


# Return the number of senteces in a text
def calculateSenteces(text):
    sentecesCount = 0

    for char in text:
        if char == "." or char == "?" or char == "!":
            sentecesCount += 1
    print(sentecesCount)
    return sentecesCount


def colemanLiau(letters, words, senteces):

    # Average number of letters per 100 words
    L = letters / words * 100
    # Average number of senteces per 100 words
    S = senteces / words * 100

    # Return the Coleman-Liau index
    return round(0.0588 * L - 0.296 * S - 15.8)


main()
