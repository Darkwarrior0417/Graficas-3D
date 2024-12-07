#include "GUI.h"
#include "Window.h"
#include "imgui_internal.h"

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
    ImVec4 yellow = ImVec4(0.95f, 0.75f, 0.05f, 1.00f);       // Amarillo principal con más brillo
    ImVec4 yellowHover = ImVec4(1.00f, 0.7f, 0.15f, 1.00f);   // Amarillo más oscuro al hacer hover
    ImVec4 yellowActive = ImVec4(1.00f, 0.5f, 0.1f, 1.00f);   // Amarillo tirando a naranja al hacer clic

    ImVec4 darkBlue = ImVec4(0.05f, 0.05f, 0.2f, 1.00f);        // Azul oscuro más profundo para el título
    ImVec4 darkBlueActive = ImVec4(0.1f, 0.1f, 0.3f, 1.00f);    // Azul más brillante al estar activo

    ImVec4* colors = style.Colors;

    // Fondo de la ventana más oscuro
    colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.08f, 0.08f, 1.00f);

    // Títulos con azul oscuro
    colors[ImGuiCol_TitleBg] = darkBlue;
    colors[ImGuiCol_TitleBgActive] = darkBlueActive;
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.04f, 0.04f, 0.2f, 1.00f);

    // Bordes con amarillo más brillante
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

    // L�neas de gráficos
    colors[ImGuiCol_PlotLines] = yellow;
    colors[ImGuiCol_PlotHistogram] = yellow;

    // Textos
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 0.95f, 1.00f);  // Texto m�s claro para mejor visibilidad
}

/**
 * @brief Muestra una consola en la interfaz de usuario.
 * @param programMessages Mapa que asocia códigos de error con sus mensajes
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
    NotificationService& notifier = NotificationService::getInstance();

    ImGui::Begin("Hierarchy");

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

            circleAct->getComponent<Transform>()->setTransform(Vector2(100.0f, 100.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));

            actors.push_back(circleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + circleAct->getName() + "' Has been created correctly.");
        }
    }
    if (ImGui::Button("Create Rectangle")) {
        auto rectangleAct = EngineUtilities::MakeShared<Actor>("Rectangle");
        if (!rectangleAct.isNull()) {
            rectangleAct->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);

            rectangleAct->getComponent<Transform>()->setTransform(Vector2(200.0f, 150.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(rectangleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + rectangleAct->getName() + "' Has been created correctly.");
        }
    }

    if (ImGui::Button("Create Triangle")) {
        auto triangleAct = EngineUtilities::MakeShared<Actor>("Triangle");
        if (!triangleAct.isNull()) {
            triangleAct->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);

            triangleAct->getComponent<Transform>()->setTransform(Vector2(150.0f, 200.0f),
                Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
            actors.push_back(triangleAct);

            notifier.addMessage(ConsolErrorType::NORMAL, "Actor '" + triangleAct->getName() + "' Has been created correctly.");
        }
    }

    ImGui::End();
    //inspector();
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

    // Muestra el nombre del actor
    char objectName[128];
    std::string name = selectedActor->getName();

    // Asegúrate de no exceder el tamaño del array
    if (name.size() < sizeof(objectName)) {
        std::copy(name.begin(), name.end(), objectName);
        objectName[name.size()] = '\0'; // Termina con null
    }

    // Campo para editar el nombre del objeto
    if (ImGui::InputText("Name", objectName, sizeof(objectName))) {
        // Si el usuario edita el nombre, actualiza el actor
        selectedActor->setName(std::string(objectName));
    }

    // Obtiene el componente Transform del actor
    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {

        float* m_position = new float[2];
        float* m_rotation = new float[2];
        float* m_scale = new float[2];
        vec2Control("Position", selectedActor->getComponent<Transform>()->getPosData());
        vec2Control("Rotation", selectedActor->getComponent<Transform>()->getRotData());
        vec2Control("Scale", selectedActor->getComponent<Transform>()->getSclData());

        /*sf::Vector2f position = transform->getPosition();
          sf::Vector2f rotation = transform->getRotation();
          sf::Vector2f scale = transform->getScale();

        // Posición
        if (ImGui::DragFloat2("Position", &position.x, 0.1f)) {
          transform->setPosition(position);
        }

        // Rotación
        if (ImGui::DragFloat2("Rotation", &rotation.x, 0.1f)) {
           transform->setRotation(rotation);
        }

        // Escala
        if (ImGui::DragFloat2("Scale", &scale.x, 0.1f)) {
            transform->setScale(scale);
        }*/
    }

    ImGui::End();
}
void
GUI::vec2Control(const std::string& label, float* values, float resetValue, float columnWidth) {
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize)) values[0] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize)) values[1] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PopStyleVar();
    ImGui::Columns(1);

    ImGui::PopID();
}