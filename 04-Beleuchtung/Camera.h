#pragma once
#include "../framework/Window.h"
#include "../framework/glmmath.h"
#include <unordered_map>

class Camera
{
public:
    // Konstruktor: Initialisiert die Kamera und setzt die Projektionsmatrix
    Camera(float aspect);

    // Getter für View-, Projektionsmatrix und Kameraposition
    const glm::mat4& getView() const { return m_view; }
    const glm::mat4& getProjection() const { return m_projection; }
    const glm::vec3& getPosition() const { return m_position; }

    // Setzt die Kamera auf die Startposition zurück
    void resetPosition() { m_position = m_startingPosition; }

    // Aktualisiert das Seitenverhältnis und setzt die Projektionsmatrix
    void setAspect(float aspect);

    // Dreht die Kamera basierend auf Mausbewegung
    void rotate(float dx, float dy);

    // Verarbeitet Tasteneingaben (WASD) und speichert den Tastenzustand
    void handleKeyInput(Window::Key key, bool down);

    // Aktualisiert die Kameraposition und -blickrichtung pro Frame
    void update(float dt);

    // Test: Rückgabe von festen View-Matrizen für Debugging oder spezielle Perspektiven
    const glm::mat4 getViewFixed1() const {
        return glm::mat4(0.98929f, -0.000377f, -0.145939484f, 0.f,
                         0.f, 0.999997497f, -0.00231421017f, 0.f,
                         0.145939872f, 0.00228943303f, 0.989290893, 0.f,
                         -0.0729699358f, -1.00114226f, -0.492331237f, 1.f);
    }
    const glm::mat4 getViewFixed2() const {
        return glm::mat4(-0.612609327f, -0.0810545161f, 0.786218762f, 0.f,
                         0.f, 0.994727731f, 0.102550566f, 0.f,
                         -0.790385842f, 0.0628234297f, -0.609379530f, 0.f,
                         0.395192921f, -1.02613950f, 0.202139199f, 1.f);
    }
    const glm::mat4 getProjectionFixed() const {
        return glm::mat4(1.16446f, 0.f, 0.f, 0.f,
                         0.f, 2.070157f, 0.f, 0.f,
                         0.f, 0.f, -1.00400794f, -1.f,
                         0.f, 0.f, -0.20004f, 0.f);
    }

private:
    // Position und Orientierung der Kamera
    const glm::vec3 m_startingPosition = glm::vec3(0.f, 1.f, 0.5f);  // Startposition der Kamera
    const glm::vec3 m_up = glm::vec3(0.f, 1.f, 0.f);  // Up-Vektor für Blickrichtung

    glm::mat4 m_projection;  // Projektionsmatrix (Perspektive)
    glm::mat4 m_view;        // View-Matrix (Kamerablickrichtung)

    glm::vec3 m_position;    // Aktuelle Position der Kamera
    glm::vec3 m_direction;   // Blickrichtung der Kamera

    glm::vec2 m_mouseMove = glm::vec2(0.f);  // Mausbewegung (dx, dy)

    // Neue Member-Variablen für Kamerasteuerung
    std::unordered_map<Window::Key, bool> m_keys;  // Speichert den Status der gedrückten Tasten
    float m_theta = glm::radians(90.0f);  // Horizontaler Blickwinkel (theta) in Bogenmaß
    float m_phi = 0.0f;                   // Vertikaler Blickwinkel (phi)
    float m_sensitivity = 0.3f;           // Empfindlichkeit der Mausbewegung
    float m_movementSpeed = 2.0f;         // Geschwindigkeit der Kamera
};
