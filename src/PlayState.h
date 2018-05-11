#ifndef TUNGUSSKA_PLAYSTATE_H
#define TUNGUSSKA_PLAYSTATE_H

#include "SDL2/SDL.h"
#include "GameState.h"
#include "Mesh.h"
#include "Scene.h"
#include "libs/imgui/imgui.h"

class PlayState : public GameState {
public:
    void Init();
    
    void Clean();
    
    void Pause();
    
    void Resume();
    
    void HandleEvents(Game* game);
    
    void Update(Game* game);
    
    void Render(Game* game);
    
    // Implement Singleton Pattern
    static PlayState *Instance() {
        return &m_PlayState;
    }

protected:
    
    PlayState() = default;

private:
    static PlayState m_PlayState;
    Camera* cam;
    Game game;
    Scene* mScene;
    SDL_Event event;
    ImGuiIO& io = ImGui::GetIO();
    bool showConsole = false;
    bool showDemo = false;
    static void ShowExampleAppConsole(bool* p_open);
    CVar mCVar;
    sol::state lua;
};

#endif //TUNGUSSKA_PLAYSTATE_H
