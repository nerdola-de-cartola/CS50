def pyramid(h):
    if h == 0:
        return

    # Draw pyramid of height h - 1
    pyramid(h - 1)

    # Print empty spaces
    for i in range(height - h):
        print(" ", end="")

    # Draw the first row of #
    for i in range(h):
        print("#", end="")

    # Print double space
    print("  ", end="")

    # Print the second row of spaces
    for i in range(h):
        print("#", end="")

    # Print a new line
    print()


while True:
    arg = input("Height: ")
    if arg.isnumeric():
        height = int(arg)
        if isinstance(height, int):
            if height > 0 and height <= 8:
                pyramid(height)
                break

