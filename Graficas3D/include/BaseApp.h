#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "ShapeFactory.h"
#include "ECS\Actor.h"
#include "GUI.h"
#include "Services/NotificationService.h"
#include "Services/ResourceManager.h"

class
BaseApp {
public:

	BaseApp() = default;
	~BaseApp();

	// Función encargada de ejecutar la aplicación en main
	int
	run();

	// Función de inicialización
	bool
	initialize();

	// Función que se actualiza por frame
	void
	update();

	// Función de renderizado
	void
	render();

	void
	cleanup();

	void
	updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
	sf::Clock clock;
	sf::Time deltaTime;

	Window* m_window;
	EngineUtilities::TSharedPointer<Actor> Triangle;
	EngineUtilities::TSharedPointer<Actor> Circle;
	EngineUtilities::TSharedPointer<Actor> Track;

	std::vector< EngineUtilities::TSharedPointer<Actor>> m_actors;


	//Array para la actividad de los puntos
	Vector2 points[9];
	int m_currentPoint = 0;
	int m_currentActor = 0;


	sf::Texture Waluigi;
	sf::Texture texture;

	GUI m_GUI;
};