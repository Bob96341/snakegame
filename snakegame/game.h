#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <SFML/System.hpp>
//#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "fpscounter.h"
#include <vector>

typedef struct food {
	sf::Vector2f position;
	sf::CircleShape shape;
} Food;

class Game {
private:
	sf::RenderWindow window;
	sf::Clock clock;
	double deltaTime;
	double totalTime;
	double gameSpeed;
	FPSCounter fpsCounter;
	Player player;
	Food food[5];
	std::vector<sf::Vector2f> freePositions;
	void updateFreePositions();
	bool isRunning;
	void processEvents();
	void update();
	void render();
	void wait(float time);
public:
	Game();
	void run();
	void restart();
};

#endif