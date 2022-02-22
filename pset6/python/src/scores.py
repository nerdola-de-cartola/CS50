from cs50 import get_int

scores = []
for i in range(3):
    scores.append(get_int("Score: "))

print(f"Average: {sum(scores) / len(scores)}")