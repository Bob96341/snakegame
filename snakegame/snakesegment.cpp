#include "snakesegment.h"
SnakeSegment::SnakeSegment(sf::Vector2f position) : position(position), nextSegment(nullptr), previousSegment(nullptr) {
	shape.setSize(sf::Vector2f(20.f, 20.f));
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(position);
	shape.setOrigin(shape.getSize() / 2.f);
}
sf::Vector2f SnakeSegment::getPosition() const {
	return position;
}
void SnakeSegment::setPosition(const sf::Vector2f position) {
	this->position = position;
	shape.setPosition(position);
}
void SnakeSegment::setNextSegment(SnakeSegment* next) {
	this->nextSegment = next;
}
SnakeSegment* SnakeSegment::getNextSegment() const {
	return nextSegment;
}
void SnakeSegment::setPreviousSegment(SnakeSegment* previous) {
	this->previousSegment = previous;
}
SnakeSegment* SnakeSegment::getPreviousSegment() const {
	return previousSegment;
}
void SnakeSegment::setShape(const sf::RectangleShape shape) {
	this->shape = shape;
}
sf::RectangleShape SnakeSegment::getShape() const {
	return shape;
}
void SnakeSegment::update(sf::Vector2f newPosition) {
	position = newPosition;
	shape.setPosition(position);
}
void SnakeSegment::draw(sf::RenderWindow& window) {
	window.draw(shape);
}
