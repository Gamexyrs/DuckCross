inline func Char_M::Enemy::ChickEgg::adaptRect(void) -> void {
  this->__realRect = this->__s.getGlobalBounds()
                   + sf::FloatRect{20, 60, -40, -60};
}

inline func Char_M::Enemy::ChickEgg::del(void) -> void {
  if(this->__s.getColor().a > 0) {
     this->__s.setColor(
        this->__s.getColor()
     | (this->__s.getColor().a - 5));
  } else Char_M::Enemy::__signal_call_del = true;
}

inline func Char_M::Enemy::ChickEgg::act(void) -> void {
  if(this->__exmove != sf::Vector2f{})
     this->del();
  else if(this->__hatch_clock.getTime().asSeconds() >= 2.0f) {
      if(Char_M::Enemy::CreatePool::valid(__ECODE_CHICK__))
         Char_M::Enemy::Alloter::__active.emplace_back(Char_M::Enemy::CreatePool::move());
    else Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::Chick>()));
    Char_M::Enemy::Alloter::__active.back()->__s.setPosition(this->__s.getPosition());
    Char_M::Enemy::__signal_call_del = true;
  }
  
  this->adaptRect();
  this->pushList();
}

Char_M::Enemy::ChickEgg::ChickEgg(void) {
  this->initData("chickEgg");
  
  this->__s.setTexture(*res::enemy::__t_chickEgg);
  this->__s.scale({0.2, 0.2});
  
  this->__trackBox.getBase().setFillColor(sf::Color::Transparent);
  this->__trackBox.getBase().setOutlineColor(sf::Color::Blue);
  this->__trackBox.getBase().setOutlineThickness(1);
  
  this->__trackLine[0].color = sf::Color::Blue;
  this->__trackLine[1].color = sf::Color::Yellow;
  
  this->__movable = false;
}
