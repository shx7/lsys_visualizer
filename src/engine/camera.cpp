#include "camera.hpp"

Camera Camera::ptr;

Camera::Camera()
    : cameraPosition(glm::vec3(0, 0, -2))
    , cameraUp(glm::vec3(0, 1, 0))
    , cameraFront(glm::vec3(0, 0, 1))
    , pitchAngle(0)
    , yawAngle(0)
    , mouseX(0)
    , mouseY(0)
    , isMouseInitialized(false)
{
}

Camera *
Camera::instance() 
{
    return &ptr;
}

void
Camera::setPosition(glm::vec3 const &pos)
{
    cameraPosition = pos;
}

void
Camera::setPitchAngle(GLfloat angle)
{
    pitchAngle = angle;
}

void
Camera::setYawAngle(GLfloat angle)
{
    yawAngle = angle;
}

glm::mat4
Camera::getLookAtMatrix()
{
    return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void
Camera::processMouseMovementInput(double xpos, double ypos)
{
    double deltaYawAngle = 0.0;
    double deltaPitchAngle = 0.0;
    if (isMouseInitialized)
    {
        deltaYawAngle = (xpos - mouseX) * mouseSensivity;
        deltaPitchAngle = (ypos - mouseY) * mouseSensivity;
    }
    else
    {
        isMouseInitialized = true;
    }
    mouseX = xpos;
    mouseY = ypos;
    yawAngle += deltaYawAngle;
    pitchAngle += deltaPitchAngle;

    glm::vec3 front;
    front.x = cos(glm::radians(pitchAngle)) * cos(glm::radians(yawAngle));
    front.y = sin(glm::radians(pitchAngle));
    front.z = cos(glm::radians(pitchAngle)) * sin(glm::radians(yawAngle));
    cameraFront = glm::normalize(front);
}

void
Camera::processMouseScrollInput(double yoffset)
{
    cameraPosition -= cameraFront * (GLfloat)(cameraScrollSpeed * yoffset);
}

void
Camera::processKeyboardInput(int key, int)
{
    switch (key)
    {
        case GLFW_KEY_W:
            cameraPosition += cameraFront * cameraSpeed;
            break;

        case GLFW_KEY_S:
            cameraPosition -= cameraFront * cameraSpeed;
            break;

        case GLFW_KEY_A:
            cameraPosition +=
                glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;

        case GLFW_KEY_D:
            cameraPosition -=
                glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
    }
}
