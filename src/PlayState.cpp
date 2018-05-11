#include <cstdio>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include "SDL2/SDL.h"

#include "CVar.h"
#include "game.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"

PlayState PlayState::m_PlayState;

/**
 * PlayState::Init
 */
void PlayState::Init() {

    lua.open_libraries( sol::lib::base );
    lua.script_file("../data/scripts/game.lua");

    cam = new Camera(game.window, 1280, 800);
    mScene = new Scene("../data/locations/start.json");
    LOG_DEBUG << "Play state init";
    lua["PlayState"]();
}

/**
 * PlayState::Clean
 */
void PlayState::Clean() {
    delete mScene;
    LOG_DEBUG << "Play state clean";
}

/**
 * PlayState::Pause
 */
void PlayState::Pause() {
    LOG_DEBUG << "Play state paused";
}

/**
 * PlayState::Resume
 */
void PlayState::Resume() {
    LOG_DEBUG << "Play state resumed";
}

/**
 * PlayState::HandleEvents process input events
 * @param game
 */
void PlayState::HandleEvents(Game *game) {
    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSdl_ProcessEvent(&event);
    
        if(ImGui::GetIO().KeysDown[SDLK_ESCAPE]){
            game->ChangeState(MenuState::Instance());
        }
    
        if(ImGui::GetIO().KeysDown[SDL_SCANCODE_PAUSE]){
            game->PushState(PauseState::Instance());
        }
        if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
            switch( event.key.keysym.sym ) {
                case SDLK_BACKQUOTE:
                    showConsole = !showConsole;
                    break;
                case SDLK_F12:
                    showDemo = !showDemo;
                    break;
                default:break;
            }
        }
    }
}

/**
 * PlayState::Update call every frame
 * @param game
 */
void PlayState::Update(Game *game) {
    glLoadIdentity();
    cam->Update();
}

/**
 * PlayState::Render render one frame
 * @param game
 */
void PlayState::Render(Game *game) {
    cam->setCameraState(true);

    if (showConsole) {
        ShowExampleAppConsole(&showConsole);
        cam->setCameraState(false);
    }

    HUD::Cross( mCVar.getVar<int>("s_objects", false) );

    if(showDemo)
        ImGui::ShowTestWindow();

     // Render scene
     mScene->render();

     if( mCVar.getVar<int>("s_objects", false) > 0 ) GLHELPERS::grid(0.0f);

    // if(g_cvars.find("tn_Grid")->second == 1) {
    //     GLHELPERS::grid(0.0f);
    // }
}

/**
 * Draw console
 */
void PlayState::ShowExampleAppConsole(bool *p_open) {
    static ExampleAppConsole console;
    console.Draw("Console", p_open);
}
