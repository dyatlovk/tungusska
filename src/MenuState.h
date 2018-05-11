#ifndef TUNGUSSKA_MENUSTATE_H
#define TUNGUSSKA_MENUSTATE_H


#include "GameState.h"

class MenuState : public GameState {
public:
    void Init();
    
    void Clean();
    
    void Pause();
    
    void Resume();
    
    void HandleEvents(Game *game);
    
    void Update(Game *game);
    
    void Render(Game *game);
    
    // Implement Singleton Pattern
    static MenuState *Instance() {
        return &m_MenuState;
    }

protected:
    
    MenuState() {}

private:
    static MenuState m_MenuState;
    SDL_Event event;
    void GameMenu(Game *game);
    Game game;
    bool showConsole = false;
    static void ShowExampleAppConsole(bool* p_open);
};

#endif //TUNGUSSKA_MENUSTATE_H
