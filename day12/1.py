import heapq, math
from sys import maxsize
def import_mapf_instance(filename):
    start = (0,0)
    goal = (0,0)
    my_map = []
    f = open(filename, 'r')
    raw_map = [x.strip('\n') for x in f.readlines()]
    for r, line in enumerate(raw_map):
        my_map.append([])
        for i, cell in enumerate(line):
            if cell == 'S':
                my_map[-1].append('a')
                start = (r, i)
            elif cell == 'E':
                my_map[-1].append('z')
                goal = (r, i)
            else:
                my_map[-1].append(cell)
    return my_map, start, goal
def import_mapf_instance2(filename):
    starts = []
    goal = (0,0)
    my_map = []
    f = open(filename, 'r')
    raw_map = [x.strip('\n') for x in f.readlines()]
    for r, line in enumerate(raw_map):
        my_map.append([])
        for i, cell in enumerate(line):
            if cell == 'a':
                my_map[-1].append('a')
                starts.append((r, i))
            elif cell == 'E':
                my_map[-1].append('z')
                goal = (r, i)
            else:
                my_map[-1].append(cell)
    return my_map, starts, goal
def move(loc, dir):
    directions = [(0, -1), (1, 0), (0, 1), (-1, 0)]
    return loc[0] + directions[dir][0], loc[1] + directions[dir][1]

def get_path(goal_node):
    path = []
    curr = goal_node
    while curr is not None:
        path.append(curr['loc'])
        curr = curr['parent']
    path.reverse()
    return path

def push_node(open_list, node):
    heapq.heappush(open_list, (node['g_val'] + node['h_val'], node['h_val'], node['loc'], node))


def pop_node(open_list):
    _, _, _, curr = heapq.heappop(open_list)
    return curr

def compare_nodes(n1, n2):
    """Return true is n1 is better than n2."""
    return n1['g_val'] + n1['h_val'] < n2['g_val'] + n2['h_val']

def euclidean_distance(point1, point2):
    x_diff = point1[0] - point2[0]
    y_diff = point1[1] - point2[1]
    distance = math.sqrt(x_diff**2 + y_diff**2)
    return distance

def compute_n2_h(my_map, goal):
    h_values = dict()
    for y in range(len(my_map)):
        for x in range(len(my_map[0])):
            h_values[(y, x)] = euclidean_distance((y,x), goal)
    return h_values

def is_valid_loc(my_map, current_loc, new_loc):
    curr_height = ord(my_map[current_loc[0]][current_loc[1]])
    new_height = ord(my_map[new_loc[0]][new_loc[1]])
    if new_height - curr_height > 1:
        return False
    else:
        return True
def a_star(my_map, start_loc, goal_loc, h_values):
    open_list = []
    closed_list = dict()
    h_value = h_values[start_loc]
    root = {'loc': start_loc, 'g_val': 0, 'h_val': h_value, 'parent': None}
    push_node(open_list, root)
    closed_list[(root['loc'])] = root
    while len(open_list) > 0:
        curr = pop_node(open_list)
        if curr['loc'] == goal_loc:
            return get_path(curr)
        for dir in range(4):
            child_loc = move(curr['loc'], dir)
            if child_loc[0] < 0 or child_loc[0] >= len(my_map) or child_loc[1] == -1 or child_loc[1] >= len(max(my_map)):
                continue
            if not is_valid_loc(my_map, curr['loc'], child_loc):
                continue
            child = {'loc': child_loc,
                    'g_val': curr['g_val'] + 1,
                    'h_val': h_values[child_loc],
                    'parent': curr}
            if (child['loc']) in closed_list:
                existing_node = closed_list[(child['loc'])]
                if compare_nodes(child, existing_node):
                    closed_list[(child['loc'])] = child
                    push_node(open_list, child)
            else:
                closed_list[(child['loc'])] = child
                push_node(open_list, child)

    return None  # Failed to find solutions

def part1():
    print("part1")
    my_map, start, goal = import_mapf_instance("./input.txt")
    h_values = compute_n2_h(my_map, goal)
    solution = a_star(my_map, start, goal, h_values)
    if solution is not None:
        print("steps: ", len(solution) - 1)

def part2():
    print("part2")
    my_map, starts, goal = import_mapf_instance2("./input.txt")
    h_values = compute_n2_h(my_map, goal)
    min_steps = maxsize
    for start in starts:
        solution = a_star(my_map, start, goal, h_values)
        if solution is not None:
            min_steps = min(min_steps, len(solution) - 1)

    print("steps: ", min_steps)
        
if __name__ == "__main__":
    part1()
    part2()
