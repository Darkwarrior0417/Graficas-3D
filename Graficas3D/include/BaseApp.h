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

	// Funci�n encargada de ejecutar la aplicaci�n en main
	int
	run();

	// Funci�n de inicializaci�n
	bool
	initialize();

	// Funci�n que se actualiza por frame
	void
	update();

	// Funci�n de renderizado
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