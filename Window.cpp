#include "Window.h"

Window::Window(int width, int height, const std::string& title) {
	/*
   * Constructor de la clase Window.
   */
	m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	if (!m_window) {
		/* Verifica si la ventana fue creada exitosamente*/
		ERROR("Window", "Window", "CHECK CONSTRUCTOR");
	}
	else {
		/* Este es el Mensaje de confirmacion de la creacion de la ventana*/
		MESSAGE("Window", "Window", "OK");
	}
}

Window::~Window() {
	/*
	 * Destructor de la clase Window.
	 */
	delete m_window;
}

void
Window::handleEvents() {
	/*
   * Maneja los eventos de la ventana.
   * Cierra la ventana.
   */
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close(); /* Cierra la ventana*/
	}
}

void
Window::clear() {
	/*
	 * Limpia la ventana.
	 */
	if (m_window != nullptr) { /* Verifica que la ventana no sea nullptr antes de limpiar. */ 
		m_window->clear(); /* Limpia lo que hay en ventana*/ 
	}
	else {
		ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
	}
}

void
Window::display() {
	/*
   * Muestra el contenido de la ventana en la pantalla.
   */
	if (m_window != nullptr) {  /* Verifica que la ventana no sea nullptr antes de mostrar.*/
		m_window->display();  /*  Muestra el contenido renderizado*/
	}
	else {
		ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
	}
}

bool
Window::isOpen() const {
	/*
	* Verifica si la ventana está abierta.
	*/
	
	if (m_window != nullptr) { /* Devuelve true si está abierta, de lo contrario devuelve false.*/
		return m_window->isOpen(); /* Retorna el estado de la ventana*/
	}
	else {
		ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");
		return false; /*  Si m_window es nullptr, retorna false*/
	}
}

void
Window::draw(const sf::Drawable& drawable) {
	if (m_window != nullptr) {
		m_window->draw(drawable);
	}
	else {
		ERROR("Window", "draw", "CHECK FOR WINDOW POINTER DATA");
	}
}

sf::RenderWindow*
Window::getWindow() {
	if (m_window != nullptr) {
		return m_window;
	}
	else {
		ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
		return nullptr;
	}
}

void
Window::destroy() {
	SAFE_PTR_RELEASE(m_window);
}