#ifndef TUNGUSSKA_PAUSESTATE_H
#define TUNGUSSKA_PAUSESTATE_H

#include "SDL2/SDL.h"
#include "GameState.h"

class PauseState : public GameState {
public:
    void Init();
    
    void Clean();
    
    void Pause();
    
    void Resume();
    
    void HandleEvents(Game *game);
    
    void Update(Game *game);
    
    void Render(Game *game);
    
    // Implement Singleton Pattern
    static PauseState *Instance() {
        return &m_PauseState;
    }

protected:
    
    PauseState() {}

private:
    static PauseState m_PauseState;
    SDL_Event event;
};

#endif //TUNGUSSKA_PAUSESTATE_H
