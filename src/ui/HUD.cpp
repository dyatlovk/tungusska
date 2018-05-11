#include "HUD.h"

/**
 * Show FPS meter
 */
void HUD::FPS( bool state ) {
    if (state) {
        if (!ImGui::Begin("FPS", nullptr, ImVec2(0, 0),
          0.0f, ImGuiWindowFlags_NoTitleBar |
          ImGuiWindowFlags_NoResize |
          ImGuiWindowFlags_NoMove |
          ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::End();
            return;
        }
        ImGui::SetWindowPos( ImVec2(0, 0) );
        ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
        ImGui::NewLine();
        ImGui::End();
    }
}

/**
 * HUD::showRAM show usage RAM (Mb)
 * @param state TRUE/FALSE
 */
void HUD::RAM( bool state ) {
    if (state) {
        if (!ImGui::Begin("RAM", nullptr, ImVec2(0, 0),
                          0.0f, ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::End();
            return;
        }
        struct rusage r_usage;
        getrusage(RUSAGE_SELF,&r_usage);

        ImGui::Text( "Core RAM: " );
        ImGui::SameLine();
        for (int i = 0; i < 20; ++i)
        {
            ImGui::Text("\u2589");
            ImGui::SameLine(0, 0);
        }
        ImGui::SameLine();
        ImGui::Text( "%ld Mb", r_usage.ru_maxrss / 1000 );
        ImGui::NewLine();
        // ImGui::ProgressBar(usage_pcnt, ImVec2(200.0f, 0.0f), "");
        // ImGui::SameLine();
        // ImGui::Text( "%ld/%0.f", r_usage.ru_maxrss / 1000, float(SDL_GetSystemRAM()) );
        ImGui::End();
    }
}

void HUD::Cross(bool state) {
    if (state) {
        if (!ImGui::Begin("Crosschair", nullptr, ImVec2(0, 0),
                          0.0f, ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::End();
            return;
        }
        ImGui::SetWindowPos(ImVec2((int) ImGui::GetIO().DisplaySize.x/2, (int) ImGui::GetIO().DisplaySize.y/2));
        ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "+");
        ImGui::End();
    }
}

void HUD::Health(bool state, float val = 1.0f) {
    if(state) {
        if (!ImGui::Begin("Health", nullptr, ImVec2(0, 0),
                          0.0f, ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::End();
            return;
        }
        ImGui::SetWindowSize(ImVec2(200, 0));
        ImGui::SetWindowPos(ImVec2(ImVec2(
            (int) ImGui::GetIO().DisplaySize.x - ImGui::GetWindowWidth() + 50,
            (int) ImGui::GetIO().DisplaySize.y - ImGui::GetWindowHeight() - 5
        )));
        ImGui::Text("Health");
        ImGui::ProgressBar(val, ImVec2(0.0f, 0.0f));
        ImGui::End();
    }
}

void HUD::Objects( int count ) {
   if (!ImGui::Begin("Objects", nullptr, ImVec2(0, 0),
                      0.0f, ImGuiWindowFlags_NoTitleBar |
                            ImGuiWindowFlags_NoResize |
                            ImGuiWindowFlags_NoMove |
                            ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::End();
        return;
    }
    ImGui::SetWindowPos( ImVec2(0, 40) );
    ImGui::Text( "Objects: %i", count );
    ImGui::End();
}

void HUD::Debug( bool state )
{
    if(state) {
        if (!ImGui::Begin("Debug", nullptr, ImVec2(0, 0),
                          0.0f, ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize |
                                ImGuiWindowFlags_NoMove |
                                ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::End();
            return;
        }

        ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);

        ImGui::End();
    }
}