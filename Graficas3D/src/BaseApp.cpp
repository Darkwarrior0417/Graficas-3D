#include "BaseApp.h"
#include "NotificationService.h"

BaseApp::~BaseApp()
{
	NotificationService::getInstance().saveMessagesToFile("LogData.txt");
}

int
BaseApp::run() {
	NotificationService& notifier = NotificationService::getInstance();

	if (!initialize()) {
		notifier.addMessage(ConsolErrorType::ERROR, "Initializes result on a false statemente, check method validations");
		notifier.saveMessagesToFile("LogData.txt");
		ERROR("BaseApp", "run", "Initializes result on a false statemente, check method validations");
	}
	else {
		notifier.addMessage(ConsolErrorType::NORMAL, "All programs were initialized correctly");
	}
	m_GUI.init();

	while (m_window->isOpen()) {
		m_window->handleEvents();
		update();
		render();
	}

	cleanup();
	return 0;
}

bool
BaseApp::initialize() {
	NotificationService& notifier = NotificationService::getInstance();
	m_window = new Window(1920, 1080, "chicuelos Engine");
	if (!m_window) {
		ERROR("BaseApp", "initialize", "Error on window creation, var is null");
		return false;
	}
	// Track Actor
	Track = EngineUtilities::MakeShared<Actor>("Track");
	if (!Track.isNull()) {
		Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

		// Establecer posici�n, rotaci�n y escala desde Transform
		Track->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));
		Track->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
		Track->getComponent<Transform>()->setScale(sf::Vector2f(11.0f, 12.0f));

		if (!texture.loadFromFile("Circuit.png")) {
			std::cout << "Error de carga de textura" << std::endl;
			return -1; // Manejar error de carga
		}
		Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
		m_actors.push_back(Track);
	}

	// Circle Actor
	Circle = EngineUtilities::MakeShared<Actor>("Circle");
	if (!Circle.isNull()) {
		Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

		// Establecer posici�n, rotaci�n y escala desde Transform
		Circle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
		Circle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
		Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));

		if (!Waluigi.loadFromFile("Characters/Waluigi.png")) {
			notifier.addMessage(ConsolErrorType::WARNING, "Warning - Missing Texture from source bin");
			return -1; // Manejar error de carga
		}
		Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&Waluigi);
		m_actors.push_back(Circle);
	}

	//// Triangle Actor
	//Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
	//if (!Triangle.isNull()) {
	//	Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
	//	Triangle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
	//	Triangle->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
	//	Triangle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));
	//}
	//m_actors.push_back(Triangle);
	return true;
}

void
BaseApp::update() {
	// Update window method
	m_window->update();

	// Mouse Position
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
	sf::Vector2f mousePosF(static_cast<float>(mousePosition.x),
		static_cast<float>(mousePosition.y));

	// Update the actors
	for (auto& actor : m_actors) {
		if (!actor.isNull()) {
			actor->update(m_window->deltaTime.asSeconds());
			if (actor->getName() == "Circle") {
				updateMovement(m_window->deltaTime.asSeconds(), actor);
			}
		}
	}
}

void
BaseApp::render() {
	NotificationService& notifier = NotificationService::getInstance();
	m_window->clear();

	for (auto& actor : m_actors) {
		if (!actor.isNull()) {
			actor->render(*m_window);
		}
	}

	/* 
	if (!Track.isNull()) {
		Track->render(*m_window);
	}
	if (!Circle.isNull()) {
		Circle->render(*m_window);
	}
	if (!Triangle.isNull()) {
		Triangle->render(*m_window);
	} */

	// Mostrar el render en ImGui
	m_window->renderToTexture();  // Finaliza el render a la textura
	m_window->showInImGui();      // Muestra la textura en ImGui

	// Configuramos la consola y le pasamos los mensajes
	m_GUI.console(notifier.getNotifications());

	// Mostramos la jerarquía de actorees
	m_GUI.hierarchy(m_actors);

	m_window->render();
	m_window->display();

}

void
BaseApp::cleanup() {
	m_window->destroy();
	delete m_window;
}

void
BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle) {
	// Verificar si el Circle es nulo
	if (!circle || circle.isNull()) {
		return;
	}

	// Obtener el componente Transform
	auto transform = circle->getComponent<Transform>();
	if (transform.isNull()) {
		return;
	}

	// Posici�n actual del destino (punto de recorrido)
	sf::Vector2f targetPos = waypoints[currentWaypoint];

	// Llamar al Seek del Transform
	transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

	// Obtener la posici�n actual del actor desde Transform
	sf::Vector2f currentPos = transform->getPosition();

	// Comprobar si el actor ha alcanzado el destino (o est� cerca)
	float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

	if (distanceToTarget < 10.0f) { // Umbral para considerar que ha llegado
		currentWaypoint = (currentWaypoint + 1) % waypoints.size(); // Ciclar a trav�s de los puntos
	}
}