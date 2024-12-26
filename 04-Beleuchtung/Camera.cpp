#include "Camera.h"
#include <iostream>  // Für Debug-Ausgaben

using namespace glm;

Camera::Camera(float aspect)
{
    setAspect(aspect);
    resetPosition();
}

void Camera::rotate(float dx, float dy)
{
    m_mouseMove = vec2(dx, dy);
}

void Camera::handleKeyInput(Window::Key key, bool down) {
    m_keys[key] = down;  // Speichert, ob eine Taste gedrückt oder losgelassen wird
}

void Camera::setAspect(float aspect)
{
    float fovY = glm::radians(60.0f);  // Standard 60 Grad
    float nearPlane = 0.1f;
    float farPlane = 100.0f;

    m_projection = glm::perspective(fovY, aspect, nearPlane, farPlane);
}

void Camera::update(float dt) {
    // Maussteuerung für Blickrichtung
    m_theta -= m_mouseMove.x * m_sensitivity;
    m_phi -= m_mouseMove.y * m_sensitivity;
    m_phi = glm::clamp(m_phi, glm::radians(-89.0f), glm::radians(89.0f));

    // Berechnung der Blickrichtung (Polarkoordinaten zu kartesischen Koordinaten)
    glm::vec3 direction;
    direction.x = cos(m_phi) * sin(m_theta);
    direction.y = sin(m_phi);
    direction.z = cos(m_phi) * cos(m_theta);
    m_direction = glm::normalize(direction);

    // Vorwärts-/Rückwärtsbewegung
    glm::vec3 forward = glm::normalize(glm::vec3(m_direction.x, 0.0f, m_direction.z));
    glm::vec3 right = glm::normalize(glm::cross(forward, m_up));
    glm::vec3 movement = glm::vec3(0.0f);

    if (m_keys[Window::Key::W]) {
        movement += forward;
    }
    if (m_keys[Window::Key::S]) {
        movement -= forward;
    }
    if (m_keys[Window::Key::D]) {
        movement += right;
    }
    if (m_keys[Window::Key::A]) {
        movement -= right;
    }

    // Bewegungsgeschwindigkeit und Delta Time
    float speed = glm::clamp(m_movementSpeed * dt, 0.0f, 0.1f);
    m_position += movement * speed;

    // Begrenzung der Höhe (z.B. zwischen 0.5 und 2.0)
    m_position.y = glm::clamp(m_position.y, 0.5f, 2.0f);

    // Aktualisierung der View-Matrix
    m_view = glm::lookAt(
        m_position,
        m_position + m_direction,
        m_up
    );


    // Mausbewegung zurücksetzen
    m_mouseMove = glm::vec2(0.0f);
}
