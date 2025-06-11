#ifndef MOTION_H
#define MOTION_H

#include <SFML/Graphics/Transform.hpp>

namespace api::motion {

  class Motor {
    sf::Vector2f position_;
    sf::Vector2f destination_;
    float speed_;

    float remainingDistance_=std::numeric_limits<float>::infinity();

  public:
    void Update(float dt);
    float RemainingDistance();

    void SetSpeed(float speed){speed_=speed;}
    void SetPosition(sf::Vector2f position){position_=position;}
    void SetDestination(sf::Vector2f destination){destination_ = destination;}

    [[nodiscard]] const sf::Vector2f& GetPosition() const{return position_;}

  };

  inline void Motor::Update(const float dt) {
    const sf::Vector2f distance = destination_ - position_;
    remainingDistance_ = distance.length();

    if (distance.length() < speed_*dt) {
      position_ = destination_;
      return;
    }
    position_ += distance.normalized()*speed_*dt;
  }

  inline float Motor::RemainingDistance() {
    return remainingDistance_;
  }

}
#endif //MOTION_H
