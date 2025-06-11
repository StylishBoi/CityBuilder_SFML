#include "motion/motor.h"

#include <SFML/Window/Mouse.hpp>

using namespace api::motion;

void Motor::Update(float dt) {
  SetSpeed(speed_*dt);
}

void Motor::MoveTo(sf::Vector2f destination) {
}


