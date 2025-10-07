#include "game.h"
#include <iostream>
Game::Game() : window(sf::VideoMode({ 800, 600 }), "Snake Game"), player(sf::Vector2f(400.f, 300.f), 20.f, sf::Vector2f(-1.f, 0.f)), isRunning(true), gameSpeed(200), deltaTime(0), totalTime(0), fpsCounter(){
	window.setFramerateLimit(60);
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
			if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
				player.handleInput(4);
		}
	}
}
void Game::update() {
	deltaTime = clock.restart().asMilliseconds();
	totalTime += deltaTime;
	if(totalTime > gameSpeed) {
		totalTime = 0;
		if (!player.update()) 
			restart();
	}
}
void Game::render() {
	window.clear(sf::Color::Black);
	player.draw(window);
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