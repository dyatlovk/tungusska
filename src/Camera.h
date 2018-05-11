#ifndef TUNGUSSKA_CAMERA_H
#define TUNGUSSKA_CAMERA_H

#include "Log.h"
#include <cstdio>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <GL/glu.h>
#include "libs/imgui/imgui.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    Camera(SDL_Window *window, float wWidth, float wHeight);
    
    ~Camera();
    
    // init camera
    void Init();
    
    // update positions
    void Update();
    
    bool getCameraState();
    
    bool setCameraState(bool newState);

private:
    // Initial position : on +Z
    glm::vec3 position = glm::vec3(0, 0, 5);
    glm::vec3 old_position = glm::vec3(0, 0, 0);
    
    // Initial horizontal angle : toward -Z
    float horizontalAngle = 0;
    float old_horizontalAngle = 0;
    
    // Initial vertical angle : none
    float verticalAngle = 0;
    float old_verticalAngle = 0;
    
    glm::vec3 direction = glm::vec3(0, 0, 0);
    glm::vec3 old_direction = glm::vec3(0,0,0);
    glm::vec3 up = glm::vec3(0,0,0);
    glm::vec3 old_up = glm::vec3(0,0,0);
    
    // Initial Field of View
    float initialFoV = 0;
    
    // units / second
    float speed = 0;
    float mouseSpeed = 0;
    float windowWidth = 0;
    float windowHeight = 0;
    
    SDL_Window *mWindow;
    
    // if true camera will be move
    bool cameraAction = true;
    
    void Position();
};

#endif