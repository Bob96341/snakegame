#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "snakesegment.h"
class Player {
private:
	sf::Vector2f position;
	float speed;
	sf::Vector2f goal;
	sf::Vector2f prevgoal;
	SnakeSegment* head;
	bool s;
	bool dead;

public:
	Player();
	Player(sf::Vector2f position, float speed, sf::Vector2f goal);
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f position);
	float getSpeed() const;
	void setSpeed(float speed);
	SnakeSegment* getHead() const;
	void addSegment(sf::Vector2f position);
	void handleInput(int dir);
	bool update();
	void move();
	void draw(sf::RenderWindow& window);
	bool checkCollision() const;
};

#endif 
