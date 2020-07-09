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

sf::Texture heroTexture;
sf::Sprite heroSprite;

sf::Vector2f playerPosition;
bool playerMoving = false;


// Inicializar sprites
void init()
{
	// Inicializacion de texturas y Sprites
	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	bgTexture.loadFromFile("Assets/graphics/bg.png");
	bgSprite.setTexture(bgTexture);

	heroTexture.loadFromFile("Assets/graphics/hero.png");
	heroSprite.setTexture(heroTexture);
	heroSprite.setPosition(sf::Vector2f(viewSize.x / 2, viewSize.y / 2));
	heroSprite.setOrigin(heroTexture.getSize().x / 2, heroTexture.getSize().x / 2);
}

// Funciones del teclado
void updateInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Right)
				playerMoving = true;
		}

		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::Right)
				playerMoving = false;
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
	window.draw(heroSprite);
}

// Funcion para mover los objetos en pantalla
void update(float dt)
{
	if (playerMoving)
		heroSprite.move(50.0f * dt, 0);
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