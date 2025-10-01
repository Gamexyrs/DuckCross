inline func Char_M::Weapon::initData(const std::string& str) -> void {
  const auto& target{__weaponData.find(str)->second};
  this->__weapon_code = std::get<0>(target);
  this->__is_remote   = std::get<1>(target);
  this->__attack      = std::get<2>(target);
  this->__cd          = std::get<3>(target);
}

inline func Char_M::Weapon::attCast(void) -> int {
  return static_cast<int>(sys::rand<int>(this->__attack)
    * (this->critCheck() ? Char_M::Value::__attack_crit_f : 1.0f)
    * (this->__is_remote ? Char_M::Value::__attack_r_f : Char_M::Value::__attack_c_f)
    * Char_M::Value::__attack_f);
}

inline func Char_M::Weapon::critCheck(void) -> bool {
  return (this->__signal_crit = (sys::rand<float>({0, 1}) <= Char_M::Value::__attack_crit_p));
}

inline func Char_M::Weapon::maths_attkLine(float __factor) -> void {
  this->__attkLine[0].position += this->__s.getPosition();
  this->__attkLine[1].position += this->__s.getPosition();
  if(Control_M::__angle_attk <= 270.0f
  && Control_M::__angle_attk >= 90.0f) {
    if(Control_M::__angle_attk >= 180.0f)
      this->__attkLine[1].position += {-(this->__t[1].getSize().x * __factor) * (static_cast<float>(std::cos((Control_M::__angle_attk - 180) * M_PI / 180))),
                                       -(this->__t[1].getSize().x * __factor) * (static_cast<float>(std::sin((Control_M::__angle_attk - 180) * M_PI / 180)))};
    else
      this->__attkLine[1].position += {-(this->__t[1].getSize().x * __factor) * (static_cast<float>(std::sin((Control_M::__angle_attk - 90)  * M_PI / 180))),
                                        (this->__t[1].getSize().x * __factor) * (static_cast<float>(std::cos((Control_M::__angle_attk - 90)  * M_PI / 180)))};
  } else {
    if(Control_M::__angle_attk > 270.0f)
      this->__attkLine[1].position += { (this->__t[1].getSize().x * __factor) * (static_cast<float>(std::sin((Control_M::__angle_attk - 180) * M_PI / 180))),
                                       -(this->__t[1].getSize().x * __factor) * (static_cast<float>(std::cos((Control_M::__angle_attk - 180) * M_PI / 180)))};
    else
      this->__attkLine[1].position += { (this->__t[1].getSize().x * __factor) * (static_cast<float>(std::cos(Control_M::__angle_attk         * M_PI / 180))),
                                        (this->__t[1].getSize().x * __factor) * (static_cast<float>(std::sin(Control_M::__angle_attk         * M_PI / 180)))};
  }
}

inline func Char_M::Weapon::act(void) -> void {
  // 定位
  this->__s.setPosition(sf::align({}, Char_M::Duck::__v->__s.getGlobalBounds()));
  
  // 旋转
  if(Control_M::__move_attk != sf::Vector2f()) {
    this->__s.setRotation(Control_M::__angle_attk);
    // 攻击
    this->attCheck();
  } else {
    this->__img_code = 0;
    this->__attkClock.restart();
    if(Char_M::Duck::__v->__img_code < 3)
      this->__s.setRotation(180);
    else
      this->__s.setRotation(0);
  } this->setTexture();
  
  // 鸭鸭
  size_t __tmp_code{Char_M::Duck::__v->__img_code};
  static short tmp_dire; {
         if(Control_M::__move_move == sf::Vector2f{})
                               tmp_dire =  0;
    else if(Control_M::__move_move.x < 0) tmp_dire = -1;
                          else tmp_dire =  1;
    if(Control_M::__move_attk != sf::Vector2f{}
                            && tmp_dire) {
      if(Control_M::__angle_attk <= 270
      && Control_M::__angle_attk >= 90) tmp_dire = -1;
                             else tmp_dire =  1;
    }
  }
  switch(tmp_dire) {
    case(0): {
      if(Control_M::__move_attk != sf::Vector2f{}) {
        if(Control_M::__angle_attk <= 270
        && Control_M::__angle_attk >= 90) {
           Char_M::Duck::__v->__img_code = 0;
        } else {
           Char_M::Duck::__v->__img_code = 3;
        }
      } else {
        if(Char_M::Duck::__v->__img_code < 3) {
           Char_M::Duck::__v->__img_code = 0;
        } else {
           Char_M::Duck::__v->__img_code = 3;
        }
      }
    } break;
    case(-1): {
      if(Char_M::Duck::__v->__img_code == 0
      || Char_M::Duck::__v->__img_code == 3) {
         Char_M::Duck::__v->__img_code = 1;
      } else if(Char_M::Duck::__v->__img_code > 3) {
         Char_M::Duck::__v->__img_code -= 3;
      } else if(Char_M::Duck::__v->__img_clock.getElapsedTime().asMilliseconds() >= 300) {
        if(Char_M::Duck::__v->__img_code == 1) {
           Char_M::Duck::__v->__img_code = 2;
        } else {
           Char_M::Duck::__v->__img_code = 1;
        }
      }
    } break;
    case(1): {
      if(Char_M::Duck::__v->__img_code == 0
      || Char_M::Duck::__v->__img_code == 3) {
         Char_M::Duck::__v->__img_code = 4;
      } else if(Char_M::Duck::__v->__img_code < 3) {
         Char_M::Duck::__v->__img_code += 3;
      } else if(Char_M::Duck::__v->__img_clock.getElapsedTime().asMilliseconds() >= 300) {
        if(Char_M::Duck::__v->__img_code == 4) {
           Char_M::Duck::__v->__img_code = 5;
        } else {
           Char_M::Duck::__v->__img_code = 4;
        }
      }
    } break;
  }
  if(__tmp_code != Char_M::Duck::__v->__img_code) {
    Char_M::Duck::__v->__img_clock.restart();
    Char_M::Duck::__v->__s.setTexture(Char_M::Duck::__v->__t[Char_M::Duck::__v->__img_code]);
  }
  
  // 子弹
  for(auto i = this->__bullet.begin(); i != this->__bullet.end(); ) {
    if((i->first.getBounds().intersects(sf::Renderable::getViewRect()) || Char_M::Skill::__bulletTime)
     && i->second != sf::Vector2f{}) {
      // 障碍物
      for(const auto& j : Map_M::__active_obstacle)
        if(i->first.getBounds().intersects(j)) i = this->__bullet.erase(i);
      // 暂停
      if(!sf::Msgable::getLocked()) {
        i->first[0].position += i->second * 0.25f * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f);
        i->first[1].position += i->second * 0.25f * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f);
      } Char_M::__drawList.emplace_back(std::make_pair<const sf::Vector2f&, sf::Drawable*>(
         sf::align({}, i->first.getBounds(), sf::Align::B), &i->first)); ++i;
    } else i = this->__bullet.erase(i);
  }
  
  // 绘制
  Char_M::__drawList.emplace_back(std::make_pair<const sf::Vector2f&, sf::Drawable*>(
    sf::align({}, this->__s.getGlobalBounds(), sf::Align::B), &this->__s));
}

#include "Scissors.cpp"
#include "Pistol.cpp"
