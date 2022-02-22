from cs50 import get_string

str_input = get_string("Do you agree? ")

if str_input == 'y' or str_input == 'Y':
    print("Agreed.")
elif str_input == "n" or str_input == "N":
    print("Not agreed.")