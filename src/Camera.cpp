#include "game.h"
#include "Camera.h"

#include <cmath>

Camera::Camera(SDL_Window *window, float wWidth, float wHeight) {
    mWindow = window;
    windowWidth = wWidth;
    windowHeight = wHeight;
    Camera::Init();
};

Camera::~Camera() = default;

void Camera::Init() {
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 45.0f;
    speed = 0.01f;
    mouseSpeed = 0.001f;
    LOG_DEBUG << "Camera vieport: " << windowWidth << "x" << windowHeight;
}

void Camera::Update() {
    static double lastTime = SDL_GetTicks();
    
    double currentTime = SDL_GetTicks();
    auto deltaTime = float(currentTime - lastTime);
    
    if(cameraAction) {
        SDL_WarpMouseInWindow(mWindow,int(windowWidth/2), int(windowHeight/2));
        SDL_ShowCursor(0);
        
        // Compute new orientation
        horizontalAngle += mouseSpeed * float(windowWidth / 2 - ImGui::GetIO().MousePos.x);
        verticalAngle += mouseSpeed * float(windowHeight / 2 - ImGui::GetIO().MousePos.y);
    
        // Direction : Spherical coordinates to Cartesian coordinates conversion
        glm::vec3 direction(
            std::cos(verticalAngle) * sin(horizontalAngle),
            std::sin(verticalAngle),
            std::cos(verticalAngle) * cos(horizontalAngle)
        );
    
        // Right vector
        glm::vec3 right = glm::vec3(
            std::sin(horizontalAngle - 3.14f / 2.0f),
            0,
            std::cos(horizontalAngle - 3.14f / 2.0f)
        );
    
        // Up vector
        glm::vec3 up = glm::cross(right, direction);
        
        if(ImGui::GetIO().KeysDown[SDLK_w]){
            position += direction * deltaTime * speed;
        }
        if(ImGui::GetIO().KeysDown[SDLK_s]){
            position -= direction * deltaTime * speed;
        }
        if(ImGui::GetIO().KeysDown[SDLK_a]){
            position -= right * deltaTime * speed;
        }
        if(ImGui::GetIO().KeysDown[SDLK_d]){
            position += right * deltaTime * speed;
        }
    
        // limit vertical angle
        if (verticalAngle > .89f)
            verticalAngle = .89f;
        if (verticalAngle < -.89f)
            verticalAngle = -.89f;
        
        gluLookAt(
            position[0], position[1], position[2],
            position[0]+ direction[0], position[1]+ direction[1], position[2]+ direction[2],
            up[0], up[1], up[2]
        );
        // last position values
        old_position = position;
        old_horizontalAngle = horizontalAngle;
        old_verticalAngle = verticalAngle;
        old_direction = direction;
        old_up = up;
    } else {
        gluLookAt(
            old_position[0], old_position[1], old_position[2],
            old_position[0]+ old_direction[0], old_position[1]+ old_direction[1], old_position[2]+ old_direction[2],
            old_up[0], old_up[1], old_up[2]
        );
    }
    
    lastTime = currentTime;
}

void Camera::Position() {}

bool Camera::getCameraState() {
    return cameraAction;
}

bool Camera::setCameraState(bool newState) {
    cameraAction = newState;
    return cameraAction;
}
