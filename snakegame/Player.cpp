#include "Player.h"
Player::Player() : position(0.f, 0.f), speed(20.f), goal(-1.f, 0.f), head(new SnakeSegment(position)), s(false), dead(false), prevgoal(goal) { 
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(20.f, 20.f));
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(position);
	//shape.setOrigin(shape.getSize() / 2.f);
	head->setShape(shape);
	head->setPreviousSegment(head);
	addSegment(head->getPosition()+sf::Vector2f(20.f,0.f));
}
Player::Player(sf::Vector2f position, float speed, sf::Vector2f goal) : position(position), speed(speed), goal(goal), head(new SnakeSegment(position)), s(false), dead(false), prevgoal(goal){
	sf::RectangleShape shape;
	shape.setSize(sf::Vector2f(20.f, 20.f));
	shape.setFillColor(sf::Color::Yellow);
	shape.setPosition(position);
	//shape.setOrigin(shape.getSize() / 2.f);
	head->setShape(shape);
	head->setPreviousSegment(head);
	addSegment(head->getPosition() + sf::Vector2f(20.f, 0.f));
}
sf::Vector2f Player::getPosition() const {
	return position;
}
void Player::setPosition(const sf::Vector2f position) {
	this->position = position;
}
sf::Vector2f Player::getEndPosition() const {
	return endposition;
}
float Player::getSpeed() const {
	return speed;
}
void Player::setSpeed(float speed) {
	this->speed = speed;
}
SnakeSegment* Player::getHead() const {
	return head;
}
void Player::addSegment(sf::Vector2f position) {
	SnakeSegment* current = head->getPreviousSegment();
	SnakeSegment* newSegment = new SnakeSegment(position);
	current->setNextSegment(newSegment);
	newSegment->setPreviousSegment(current);
	head->setPreviousSegment(newSegment);
}
void Player::handleInput(int dir) {
	switch (dir) {
		case 0: // up
			goal = prevgoal == sf::Vector2f(0.f, 1.f) ? goal : sf::Vector2f(0.f, -1.f);
			break;
		case 1: // down
			goal = prevgoal == sf::Vector2f(0.f, -1.f) ? goal : sf::Vector2f(0.f, 1.f);
			break;
		case 2: // left
			goal = prevgoal == sf::Vector2f(1.f, 0.f) ? goal : sf::Vector2f(-1.f, 0.f);
			break;
		case 3: // right
			goal = prevgoal == sf::Vector2f(-1.f, 0.f) ? goal : sf::Vector2f(1.f, 0.f);
			break;
		default:
			break;
	}
}
void Player::move() {
	SnakeSegment* current = head;
	sf::Vector2f previousPosition = current->getPosition();
	current->setPosition(position);
	current = current->getNextSegment();
	while (current) {
		sf::Vector2f tempPosition = current->getPosition();
		current->setPosition(previousPosition);
		previousPosition = tempPosition;
		current = current->getNextSegment();
	}
}
void Player::draw(sf::RenderWindow& window) {
	SnakeSegment *start = head;
	for (; start; start = start->getNextSegment())
		start->draw(window);
}
bool Player::checkCollision() const {
	SnakeSegment* current = head->getNextSegment();
	for (; current; current = current->getNextSegment()) 
		if (head->getPosition() == current->getPosition() || head->getPosition().x >= 800 || head->getPosition().x < 0 || head->getPosition().y >= 600 || head->getPosition().y < 0)
			return true;
	return false;
}
bool Player::isOn(sf::Vector2f place) const {
	for (SnakeSegment* current = head; current; current = current->getNextSegment()) 
		if (current->getPosition() == place)
			return true;
	return false;
}
std::vector<sf::Vector2f> Player::getPositions() const {
	std::vector<sf::Vector2f> positions;
	for (SnakeSegment* current = head; current; current = current->getNextSegment())
		positions.push_back(current->getPosition());
	return positions;
}
bool Player::update() {
	if (dead) return false;
	position += goal * speed;
	endposition = head->getPreviousSegment()->getPosition();
	move();
	if (checkCollision()) {
		dead = true;
		return false;
	}
	prevgoal = goal;
	return true;
}