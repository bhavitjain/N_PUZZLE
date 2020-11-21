#include <bits/stdc++.h>
using namespace std;

# ifndef CLK_TCK
# define CLK_TCK CLOCKS_PER_SEC
# endif

//----------------------------------

#include <cstdio>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <algorithm>

#define Orig_temp 10
#define Max_Tries 300
#define Stop_T 0.000000001
#define Cool_dwn 0.8

//----------------------------------

#define CASES 1000
#define Up 0
#define dwn 1
#define lft 2
#define rght 3

double Solving_time_taken_n_digit;
int Failed_case_n_digit;
double temperature;

inline bool solved(int *state) {
      for (int i = 0; i < 8; i++)
          if (state[i] != i + 1)
              return false;
      return true;
}

//------------------------------------

inline void swap_func(int &a, int &b) 
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}




inline int manhattandis(int num, int Pos) 
{
      int dest_x = ceil(num / 3), dest_y = (num - 1) % 3 + 1, Pos_x = ceil(Pos / 3), Pos_y = (Pos - 1) % 3 + 1;
      return abs(dest_x - Pos_x) + abs(dest_y - Pos_y);
}


//---------------------------

bool N_dig_sol(int *state, int Pos, int dirctn) 
{
    int dis;
    switch (dirctn) {
          case Up:
             if (Pos <= 3)
                  return false;
             else 
             {
                  dis = manhattandis(state[Pos - 4], Pos - 3) - manhattandis(state[Pos - 4], Pos);

                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
          case dwn:
              if (Pos >= 7)
                  return false;
             else 
             {
                  dis = manhattandis(state[Pos + 2], Pos + 3) - manhattandis(state[Pos + 2], Pos);

                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
          case lft:
             if (Pos % 3 == 1)
                  return false;
              else 
              {
                  dis = manhattandis(state[Pos - 2], Pos - 1) - manhattandis(state[Pos - 2], Pos);

                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
          case rght:
              if (Pos % 3 == 0)
                  return false;
             else 
             {
                  dis = manhattandis(state[Pos], Pos + 1) - manhattandis(state[Pos], Pos);

                  return (dis > 0) ? true : ((double)(rand() % 1000) / 1000) < exp(dis / temperature);
              }
      }
      return false;
  }

void Indiv_case(int *state) {
      clock_t start_time = clock();
      int Pos, i, tries_count;
      bool found;

      for (i = 0; i < 9; i++)
      {
          if (state[i] == 0) {
             Pos = i + 1;
              break;
          }
      }


      temperature = Orig_temp;
      tries_count = Max_Tries;
      while (!solved(state)) {
         found = false;
          for (i = 0; i < 4; i++)
             if (N_dig_sol(state, Pos, i)) {
                  found = true;
                  switch (i) {
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
                 break;
            }
         if (--tries_count == 0)
            tries_count = Max_Tries, temperature *= Cool_dwn;

         if (!found || temperature < Stop_T) {
           Failed_case_n_digit++;
             return;
        }
    }
    Solving_time_taken_n_digit += (double)(clock() - start_time) / CLK_TCK;
}

 void Simulated_Annealing_Solution() {
  FILE *fp = fopen("CASE.txt", "r");
    int ini_stg[9];
     while (fscanf(fp, "%d %d %d %d %d %d %d %d %d", ini_stg, ini_stg + 1, ini_stg + 2, ini_stg + 3, ini_stg + 4, ini_stg + 5, ini_stg + 6, ini_stg + 7, ini_stg + 8) != EOF)
         Indiv_case(ini_stg);
     fclose(fp);
 }

 void PRINT_IT() {

    #ifndef ONLINE_JUDGE
    // for writing output from input text file
    freopen("Random_restart_method.txt", "w", stdout);
    #endif

    printf("N-puzzle Simulated Annealing Approach average time: %lf\n", Solving_time_taken_n_digit / (double)(CASES - Failed_case_n_digit));
    printf("N-puzzle Simulated Annealing Approach Rate of Success: %lf\n", 1 - (double(Failed_case_n_digit) / CASES));
}

int main() 
{
    Solving_time_taken_n_digit = 0;

    Failed_case_n_digit = 0;

    Simulated_Annealing_Solution();

    PRINT_IT();

    return 0;
}
