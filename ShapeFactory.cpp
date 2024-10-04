#include "ShapeFactory.h"

sf::Shape*
ShapeFactory::createShape(ShapeType shapeType) {
	/*
	 * Crea una forma (círculo, rectángulo o triángulo) basado en el tipo especificado.
	 */
	m_shapeType = shapeType; /* Se almacena el tipo de figura*/
	switch (shapeType) {
	case EMPTY: {
		return nullptr; /* No se crea ninguna figura*/
	}
	case CIRCLE: { 
		/* Se crea un circulo*/
		sf::CircleShape* circle = new sf::CircleShape(10.0f); /* Su radio*/
		circle->setFillColor(sf::Color::White); /* su color*/
		m_shape = circle; /* Almacena la figura creada*/
		return circle; /* Devuelve el circulo creado*/
	}
	case RECTANGLE: {
		/* Se crea un rectangulo*/
		sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2(100.0f, 50.0f)); /* Se establecen las medidas 100 x 50  */
		rectangle->setFillColor(sf::Color::White); /* Su Color*/
		m_shape = rectangle; /* Almacena la figura creada*/
		return rectangle; /* Devuelve el rectangulo creado*/
	}
	case TRIANGLE: {
		/* Se crea un triangulo */
		sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3); /* Su radio*/
		triangle->setFillColor(sf::Color::White); /* Su color*/
		m_shape = triangle; /* Almacena la figura creada*/
		return triangle; /* Devuelve el triangulo creado*/
	}
	default:
		return nullptr; /*  Tipo no reconocido, devuelve nullptr*/
	}
}

void
ShapeFactory::setPosition(float x, float y) {
	/* Se establecen las coordenadas de la figura en X, Y */
	m_shape->setPosition(x, y); /* Se establece la posicion de la figura*/
}

void
ShapeFactory::setPosition(const sf::Vector2f& position) {
	/* Establece la posicion de la figura en un Vector 2D*/
	m_shape->setPosition(position); /* Se establece la posicion de la figura*/ 
}

void
ShapeFactory::setFillColor(const sf::Color& color) {
	/*
	 * Establece el color de relleno de la forma.
	 */
	m_shape->setFillColor(color); /* Se establece el color de relleno*/
}

void
ShapeFactory::Seek(const sf::Vector2f& targetPosition,
	float speed,
	float deltaTime,
	float range) {
	/*
	* Mueve la forma hacia la posición objetivo a una velocidad determinada.
	*/
	
	sf::Vector2f shapePosition = m_shape->getPosition(); /* Consigue la posicion actual de la figura*/

	
	sf::Vector2f direction = targetPosition - shapePosition; /*  Calcula la dirección hacia la posición objetivo*/


	float lenght = std::sqrt(direction.x * direction.x + direction.y * direction.y); /* Calcula la longitud del vector de dirección*/

	/* Si la distancia es mayor que el rango, mueve la figura */
	if (lenght > range) {
		direction /= lenght; /* Se normaliza la direccion*/
		m_shape->move(direction * speed * deltaTime); /* Mueve la figura en la dirección normalizada*/
	}
}