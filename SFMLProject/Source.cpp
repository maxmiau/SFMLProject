#include "SFML-2.5.1/include/SFML/Graphics.hpp"

// Manejo de ventana
sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Test", sf::Style::Default);

// Manejo de los sprites
sf::Texture skyTexture;
sf::Sprite skySprite;

sf::Texture bgTexture;
sf::Sprite bgSprite;




// Inicializar sprites
void init()
{
	// Inicializacion de texturas y Sprites
	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	bgTexture.loadFromFile("Assets/graphics/bg.png");
	bgSprite.setTexture(bgTexture);

	
}

// Funciones del teclado
void updateInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			window.close();
	}
}

// Funcion que dibuja los objectos en la ventana
void draw()
{
	window.draw(skySprite);
	window.draw(bgSprite);
	
}

// Funcion para mover los objetos en pantalla
void update(float dt)
{
	
}

int main()
{
	// Objeto tipo clock
	sf::Clock clock;

	// init
	init();

	while (window.isOpen())
	{
		// Update input
		updateInput();

		// Update Game
		sf::Time dt = clock.restart();
		update(dt.asSeconds());

		window.clear(sf::Color::Blue);
		draw();

		window.display();
	
	}

	return EXIT_SUCCESS;
}