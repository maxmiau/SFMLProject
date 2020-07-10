#include "SFML-2.5.1/include/SFML/Graphics.hpp"
#include <vector>

#include "Hero.h"
#include "Enemy.h"

// Manejo de ventana
sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "Test", sf::Style::Default);

// Crear enemigos
void spawnEnemy();

// Manejo de los sprites
sf::Texture skyTexture;
sf::Sprite skySprite;

sf::Texture bgTexture;
sf::Sprite bgSprite;

// Instancia del heroe
Hero hero;

// Vector donde se almacenan los enemigos en pantalla
std::vector<Enemy*> enemies;

// Frecuencia de generacion de los enemigos
float currentTime;
float prevTime = 0.0f;



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

	srand((int)time(0));
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

	for (Enemy *enemy : enemies)
	{
		window.draw(enemy->getSprite());
	}
	
}

// Funcion para mover los objetos en pantalla
void update(float dt)
{
	hero.update(dt);

	currentTime += dt;
	// crear enemigos
	if (currentTime >= prevTime + 1.125f) {
		spawnEnemy();
		prevTime = currentTime;
	}

	// Eliminar enemigos del vector
	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy *enemy = enemies[i];

		enemy->update(dt);

		if (enemy->getSprite().getPosition().x < 0)
		{
			enemies.erase(enemies.begin() + i);
			delete(enemy);
		}
	}
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

void spawnEnemy() {
	int randLoc = rand() % 3;

	sf::Vector2f enemyPos;

	float speed;

	switch (randLoc)
	{
	case 0: 
		enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f);
		speed = -400; break;

	case 1:
		enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f);
		speed = -550; break;

	case 2:
		enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f);
		speed = -650; break;

	default:
		printf("Incorrect 'y' value \n"); return;
	}

	Enemy* enemy = new Enemy();
	enemy->init("Assets/graphics/enemy.png", enemyPos, speed);

	enemies.push_back(enemy);
}