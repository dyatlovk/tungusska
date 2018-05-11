#include "game.h"
#include "GameState.h"

// cvars global vector
std::map< std::string, std::vector< std::string > > cvars;

/**
 * Game constructor
 */
Game::Game() : window(), glcontext(), m_bFullscreen(), m_bRunning() {}

/**
 * Game destructor
 */
Game::~Game() = default;

/**
 * let the state handle events
 */
void Game::HandleEvents() {
    states.back()->HandleEvents(this);
}

/**
 * let the state update the game
 */
void Game::Update() {
    ImGui_ImplSdl_NewFrame(window);
    states.back()->Update(this);
}

void Game::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    states.back()->Render(this);
    
    // FPS Counter
    // HUD::showFPS( mCVar.getVar<int>("tn_fps", false) );

    // RAM
    // HUD::showRAM( mCVar.getVar<int>("tn_ram", false) );

    if( mCVar.getVar<int>("s_objects", false) > 0 ) {
        // HUD::objects( mCVar.getVar<int>("s_objects", false) );
    } else {
        // HUD::objects( 0 );
    }

    ImGui::Render();
}

void Game::Clean() {
    while (!states.empty()) {
        states.back()->Clean();
        states.pop_back();
    }
    LOG_DEBUG << "cleaning states";
    
    // shutdown Imgui
    ImGui_ImplSdl_Shutdown();
    LOG_DEBUG << "shutdown UI";
    
    // shutdown SDL
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( window );
    SDL_GL_DeleteContext(glcontext);
    window = nullptr;
    gRenderer = nullptr;
    SDL_Quit();
    LOG_DEBUG << "shutdown SDL";
    LOG_DEBUG << "quit";
}

/**
 * Game Init
 */
void Game::Init() {

    lua.open_libraries( sol::lib::base );
    lua.script_file("../data/scripts/game.lua");
    lua["Game"]();

    // register cvars
    mCVar.registerVar<int>("tn_cross", 1, 1, "Show cross at the center of the screen");
    mCVar.registerVar<int>("tn_ram", 1, 1, "Show available RAM");
    mCVar.registerVar<int>("r_wireframe", 0, 0, "Render wireframe grid");
    mCVar.registerVar<int>("tn_fps", 1, 1, "Show currrent FPS");
    mCVar.registerVar<int>("tn_demoUI", 0, 0, "Toggle demo UI window");
    mCVar.registerVar<int>("tn_grid", 1, 1, "Toggle ground grid helper");

     // user config
    boost::property_tree::ini_parser::read_ini("config.cfg", treeCfg);

    // parse settings
    w_Title      = "Tungusska";
    w_Width      = treeCfg.get<int>("Render.width");
    w_Height     = treeCfg.get<int>("Render.height");
    w_Bpp        = treeCfg.get<int>("Render.bpp");
    w_Fullscreen = treeCfg.get<bool>("Render.fullscreen");

    int flags = 0;
    if ( w_Fullscreen ) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    LOG_INFO << "Start Tungusska initialisation...";

    // Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_FATAL << "Unable to init SDL";
        exit(1);
    }
    LOG_DEBUG << "Init SDL [ok]";
    
    // Включаем двойной буфер, настраиваем цвета
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    
    // Создаем окно
    window = SDL_CreateWindow(w_Title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, w_Width, w_Height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | flags);
    m_bFullscreen = w_Fullscreen;
    LOG_INFO << "Window: " << w_Width << "x" << w_Height << "@" << w_Bpp;
    
    // OpenGl context
    glcontext = SDL_GL_CreateContext(window);

    SDL_Surface* icon = IMG_Load("./ico16.png");
    SDL_SetWindowIcon(window, icon);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        LOG_FATAL << "GLEW not initialized correctly";
    LOG_INFO << "Init GLEW [ok]";

    // если не получилось создать окно, то выходим
    if (window == nullptr) {
        LOG_FATAL << "Unable to create window";
        exit(1);
    }
    
    gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC);

    // Hard & sowtware about
    LOG_INFO << "---------------------------------------";
    LOG_INFO << "OpenGl info:";
    LOG_INFO << "Vendor: \t" << glGetString(GL_VENDOR);
    LOG_INFO << "Renderer: \t" << glGetString(GL_RENDERER);
    LOG_INFO << "OpenGL: \t" << glGetString(GL_VERSION);
    LOG_INFO << "Shaders: \t" << glGetString(GL_SHADING_LANGUAGE_VERSION);
    LOG_INFO << "---------------------------------------";
    
    // Инициализация OpenGL
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_COLOR_MATERIAL);
    // включаем тест глубины
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,
                   (float) w_Width / (float) w_Height,
                   0.1f,
                   100.0f);
    // переходим в трехмерный режим
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    LOG_INFO << "OpenGL init [ok]";
    
    m_bRunning = true;
    
    // Imgui Init
    ImGui_ImplSdl_Init(window);
    HUD::SetupImGuiStyle(true, 1);
    LOG_INFO << "Init system complete";

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("../data/Fonts/DejaVuSans-Bold.ttf", 15.0f);
}

/**
 * ChangeState() takes a pointer to a GameState as
 * a parameter and then pushes that state onto the vector of pointers
 * to GameStates, before that it uses the clean function to remove
 * the old state from the stack.
 * @param state
 */
void Game::ChangeState(GameState *state) {
    // cleanup the current state
    if (!states.empty()) {
        states.back()->Clean();
        states.pop_back();
    }
    // store and init the new state
    states.push_back(state);
    states.back()->Init();
}

/**
 * Whereas ChangeState() pushes a state onto the stack and removes the
 * previous state, PushState() pauses the previous state before pushing
 * a new state onto the stack, this state can then be removed and the
 * previous state resumed. Extremely useful for pausing.
 * @param state
 */
void Game::PushState(GameState *state) {
    // pause current state
    if (!states.empty()) {
        states.back()->Pause();
    }
    
    // store and init the new state
    states.push_back(state);
    states.back()->Init();
}

/**
 * Remove and resume previous state.
 */
void Game::PopState() {
    // cleanup the current state
    if (!states.empty()) {
        states.back()->Clean();
        states.pop_back();
    }
    
    // resume previous state
    if (!states.empty()) {
        states.back()->Resume();
    }
}