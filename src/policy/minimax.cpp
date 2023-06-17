#include <cstdlib>
#include "../state/state.hpp"
#include "./minimax.hpp"
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int Minimax::max(int a,int b){
    if(a>=b) return a;
    return b;
}
int Minimax::min(int a,int b){
    if(a<=b) return a;
    return b;
}
int Minimax::set_heuristic(State *state,int depth){
    int a;
    a=state->evaluate();
    if(depth==0||state->game_state==DRAW) return a;
    else if(state->game_state==WIN){
        if(state->player==0){
            return 1000000000;
        }
        else return -1000000000;
    } 
    else if(state->player==0){
        int b;
        b=-1000000000;
        for(int i=0;i<state->legal_actions.size();i++){
            b=max(b,set_heuristic(state->next_state(state->legal_actions[i]),depth-1));
        }
        return b;
    }
    else if(state->player==1){
        int b;
        b=1000000000;
        for(int i=0;i<state->legal_actions.size();i++){
            b=min(b,set_heuristic(state->next_state(state->legal_actions[i]),depth-1));
        }
        return b;
    }
}
Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;
    int maxvalue=1000000000;
    int minvalue=-1000000000;
    if(state->player==0){
        int nx=-1;
        for(int i=0;i<actions.size();i++){
            int tmp=set_heuristic(state->next_state(state->legal_actions[i]),depth-1);
            if(tmp>minvalue){
                minvalue=tmp;
                nx=i;
            }
        }
        return state->legal_actions[nx];
    }
    else{
        int nx=-1;
        for(int i=0;i<actions.size();i++){
            int tmp=set_heuristic(state->next_state(state->legal_actions[i]),depth-1);
            if(tmp<maxvalue){
                maxvalue=tmp;
                nx=i;
            }
        }
        return state->legal_actions[nx];
    }
}