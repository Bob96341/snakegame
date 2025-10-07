#pragma once
#ifndef SNAKESEGMENT_H
#define SNAKESEGMENT_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
class SnakeSegment {
private:
	sf::Vector2f position;
	sf::RectangleShape shape;
	SnakeSegment* nextSegment;
	SnakeSegment* previousSegment;
	//bool isHead;
public:
	SnakeSegment(sf::Vector2f position);
	sf::Vector2f getPosition() const;
	void setPosition(const sf::Vector2f position);
	void setNextSegment(SnakeSegment* next);
	SnakeSegment* getNextSegment() const;
	void setPreviousSegment(SnakeSegment* previous);
	SnakeSegment* getPreviousSegment() const;
	void setShape(const sf::RectangleShape shape);
	sf::RectangleShape getShape() const;
	void update(sf::Vector2f newPosition);
	void draw(sf::RenderWindow& window);
	//bool getIsHead() const;
	//void setIsHead(bool head);
};

#endif
