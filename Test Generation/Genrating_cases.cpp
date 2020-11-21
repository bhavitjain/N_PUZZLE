#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>

#define Up 0
#define dwn 1
#define lft 2
#define rght 3

using namespace std;

#define Cases 1000
#define STEP 10000


inline void swap_func(int &A, int &B) 
{
    int temp;
    temp = A;
    A = B;
    B = temp;
}
    
//Function for generating N-Puzzle problem

void N_puzzle_testcases() {
    FILE *fp = fopen("CASE.txt", "w");


    int testcase = Cases, dirctn, Pos, steps;
    
    while (testcase--) 
    {
        int state[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        steps = STEP;
        Pos = 9;
        while (steps--) 
        {
            
            dirctn = rand() % 4;
            switch (dirctn) 
            {
                case Up:
                    if (Pos <= 3)
                        break;
                    else {
                        swap_func(state[Pos - 1], state[Pos - 4]), Pos -= 3;
                        break;
                    }
                case dwn:
                    if (Pos >= 7)
                        break;
                    else {
                        swap_func(state[Pos - 1], state[Pos + 2]), Pos += 3;
                        break;
                    }
                case lft:
                    if (Pos % 3 == 1)
                        break;
                    else {
                        swap_func(state[Pos - 1], state[Pos - 2]), Pos--;
                        break;
                    }
                case rght:
                    if (Pos % 3 == 0)
                        break;
                    else {
                        swap_func(state[Pos - 1], state[Pos]), Pos++;
                        break;
                    }
            }
        }
        



        fprintf(fp, "%d %d %d %d %d %d %d %d %d\n", state[0], state[1], state[2], state[3], state[4], state[5], state[6], state[7], state[8]);
    }

    fclose(fp);
}


//---------------------------------------


int main() 
{
    N_puzzle_testcases();
    return 0;
}
