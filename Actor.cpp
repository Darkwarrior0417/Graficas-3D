#include "Actor.h"

Actor::Actor(std::string actorName) {
    /* Aquí si Inicializa el nombre del actor */
    m_name = actorName;

    /* Se configura un componente de tipo ShapeFactory para el actor */
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);
}

void
Actor::update(float deltaTime)
{
  
}

void 
Actor::render(Window& window)
{
    /* Recorre todos los componentes del actor */
    /* Se dibuja los componentes de tipo ShapeFactory en la window */
    for (unsigned int i = 0; i < components.size(); i++) {
        window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
    }
}

void 
Actor::destroy()
{
    /*Se destruille los componentes del actor */
  
}
