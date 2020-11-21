import time
import random

fail = False

# manhattan_distance
def Manhattan_Distance(board):
    dist = 0
    
    l=len(board)

    for i in range(l):
        dist += abs(i%3 - board[i]%3) + abs(i/3 - board[i]/3)
    return dist


def Random_HillClimbing(board):
    for i in range(len(board)):
        if board[i] == 0:
            break

    while True:
        x = random.randint(0,4)
        
        if x == 0:
            if i >= 3:
                upMove = list(board)
                upMove[i] = board[i-3]
                upMove[i-3] = 0
                return upMove
        
        elif x == 2:
            if i%3 != 0:
                leftMove = list(board)
                leftMove[i] = board[i-1]
                leftMove[i-1] = 0
                return leftMove

        elif x == 1:
            if i < 6:
                downMove = list(board)
                downMove[i] = board[i+3]
                downMove[i+3] = 0
                return downMove
        
        else:    
            if (i+1)%3 != 0:
                rightMove = list(board)
                rightMove[i] = board[i+1]
                rightMove[i+1] = 0
                return rightMove
        
    return board

def solution_RandomHillClimbing(board):
    m = 500000
    c = 0
    while True:
        dist = Manhattan_Distance(board)
        if dist == 0:
            return board

        board = Random_HillClimbing(board)
        c += 1
        
        if(c >= m):
            global fail
            fail = True
            return board
    
def main():
    title = "N_Puzzle_First_Choice"
    start = time.process_time()
    success_Case = 0
    total_Case = 0

    outcome = title + " outcome:\n\n"
    
    with open("CASE.txt", "r") as k:
        for arr in k:
            print("case: ", total_Case)
            global fail
            fail = False
            total_Case += 1
            board = list()

            for colm in arr.split():
                board.append(int(colm))
            
            board = solution_RandomHillClimbing(board)
            
            if fail:
                outcome += "Failed!"
            else:
                success_Case += 1
                for colm in range(len(board)):
                    outcome += str(board[colm]) + " "
            
            outcome += "\n"
    
    end = time.process_time()
    outcome += "\nTotal time: " + str(end - start) + '\n'
    outcome += "Total case number: " + str(total_Case) + ", Success case number: " + str(success_Case) + '\n'
    outcome += "Success rate: " + str(success_Case / float(total_Case)) + '\n'
    print(outcome)
    
    f = open(title + '.txt', 'w')
    f.write(outcome)
    f.close()
            
if __name__ == '__main__':
    main()
