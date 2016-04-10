#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GL/gl.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <GLFW/glfw3.h>

class Camera
{
        static bool isInstantiated;
        static Camera* ptr;

        glm::vec3 cameraPosition;
        glm::vec3 cameraUp;
        glm::vec3 cameraFront;

        GLfloat pitchAngle = 0;
        GLfloat yawAngle = 0;

        double mouseX, mouseY;
        const double mouseSensivity = 0.05;

        const glm::vec3 cameraSpeed = glm::vec3(0.1);

    public:
        static Camera *instance();

        void setPosition(glm::vec3 const &pos);

        void setPitchAngle(GLfloat pitch_angle);

        void setYawAngle(GLfloat yaw_angle);

        glm::mat4 getLookAtMatrix();

        void updateMouse(double xpos, double ypos);

        void updateKeyboard(int key, int action);

    private:
        Camera();
};

#endif
