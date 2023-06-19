#include <cstdlib>
#include "../state/state.hpp"
#include "./alphabeta.hpp"
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
int Alphabeta::max(int a,int b){
    if(a>b) return a;
    return b;
}
int Alphabeta::min(int a,int b){
    if(a<b) return a;
    return b;
}
int Alphabeta::set_heuristic(State *state,int alpha,int beta,int depth){
    if(state->game_state==WIN){
        if(state->player==0){
            return 1000000000;
        }
        else return -1000000000;
    } 
    else if(depth==0) return state->evaluate();
    else if(state->game_state==DRAW) return 0;
    else if(state->player==0){
        int b;
        b=-1000000000;
        for(int i=0;i<state->legal_actions.size();i++){
            b=max(b,set_heuristic(state->next_state(state->legal_actions[i]),alpha,beta,depth-1));
            alpha=max(b,alpha);
            if(alpha>=beta) break;
        }
        return b;
    }
    else if(state->player==1){
        int b;
        b=1000000000;
        for(int i=0;i<state->legal_actions.size();i++){
            b=min(b,set_heuristic(state->next_state(state->legal_actions[i]),alpha,beta,depth-1));
            beta=min(beta,b);
            if(beta<=alpha) break;
        }
        return b;
    }
}
Move Alphabeta::get_move(State *state, int depth){
    if(!state->legal_actions.size()) state->get_legal_actions();
    auto actions = state->legal_actions;
    int maxvalue=1000000000;
    int minvalue=-1000000000;
    int alpha=minvalue;
    int beta=maxvalue;
    if(state->player==0){
        int nx=0;
        for(int i=0;i<actions.size();i++){
            int tmp=set_heuristic(state->next_state(state->legal_actions[i]),alpha,beta,depth-1);
            if(tmp>minvalue){
                minvalue=tmp;
                alpha=tmp;
                nx=i;
            }
        }
        return state->legal_actions[nx];
    }
    else{
        int nx=0;
        for(int i=0;i<actions.size();i++){
            int tmp=set_heuristic(state->next_state(state->legal_actions[i]),alpha,beta,depth-1);
            if(tmp<maxvalue){
                maxvalue=tmp;
                beta=tmp;
                nx=i;
            }
        }
        return state->legal_actions[nx];
    }
}