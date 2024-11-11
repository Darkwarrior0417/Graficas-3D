#pragma once
#include "Prerequisites.h"
#include "ECS\Component.h"
#include "Window.h"

class
ShapeFactory : public Component {
public:
		/* Constructor por defecto*/
		ShapeFactory() = default;

		/*Destructor por defecto */
		virtual
		~ShapeFactory() = default;

		/*Constructor que inicializa con un tipo de forma vacío */
		ShapeFactory(ShapeType shapeType) :
		m_shape(nullptr), m_shapeType(ShapeType::EMPTY), Component(ComponentType::SHAPE) {}

		/* Crea una forma basada en el tipo dado.*/
		sf::Shape*
		createShape(ShapeType shapeType);

	/* Función vacía de actualización*/
	void
	update(float deltaTime) override {}

	/* Función vacía de renderizado*/
	void
	render(Window window) override {}

	/*  Establece la posición de la forma usando coordenadas X e Y.*/
	void
	setPosition(float x, float y);

	/* Establece la posición de la forma usando un vector 2D.*/
	void
	setPosition(const sf::Vector2f& position);

	/* Establece el color de relleno de la forma.*/
	void
	setFillColor(const sf::Color& color);

	void
	setRotation(float angle);

	void
	setScale(const sf::Vector2f& scl);

	/* Devuelve la forma almacenada.*/
	sf::Shape*
	getShape() {
		return m_shape;
	}
private:
	sf::Shape* m_shape; /*Puntero a la forma creada */
	ShapeType m_shapeType; /*Tipo de forma*/
};