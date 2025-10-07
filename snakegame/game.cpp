#include "game.h"
#include <iostream>
Game::Game() : window(sf::VideoMode({ 800, 600 }), "Snake Game", sf::Style::Close), player(sf::Vector2f(400.f, 300.f), 20.f, sf::Vector2f(-1.f, 0.f)), isRunning(true), gameSpeed(200), deltaTime(0), totalTime(0), fpsCounter(), food(), freePositions() {
	window.setFramerateLimit(60);
	freePositions = std::vector<sf::Vector2f>();
	for(int i = 0.f; i < 800.f; i += 20.f)
		for(int j = 0.f; j < 600.f; j += 20.f)
			freePositions.push_back(sf::Vector2f(i, j));
	std::vector<sf::Vector2f> playerPositions = player.getPositions();
	for (const sf::Vector2f& pos : playerPositions) {
		auto it = std::find(freePositions.begin(), freePositions.end(), pos);
		if (it != freePositions.end())
			freePositions.erase(it);
	}
	for (int i = 0; i < 5; i++) {
		int r = rand() % freePositions.size();
		food[i].position = freePositions[r];
		freePositions.erase(freePositions.begin() + r);
		food[i].shape.setRadius(10.f);
		food[i].shape.setFillColor(sf::Color::Red);
		food[i].shape.setPosition(food[i].position);
	}
}
void Game::updateFreePositions() {
	freePositions = std::vector<sf::Vector2f>();
	for (int i = 0.f; i < 800.f; i += 20.f)
		for (int j = 0.f; j < 600.f; j += 20.f)
			freePositions.push_back(sf::Vector2f(i, j));
	std::vector<sf::Vector2f> playerPositions = player.getPositions();
	for (const sf::Vector2f& pos : playerPositions) {
		auto it = std::find(freePositions.begin(), freePositions.end(), pos);
		if (it != freePositions.end())
			freePositions.erase(it);
	}
	for (int i = 0; i < 5; i++) {
		auto it = std::find(freePositions.begin(), freePositions.end(), food[i].position);
		if (it != freePositions.end())
			freePositions.erase(it);
	}
}
void Game::wait(float time) {
	sf::Clock waitClock;
	while (waitClock.getElapsedTime().asMilliseconds() < time) {
		processEvents();
	}
}
void Game::processEvents() {
	while (const std::optional event = window.pollEvent()) {
		if (event->is<sf::Event::Closed>())
			window.close();
		else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				window.close();

			if (keyPressed->scancode == sf::Keyboard::Scancode::W) 
				player.handleInput(0);
			else if (keyPressed->scancode == sf::Keyboard::Scancode::S)
				player.handleInput(1);
			else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
				player.handleInput(2);
			else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
				player.handleInput(3);
		}
	}
}
void Game::update() {
	deltaTime = clock.restart().asMilliseconds();
	totalTime += deltaTime;
	if(totalTime > gameSpeed) {
		totalTime = 0;
		if (!player.update()) {
			restart();
			return;
		}
		for (int i = 0; i < 5; i++) {
			if (player.isOn(food[i].position)) {
				player.addSegment(player.getEndPosition());
				updateFreePositions();
				int r = rand() % freePositions.size();
				food[i].position = freePositions[r];
				freePositions.erase(freePositions.begin() + r);
				food[i].shape.setPosition(food[i].position);
			}
		}
	}
}
void Game::render() {
	window.clear(sf::Color::Black);
	player.draw(window);
	for (int i = 0; i < 5; i++)
		window.draw(food[i].shape);
	window.display();
}
void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
		window.setTitle("Snake Game - FPS: " + std::to_string(fpsCounter.update(deltaTime / 1000)));
	}
}
void Game::restart() {
	wait(1000.f);
	player = Player(sf::Vector2f(400.f, 300.f), 20.f, sf::Vector2f(-1.f, 0.f));
	totalTime = 0;
	deltaTime = 0;
}