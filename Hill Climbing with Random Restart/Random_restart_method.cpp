#include<bits/stdc++.h>
#include <cmath>
#include <cstdlib>

# ifndef CLK_TCK
# define CLK_TCK CLOCKS_PER_SEC
# endif

#include <cstdio>

#include <ctime>
#include <algorithm>
using namespace std;
#define Up 0
#define dwn 1
#define lft 2
#define rght 3

#define CASES 1000
#define STEP 100


struct State {
    int dirctn, manhattandifference;
    State(int i, int dis) 
    {
        this->dirctn = i;
        this->manhattandifference = dis;
    }
    bool operator<(const State &s) const {
        return manhattandifference > s.manhattandifference;
    }
};

  double Solving_time_taken_n_digit;
  int Failed_case_n_digit;
  int manhattandifference_dis;

inline void swap_func(int &a, int &b) 
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

inline bool solved(int *state) 
{
    for (int i = 0; i < 8; i++)
         if (state[i]!= (i+1))
              return  false ;
     return  true ;
}

inline int manhattan_distance ( int num, int Pos) {
       int dest_x = ceil (num / 3 ), dest_y = (num - 1 )% 3 + 1 , Pos_x = ceil (Pos / 3 ), Pos_y = ( Pos - 1 )% 3 + 1 ;
    return abs(dest_x - Pos_x) + abs(dest_y - Pos_y);
}

bool N_dig_sol(int *state, int Pos, int dirctn) {
      switch (dirctn) {
         case Up:
              if (Pos <= 3)
                  return false;
              else 
              {
                  manhattandifference_dis =  manhattan_distance(state[Pos - 4], Pos - 3) - manhattan_distance(state[Pos - 4], Pos);
                  return manhattan_distance(state[Pos - 4], Pos - 3) > manhattan_distance(state[Pos - 4], Pos);
              }
          case dwn:
              if (Pos >= 7)
                  return false;
              else
              {
                  manhattandifference_dis = manhattan_distance(state[Pos + 2], Pos + 3) - manhattan_distance(state[Pos + 2], Pos);
                  return manhattan_distance(state[Pos + 2], Pos + 3) > manhattan_distance(state[Pos + 2], Pos);
              }
          case lft:
              if (Pos % 3 == 1)
                  return false;
              else 
              {
                  manhattandifference_dis = manhattan_distance(state[Pos - 2], Pos - 1) - manhattan_distance(state[Pos - 2], Pos);
                  return manhattan_distance(state[Pos - 2], Pos - 1) > manhattan_distance(state[Pos - 2], Pos);
              }
         case rght:
              if (Pos % 3 == 0)
                 return false;
              else 
              {
                  manhattandifference_dis =  manhattan_distance(state[Pos], Pos + 1) - manhattan_distance(state[Pos], Pos);
                  return manhattan_distance(state[Pos], Pos + 1) > manhattan_distance(state[Pos], Pos);
              }
      }
      return false;
}

void n_digit_states(int *s) {
      int state[9] = {1, 2, 3, 4, 0, 5, 6, 7, 8}, steps, Pos, dirctn;
      steps = STEP;
      Pos = 9;
      while (steps--) {
         dirctn = rand() % 4;
          switch (dirctn) {
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
     for (int i = 0; i < 9; i++)
         s[i] = state[i];
}

void Indiv_case(int *state) {
     clock_t start_time = clock();
     int Pos, i;
     bool found;
     for (i = 0; i < 9; i++)
         if (state[i] == 0) {
             Pos = i + 1;
             break;
         }
    while (!solved(state)) {
        found = false;
         std::vector<State> v;
         for (i = 0; i < 4; i++) {
            if (N_dig_sol(state, Pos, i)) {
                found = true;
                 v.push_back(State(i, manhattandifference_dis));
             }
             if (i == 3 && found) {
                 std::sort(v.begin(), v.end());
                 switch (v[0].dirctn) {
                     case Up:
                        swap_func(state[Pos - 1], state[Pos - 4]), Pos -= 3;
                         break;
                     case dwn:
                       swap_func(state[Pos - 1], state[Pos + 2]), Pos += 3;
                         break;
                     case lft:
                        swap_func(state[Pos - 1], state[Pos - 2]), Pos--;
                        break;
                     case rght:
                        swap_func(state[Pos - 1], state[Pos]), Pos++;
                         break;
                }
             }
        }
         if (!found)
             n_digit_states(state);
    }
    Solving_time_taken_n_digit += (double)(clock() - start_time) / CLK_TCK;
}

void Randm_Restart_solution() {
    FILE *fp = fopen("CASE.txt", "r");
    int ini_stg[9];
    while (fscanf(fp, "%d %d %d %d %d %d %d %d %d", ini_stg, ini_stg + 1, ini_stg + 2, ini_stg + 3, ini_stg + 4, ini_stg + 5, ini_stg + 6, ini_stg + 7, ini_stg + 8) != EOF)
    {
        Indiv_case(ini_stg);
    }
    fclose(fp);
 }

 void PRINT_IT() {

    #ifndef ONLINE_JUDGE
    // for writing output from input text file
    freopen("Random_Restart_output.txt", "w", stdout);
    #endif

    printf("N-puzzle Random Restart Approach average time: %lf\n", Solving_time_taken_n_digit / (double)(CASES - Failed_case_n_digit));
    printf("N-puzzle Random Restart Approach Rate of Success: %lf\n", 1 - double(Failed_case_n_digit) / CASES);
}

 int main() {

    /*#ifndef ONLINE_JUDGE
    // for writing output from input text file
    freopen("Inp.txt", "r", stdin);
    #endif*/


    Solving_time_taken_n_digit = 0;
    Failed_case_n_digit = 0;
    Randm_Restart_solution();
    PRINT_IT();
    return 0;
 }
