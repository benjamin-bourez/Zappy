/*
** EPITECH PROJECT, 2023
** raylib
** File description:
** Camera
*/

#pragma once

#include "Voxel.hpp"

namespace Voxel {
    class Camera {
        public:
            Camera();
            ~Camera();

            /**
             * @brief Set the position of the camera
            */
            void setPosition(float x, float y, float z);
            /**
             * @brief Set the position of the camera
             * @param position The position
            */
            void setPosition(Vector3 &position);
            /**
             * @brief Get the position of the camera
             * @return The position
            */
            Vector3 getPosition() const;
            /**
            * @brief Set the target of the camera
            * @param x The x target
            * @param y The y target
            * @param z The z target
            */
            void setTarget(float x, float y, float z);
            /**
            * @brief Set the target of the camera
            * @param target The target
            */
            void setTarget(Vector3 &target);
            /**
            * @brief Get the target of the camera
            * @return The target
            */
            Vector3 getTarget() const;
            /**
            * @brief Set the up of the camera
            * @param x The x up
            * @param y The y up
            * @param z The z up
            */
            void setUp(float x, float y, float z);
            /**
            * @brief Set the up of the camera
            * @param up The up
            */
            void setUp(Vector3 &up);
            /**
            * @brief Get the up of the camera
            * @return The up
            */
            Vector3 getUp() const;
            /**
            * @brief Set the field of view of the camera
            * @param fovy The field of view
            */
            void setFOVY(float fovy);
            /**
            * @brief Get the field of view of the camera
            * @return The field of view
            */
            float getFOVY() const;
            /**
            * @brief Set the projection of the camera
            * @param projection The projection
            */
            void setProjection(CameraProjection projection);
            /**
            * @brief Get the projection of the camera
            * @return The projection
            */
            CameraProjection getProjection() const;
            /**
            * @brief Get the camera
            * @return The camera
            */
            Camera3D getCamera();
            /**
            * @brief Update the camera
            */
            void updateCamera();
            /**
            * @brief Reset the position of the camera
            */
            void resetPosition();
        private:
            Camera3D _camera;
            int x;
            int y;
    };
};
