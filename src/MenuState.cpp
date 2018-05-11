#include <iostream>
#include <sstream>
#include "SDL2/SDL.h"
#include "game.h"
#include "MenuState.h"
#include "PlayState.h"

MenuState MenuState::m_MenuState;

/**
 * Menu state init
 */
void MenuState::Init() {
    LOG_DEBUG << "Menu state init";
}

/**
 * Menu state clean
 */
void MenuState::Clean() {
    LOG_DEBUG << "Menu state clean";
}

/**
 * Menu state pause
 */
void MenuState::Pause() {
    LOG_DEBUG << "Menu state paused";
}

/**
 * Menu state resume
 */
void MenuState::Resume() {
    LOG_DEBUG << "Menu state resumed";
}

/**
 * Menu state handle events
 * @param game
 */
void MenuState::HandleEvents(Game *game) {
    while (SDL_PollEvent(&event) != 0)
    {
        ImGui_ImplSdl_ProcessEvent(&event);
        std::stringstream ss;
        ss << "X: " << ImGui::GetIO().MousePos.x << " Y: "
           << ImGui::GetIO().MousePos.y;SDL_SetWindowTitle(game->window, ss.str().c_str());

        if( event.type == SDL_KEYDOWN && event.key.repeat == 0 ) {
            switch( event.key.keysym.sym ) {
                case SDLK_BACKQUOTE:
                    showConsole = !showConsole;
                    break;
                default:break;
            }
        }
    }
}

/**
 * Menu state update
 * @param game
 */
void MenuState::Update(Game *game) {
}

/**
 * Menu state render
 * @param game
 */
void MenuState::Render(Game *game) {
    // Main menu
    this->GameMenu(game);
    if (showConsole) {
        ShowExampleAppConsole(&showConsole);
    };
}  

/**
 * MenuState::GameMenu Prepare UI menu listing
 * @param game
 */
void MenuState::GameMenu(Game *game) {
    float _y = (int)ImGui::GetIO().DisplaySize.y;
    
    if (!ImGui::Begin("Game Menu", nullptr, ImVec2(0, 0),
                      0.0f, ImGuiWindowFlags_NoTitleBar        |
                            ImGuiWindowFlags_NoResize          |
                            ImGuiWindowFlags_NoMove            |
                            ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::End();
        return;
    }
    ImGui::SetWindowPos(ImVec2(30, _y * .25f));
    
    //START DEMO
    if (ImGui::Button("Start Demo")) {
        game->ChangeState(PlayState::Instance());
    }
    
    // ABOUT
    if (ImGui::Button("About")) {
    
    }
    
    //EXIT
    if (ImGui::Button("Exit")) {
        game->Quit();
    }
    ImGui::End();
}

/**
 * Draw console
 */
void MenuState::ShowExampleAppConsole(bool *p_open) {
    static ExampleAppConsole console;
    console.Draw("Console", p_open);
}
