from cs50 import get_string

str_input = get_string("Do you agree? ")

if str_input.lower() in ["y", "yes"]:
    print("Agreed.")
elif str_input.lower() in ["n", "no"]:
    print("Not agreed.")