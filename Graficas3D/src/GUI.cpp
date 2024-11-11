#include "GUI.h"
#include "Window.h"
#include "NotificationService.h"

/**
 * @brief Configura el estilo y la apariencia de la interfaz gr�fica.
 */
void
GUI::init() {
    // Setup GUI Style
    setupGUIStyle();
}

/**
 * @brief Actualiza la interfaz de usuario.
 */
void
GUI::update() {
}

/**
 * @brief Renderiza los elementos visuales de la UI en pantalla.
 */
void
GUI::render() {
}

/**
 * @brief Libera los recursos de la interfaz de usuario.
 */
void
GUI::destroy() {
}

/**
 * @brief Configura el estilo y los colores de la GUI mediante ImGUI
 */
void GUI::setupGUIStyle() {
    ImGuiStyle& style = ImGui::GetStyle();

    // Ajuste de bordes
    style.WindowBorderSize = 2.0f;
    style.FrameBorderSize = 2.0f;
    style.WindowRounding = 4.0f;
    style.FrameRounding = 4.0f;
    style.ScrollbarRounding = 3.0f;
    style.GrabRounding = 3.0f;

    // Colores con mayor contraste
    ImVec4 yellow = ImVec4(0.95f, 0.75f, 0.05f, 1.00f);       // Amarillo principal con m�s brillo
    ImVec4 yellowHover = ImVec4(1.00f, 0.7f, 0.15f, 1.00f);   // Amarillo m�s oscuro al hacer hover
    ImVec4 yellowActive = ImVec4(1.00f, 0.5f, 0.1f, 1.00f);   // Amarillo tirando a naranja al hacer clic

    ImVec4 darkBlue = ImVec4(0.05f, 0.05f, 0.2f, 1.00f);        // Azul oscuro m�s profundo para el t�tulo
    ImVec4 darkBlueActive = ImVec4(0.1f, 0.1f, 0.3f, 1.00f);    // Azul m�s brillante al estar activo

    ImVec4* colors = style.Colors;

    // Fondo de la ventana m�s oscuro
    colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.08f, 0.08f, 1.00f);

    // T�tulos con azul oscuro
    colors[ImGuiCol_TitleBg] = darkBlue;
    colors[ImGuiCol_TitleBgActive] = darkBlueActive;
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.2f, 1.00f);

    // Bordes con amarillo m�s brillante
    colors[ImGuiCol_Border] = yellow;

    // Elementos interactivos con mayor contraste
    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = yellowHover;
    colors[ImGuiCol_FrameBgActive] = yellowActive;

    // Botones
    colors[ImGuiCol_Button] = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);  // Fondo m�s oscuro para resaltar el amarillo al pasar hover
    colors[ImGuiCol_ButtonHovered] = yellowHover;
    colors[ImGuiCol_ButtonActive] = yellowActive;

    // Checkboxes y sliders
    colors[ImGuiCol_CheckMark] = yellow;
    colors[ImGuiCol_SliderGrab] = yellow;
    colors[ImGuiCol_SliderGrabActive] = yellowHover;

    // Headers
    colors[ImGuiCol_Header] = darkBlue;
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.45f, 0.65f, 1.0f); // Azul m�s claro
    colors[ImGuiCol_HeaderActive] = darkBlueActive;

    // L�neas de gr�ficos
    colors[ImGuiCol_PlotLines] = yellow;
    colors[ImGuiCol_PlotHistogram] = yellow;

    // Textos
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);  // Texto m�s claro para mejor visibilidad
}

/**
 * @brief Muestra una consola en la interfaz de usuario.
 * @param programMessages Mapa que asocia c�digos de error con sus mensajes
 */
void
GUI::console(std::map<ConsolErrorType, std::string> programMessages) {
    ImGui::Begin("Console");
    for (const auto& pair : programMessages) {
        ImGui::Text("Code: %d - Message: %s", pair.first, pair.second.c_str());
    }
    ImGui::End();

}

void GUI::hierarchy(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    ImGui::Begin("Hierarchy");
    NotificationService& notifier = NotificationService::getInstance();  // Declaración de notifier

    for (int i = 0; i < actors.size(); ++i) {
        auto& actor = actors[i];
        if (actor.isNull()) continue;

        ImGui::PushID(i);
        std::string displayName = std::to_string(i) + " - " + actor->getName();
        if (ImGui::Selectable(displayName.c_str(), selectedActor == actor)) {
            selectedActor = actor;
        }
        ImGui::PopID();
    }

    ImGui::Separator();
    ImGui::Spacing();

    // Creación de actores
    if (ImGui::Button("Create Circle")) {
        auto circleAct = EngineUtilities::MakeShared<Actor>("Circle");
        if (!circleAct.isNull()) {
            circleAct->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
            circleAct->getComponent<Transform>()->setPosition(sf::Vector2(100.0f, 100.0f));
            circleAct->getComponent<Transform>()->setRotation(sf::Vector2(0.0f, 0.0f));
            circleAct->getComponent<Transform>()->setScale(sf::Vector2(1.0f, 1.0f));

            actors.push_back(circleAct);
            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + circleAct->getName() + "' created successfully.");
        }
    }

    // Código similar para "Create Rectangle" y "Create Triangle"
    ImGui::End();
    inspector();
}

/**
   * @brief Verifica si hay un actor seleccionado y, muestra las propiedades de transform
   */
void
GUI::inspector() {
    if (selectedActor.isNull()) {
        return;
    }

    ImGui::Begin("Inspector");

    // Obtiene el componente Transform del actor
    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {
        sf::Vector2f position = transform->getPosition();
        sf::Vector2f rotation = transform->getRotation();
        sf::Vector2f scale = transform->getScale();

        // Posici�n
        if (ImGui::DragFloat2("Position", &position.x, 0.1f)) {
            transform->setPosition(position);
        }

        // Rotaci�n
        if (ImGui::DragFloat2("Rotation", &rotation.x, 0.1f)) {
            transform->setRotation(rotation);
        }

        // Escala
        if (ImGui::DragFloat2("Scale", &scale.x, 0.1f)) {
            transform->setScale(scale);
        }
    }

    ImGui::End();
}