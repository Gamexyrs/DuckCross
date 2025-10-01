inline func Char_M::Enemy::BombChick::setTexture(void) -> void {
  this->__img_code = (this->__img_code >= 3) ? 3 : 0;
  
  if(this->__attkc.getElapsedTime().asSeconds() >= 0.5) {
     this->__attkc.restart();
    if(!sf::Msgable::getLocked()) {
    ++this->__kindlingTick;
      this->__s.setTexture(*res::enemy::__t_bombChick[(this->__attking = !this->__attking)][this->__img_code]);
    }
  } if(this->__kindlingTick >= 4
    && this->__bombState != BombState::Exploded) {
       this->__bombState  = BombState::Exploded; this->del(); __AUDIO__CHECK_SOUND__(kill);
       Char_M::Explode::make(sf::Fm::getCenter(this->__realRect));
  }
}

inline func Char_M::Enemy::BombChick::adaptRect(void) -> void {
  this->__realRect = this->__s.getGlobalBounds()
                   + sf::FloatRect{20, 40, -40, -60};
}

inline func Char_M::Enemy::BombChick::checkDrop(void) -> void {
  if(this->__nodrop) { this->__cast_exp = 0; return; }
  
  if(this->__cast_exp) {
    int __randint{sys::rand<int>({0, 1000})};
    Storage_M::__buf.push(sis::Item::Coin,
      static_cast<size_t>(__randint % 5 + 1));
         if(__randint >=   0 && __randint < 300) { // 30%
            __SEND_ITEM__(sis::Item::Drumstick, 1);
    }
    else if(__randint >= 300 && __randint < 400) { // 10%
            __SEND_ITEM__(sis::Item::ChickWing, 1);
    }
    else if(__randint >= 400 && __randint < 402) { // 0.2%
            __SEND_ITEM__(sis::Item::BombChick_token, 1);
    }
  } Char_M::Enemy::checkDrop();
}

inline func Char_M::Enemy::BombChick::del(void) -> void {
  if(this->__cast_exp) {
    this->checkDrop(); ++Char_M::data.killedNum.__ordi;
  } this->Enemy::del();
}

inline func Char_M::Enemy::BombChick::act(void) -> void {
  switch(this->__bombState) {
    case(BombState::None): {
      this->moveToDuck(); // 移动
      if(this->__realRect.intersects(Char_M::Duck::__v->__realRect)) // 引燃
         this->__bombState = BombState::Kindling;
      if(this->__exmove != sf::Vector2f{}) {
         this->__bombState = BombState::Defuse;
      }  this->Enemy::setTexture();
    } break;
    case(BombState::Kindling): {
      if(this->__exmove != sf::Vector2f{}) {
         this->__bombState = BombState::Defuse;
      }  this->setTexture();
    } break;
    case(BombState::Exploded): {
      this->__bombState = BombState::Defuse;
      this->__exmove =
        sf::geometry::parse_circle_point({._radius = 240, ._center = sf::Fm::getCenter(Char_M::Duck::__v->__realRect),
          ._allow_in = false}, sf::Fm::getCenter(this->__realRect)).v_LengthToCenter_Coordinates * 0.15f;
    } [[fallthrough]];
    case(BombState::Defuse): {
      this->moveToDuck();
      this->del();
    } break;
    default: break;
  }
  // 绘制
  this->pushList();
}

Char_M::Enemy::BombChick::BombChick(void) {
  this->initData("bombChick");
  
  ++Char_M::data.enemyNum.__bombChick;
  
  this->__s.setTexture(*res::enemy::__t_bombChick[0][this->__img_code]);
  this->__s.scale({0.2, 0.2});
  
  this->__trackBox.getBase().setFillColor(sf::Color::Transparent);
  this->__trackBox.getBase().setOutlineColor(sf::Color::Red);
  this->__trackBox.getBase().setOutlineThickness(1);
  
  this->__trackLine[0].color = sf::Color::Red;
  this->__trackLine[1].color = sf::Color::Yellow;
  
  this->initPos();
}
