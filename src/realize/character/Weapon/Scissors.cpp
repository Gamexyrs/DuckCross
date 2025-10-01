inline func Char_M::Weapon::Scissors::act(void) -> void {
  // 计算击杀线
  this->__attkLine[0].position = sf::Vector2f{};
  this->__attkLine[1].position = sf::Vector2f{};
  this->maths_attkLine(0.2f); this->Weapon::act();
  
  // Debug
  if(sys::__dataMode) {
     sys::__debugList.emplace_back(&this->__attkLine);
  }
}

inline func Char_M::Weapon::Scissors::setTexture(void) -> void {
  this->__s.setTexture(this->__t[this->__img_code], true);
  this->__s.setOrigin(sf::Fm::getSize(Char_M::Duck::__v->__s).x / -2.0f,
                        this->__t[this->__img_code].getSize().y /  2.0f);
}

inline func Char_M::Weapon::Scissors::attValid(Char_M::Enemy* v, bool __isBoss) -> void {
  if(!v->__realRect.intersects(this->__attkLine.getBounds())) return;

  if(Control_M::__move_attk.x < 0) {
    for(float x{this->__s.getPosition().x}; x > this->__attkLine[1].position.x; --x) {
      if(v->__realRect.contains({x, mathsKLCoord(this->__attkLine[0].position, this->__attkLine[1].position, x)})) {
        if(__isBoss) ChickBoss::hurt(this->attCast());
        else v->hurt(this->attCast() * Char_M::Element::attCast(Char_M::Duck::__v->__element, v->__element),
          sf::geometry::parse_circle_point({._radius = 15, ._center = this->__s.getPosition(),
            ._allow_in = false}, this->__attkLine[1].position).v_LengthToCenter_Coordinates);
          
        break;
      }
    }
  } else {
    for(float x{this->__s.getPosition().x}; x < this->__attkLine[1].position.x; ++x) {
      if(v->__realRect.contains({x, mathsKLCoord(this->__attkLine[0].position, this->__attkLine[1].position, x)})) {
        if(__isBoss) ChickBoss::hurt(this->attCast());
        else v->hurt(this->attCast() * Char_M::Element::attCast(Char_M::Duck::__v->__element, v->__element),
          sf::geometry::parse_circle_point({._radius = 15, ._center = this->__s.getPosition(),
            ._allow_in = false}, this->__attkLine[1].position).v_LengthToCenter_Coordinates);
          
        break;
      }
    }
  }
}

inline func Char_M::Weapon::Scissors::attCheck(void) -> void {
  if(this->__attkClock.getElapsedTime().asSeconds() > (this->__cd / Char_M::Value::__attack_speed_c_f)) {
     this->__attkClock.restart();
    if((Char_M::Weapon::__signal_call_att = (this->__img_code = !static_cast<bool>(this->__img_code))))
      __AUDIO__CHECK_SOUND__(scissors);
      ++Char_M::Value::__total_attk;
  }
}

Char_M::Weapon::Scissors::Scissors(void) {
  this->initData("scissors");
    
  this->__i[0].loadFromFile("./src/res/img/duck/weapon/scissors/default/_N.png");
  this->__i[1].loadFromFile("./src/res/img/duck/weapon/scissors/default/_Y.png");
  
  this->__t[0].loadFromImage(this->__i[0]);
  this->__t[1].loadFromImage(this->__i[1]);
  
  this->__t[0].setSmooth(sys::__smoothTex);
  this->__t[1].setSmooth(sys::__smoothTex);
  
  this->setTexture();
  this->__s.setScale({0.2, 0.2});
  
  this->__attkLine[0].color = sf::Color::Blue;
  this->__attkLine[1].color = sf::Color::Blue;
}
