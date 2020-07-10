#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include "Hero.h"

// Manejo de ventana
sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Test", sf::Style::Default);

// Manejo de los sprites
sf::Texture skyTexture;
sf::Sprite skySprite;

sf::Texture bgTexture;
sf::Sprite bgSprite;

// Instancia del heroe
Hero hero;




// Inicializar sprites
void init()
{
	// Inicializacion de texturas y Sprites
	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	bgTexture.loadFromFile("Assets/graphics/bg.png");
	bgSprite.setTexture(bgTexture);

	hero.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x * 0.25f,
		viewSize.y * 0.5f), 200);
}

// Funciones del teclado
void updateInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::W)
				hero.jump(750.0f);
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed)
			window.close();
	}
}

// Funcion que dibuja los objectos en la ventana
void draw()
{
	window.draw(skySprite);
	window.draw(bgSprite);
	window.draw(hero.getSprite());
	
}

// Funcion para mover los objetos en pantalla
void update(float dt)
{
	hero.update(dt);
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