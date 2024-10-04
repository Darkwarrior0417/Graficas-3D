#pragma once
#include "Prerequisites.h"

class
	Window {
public:
	Window() = default; /* Constructor por defecto de la clase Window.*/
	Window(int width, int height, const std::string& title); /* Constructor que crea una ventana con dimensiones y título proporcionados.*/
	~Window(); /* Destructor */

	void
		handleEvents(); /* Maneja los eventos de la ventana*/

	
	void
		clear(); /* Limpia la pantalla*/

	
	void
		display(); /* Muestra el contenido renderizado*/

	
	bool
		isOpen() const; /*Checa si está abierta.*/

	
	void
		draw(const sf::Drawable& drawable);  /* Dibuja un objeto*/

	
	sf::RenderWindow* /* Devuelve un puntero a la ventana SFML.*/
		getWindow();

	
	void
		init(); /* Inicializa la ventana*/

	
	void
		update(); /*Actualiza el estado de la ventana.*/


	void
		render(); /* Renderiza el contenido */

	void
		destroy(); /*Libera los recursos y destruye la ventana.*/

private:
	sf::RenderWindow* m_window; /*Puntero a la ventana de SFML.*/
};