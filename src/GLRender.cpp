#include "GLRender.h"

GLRender::GLRender(){
	this.setupRenderer();
}
GLRender::~GLRender() = default;

void GLRender::setupRenderer(const char *title, int width, int height, int bpp, bool fullscreen) {
	// Инициализация SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        LOG_FATAL << "Unable to init SDL";
        exit(1);
    }
    LOG_DEBUG << "Init SDL";

     // Включаем двойной буфер, настраиваем цвета
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    // Создаем окно
    window = SDL_CreateWindow(title,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | flags);
    LOG_DEBUG << "Create window";

    // setup GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
        LOG_FATAL << "GLEW not initialized correctly";

    gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC);

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
                   (float) width / (float) height,
                   0.1f,
                   100.0f);
    // переходим в трехмерный режим
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    LOG_DEBUG << "OpenGL init";

    m_bRunning = true;
}

void destroyRender() {
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