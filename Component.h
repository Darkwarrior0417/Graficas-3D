#pragma once
class Window; /*Declaraci�n de la clase Window.*/

enum
	ComponentType { 
	NONE = 0,	/* Componente no definido.*/
	TRANSFORM = 1, /* Componente de transformaci�n*/
	SPRITE = 2, /* Componente de sprite*/
	RENDERER = 3, /* Componente de renderizado.*/
	PHYSICS = 4, /* Componente de f�sica.*/
	AUDIOSOURCE = 5, /* Componente de fuente de audio.*/
	SHAPE = 6, /*Componente de figura*/
};


class
	Component {
public:
	
	Component() = default; /* Constructor por defecto.*/

	
	Component(const ComponentType type) : m_type(type) {} /*  Constructor que inicializa el tipo del componente.*/

	
	virtual
		~Component() = default; /*  Destructor virtual.*/

	
	virtual void
		update(float deltaTime) = 0; /* M�todo virtual para actualizar el componente*/

	
	virtual void
		render(Window window) = 0; /* M�todo virtual para renderizar el componente*/

	ComponentType
		getType() const { return m_type; } /* Devuelve el tipo del componente.*/

protected:
	ComponentType m_type; /* Almacena el tipo de componente.*/
};