#include "SDL2/SDL.h"
#include "game.h"
#include "PauseState.h"

PauseState PauseState::m_PauseState;

void PauseState::Init() {
    LOG_DEBUG << "Pause state init";
}

void PauseState::Clean() {
    LOG_DEBUG << "Pause state clean";
}

void PauseState::Pause() {
    LOG_DEBUG << "Pause state paused";
}

void PauseState::Resume() {
    LOG_DEBUG << "Pause state resumed";
}

void PauseState::HandleEvents(Game *game) {
    while (SDL_PollEvent(&event) != 0) {
        ImGui_ImplSdl_ProcessEvent(&event);
        if(ImGui::GetIO().KeysDown[SDL_SCANCODE_PAUSE]){
            game->PopState();
        }
    }
}

void PauseState::Update(Game *game) {

}

void PauseState::Render(Game *game) {
    float _x = (int)ImGui::GetIO().DisplaySize.x;
    float _y = (int)ImGui::GetIO().DisplaySize.y;
    
    if (!ImGui::Begin("Game Pause", nullptr, ImVec2(0, 0),
                      0.5f, ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove |
                            ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::End();
        return;
    }
    ImGui::SetWindowPos(ImVec2(0, 0));
    ImGui::SetWindowSize(ImVec2(_x,_y));
    ImGui::Text("Paused");
    ImGui::End();
}
