# TODO

# Asks for input for height cheking if is valid.
while True:
    try:
        height = int(input("Height: "))
        if 1 <= height <= 8:
            break
        else:
            print("Must be an integer between 1 and 8")
    except ValueError:
        print("Must be an integer between 1 and 8")

# Prints mario stairs.
for steps_line in range(1, height + 1):
    spaces_line = height - steps_line
    print(" " * spaces_line + "#" * steps_line + "  " + "#" * steps_line)