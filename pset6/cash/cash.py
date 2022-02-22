from cs50 import get_float
from math import floor


# Prompt the user for the amount for change and print the amount of coins needed

def main():
    # Loops until the user give a valid input

    while True:
        change = get_float("Change owned: ")
        if change >= 0:
            break

    print(calculateCoins(change))


def calculateCoins(total):
    # Define variables

    coins = 0
    quarter = 0.25
    dime = 0.10
    nickel = 0.05
    pennie = 0.01

    # Vefify the best coin to use

    if total >= quarter:
        coins += floor(total / quarter)
        total = round(total % quarter, 2)
    if total >= dime:
        coins += floor(total / dime)
        total = round(total % dime, 2)
    if total >= nickel:
        coins += floor(total / nickel)
        total = round(total % nickel, 2)
    if total >= pennie:
        coins += floor(total / pennie)
        total = round(total % pennie, 2)

    return coins


# Call main

main()
