

from pickle import TRUE


class Monkey:
    def __init__(self, index: int, operator: bool, operator_amount: int, test: int, testT: int, testF: int, sq=False) -> None:
        self.index = index
        self.items = []
        self.operator = operator
        self.operator_amount = operator_amount 
        self.test = test
        self.testT = testT
        self.testF = testF
        self.sq = sq
        self.count = 0
    def add_item(self, item: int):
        self.items.append(item)

    def inspect_items(self):
        sending = []
        while self.items:
            self.count += 1
            curr_item = self.items.pop(0)
            if self.sq:
                curr_item *= curr_item
            else:
                if self.operator:
                    #add
                    curr_item += self.operator_amount
                else:
                    #mul
                    curr_item *= self.operator_amount

            #bored
            curr_item = curr_item // 3
            print("monkey: ", self.index, self.testT, curr_item)
            if curr_item % self.test == 0:
                sending.append([self.testT, curr_item])
            else:
                sending.append([self.testF, curr_item])
        return sending

class Monkeys:
    def __init__(self) -> None:
        self.monkeys = {}
    
    def add_monkey(self, monkey: Monkey):
        self.monkeys[monkey.index] = monkey


    def take_turns(self):
        for monkey in self.monkeys:
            sending = self.monkeys[monkey].inspect_items()
            for index, item in sending:
                self.monkeys[index].add_item(item)

    def get_monkey_business(self):
        maxcount = 0
        monkeyindex = 0
        for monkey in self.monkeys:
            if self.monkeys[monkey].count > maxcount:
                maxcount = self.monkeys[monkey].count
                monkeyindex = self.monkeys[monkey].index
        self.monkeys.pop(monkeyindex)
        maxcount2 = 0
        for monkey in self.monkeys:
            maxcount2 = max(self.monkeys[monkey].count, maxcount2)
        
        print(maxcount)
        print(maxcount2)
        return maxcount * maxcount2

if __name__ == "__main__":
    group = Monkeys()
    m0 = Monkey(0, False, 13, 19, 6, 2)
    m0.items = [91, 66]
    m1 = Monkey(1, True, 7, 5, 0, 3)
    m1.items = [78, 97, 59]
    m2 = Monkey(2, True, 6, 19, 6, 2)
    m2.items = [57, 59, 97, 84, 72, 83, 56, 76]
   
    m3 = Monkey(3, True, 5, 17, 6, 0)
    m3.items = [81, 78, 70, 58, 84]
    m4 = Monkey(4, True, 8, 7, 1, 3)
    m4.items = [60]
    m5 = Monkey(5, False, 5, 13, 7, 4)
    m5.items = [57, 69, 63, 75, 62, 77, 72]
    m6 = Monkey(6, False, 0, 3, 5, 2, True)
    m6.items = [73, 66, 86, 79, 98, 87]
    m7 = Monkey(7, True, 13, 19, 6, 2)
    m7.items = [95, 89, 63, 67]

    group.add_monkey(m0)
    group.add_monkey(m1)
    group.add_monkey(m2)
    group.add_monkey(m3)
    group.add_monkey(m4)
    group.add_monkey(m5)
    group.add_monkey(m6)
    group.add_monkey(m7)
    for _ in range(20):
        group.take_turns()

    print(group.get_monkey_business())



