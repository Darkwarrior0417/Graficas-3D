#include "BaseApp.h"

BaseApp::~BaseApp()
{
    NotificationService::getInstance().saveMessagesToFile("LogData.txt");
}

int
BaseApp::run() {
    NotificationService& notifier = NotificationService::getInstance();

    if (!initialize()) {
        notifier.addMessage(ConsolErrorType::ERROR, "Initialization failed, check method validations");
        notifier.saveMessagesToFile("LogData.txt");
        ERROR("BaseApp", "run", "Initialization failed, check method validations");
        return -1; // Agregar un código de error en caso de fallo
    }
    else {
        notifier.addMessage(ConsolErrorType::NORMAL, "All programs were initialized correctly");
    }
    m_GUI.init();

    while (m_window->isOpen()) {
        m_window->handleEvents();
        deltaTime = clock.restart();
        update();
        render();
    }

    cleanup();
    return 0;
}

bool
BaseApp::initialize() {
    NotificationService& notifier = NotificationService::getInstance();
    ResourceManager& resourceManager = ResourceManager::getInstance();

    m_window = new Window(960, 540, "Chicuelos Engine");
    if (!m_window) {
        notifier.addMessage(ConsolErrorType::ERROR, "Error on window creation, pointer is null");
        ERROR("BaseApp", "initialize", "Error on window creation, var is null");
        return false;
    }

    // Al iniciar el programa, establecer los puntos de destino
    points[0] = Vector2(25.0f, 560.0f);
    points[1] = Vector2(25.0f, 20.0f);
    points[2] = Vector2(700.0f, 20.0f);
    points[3] = Vector2(700.0f, 200.0f);
    points[4] = Vector2(500.0f, 200.0f);
    points[5] = Vector2(500.0f, 120.0f);
    points[6] = Vector2(350.0f, 120.0f);
    points[7] = Vector2(350.0f, 340.0f);
    points[8] = Vector2(700.0f, 340.0f);

    // Track Actor
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

        // Establecer posición, rotación y escala desde Transform
        Track->getComponent<Transform>()->setTransform(Vector2(0.0f, 0.0f),
            Vector2(0.0f, 0.0f), Vector2(10.0f, 10.0f));

        // Cargar la textura de Track
        if (!resourceManager.loadTexture("Circuit", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Can't load texture: Circuit");
        }

        EngineUtilities::TSharedPointer<Texture> trackTexture = resourceManager.getTexture("Circuit");
        if (trackTexture) {
            Track->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Track);
    }
    else {
        notifier.addMessage(ConsolErrorType::ERROR, "Error - Null pointer Reference");
        notifier.addMessage(ConsolErrorType::WARNING, "Warning - Missing Texture from source bin");
    }

    // Circle Actor
    Circle = EngineUtilities::MakeShared<Actor>("Player");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

        Circle->getComponent<Transform>()->setTransform(Vector2(200.0f, 200.0f),
            Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        if (!resourceManager.loadTexture("Characters/Waluigi", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Can't load texture: Waluigi");
        }
        EngineUtilities::TSharedPointer<Texture> trackTexture = resourceManager.getTexture("Characters/Waluigi");
        if (trackTexture) {
            Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Circle);
    }
    else {
        notifier.addMessage(ConsolErrorType::ERROR, "Error - Nullpointer Reference");
        notifier.addMessage(ConsolErrorType::WARNING, "Warning - Missing Texture from source bin");
    }

    // Triangle Actor
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
        Triangle->getComponent<Transform>()->setTransform(Vector2(150.0f, 200.0f),
            Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

        // Cargar la textura de Triangle
        if (!resourceManager.loadTexture("Characters/Waluigi2", "png")) {
            notifier.addMessage(ConsolErrorType::ERROR, "Can't load texture: Waluigi2");
        }

        EngineUtilities::TSharedPointer<Texture> trackTexture = resourceManager.getTexture("Characters/Waluigi2");
        if (trackTexture) {
            Triangle->getComponent<ShapeFactory>()->getShape()->setTexture(&trackTexture->getTexture());
        }

        m_actors.push_back(Triangle);
    }
    else {
        notifier.addMessage(ConsolErrorType::ERROR, "Error - Nullpointer Reference");
        notifier.addMessage(ConsolErrorType::WARNING, "Warning - Missing Texture from source bin");
    }

    return true;
}

void
BaseApp::update() {
    m_window->update();

    // Update the actors
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());
            if (actor->getName() == "Player") {
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

    // Mostrar el render en ImGui
    m_window->renderToTexture();  // Finaliza el render a la textura
    m_window->showInImGui();      // Muestra la textura en ImGui

    // Configuramos la consola y le pasamos los mensajes
    m_GUI.console(notifier.getNotifications());

    m_GUI.inspector();

    // Mostramos la jerarquía de actores
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
    if (!circle || circle.isNull()) return;

    // Obtener el componente Transform
    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) return;

    // Posición actual del destino (punto de recorrido)
    Vector2 targetPos = points[m_currentPoint];

    // Llamar al Seek del Transform
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    // Obtener la posición actual del actor desde Transform
    Vector2 currentPos = transform->getPosition();

    // Comprobar si el actor ha alcanzado el destino (o está cerca)
    float distanceToTarget = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    if (distanceToTarget < 5.0f) {
        // Incrementar el punto de destino al siguiente
        m_currentPoint++;
        if (m_currentPoint >= 9) { // Si se ha alcanzado el último punto, reiniciar al primero
            m_currentPoint = 0;
        }
    }
}
