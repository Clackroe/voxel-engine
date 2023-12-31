#pragma once
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "../Graphics/Screen.h"


enum cameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    DOWN,
    UP
};



const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 68.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class Camera {

public:

    static glm::mat4 getProjection() { return glm::perspective(glm::radians(FOV), (float)Screen::getWidth() / (float)Screen::getHeight(), 0.1f, 500.0f); };

    glm::vec3 cameraPosition, cameraUp, cameraFront, cameraRight, worldUp;
    float cameraYaw, cameraPitch, cameraMovementSpeed, cameraMouseSens, cameraFOV;

    glm::vec3 cameraTarget;
    glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);
    bool firstMouse = true;

    // constructor with defaults
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraMovementSpeed(SPEED), cameraMouseSens(SENSITIVITY), cameraFOV(FOV)
    {
        cameraPosition = position;
        worldUp = up;
        cameraYaw = yaw;
        cameraPitch = pitch;
        updateCameraVectors();
    }
    // constructor with custom scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraMovementSpeed(SPEED), cameraMouseSens(SENSITIVITY), cameraFOV(FOV)
    {
        cameraPosition = glm::vec3(posX, posY, posZ);
        worldUp = glm::vec3(upX, upY, upZ);
        cameraYaw = yaw;
        cameraPitch = pitch;
        updateCameraVectors();
    }


    glm::mat4 getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    }


    void processKeyboardInput(cameraMovement dir) {
        float vel = cameraMovementSpeed * Time::deltaTime;
        if (dir == FORWARD)
            cameraPosition += glm::normalize(glm::cross(worldUp, cameraRight)) * vel;
        if (dir == BACKWARD)
            cameraPosition -= glm::normalize(glm::cross(worldUp, cameraRight)) * vel;
        if (dir == LEFT)
            cameraPosition -= cameraRight * vel;
        if (dir == RIGHT)
            cameraPosition += cameraRight * vel;
        if (dir == UP)
            cameraPosition += worldUp * vel;
        if (dir == DOWN)
            cameraPosition -= worldUp * vel;
    }

    void processMouseInput(GLboolean constrainPitch = true) {

        // std::cout << cameraFront.x << std::endl;

        float xpos = static_cast<float>(Input::xPos);
        float ypos = static_cast<float>(Input::yPos);

        if (firstMouse)
        {
            Input::lastX = xpos;
            Input::lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - Input::lastX;
        float yoffset = Input::lastY - ypos; // reversed since y-coordinates go from bottom to top

        Input::lastX = xpos;
        Input::lastY = ypos;

        // return std::make_pair(xoffset, yoffset);

        xoffset *= cameraMouseSens;
        yoffset *= cameraMouseSens;

        cameraYaw += xoffset;
        cameraPitch += yoffset;

        if (constrainPitch)
        {
            if (cameraPitch > 89.0f)
                cameraPitch = 89.0f;
            if (cameraPitch < -89.0f)
                cameraPitch = -89.0f;
        }
        updateCameraVectors();
    }

    void processScroll(float yoffset)
    {
        cameraFOV -= (float)yoffset;
        if (cameraFOV < 1.0f)
            cameraFOV = 1.0f;
        if (cameraFOV > 45.0f)
            cameraFOV = 45.0f;
    }

private:
    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));
        front.y = sin(glm::radians(cameraPitch));
        front.z = sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch));

        cameraFront = glm::normalize(front);

        cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
        cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
    }
};