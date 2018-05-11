#ifndef TUNGUSSKA_GAMESTATE_H
#define TUNGUSSKA_GAMESTATE_H

#include "game.h"

class GameState {
public:
    virtual void Init() = 0;
    
    virtual void Clean() = 0;
    
    virtual void Pause() = 0;
    
    virtual void Resume() = 0;
    
    virtual void HandleEvents(Game *game) = 0;
    
    virtual void Update(Game *game) = 0;
    
    virtual void Render(Game *game) = 0;
    
    void ChangeState(Game *game, GameState *state) {
        game->ChangeState(state);
    }

protected:
    GameState() {}
};

#endif //TUNGUSSKA_GAMESTATE_H
