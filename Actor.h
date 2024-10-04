#pragma once
#include "Prerequisites.h"
#include "Entity.h"
#include "ShapeFactory.h"

class
    Actor : Entity {
public:
    /*
     * Constructor por defecto del Actor.
     */
    Actor() = default;
    /*
     * Constructor que inicializa el Actor con un nombre dado.
     */

    Actor(std::string actorName);
    /*
    * Destructor virtual del Actor.
    */

    virtual
        ~Actor() = default;

    /*
     * Actualiza el estado del actor.
     * Se debe llamar con el tiempo transcurrido desde la última actualización.
     */
    void
        update(float deltaTime) override;

    /*
     * Renderiza el actor en la ventana.
     */
    void
        render(Window& window) override;

    /*
      * Destruye el actor y libera los recursos que esten juntos.
      */
    void
        destroy();
    /*
       * Obtiene un componente específico del actor.
       * Retorna un puntero compartido al componente, o un puntero vacío si no se encuentra.
       */
    template <typename T>
    EngineUtilities::TSharedPointer<T>
        getComponent();
private:
    std::string m_name = "Actor"; /* Nombre del actor.*/
};

/*
 * Busca y devuelve un componente específico de un actor.
 */
template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
    for (auto& component : components) {
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent; /* Retorna el componente si se encuentra*/
        }
    }
    /* Devuelve un puntero compartido vacío del tipo T*/
    return EngineUtilities::TSharedPointer<T>();
}