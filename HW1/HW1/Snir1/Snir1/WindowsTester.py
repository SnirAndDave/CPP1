from random import randint
from random import shuffle
from subprocess import Popen, PIPE

sides = ['right', 'left', 'up', 'down']
side_direction = [(0,1),(0,-1),(-1,0),(1,0)]
opposite_side = ['left', 'right', 'down', 'up']


class Puzzle:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.size = x*y
        self.pieces = [[None for y in range(y)] for x in range(x)]

    def __iter__(self):
        combinations = [(x,y) for x in range(self.x) for y in range(self.y)]
        for x,y in combinations:
            yield (x,y)

    def get_piece_by_index(self, index):
        return [self.pieces[x][y] for x,y in self if self.pieces[x][y]["index"] == index-1][0]


def get_piece_side(puzzle, x, y, side):
    if 0 <= x < puzzle.x and 0 <= y < puzzle.y:
        if puzzle.pieces[x][y] is None:
            return None
        return puzzle.pieces[x][y][side]
    return 0


def set_piece(puzzle, x, y):
    puzzle.pieces[x][y] = {"x":x,"y":y}
    for i, side in enumerate(sides):
        type = get_piece_side(puzzle, x + side_direction[i][0], y + side_direction[i][1], opposite_side[i])
        if type is None:
            puzzle.pieces[x][y][side] = randint(-1,1)
        else:
            puzzle.pieces[x][y][side] = -1 * type


def set_puzzle():
    puzzle = Puzzle(randint(1, 5), randint(1, 5))
    indexes = [x for x in range(puzzle.size)]
    shuffle(indexes)
    for i, (x, y) in enumerate(puzzle):
        set_piece(puzzle, x, y)
        puzzle.pieces[x][y]["index"] = indexes[i]

    return puzzle


def export_puzzle(puzzle):
    with open("a", "w") as f:
        f.write("NumElements=%d\n" % puzzle.size)
        for x,y in puzzle:
            piece = puzzle.pieces[x][y]
            f.write("%d %d %d %d %d\n" % (piece["index"]+1, piece["left"], piece["up"], piece["right"], piece["down"]))
        f.close()

def read_puzzle():
    new_puzzle = []
    with open("b") as f:
        for line in f:
            line = line.split()  # to deal with blank
            if line:  # lines (ie skip them)
                line = [int(i) for i in line]
                new_puzzle.append(line)
    return new_puzzle

def check_all_pieces_exists(puzzle, new_puzzle):
    flattened = [val for sublist in new_puzzle for val in sublist]
    flattened.sort()
    for i in range(puzzle.size):
        assert(flattened[i] == i+1)

def check_output_file(puzzle):
    new_puzzle = read_puzzle()

    check_all_pieces_exists(puzzle,new_puzzle)

    for x in range(len(new_puzzle)):
        for y in range(len(new_puzzle[x])):
            piece = puzzle.get_piece_by_index(new_puzzle[x][y])
            for i, side in enumerate(sides):
                new_x = x + side_direction[i][0]
                new_y = y + side_direction[i][1]
                if 0 <= new_x < len(new_puzzle) and 0 <= new_y < len(new_puzzle[x]):
                    side_piece = puzzle.get_piece_by_index(new_puzzle[new_x][new_y])
                    if -1 * piece[side] != side_piece[opposite_side[i]]:
                        print("failed!1")
                        return
                elif piece[side] != 0:
                    print("failed!2")
                    return


print("make:")
#p1 = Popen(["make", "clean"], stdin=PIPE, stdout=PIPE, stderr=PIPE)
#p1.wait()
#p1 = Popen(["make"], stdin=PIPE, stdout=PIPE, stderr=PIPE)
#p1.wait()
print("start:")
for x in range(1000):
    puzzle = set_puzzle()
    export_puzzle(puzzle)
    p = Popen(['C:/Users/David/source/repos/CPP1/HW1/HW1/Snir1/CPP1/David5/Debug/David5.exe', 'a', 'b'], stdin=PIPE, stdout=PIPE, stderr=PIPE)
    output, err = p.communicate()
    print(err)
    check_output_file(puzzle)
    print(x)








