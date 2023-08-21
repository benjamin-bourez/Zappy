/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Camera
*/

#include "Camera.hpp"

namespace Voxel {
    void Camera::resetPosition()
    {
        setPosition(0, std::max(x, y), std::max(x, y));
    }

    void Camera::updateCamera()
    {
        UpdateCamera(&_camera, CAMERA_THIRD_PERSON);
    }

    void Camera::setPosition(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        _camera.position = (Vector3){ x, y, z };
    }

    void Camera::setPosition(Vector3 &position)
    {
        this->x = position.x;
        this->y = position.y;
        _camera.position = position;
    }

    Vector3 Camera::getPosition() const
    {
        return _camera.position;
    }

    void Camera::setTarget(float x, float y, float z)
    {
        _camera.target = (Vector3){ x, y, z };
    }

    void Camera::setTarget(Vector3 &target)
    {
        _camera.target = target;
    }

    Vector3 Camera::getTarget() const
    {
        return _camera.target;
    }

    void Camera::setUp(float x, float y, float z)
    {
        _camera.up = (Vector3){ x, y, z };
    }

    void Camera::setUp(Vector3 &up)
    {
        _camera.up = up;
    }

    Vector3 Camera::getUp() const
    {
        return _camera.up;
    }

    void Camera::setFOVY(float fovy)
    {
        _camera.fovy = fovy;
    }

    float Camera::getFOVY() const
    {
        return _camera.fovy;
    }

    void Camera::setProjection(CameraProjection projection)
    {
        _camera.projection = projection;
    }

    CameraProjection Camera::getProjection() const
    {
        return (CameraProjection) _camera.projection;
    }

    Camera3D Camera::getCamera()
    {
        return _camera;
    }

    Camera::Camera()
    {
        x = 0;
        y = 0;
    }

    Camera::~Camera()
    {
    }
}