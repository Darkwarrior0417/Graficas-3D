/*
 * MIT License
 *
 * Copyright (c) 2024 Roberto Charreton
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * In addition, any project or software that uses this library or class must include
 * the following acknowledgment in the credits:
 *
 * "This project uses software developed by Roberto Charreton and Attribute Overload."
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/
#include "BaseApp.h"

int 
BaseApp::run() {
	/*
	* Inicializa la aplicación y entra en el bucle principal
	* que maneja eventos, actualiza y renderiza.
	*/
	if (!initialize()) {
		ERROR("BaseApp", "run", "Initializes result on a false statemente, check method validations");
	}
	while (m_window->isOpen()) {
		m_window->handleEvents();  /* Manejea los eventos de la ventana */
		deltaTime = clock.restart(); /* Se reinicia el reloj*/
		update();  /* Actualiza la aplicacion*/
		render(); /* Renderiza*/
	}

	cleanup(); /* Limpia los recursos*/
	return 0;
}

bool 
BaseApp::initialize() {

	/*
   * Inicializa la aplicación y entra en el bucle principal
   */

	m_window = new Window(800, 600, "Galvan Engine");
	if (!m_window) {
		ERROR("BaseApp", "initialize", "Error on window creation, var is null");
		return false;
	}

	/* Se crea un actor para el circulo*/
	Circle = EngineUtilities::MakeShared<Actor>("Circle");
	if (!Circle.isNull()) {
		Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
		Circle->getComponent<ShapeFactory>()->setPosition(200.0f, 200.0f);
		Circle->getComponent<ShapeFactory>()->setFillColor(sf::Color::Blue);
	}

	/* Se crea un actor para el triangulo*/
	Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
	if (!Triangle.isNull()) {
		Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
	}

	return true; /* Se devuelve a true si la inicializacion fue buena*/
}

void 
BaseApp::update() {
	/*
	* Actualiza la lógica del juego obteniendo la posición
	* del ratón y actualizando el movimiento del círculo.
	*/

	sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
	sf::Vector2f mousePosF(static_cast<float>(mousePosition.x),
		static_cast<float>(mousePosition.y));

	if (!Circle.isNull()) {
		
		updateMovement(deltaTime.asSeconds(), Circle); /* Se actualiza el movimiento del circulo*/
	}

}

void 
BaseApp::render() {
	/*  
     * Actualiza la lógica del juego obteniendo la posición 
     * del ratón y actualizando el movimiento del círculo.
     */ 
	m_window->clear(); /* Limpia la ventana*/
	Circle->render(*m_window); /* Se renderiza el circulo*/
	Triangle->render(*m_window); /* Se renderiza el tringulo */
	m_window->display();  /* Muestra los cambios en la ventana*/
}

void
BaseApp::cleanup() {
	/*
	* Libera recursos al cerrar la aplicación
	* y destruye la ventana.
	*/
	m_window->destroy(); /* Destruye la ventana*/
	delete m_window; /* Libera la memoria que sew ocupo en la ventana*/
}

void
BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
	/*
	 * Actualiza la posición del círculo en base a su
	 * destino actual y el tiempo transcurrido.
	 */

	if (!circle || circle.isNull()) return; /* Se verifica si el circulo es nulo*/

	
	sf::Vector2f targetPos = waypoints[currentWaypoint]; /* La posicion del WayPoint*/

	
	circle->getComponent<ShapeFactory>()->Seek(targetPos, 200.0f, deltaTime, 10.0f); /* Se llama a la funcion Seek*/

	
	sf::Vector2f currentPos = circle->getComponent<ShapeFactory>()->getShape()->getPosition(); /* Posicion actual del circulo*/


	float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2)); /* Se calcula la distancia del circulo */

	/* Verifica si todo has llegado al WayPoint*/
	if (distanceToTarget < 10.0f) {
	
		currentWaypoint = (currentWaypoint + 1) % waypoints.size(); /* Se cicla a traves de los WayPoint*/
	}
}