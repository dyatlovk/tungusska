#include "game.h"
#include "MenuState.h"
#include "PlayState.h"

int main(int argc, char *argv[]) {

    Game Tunguska;
    Tunguska.Init();
    
    Tunguska.ChangeState(MenuState::Instance());
    
    while (Tunguska.Running()) {
        Tunguska.HandleEvents();
        Tunguska.Update();
        Tunguska.Render();
    
        glFlush();
        SDL_GL_SwapWindow(Tunguska.window);
    }
    
    Tunguska.Clean();
    
    return 0;
}