inline func Char_M::Enemy::ShellPig::adaptRect(void) -> void {
  this->__realRect = this->__s.getGlobalBounds()
                   + sf::FloatRect{40, 100, -70, -155};
}

inline func Char_M::Enemy::ShellPig::checkDrop(void) -> void {
  if(this->__nodrop) { this->__cast_exp = 0; return; }

  if(this->__cast_exp) {
    int __randint{sys::rand<int>({0, 1000})};
    Storage_M::__buf.push(sis::Item::Coin,
      static_cast<size_t>(__randint % 6 + 1));
         if(__randint >=   0 && __randint < 250) { // 25%
            __SEND_ITEM__(sis::Item::Shell, 1);
    }
    else if(__randint >= 250 && __randint < 320) { // 7%
            __SEND_ITEM__(sis::Item::PigFeet, 1);
    }
    else if(__randint >= 320 && __randint < 322) { // 0.2%
            __SEND_ITEM__(sis::Item::ShellPig_token, 1);
    }
  } Char_M::Enemy::checkDrop();
}

inline func Char_M::Enemy::ShellPig::del(void) -> void {
  if(this->__cast_exp) {
    this->checkDrop(); ++Char_M::data.killedNum.__ordi;
  } this->Enemy::del();
}

inline func Char_M::Enemy::ShellPig::act(void) -> void {
  this->moveToDuck(); // 移动
  if(this->__exmove == sf::Vector2f{}) {
    if(this->__realRect.intersects(Char_M::Duck::__v->__realRect)) { // 攻击
      if(Char_M::Duck::__v->__last.getElapsedTime().asSeconds() >= 1) {
        this->__attkc.restart();
        Char_M::Duck::__v->__last.restart();
        Char_M::Duck::__v->__repel
        = this->__move * 5.0f;
        Char_M::Value::effect.__blood -= this->__attack;
        
        if(Char_M::Value::__thorns_f != 1.0f)
          this->hurt(std::ceil(this->__attack * (Char_M::Value::__thorns_f - 1.0f)));
      }
    }
         this->setTexture(); // 贴图
  } else this->del();
  // 绘制
  this->pushList();
}

Char_M::Enemy::ShellPig::ShellPig(void) {
  this->initData("shellPig");
  
  ++Char_M::data.enemyNum.__shellPig;
  
  this->__s.setTexture(*res::enemy::__t_shellPig[0][this->__img_code]);
  this->__s.scale({0.4, 0.4});
  
  this->__trackBox.getBase().setFillColor(sf::Color::Transparent);
  this->__trackBox.getBase().setOutlineColor(sf::Color::Red);
  this->__trackBox.getBase().setOutlineThickness(1);
  
  this->__trackLine[0].color = sf::Color::Red;
  this->__trackLine[1].color = sf::Color::Yellow;
  
  this->initPos();
}
