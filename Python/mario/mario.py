# Try until valid input is recieved
while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Invalid input.")
        continue
    if height > 8 or height < 1:
        print("Height must be from 1 to 8 inclusive.")
        continue
    else:
        break;

# Print pyramid
for i in range(1, height + 1, 1):
    print((" " * (height - i)) + ("#" * i) + "  " + ("#" * i))