#ifndef GAME_H
#define GAME_H

// std
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include <lua5.1/lua.hpp>
#include "external/sol2/single/sol/sol.hpp"

#include "Log.h"
#include "CVar.h"
#include "utils/Watcher.h"
#include "utils/sys.h"

// Boost
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "libs/imgui/imgui.h"
#include "libs/imgui/imgui_impl_sdl.h"
#include "ui/HUD.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Console.h"
#include "Camera.h"
#include "utils/gl_helpers.h"
#include "Scene.h"

/**
 * Game holds all game-related state and functionality.
 * Combines all game-related data into a single class for asy access
 * to each of the components and manageability.
 */
class GameState;

class Game {
public:
    Game();
    
    ~Game();
    
    // Initialize game state (load all shaders/textures/levels)
    void Init();
    
    SDL_Window *window;
    
    SDL_Renderer *gRenderer = NULL;
    
    SDL_GLContext glcontext;
    
    void ChangeState(GameState *state);
    
    void PushState(GameState *state);
    
    void PopState();
    
    void HandleEvents();
    
    void Update();
    
    void Render();
    
    void Clean();
    
    bool Running() { return m_bRunning; };
    
    void Quit() { m_bRunning = false; }

private:
    bool m_bFullscreen;
    bool m_bRunning;
    std::vector<GameState *> states;
    boost::property_tree::ptree treeCfg;

    // window default settings
    const char* w_Title = "Tungusska";
    int w_Width         = 800;
    int w_Height        = 600;
    int w_Bpp           = 32;
    bool w_Fullscreen   = false;
    CVar mCVar;
    sol::state lua;
};

#endif