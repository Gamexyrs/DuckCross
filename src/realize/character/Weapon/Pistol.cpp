inline func Char_M::Weapon::Pistol::act(void) -> void {
  // 计算瞄准线
  this->__attkLine[0].position = sf::Vector2f{0, -20};
  this->__attkLine[1].position = sf::Vector2f{0, -20};
  this->maths_attkLine(0.65f);
  this->Weapon::act();
  
  // Debug
  if(sys::__dataMode) {
     sys::__debugList.emplace_back(&this->__attkLine);
  }
}

inline func Char_M::Weapon::Pistol::setTexture(void) -> void {
  this->__s.setTexture(this->__t[this->__img_code
    + ((this->__s.getRotation() <= 270.0f
     && this->__s.getRotation() >= 90.0f) ? 2 : 0)], true);
  this->__s.setOrigin(sf::Fm::getSize(Char_M::Duck::__v->__s).x   / -2.0f,
                          this->__t[this->__img_code].getSize().y /  2.0f);
}

inline func Char_M::Weapon::Pistol::attValid(Char_M::Enemy* v, bool __isBoss) -> void {
  if(__isBoss) ; // ChickBoss::hurt(this->attCast());
  else v->hurt(this->attCast() * Char_M::Element::attCast(Char_M::Duck::__v->__element, v->__element),
               this->__attk_bullet->second * 0.06f);
  
  this->__attk_bullet->second = {};
  this->__attk_bullet = nullptr;
}

inline func Char_M::Weapon::Pistol::attCheck(void) -> void {
  if(this->__attkClock.getElapsedTime().asSeconds() > (Char_M::Skill::__bulletTime ? 0.2f : (this->__cd / Char_M::Value::__attack_speed_r_f))) {
     this->__attkClock.restart(); this->__img_code = true;
     __AUDIO__CHECK_SOUND__(pistol);
     ++Char_M::Value::__total_attk;
     
     this->__bullet.emplace_back(std::make_pair<sf::VertexArray,
       sf::Vector2f>(sf::VertexArray{sf::PrimitiveType::Lines, 2},
       this->__attkLine[1].position - this->__attkLine[0].position));
     this->__bullet.back().first[0].position = this->__attkLine[0].position;
     this->__bullet.back().first[1].position = this->__attkLine[0].position
      + 0.5f * (this->__attkLine[1].position - this->__attkLine[0].position);
     this->__bullet.back().first[0].color = sf::Color::Yellow;
     this->__bullet.back().first[1].color = sf::Color::Red;
     
  } else if(this->__attkClock.getElapsedTime().asSeconds() > 0.1f
    && this->__img_code) this->__img_code = false;
}

Char_M::Weapon::Pistol::Pistol(void) {
  this->initData("pistol");

  this->__i.resize(4);
  this->__i[0].loadFromFile("./src/res/img/duck/weapon/pistol/default/_N.png");
  this->__i[1].loadFromFile("./src/res/img/duck/weapon/pistol/default/_Y.png");
  this->__i[2].loadFromFile("./src/res/img/duck/weapon/pistol/default/_N.png");
  this->__i[3].loadFromFile("./src/res/img/duck/weapon/pistol/default/_Y.png");
  this->__i[2].flipVertically();
  this->__i[3].flipVertically();
  
  this->__t.resize(4);
  this->__t[0].loadFromImage(this->__i[0]);
  this->__t[1].loadFromImage(this->__i[1]);
  this->__t[2].loadFromImage(this->__i[2]);
  this->__t[3].loadFromImage(this->__i[3]);
  
  this->__t[0].setSmooth(sys::__smoothTex);
  this->__t[1].setSmooth(sys::__smoothTex);
  this->__t[2].setSmooth(sys::__smoothTex);
  this->__t[3].setSmooth(sys::__smoothTex);
  
  this->setTexture();
  this->__s.setScale({0.45, 0.45});
  
  this->__attkLine[0].color = sf::Color::Blue;
  this->__attkLine[1].color = sf::Color::Blue;
}
