inline func ChickBoss::start(void) -> void {
  if(Char_M::Duck::__v->noBlood() || Char_M::Skill::__bulletTime || sf::Msgable::getLocked()) return;

  // search target
  for(auto& i : Char_M::Enemy::Alloter::__active) if(!i->__inview && i->__enemy_code == __ECODE_CHICK__) {
    // make camera_move_path
    const auto& __path{sf::MoveMethod::linear_down(ui_m->__view.getCenter(), (ChickBoss::__scaleCenter = sf::Fm::getCenter(i->__s)), {}, 400)};
    for(const auto& j : __path)
      ui_m->__cameraMovePath.push(j);

    ChickBoss::__proceed = ChickBossState::Ani_Move_to;
    ChickBoss::__this = std::move(i); break;
  }
}

inline func ChickBoss::startInit(void) -> void {
  ChickBoss::__flashHint = std::make_unique<sf::Div>();
  ChickBoss::__flashHint->setOutlineThickness(0);
  ChickBoss::__flashHint->setSize({200, 200});
  ChickBoss::__flashHint->setRadius(-1);
  ChickBoss::__flashHint->setTag<int>(0);
  ChickBoss::__flashHint->setFillColor(sf::ColorEx::Grey | 0);
  
  ChickBoss::__name = std::make_unique<sf::TextDiv>();
  ChickBoss::__name->setBuilder(ui_m->__viewpos);
  ChickBoss::__name->setSize({100, 80});
  ChickBoss::__name->setFillColor(sf::Color::Transparent);
  ChickBoss::__name->setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
  ChickBoss::__name->getText().setStyle(sf::Text::Style::Bold);
  ChickBoss::__name->setText(L"—— 鸡霸 ——", res::__font_ac, 60);
  ChickBoss::__name->setTextAlign(sf::Align::C);
  ChickBoss::__name->setOutlineThickness(0);
  ChickBoss::__name->align(sf::Align::T);
  
  ChickBoss::__blood_prog = std::make_unique<sf::ProgressDiv>();
  ChickBoss::__blood_prog->setBuilder(ui_m->__viewpos);
  ChickBoss::__blood_prog->setPerHeight("8%");
  ChickBoss::__blood_prog->setPerWidth("25%");
  ChickBoss::__blood_prog->getInside().setFillColor(sf::Color::Red);
  ChickBoss::__blood_prog->setFillColor(sf::ColorEx::LightPink | 70);
  ChickBoss::__blood_prog->getText().setStyle(sf::Text::Style::Bold | sf::Text::Style::Italic);
  ChickBoss::__blood_prog->setText(L"×1", res::__font_en, 80);
  ChickBoss::__blood_prog->setTextAlign(sf::Align::R);
  ChickBoss::__blood_prog->setTextDeviat({-30, -14});
  ChickBoss::__blood_prog->setOutlineThickness(2);
  ChickBoss::__blood_prog->setBusyRunning(false);
  ChickBoss::__blood_prog->setTag<int>(1);
  ChickBoss::__blood_prog->setProgress(0);
  ChickBoss::__blood_prog->setRadius(5);
  ChickBoss::__blood_prog->align(sf::Align::T) += {0, 80};
  
  ChickBoss::__defence_div = std::make_unique<sf::Div>();
  ChickBoss::__defence_div->setBuilder(*ChickBoss::__blood_prog, sf::Vector2f{0, 10}, sf::Vector2b{false, true});
  ChickBoss::__defence_div->setSize({ChickBoss::__blood_prog->getSize().x, 10});
  ChickBoss::__defence_div->setFillColor(sf::ColorEx::SkyBlue | 0);
  ChickBoss::__defence_div->setOutlineThickness(0);
  ChickBoss::__defence_div->setRadius(2);
  
  ChickBoss::__BLOOD_LAYERS_COLOR__ = {
 // sf::Color::Red,          // 1a
    sf::Color::Magenta,      // 2a
    sf::ColorEx::Orange,     // 3a
    sf::Color::Yellow,       // 4a
    sf::ColorEx::LightGreen, // 5a
    sf::Color::Cyan,         // 6a
    sf::ColorEx::Pink,       // 7a
    sf::ColorEx::LightBlue,  // 8a -> 400hp
    sf::Color::Red,          // 1b
    sf::ColorEx::LightBlue,  // 2b
    sf::ColorEx::Orange,     // 3b
    sf::Color::Yellow,       // 4b
    sf::ColorEx::LightGreen, // 5b
    sf::Color::Cyan,         // 6b
    sf::ColorEx::Pink,       // 7b
 // sf::Color::Red,          // 8b -> 800hp
  };
  // random_sort
  do {
  std::shuffle(ChickBoss::__BLOOD_LAYERS_COLOR__.begin(),
               ChickBoss::__BLOOD_LAYERS_COLOR__.end(), sys::__rander);
  } while(std::adjacent_find(
       ChickBoss::__BLOOD_LAYERS_COLOR__.begin(),
       ChickBoss::__BLOOD_LAYERS_COLOR__.end())
    != ChickBoss::__BLOOD_LAYERS_COLOR__.end());
  ChickBoss::__BLOOD_LAYERS_COLOR__.emplace_front(sf::Color::Red);
  ChickBoss::__BLOOD_LAYERS_COLOR__.emplace_back(sf::Color::Red);
  
  ChickBoss::initData();
}

//>>>

inline func ChickBoss::moveToDuck(void) -> void {
  // 正常
  if(ChickBoss::__boss_living) {
    // 移动
    if(ChickBoss::__this->__hinderWith != nullptr) {
      if(std::fabs(ChickBoss::__this->__move.x) < 1.6
      && std::fabs(ChickBoss::__this->__move.y) < 1.6) {
        ChickBoss::__this->__hinderWith = nullptr;
      } else {
        if(std::fabs(ChickBoss::__this->__move.x) > 1.6) {
          if(ChickBoss::__this->__move.x > 0)
            ChickBoss::__this->__move.x -= 0.5 / sys::tickSync();
          else
            ChickBoss::__this->__move.x += 0.5 / sys::tickSync();
        }
        if(std::fabs(ChickBoss::__this->__move.y) > 1.6) {
          if(ChickBoss::__this->__move.y > 0)
            ChickBoss::__this->__move.y -= 0.5 / sys::tickSync();
          else
            ChickBoss::__this->__move.y += 0.5 / sys::tickSync();
        }
      }
    } else {
      sf::Vector2f tmp_v{sf::Fm::getCenter(Char_M::Duck::__v->__realRect)},
                   tmp_c{sf::Fm::getCenter(ChickBoss::__this->__realRect)};
      float tmpv_atan
        {std::atan((tmp_c.y - tmp_v.y)
                 / (tmp_c.x - tmp_v.x))};
      ChickBoss::__this->__move = sf::Vector2f{std::cos(tmpv_atan), std::sin(tmpv_atan)}
        * ((tmp_c.x < tmp_v.x) ? ChickBoss::__this->__speed_f : -ChickBoss::__this->__speed_f)
        * (1.0f + std::min(static_cast<int>(Char_M::Value::__level), 14) * 0.04f);
    }
    
    // 阻碍
    if(ChickBoss::__this->__hinderWith == nullptr
    && ChickBoss::__this->__inview
    && ChickBoss::__this->__ghost.getElapsedTime().asSeconds() > 1.5) {
      sf::Vector2f __powerPoint{};
      if(std::fabs(ChickBoss::__this->__move.x) < 1.2) {
        if(ChickBoss::__this->__move.y > 0)
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::B);
        else
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::T);
      } else if(ChickBoss::__this->__img_code < 3) {
        if(std::fabs(ChickBoss::__this->__move.x)
         - std::fabs(ChickBoss::__this->__move.y) > 0)
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::L);
        else if(ChickBoss::__this->__move.y > 0)
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::LB);
        else
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::LT);
      } else {
        if(std::fabs(ChickBoss::__this->__move.x)
         - std::fabs(ChickBoss::__this->__move.y) > 0)
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::R);
        else if(ChickBoss::__this->__move.y > 0)
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::RB);
        else
          __powerPoint = sf::align({}, ChickBoss::__this->__realRect, sf::Align::RT);
      }
      for(auto& i : Char_M::Enemy::Alloter::__active) {
        if(i.operator bool() && i->__movable && i->__realRect.contains(__powerPoint)) {
          (ChickBoss::__this->__hinderWith = i.get())->__s.move(sys::movtionSync(i->__move * 0.4f) * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f));
          break;
        }
      }
    }
  }
  
  ChickBoss::__this->__s.move(sys::movtionSync(
                          Map_M::mathsObsPath(
                          Map_M::mathsObsSide(ChickBoss::__this->__realRect), ChickBoss::__this->__move))
                      * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f));
}

inline func ChickBoss::setTexture(void) -> void {
  ChickBoss::__this->setTexture();
  
  // 遮挡
  if((ChickBoss::__this->__s.getGlobalBounds() + sf::FloatRect{170, 160, -340, -360})
       .intersects(Char_M::Duck::__v->__s.getGlobalBounds()))
       ChickBoss::__this->__s.setColor(ChickBoss::__this->__s.getColor() | 100);
  else ChickBoss::__this->__s.setColor(ChickBoss::__this->__s.getColor() | 255);
}

inline func ChickBoss::adaptRect(void) -> void {
  ChickBoss::__this->__realRect = ChickBoss::__this->__s.getGlobalBounds() + sf::FloatRect{160, 360, -340, -460};
}

inline func ChickBoss::pushList(void) -> void {
  if(!ChickBoss::__this.operator bool()) return;

  if((ChickBoss::__this->__inview = ChickBoss::__this->__s.getGlobalBounds().intersects(sf::Renderable::getViewRect()))) {
      ChickBoss::__this->__out_of_screen_clock.restart();
    Char_M::__drawList.emplace_back(
      std::make_pair<const sf::Vector2f&, sf::Drawable*>(
        sf::align({}, ChickBoss::__this->__s.getGlobalBounds(), sf::Align::B) - sf::Vector2f{0, 40}, &ChickBoss::__this->__s));
  }
  
  if(ChickBoss::__defence_div.operator bool()
  && ChickBoss::__defence_div->getFillColor().a > 0)
     ChickBoss::__defence_div->setFillColor(
        ChickBoss::__defence_div->getFillColor()
     | (ChickBoss::__defence_div->getFillColor().a - 3));
  
  // Debug
  ChickBoss::__this->__trackBox.setRect(ChickBoss::__this->__realRect);
  ChickBoss::__this->__trackLine[0].position = sf::Fm::getCenter(Char_M::Duck::__v->__realRect);
  ChickBoss::__this->__trackLine[1].position = sf::Fm::getCenter(ChickBoss::__this->__realRect);
  if(sys::__dataMode) {
     sys::__debugList.emplace_back(&ChickBoss::__this->__trackLine);
     sys::__debugList.emplace_back(&ChickBoss::__this->__trackBox);
  }
}

inline func ChickBoss::initData(void) -> void {
  ChickBoss::__this->__cast_blood = ChickBoss::__BLOOD_LAYERS_COLOR__.size() * 50;
  ChickBoss::__this->__s.setScale({1.2f, 1.2f});
  ChickBoss::__this->__speed_f = 3.4f;
  ChickBoss::__this->__nodrop = true;
  ChickBoss::__this->__attack = 16;
}

inline func ChickBoss::hurt(int _bl) -> void {
  ChickBoss::__this->__cast_blood -= _bl;
  Char_M::Value::effect.__food += 35;
  
  Char_M::Value::__total_attkV += _bl;
++Char_M::Value::__total_hit;

  // 受击效果
  ChickBoss::__this->__s.setColor(sf::Color{255, 126, 126});
}

//>>>

inline func ChickBoss::update(void) -> void {
       if(ChickBoss::__boss_died) return;
  else if(!static_cast<int>(ChickBoss::__proceed)) { if(Char_M::Value::__level >= 14 || Arc_M::__playTime.asSeconds() >= (60 * 8)) ChickBoss::start(); }
  else if( static_cast<int>(ChickBoss::__proceed) < 10) ChickBoss::ani_update();
  else if( static_cast<int>(ChickBoss::__proceed) < 20) ChickBoss::live_update();
  else if( static_cast<int>(ChickBoss::__proceed) < 30) ChickBoss::beatAni_update();
  else return;
  
  ChickBoss::pushList();
}

//>>>

inline func ChickBoss::ani_update(void) -> void {
  static sf::Clock __flashTickClock{};
  static size_t __flashTick{0};

  ui_m->__cameraOnceUnlock = true;
  Control_M::__once_hide = true;
  sf::Msgable::setLocked(true);
  
  if(ChickBoss::__proceed == ChickBossState::Ani_Move_to) {
    if(ui_m->__cameraMovePath.empty())
      ChickBoss::__proceed = ChickBossState::Ani_Scale;
  }
  
  else if(ChickBoss::__proceed == ChickBossState::Ani_Scale) {
    if(ChickBoss::__this->__s.getScale().x < 1.2f) {
       ChickBoss::__this->__s.setScale({ChickBoss::__this->__s.getScale().x + 0.005f,
                                        ChickBoss::__this->__s.getScale().y + 0.005f});
       ChickBoss::__this->__s.move(ChickBoss::__scaleCenter - sf::Fm::getCenter(ChickBoss::__this->__s));
    }
    else {
       ChickBoss::__proceed = ChickBossState::Ani_Blood;
       ChickBoss::startInit();
       
       Char_M::Explode::make_boss(ChickBoss::__scaleCenter);
       __flashTickClock.restart();
       __flashTick = 0;
    }
  }
  
  else if(ChickBoss::__proceed == ChickBossState::Ani_Blood) {
    // 闪屏
    if(__flashTick <= 3 && __flashTickClock.getElapsedTime().asSeconds() >= 0.11f) {
      ui_m->flashScreen(); __flashTickClock.restart();
      
      if(__flashTick++ == 3) __AUDIO__CHECK_SOUND__(levelup);
    }
    
    // 血条
    if(__flashTick > 3) {
      if(ChickBoss::__blood_prog->getProgress() < 1)
         ChickBoss::__blood_prog->movProgress(0.1f);
      else if(ChickBoss::__blood_prog->getTag<int>() == static_cast<int>(ChickBoss::__BLOOD_LAYERS_COLOR__.size())) {
         ChickBoss::__proceed = ChickBossState::Ani_Move_back;
         // make camera_move_path
         const auto& __path{sf::MoveMethod::linear_down(ChickBoss::__scaleCenter, sf::Fm::getCenter(Char_M::Duck::__v->__s), {}, 400)};
         for(const auto& j : __path)
           ui_m->__cameraMovePath.push(j);
      }
      else {
         ChickBoss::__blood_prog->setProgress(0);
         ChickBoss::__blood_prog->setTag<int>(ChickBoss::__blood_prog->getTag<int>() + 1);
         ChickBoss::__blood_prog->setFillColor(ChickBoss::__blood_prog->getInside().getFillColor());
         ChickBoss::__blood_prog->setTextString(L"×" + std::to_wstring(ChickBoss::__blood_prog->getTag<int>()));
         ChickBoss::__blood_prog->getInside().setFillColor(ChickBoss::__BLOOD_LAYERS_COLOR__[ChickBoss::__blood_prog->getTag<int>() - 1]);
      }
    }
  }
  
  else if(ChickBoss::__proceed == ChickBossState::Ani_Move_back) {
    if(ui_m->__cameraMovePath.empty()) {
      ChickBoss::__this->__out_of_screen_clock.restart();
      ChickBoss::__proceed = ChickBossState::Live;
      ChickBoss::__boss_living = true;
      sf::Msgable::setLocked(false);
    }
  }
}

inline func ChickBoss::beatAni_update(void) -> void {
  ui_m->__cameraOnceUnlock = true;
  Control_M::__once_hide = true;
  sf::Msgable::setLocked(true);
  
  if(ChickBoss::__proceed == ChickBossState::BeatAni_Move_to) {
    if(ui_m->__cameraMovePath.empty())
      ChickBoss::__proceed = ChickBossState::BeatAni_Fade;
  }
  
  else if(ChickBoss::__proceed == ChickBossState::BeatAni_Fade) {
    if(ChickBoss::__this->__s.getColor().a > 0) {
       ChickBoss::__this->__s.setColor(
          ChickBoss::__this->__s.getColor()
       | (ChickBoss::__this->__s.getColor().a - 3));
    }
    else {
       ChickBoss::__proceed = ChickBossState::BeatAni_Move_back;
       // make camera_move_path
       const auto& __path{sf::MoveMethod::linear_down(ui_m->__view.getCenter(), sf::Fm::getCenter(Char_M::Duck::__v->__s), {}, 400)};
       for(const auto& j : __path) {
         ui_m->__cameraMovePath.push(j);
       } ui_m->flashScreen(); __AUDIO__CHECK_SOUND__(levelup);
    }
  }
  
  else if(ChickBoss::__proceed == ChickBossState::BeatAni_Move_back) {
    if(ui_m->__cameraMovePath.empty()) {
      ChickBoss::__proceed = ChickBossState::None;
      ChickBoss::__boss_died = true;
      ChickBoss::__this.release();
      sf::Msgable::setLocked(false);
    }
  }
}

//>>>

inline func ChickBoss::live_update(void) -> void {
  // 状态机
         if(sf::Msgable::getLocked()) return;
    else if(ChickBoss::__proceed == ChickBossState::Live) {
     ChickBoss::live_proceed_update();
     ChickBoss::moveToDuck(); // 移动
  
  } else if(ChickBoss::__proceed == ChickBossState::Ready_to_rush) {
    if(ChickBoss::__rushClock.getElapsedTime().asSeconds() >= 1.0f)
       ChickBoss::__proceed = ChickBossState::Rushing;
    
  } else if(ChickBoss::__proceed == ChickBossState::Rushing) {
    if(!ChickBoss::__this->__inview || ChickBoss::__rushTowards == sf::Vector2f{}) {
      ChickBoss::__proceed = ChickBossState::Live;
      ChickBoss::__rushTowards = {};
    } else {
      ChickBoss::live_putEnemy_update(false);
      ChickBoss::__this->__s.move(sys::movtionSync(ChickBoss::__rushTowards)
                               * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f));
    }
  } else if(ChickBoss::__proceed == ChickBossState::Ready_to_flash) {
    if(ChickBoss::__flashHint->getFillColor().a < 80)
       ChickBoss::__flashHint->setFillColor(
         ChickBoss::__flashHint->getFillColor()
      | (ChickBoss::__flashHint->getFillColor().a + 2));
    else ChickBoss::__proceed = ChickBossState::Flashing;
    
  } else if(ChickBoss::__proceed == ChickBossState::Flashing) {
    if(sf::align({}, ChickBoss::__this->__s.getGlobalBounds(), sf::Align::B).y - 40
    < ChickBoss::__flashHint->getCenter().y)
      ChickBoss::__this->__s.move(sys::movtionSync({0, 30})
                         * (Char_M::Skill::__bulletTime ? 0.02f : 1.0f));
    else {
      ChickBoss::__flashHint->setFillColor(ChickBoss::__flashHint->getFillColor() | 0);
      ChickBoss::__proceed = ChickBossState::Live;
      ChickBoss::live_putEnemy_update(true);
    }
  } else ChickBoss::__proceed = ChickBossState::Live;
  
  // 受击效果恢复
  const sf::Color __color{ChickBoss::__this->__s.getColor()};
  if(__color.r < 255 || __color.g < 255 || __color.b < 255) {
    ChickBoss::__this->__s.setColor(sf::Color{
      static_cast<sf::Uint8>(std::min(static_cast<int>(__color.r) + 3, 255)),
      static_cast<sf::Uint8>(std::min(static_cast<int>(__color.g) + 3, 255)),
      static_cast<sf::Uint8>(std::min(static_cast<int>(__color.b) + 3, 255))
    });
  }
  
  // 血条移动
       if(ChickBoss::__blood_prog->getProgress() > 0
     && ((ChickBoss::__this->__cast_blood % 50
     &&   ChickBoss::__blood_prog->getProgress() - static_cast<float>(ChickBoss::__this->__cast_blood % 50) / 50.0f > 0.02f)
     ||   ChickBoss::__this->__cast_blood <= (ChickBoss::__blood_prog->getTag<int>() - 1) * 50))
          ChickBoss::__blood_prog->movProgress(-0.02f / sys::tickSync());
  else if(ChickBoss::__blood_prog->getProgress() <= 0) {
          ChickBoss::__blood_prog->setTag<int>(ChickBoss::__blood_prog->getTag<int>() - 1);
    // 击败
    if(ChickBoss::__blood_prog->getTag<int>() <= 0) {
       // make camera_move_path
       const auto& __path{sf::MoveMethod::linear_down(ui_m->__view.getCenter(), sf::Fm::getCenter(ChickBoss::__this->__s), {}, 400)};
       for(const auto& j : __path)
         ui_m->__cameraMovePath.push(j);
       ChickBoss::__proceed = ChickBossState::BeatAni_Move_to;
       ChickBoss::__blood_prog->setBusyRunning(true);
       ChickBoss::__blood_prog->setTextString(L"");
       ChickBoss::__boss_living = false;
       __ACC_UPDATE__(++Acc_M::__enemy_data.find("kill_chickBoss")->second);
    } else {
       ChickBoss::__blood_prog->setProgress(1);
       ChickBoss::__blood_prog->getInside().setFillColor(ChickBoss::__blood_prog->getFillColor());
       ChickBoss::__blood_prog->setTextString(L"×" + std::to_wstring(ChickBoss::__blood_prog->getTag<int>()));
       if(ChickBoss::__blood_prog->getTag<int>() >= 2)
          ChickBoss::__blood_prog->setFillColor(ChickBoss::__BLOOD_LAYERS_COLOR__[ChickBoss::__blood_prog->getTag<int>() - 2]);
       else
          ChickBoss::__blood_prog->setFillColor(sf::ColorEx::LightPink | 70);
    }
  }
  
  if(ChickBoss::__boss_living) {
    // 攻击
    if(ChickBoss::__proceed != ChickBossState::Flashing
    && ChickBoss::__this->__realRect.intersects(Char_M::Duck::__v->__realRect)) {
      if(Char_M::Duck::__v->__last.getElapsedTime().asSeconds() >= 1) {
        ChickBoss::__this->__attkc.restart();
        Char_M::Duck::__v->__last.restart();
        Char_M::Duck::__v->__repel
        = ChickBoss::__this->__move * 4.0f;
        Char_M::Value::effect.__blood -= ChickBoss::__this->__attack;
        
        if(Char_M::Value::__thorns_f != 1.0f)
          ChickBoss::__this->hurt(std::ceil(ChickBoss::__this->__attack * (Char_M::Value::__thorns_f - 1.0f)));
      }
    }
    
    ChickBoss::setTexture();
    
    // 受击
    if(Char_M::Weapon::__signal_call_att) {
       const int __tmp_bl{ChickBoss::__this->__cast_blood};
       Char_M::Weapon::__v->attValid(ChickBoss::__this.get(), true);
       if(__tmp_bl != ChickBoss::__this->__cast_blood) {
         AttackDisplay_M::call(std::to_wstring(__tmp_bl - ChickBoss::__this->__cast_blood), Char_M::Weapon::__v->__attkLine[1].position);
         if(Char_M::Weapon::__signal_crit)
           AttackDisplay_M::call(L"暴击");
       }
    }
    for(auto& j : Char_M::Weapon::__bullet) {
      if(j.first.getBounds().intersects(ChickBoss::__this->__realRect)) {
        AttackDisplay_M::call(L"无效", j.first[1].position, sf::ColorEx::LightBlue);
        Char_M::Weapon::__v->__attk_bullet = &j; // Ban_remote_attack
        Char_M::Weapon::__v->attValid(ChickBoss::__this.get(), true);
        ChickBoss::__this->__s.setColor(sf::ColorEx::SkyBlue);
        ChickBoss::__defence_div->setFillColor(
        ChickBoss::__defence_div->getFillColor() | 255);
        break;
      }
    }
  }
  
  ChickBoss::adaptRect();
}

inline func ChickBoss::live_proceed_update(void) -> void {
  // 闪现
  if(ChickBoss::__this->__out_of_screen_clock.getElapsedTime().asSeconds() >= 3) {
     ChickBoss::__this->__out_of_screen_clock.restart();
     ChickBoss::__flashHint->setCenter(sf::Fm::getCenter(Char_M::Duck::__v->__realRect)
          + 10.0f * sys::movtionSync(Control_M::__move_move * Char_M::Value::__speed_f) /* predict_move */);
     ChickBoss::__this->__s.setPosition({ChickBoss::__flashHint->getCenter().x
     - sf::Fm::getSize(ChickBoss::__this->__s.getGlobalBounds()).x / 2.0f,
       sf::Renderable::getViewRect().top - 50.0f
     - sf::Fm::getSize(ChickBoss::__this->__s.getGlobalBounds()).y});
     ChickBoss::__proceed = ChickBossState::Ready_to_flash;
     return;
  }
  
  // 冲撞
  if(ChickBoss::__rushClock.getElapsedTime().asSeconds() >= 3.8f) {
     ChickBoss::__rushClock.restart();
     
    if(sys::rand<int>({1, 100}) <= 26) {
      sf::Vector2f tmp_v{sf::Fm::getCenter(Char_M::Duck::__v->__realRect)},
                   tmp_c{sf::Fm::getCenter(ChickBoss::__this->__realRect)};
      float tmpv_atan
        {std::atan((tmp_c.y - tmp_v.y)
                 / (tmp_c.x - tmp_v.x))};
      ChickBoss::__rushTowards = sf::Vector2f{std::cos(tmpv_atan), std::sin(tmpv_atan)}
        * ((tmp_c.x < tmp_v.x) ? ChickBoss::__this->__speed_f : -ChickBoss::__this->__speed_f)
        * (1.0f + std::min(static_cast<int>(Char_M::Value::__level), 14)) * 2.8f;
      ChickBoss::__proceed = ChickBossState::Ready_to_rush;
      return;
    }
  }
}

inline func ChickBoss::live_putEnemy_update(bool force) -> void {
  if(ChickBoss::__putEClock.getElapsedTime().asSeconds() >= (0.04f * (Char_M::Skill::__bulletTime ? 50.0f : 1.0f)) || force) {
     ChickBoss::__putEClock.restart();
    Char_M::Enemy::Alloter::__active.emplace_back(std::move(std::make_unique<Char_M::Enemy::ChickEgg>()));
    Char_M::Enemy::Alloter::__active.back()->__s.setPosition(sf::Fm::getCenter(ChickBoss::__this->__realRect));
  }
}
