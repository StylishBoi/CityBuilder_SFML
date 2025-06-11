#ifndef MOTION_H
#define MOTION_H

#include <SFML/Graphics/Transform.hpp>

namespace api::motion {

  class Motor {
    sf::Vector2f position_;
    sf::Vector2f destination_;
    float speed_=1.f;

  public:
    void Update(float dt);
    void MoveTo(sf::Vector2f destination);

    void SetSpeed(float speed){speed_=speed;}
    void SetPosition(sf::Vector2f position){position_=position;}
    [[nodiscard]] const sf::Vector2f& GetPosition() const{return position_;}

  };

}
#endif //MOTION_H
