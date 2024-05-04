#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera {
    public:
        glm::vec3 _position;
        glm::vec3 _front;
        glm::vec3 _up;
        glm::vec3 _right;
        glm::vec3 _worldUp;

        float _yaw;
        float _pitch;

        float _movementSpeed;
        float _mouseSensitivity;
        float _zoom;

        // constructor with vectors
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM) {
            _position = position;
            _worldUp = up;
            _yaw = yaw;
            _pitch = pitch;
            updateCameraVectors();
        }

        // constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : _front(glm::vec3(0.0f, 0.0f, -1.0f)), _movementSpeed(SPEED), _mouseSensitivity(SENSITIVITY), _zoom(ZOOM) {
            _position = glm::vec3(posX, posY, posZ);
            _worldUp = glm::vec3(upX, upY, upZ);
            _yaw = yaw;
            _pitch = pitch;
            updateCameraVectors();
        }

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix() {
            return glm::lookAt(_position, _position + _front, _up);
        }

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(Camera_Movement direction, float deltaTime) {
            float velocity = _movementSpeed * deltaTime;
            if(direction == FORWARD)
                _position += _front * velocity;
            if(direction == BACKWARD)
                _position -= _front * velocity;
            if(direction == LEFT)
                _position -= _right * velocity;
            if(direction == RIGHT)
                _position += _right * velocity;
            if(direction == UP)
                _position += _up * velocity;
            if(direction == DOWN)
                _position -= _up * velocity;
        }

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true) {
            xoffset *= _mouseSensitivity;
            yoffset *= _mouseSensitivity;

            _yaw   += xoffset;
            _pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrainPitch) {
                if (_pitch > 89.0f)
                    _pitch = 89.0f;
                if (_pitch < -89.0f)
                    _pitch = -89.0f;
            }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset) {
        _zoom -= (float)yoffset;
        if (_zoom < 1.0f)
            _zoom = 1.0f;
        if (_zoom > 45.0f)
            _zoom = 45.0f;
    }

    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors() {
            // calculate the new Front vector
            glm::vec3 front;
            front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
            front.y = sin(glm::radians(_pitch));
            front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
            _front = glm::normalize(front);
            // also re-calculate the Right and Up vector
            _right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
            _up    = glm::normalize(glm::cross(_right, _front));
    }
};

#endif