import random
import time

fail = False

# manhattan_distance
def Manhattan_Distance(board):
    dist = 0
    
    l=len(board)

    for i in range(l):
        dist += abs(i%3 - board[i]%3) + abs(i/3 - board[i]/3)
    return dist

def Steepest_Hill_Climbing(board):
    for i in range(len(board)):
        if board[i] == 0:
            break

    distBoard = dict()
    
    if i%3 != 0:
        leftMove = list(board)
        leftMove[i] = board[i-1]
        leftMove[i-1] = 0
        distBoard[i-1] = Manhattan_Distance(leftMove)
    
    if (i+1)%3 != 0:
        rightMove = list(board)
        rightMove[i] = board[i+1]
        rightMove[i+1] = 0
        distBoard[i+1] = Manhattan_Distance(rightMove)
    
    if i >= 3:
        upMove = list(board)
        upMove[i] = board[i-3]
        upMove[i-3] = 0
        distBoard[i-3] = Manhattan_Distance(upMove)

    if i < 6:
        downMove = list(board)
        downMove[i] = board[i+3]
        downMove[i+3] = 0
        distBoard[i+3] = Manhattan_Distance(downMove)

    shortest_Dist = Manhattan_Distance(board)

    for p,val in distBoard.items():
        # "<=" means "not worse than" situation
        # plain
        if val <= shortest_Dist:
            shortest_Dist = val
    
    shortest_distance_points = list()
    for p,val in distBoard.items():
        if val == shortest_Dist:
            shortest_distance_points.append(p)
    
    # can not find a steeper move
    # we have come to the peek(local optimization)
    if len(shortest_distance_points) == 0:
        # print "local optimization"
        global fail
        fail = True
        return board
    
    random.shuffle(shortest_distance_points)
    
    board[i] = board[shortest_distance_points[0]]
    board[shortest_distance_points[0]]= 0
    
    return board

def sol_steepest_Hill_Climbing(board):
    # For each case, there are only several situations using this solution.
    # In average, we will reach a local optimization within 100 steps
    # or fall into a infinite loop (a plain) within 100 steps.
    m = 100
    c = 0
    while True:
        c += 1
        collision_No = Manhattan_Distance(board)
        # print count, collision_No
        if collision_No == 0:
            return board
        board = Steepest_Hill_Climbing(board)
        global fail
        if fail:
            return board
        if(c >= m):
            # for i in range(0,len(board)):
            #     print board[i]
            fail = True
            return board
    
def main():
    title = "N_Puzzle_steepestHillClimbing"
    start = time.process_time()
    success_case_count = 0
    total_case_count = 0
    
    outcome = title + " outcome:\n\n"
    
    with open("N_Puzzle_Test.txt", "r") as k:
        for arr in k:
            print("case: ", total_case_count)
            global fail
            fail = False
            total_case_count += 1
            board = list()

            for j in arr.split():
                board.append(int(j))

            board = sol_steepest_Hill_Climbing(board)
            
            if fail:
                outcome += "Failed!"
            else:
                success_case_count += 1
                for j in range(len(board)):
                    outcome += str(board[j]) + " "
            
            outcome += "\n"
    
    end = time.process_time()
    
    outcome += "\nTotal time: " + str(end - start) + '\n'
    
    outcome += "Total case number: " + str(total_case_count) + ", Success case number: " + str(success_case_count) + '\n'
    
    outcome += "Success rate: " + str(success_case_count / float(total_case_count)) + '\n'
    # print outcome
    
    f = open(title + '.txt', 'w')
    f.write(outcome)
    f.close()
        
if __name__ == '__main__':
    main()