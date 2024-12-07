#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

class
Transform : public Component {
public:
    Transform() : position(0.0f, 0.0f),
        rotation(0.0f, 0.0f),
        scale(1.0f, 1.0f),
        Component(ComponentType::TRANSFORM) {}

    virtual
    ~Transform() = default;

    /**
   * @brief Actualiza el componente de malla.
   * @param deltaTime El tiempo transcurrido desde la ultima actualización.
   */
    void
    update(float deltaTime) override {}

    /**
     * @brief Renderiza el componente de malla.
     * @param deviceContext Contexto del dispositivo para operaciones gr�ficas.
     */
    void
    render(Window window) override {}


    void
    setPosition(const Vector2& _position) {
        position = _position;
    }

    void
    setRotation(const Vector2& _rotation) {
        rotation = _rotation;
    }
    void
    setScale(const Vector2& _scale) {
        scale = _scale;
    }

    Vector2
    getPosition() {
        return position;
    }

    Vector2
    getRotation() {
        return rotation;
    }

    float*
    getPosData() {
        return &position.x;
    }

    Vector2
    getScale() {
        return scale;
    }

    float*
    getRotData() {
        return &rotation.x;
    }

    float*
    getSclData() {
        return &scale.x;
    }

    void
    setTransform(const Vector2& pos, const Vector2& rot, const Vector2& scl) {
        position = pos;
        rotation = rot;
        scale = scl;
    }

    void
    Seek(const Vector2& targetPosition,
        float speed,
        float deltaTime,
        float range) {
        Vector2 direction = targetPosition - position;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length > range) {
            direction /= length;  // Normaliza el vector
            position += direction * speed * deltaTime;
        }
    }

    void
    destroy() {};
private:
    Vector2 position; // Posición del objeto
    Vector2 rotation; // Rotación del objeto
    Vector2 scale;	// Escala del objeto
};