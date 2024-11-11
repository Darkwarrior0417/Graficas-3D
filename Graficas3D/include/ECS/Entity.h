#pragma once
#include "Prerequisites.h"
#include "Component.h"

class Window;

class
Entity {
public:
    /* Destructor virtual para permitir la destrucci�n correcta de clases derivadas.*/
  
        virtual
        ~Entity() = default;

    /*M�todo virtual puro para actualizar la entidad. */
    virtual void
    update(float deltaTime) = 0;

    /* M�todo virtual puro para renderizar la entidad. (Debe ser implementado por clases derivadas.) */
    virtual void
    render(Window& window) = 0;

    /*M�todo para agregar un componente a la entidad.*/
    template <typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component) {
        /*Asegura que el tipo T sea derivado de la clase base Component.*/
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        /* Convierte el componente a tipo Component y lo a�ade al vector.*/
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }



    template <typename T>
    EngineUtilities::TSharedPointer<T>
    getComponent() {
        for (auto& component : components) {
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent) {
                return specificComponent;
            }
        }
        /*Retorna un TSharedPointer vac�o si no se encuentra el componente.*/
        return EngineUtilities::TSharedPointer<T>();
    }

    protected:
        bool isActive; /* Indica si la entidad est� activa o no.*/

        int id; /* Identificador �nico.*/

        std::vector<EngineUtilities::TSharedPointer<Component>> components; /*Vector de componentes.*/
};