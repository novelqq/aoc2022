f = open("./input.txt", "r")
curr = 0
top = [0]*3
for num in f.readlines():
    if num == '\n':
        if curr > top[-1]:        
            top.append(curr)
        elif curr > top[-2]:
            top.insert(-2, curr)
        elif curr > top[-3]:
            top.insert(-3, curr)
        curr = 0
    else:
        curr += int(num)

ret = top.pop() + top.pop() + top.pop()
print(ret)
