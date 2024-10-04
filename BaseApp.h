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
#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"

class
	BaseApp {
public:
	BaseApp() = default; /* Constructor por defecto de la clase BaseApp.*/
	~BaseApp() = default; /* Destructor por defecto de la clase BaseApp.*/

	
	int
		run(); /*Inicia la ejecución de la aplicación.*/


	bool
		initialize(); /* Inicializa los recursos necesarios. */

	
	void
		update(); /*  Actualiza la lógica.*/


	void
		render(); /* Renderiza los objetos en la ventana.*/

	void
		cleanup(); /* Libera los recursos utilizados.*/

	void
		updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle); /* Actualiza la posición del círculo.*/
private:
	sf::Clock clock; /*Reloj para medir el tiempo transcurrido.*/
	sf::Time deltaTime; /* Tiempo transcurrido*/

	Window* m_window; /* Puntero a la ventana de la aplicación.*/
	EngineUtilities::TSharedPointer<Actor> Triangle; /* Puntero compartido al actor triangular.*/
	EngineUtilities::TSharedPointer<Actor> Circle; /*Puntero compartido al actor circular.*/


	int currentWaypoint = 0; /*Índice del waypoint actual.*/

	/* Vector que contiene las posiciones de los waypoints.*/
	std::vector<sf::Vector2f> waypoints = {
		{100.0f, 100.0f},
		{400.0f, 100.0f},
		{400.0f, 400.0f},
		{100.0f, 400.0f}
	};
};