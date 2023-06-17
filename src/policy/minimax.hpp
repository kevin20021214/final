#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
   static Move get_move(State *state, int depth);
   static int set_heuristic(State *state, int depth);
   static int max(int,int);
   static int min(int,int);
};