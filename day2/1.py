f = open("./input.txt", "r")
total = 0
mapping = {
    "AX": 4,
    "AY": 8,
    "AZ": 3,
    "BX": 1,
    "BY": 5,
    "BZ": 9,
    "CX": 7,
    "CY": 2,
    "CZ": 6
}

stratmap = {
    "AX": 3,
    "AY": 4,
    "AZ": 8,
    "BX": 1,
    "BY": 5,
    "BZ": 9,
    "CX": 2,
    "CY": 6,
    "CZ": 7
}

win = {
    "A": 2,
    "B": 3,
    "C": 1
}

lose = {
    "A": 3,
    "B": 1,
    "C": 2
}
for line in f.readlines():
    opp, you = line.split(" ")
    total += stratmap[opp.lstrip()+you.removesuffix('\n')]

print(total)
