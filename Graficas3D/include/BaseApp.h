#pragma once
#include <SFML/Graphics.hpp>
#include "Prerequisites.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "ECS\Actor.h"
#include "GUI.h"
#include "NotificationService.h"

class
BaseApp {
public:
	BaseApp() = default;
	~BaseApp();

	// Funcion encargada de ejecutar la aplicacion en main
	int
	run();

	// Funcion de inicializacion
	bool
	initialize();

	// Funcion que se actualiza por frame
	void
	update();

	// Funcion de renderizado
	void
	render();

	void
	cleanup();

	void
	updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

	int
		ActualPosition = 0; //Posicion actual de los waypoints

private:
	Window* m_window;
	EngineUtilities::TSharedPointer<Actor> Triangle;
	EngineUtilities::TSharedPointer<Actor> Circle;
	EngineUtilities::TSharedPointer<Actor> Track;
	std::vector< EngineUtilities::TSharedPointer<Actor>> m_actors;

	// Seek Activity
	int currentWaypoint = 0;

	std::vector<sf::Vector2f> waypoints = {
		{720.0f, 350.0f},
		{720.0f, 260.0f},
		{125.0f, 50.0f},
		{70.0f, 120.0f},
		{70.0f, 450.0f},
		{400.0f, 350.0f},
		{550.0f, 500.0f},
		{650.0f, 550.0f},
		{720.0f, 450.0f}
	};
	sf::Texture Waluigi;
	sf::Texture texture;

	GUI m_GUI;
};