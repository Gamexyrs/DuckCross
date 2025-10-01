inline func Char_M::Duck::noBlood(void) -> bool {
  return(!sys::__cheat___allow_duck_unlimited_blood__
      && (!Char_M::Value::__blood
      ||   Char_M::Value::__food <= 0));
}

inline func Char_M::Duck::act(void) -> void {
  // 移动
  if(!sf::Msgable::getLocked()) {

#ifndef __KF
    if((static_cast<int>(ChickBoss::__proceed) > 0
     && static_cast<int>(ChickBoss::__proceed) < 10)
     || static_cast<int>(ChickBoss::__proceed) > 20)
       ; else Char_M::Value::effect.__food -= (0.2f / sys::tickSync()) * Char_M::Value::__food_f * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f);
#endif
    
    // 摇杆
    if(std::fabs(this->__repel.x) < 2
    && std::fabs(this->__repel.y) < 2) {
      this->__repel = {};
      switch(sys::__cheat___allow_duck_through_obstacles__
           ? sf::Align::C : Map_M::mathsObsSide(this->__realRect)) {
        case(sf::Align::L): {
          this->__s.move(sys::movtionSync(sf::Vector2f((Control_M::__move_move.x < 0)
            ? Control_M::__move_move.x : 0, Control_M::__move_move.y) * Char_M::Value::__speed_f));
        } break;
        case(sf::Align::R): {
          this->__s.move(sys::movtionSync(sf::Vector2f((Control_M::__move_move.x > 0)
            ? Control_M::__move_move.x : 0, Control_M::__move_move.y) * Char_M::Value::__speed_f));
        } break;
        case(sf::Align::T): {
          this->__s.move(sys::movtionSync(sf::Vector2f(Control_M::__move_move.x, (Control_M::__move_move.y < 0)
            ? Control_M::__move_move.y : 0) * Char_M::Value::__speed_f));
        } break;
        case(sf::Align::B): {
          this->__s.move(sys::movtionSync(sf::Vector2f(Control_M::__move_move.x, (Control_M::__move_move.y > 0)
            ? Control_M::__move_move.y : 0) * Char_M::Value::__speed_f));
        } break;
        default: {
          this->__s.move(sys::movtionSync(Control_M::__move_move * Char_M::Value::__speed_f));
        } break;
      }
    // 被击退
    } else {
      if(std::fabs(this->__repel.x) > 2) {
        if(this->__repel.x > 0)
          this->__repel.x -= 0.5 / sys::tickSync();
        else
          this->__repel.x += 0.5 / sys::tickSync();
      }
      if(std::fabs(this->__repel.y) > 2) {
        if(this->__repel.y > 0)
          this->__repel.y -= 0.5 / sys::tickSync();
        else
          this->__repel.y += 0.5 / sys::tickSync();
      } this->__s.move(sys::movtionSync(Map_M::mathsObsPath(sys::__cheat___allow_duck_through_obstacles__
           ? sf::Align::C : Map_M::mathsObsSide(this->__realRect), this->__repel)));
    }
  }

  Char_M::Value::__total_move += sf::Fm::length(sys::movtionSync(Control_M::__move_move * Char_M::Value::__speed_f));

  this->__realRect = this->__s.getGlobalBounds()
                   + sf::FloatRect{76, 136, -145, -136};
  
  // 血量
  if(Char_M::Value::effect.__blood) {
    if(Char_M::Value::effect.__blood < 0) {
      AttackDisplay_M::call(std::to_wstring(Char_M::Value::effect.__blood), sf::Fm::getCenter(this->__realRect), sf::Color::Red);
      Char_M::Value::__blood
        += std::fmax(Char_M::Value::effect.__blood,
         - static_cast<int>(Char_M::Value::__blood));
    } else {
      AttackDisplay_M::call(std::to_wstring(Char_M::Value::effect.__blood), sf::Fm::getCenter(this->__realRect), sf::ColorEx::LightGreen);
      Char_M::Value::__total_cureV += Char_M::Value::effect.__blood;
      Char_M::Value::__blood
        = std::fmin(Char_M::Value::__blood + Char_M::Value::effect.__blood,
                    Char_M::Value::__blood_max);
    }
    Char_M::Value::effect.__blood = 0;
    Char_M::Value::__update_blood = true;
  }
  if(Char_M::Value::__blood > Char_M::Value::__blood_max)
     Char_M::Value::__blood = Char_M::Value::__blood_max;

  // 饱食
  if(Char_M::Value::effect.__food) {
    Char_M::Value::__food += Char_M::Value::effect.__food;
    Char_M::Value::effect.__food = 0;
  }
  if(Char_M::Value::__food > 100)
     Char_M::Value::__food = 100;
  if(Char_M::Value::__food < 0)
     Char_M::Value::__food = -1;

  // 等级
  if(Char_M::Value::effect.__exp) {
    Char_M::Value::__exp += Char_M::Value::effect.__exp * Char_M::Value::__exp_f;
                        Char_M::Value::effect.__exp = 0;
    unsigned tmp_exp{Char_M::mathsLevelExp(Char_M::Value::__level + 1)};
    if(Char_M::Value::__exp >= tmp_exp) {
       Char_M::Value::__exp -= tmp_exp;
     ++Char_M::Value::__level;
       Char_M::Value::__update_level = true;
       Char_M::Enemy::Alloter::__need_update = true;
      
      if(!this->noBlood()) Char_M::Value::effect.__blood += 30;
       
      __AUDIO__CHECK_SOUND__(levelup);
      
      if(Char_M::Value::__level == 6) {
        ui_m->bubble(L"新武器已解锁!");
        ui_m->bubble(L"新主动技能可使用!");
      }
      
    } Char_M::Value::__update_exp = true;
  }
  
  Char_M::__drawList.emplace_back(std::make_pair<const sf::Vector2f&, sf::Drawable*>(
    sf::align({}, this->__s.getGlobalBounds(), sf::Align::B), &this->__s));

  // Debug
  this->__trackBox.setRect(this->__realRect);
  if(sys::__dataMode && this->__trackBox.inView())
     sys::__debugList.emplace_back(&this->__trackBox);
}

Char_M::Duck::Duck(void) {
  this->__i[0].loadFromFile("./src/res/img/duck/default/_A.png");
  this->__i[1].loadFromFile("./src/res/img/duck/default/_R.png");
  this->__i[2].loadFromFile("./src/res/img/duck/default/_L.png");
  this->__i[3].loadFromFile("./src/res/img/duck/default/_A.png");
  this->__i[4].loadFromFile("./src/res/img/duck/default/_L.png");
  this->__i[5].loadFromFile("./src/res/img/duck/default/_R.png");
  this->__i[0].flipHorizontally();
  this->__i[1].flipHorizontally();
  this->__i[2].flipHorizontally();
  
  for(size_t i = 0; i < this->__t.size(); ++i) {
    this->__t[i].loadFromImage(this->__i[i]);
    this->__t[i].setSmooth(sys::__smoothTex);
  }
  
  this->__s.setTexture(this->__t[this->__img_code]);
  this->__s.scale({0.2, 0.2});
  
  this->__trackBox.setFillColor(sf::Color::Transparent);
  this->__trackBox.setOutlineColor(sf::Color::Blue);
  this->__trackBox.setOutlineThickness(1);
}
