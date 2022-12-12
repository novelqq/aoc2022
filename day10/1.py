if __name__ == "__main__":
    file = open("./input.txt", "r")
    instructions = [x.strip("\n").split(" ") for x in file.readlines()]
    signal = [0]*250
    cycle = 1
    x = 1
    for instruction in instructions:
        if instruction[0] == "noop":
            signal[cycle] = x
            cycle += 1
        elif instruction[0] == "addx":
            signal[cycle] = x
            signal[cycle+1] = x
            cycle += 2
            x += int(instruction[1])
    summage = signal[20]*20 + signal[60]*60 + signal[100]*100 + signal[140]*140 + signal[180]*180 + signal[220]*220
    print(summage)
    crt = [['.']*40, ['.']*40,['.']*40, ['.']*40,['.']*40, ['.']*40]
    print(crt)
    crt_index = 0
    crt_indexh = 0
    for i in range(1, 241):
        #print("cycle: ", i, " crt x: ", crt_index, " crt y: ", crt_indexh, " signal i: ", signal[i])
        if signal[i] == crt_index or signal[i]+1 == crt_index or signal[i]-1 == crt_index:
            crt[crt_indexh][crt_index] = '#'    


        if i % 40 == 0:
            crt_index = 0
            crt_indexh += 1
        else:
            crt_index += 1

    for i in range(6):
        for k in range(40):
            print(crt[i][k], end="")
        print("") 
