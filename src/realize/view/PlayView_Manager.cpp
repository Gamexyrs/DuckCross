PlayView_M::PlayView_Manager(void) {
  this->__fps.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->__fps.setBuilder(ui_m->__viewpos);
  this->__fps.setTextColor(sf::Color::Green);
  this->__fps.align(sf::Align::TR) -= {400, 0};
  this->__fps.setText(L"FPS : --", res::__font_en);
  
  this->__con.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->__con.setBuilder(ui_m->__viewpos);
  this->__con.setTextColor(sf::Color::Blue);
  this->__con.align(sf::Align::LT) += {750, 0};
  this->__con.setFont(res::__font_en);
  
  this->__time.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->__time.setBuilder(this->__con,
    sf::Vector2f{50, 0}, sf::Vector2b(true, false));
  this->__time.setText(L"[Time: -- s]", res::__font_en);
  this->__time.setTextColor(sf::Color::Blue);
  
  this->__settings.getBase().setTexture(res::ui::__settings.get());
  this->__settings.getBase().setOutlineThickness(0);
  this->__settings.setBuilder(ui_m->__viewpos);
  this->__settings.align(sf::Align::TR)
  -= rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["View_Settings"]);
  
  this->__pause.getBase().setTexture(res::ui::__pause.get());
  this->__pause.getBase().setOutlineThickness(0);
  this->__pause.setBuilder(ui_m->__viewpos);
  this->__pause.align(sf::Align::TL)
  += rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["View_Pause"]);
  
  this->__fighting_prog.setProgress(-1);
  this->__fighting_prog.setBusyRunning(true);
  this->__fighting_prog.setBusyRunSpeed(2.0f);
  this->__fighting_prog.getInside().setFillColor(sf::Color::Black | 120);
  this->__fighting_prog.setOutlineColor(sf::Color::Black | 120);
  this->__fighting_prog.setTextColor(sf::Color::Black | 120);
  this->__fighting_prog.setFillColor(sf::Color::Transparent);
  this->__fighting_prog.setText(L"敌方突袭中", res::__font);
  this->__fighting_prog.setTextAlign(sf::Align::T);
  this->__fighting_prog.setTextDeviat({0, -40});
  this->__fighting_prog.setBuilder(ui_m->__viewpos);
  this->__fighting_prog.align(sf::Align::BR) -= {50, 50};
  
  Char_M::Value::__update_blood = true;
  Char_M::Value::__update_exp   = true;

  this->Over_init();
  this->Pause_init();
  this->Level_init();
  this->Skill_init();
  this->Skill_actived_init();
  this->Blood_init();
  this->Food_init();
  this->Equip_init();
  this->MsgBox_init();
  this->Coin_init();
}

inline func PlayView_M::require_pause(bool require) -> void {
  sf::Msgable::setLocked(require);
  if(require) sf::Timer::all_stop();
         else sf::Timer::all_start_if_noZero();
}

inline func PlayView_M::update(void) -> void {
  static unsigned __flash{0};
  
  this->Over_act();
  this->Pause_act();
  this->Level_act();
  this->Skill_act();
  this->Skill_actived_act();
  this->Blood_act();
  this->Food_act();
  this->Equip_act();
  this->MsgBox_act();
  this->Coin_act();
  
  this->__signal_reload__ = false;
  
  if(sys::__dataMode) {
    this->__time.setTextString(L"[Time: "
    + std::to_wstring(static_cast<unsigned>(Arc_M::__playTime.asSeconds())) + L" s]");
    this->__con.setTextString(sf::Fm::toString(sf::Fm::getPosition(Char_M::Duck::__v->__realRect)));
    this->__con.resizeByText();
    sys::__debugList.emplace_back(&this->__con);
    sys::__debugList.emplace_back(&this->__time);
  }
  if(sys::__jcontext["Graphics"]["DisplayFPS"].GetBool()) {
         if(  __flash > 1e4 &&  (__flash =  0));
    else if(++__flash       && !(__flash % 30))
      this->__fps.setTextString(L"FPS : " + std::to_wstring(sys::__fps));
    sys::__debugList.emplace_back(&this->__fps);
  }
}

inline func PlayView_M::draw(void) -> void {
  if(Char_M::Duck::__v->noBlood())
    sf::Renderable::draw(this->over.__text,
                         this->over.__settle,
                         this->over.__reborn);
  sf::Renderable::draw(this->__fighting_prog);
  sf::Renderable::draw(this->eq.__box,
                       this->eq.__pic);
  sf::Renderable::draw(this->bl.__prog);
  
  if(static_cast<int>(ChickBoss::__proceed) >= 3
  && static_cast<int>(ChickBoss::__proceed) <= 21) {
    sf::Renderable::draw(*ChickBoss::__name);
    sf::Renderable::draw(*ChickBoss::__blood_prog);
    sf::Renderable::draw(*ChickBoss::__defence_div);
  }
  
  sf::Renderable::draw(this->fd.__prog,
                       this->fd.__pic);
  sf::Renderable::draw(this->lv.__prog,
                       this->lv.__text);
  if(Char_M::Value::__level < 6)
    sf::Renderable::draw(this->lv.__cheatlv6);
  if(Char_M::Value::__level < 14)
    sf::Renderable::draw(this->lv.__cheatboss);
  sf::Renderable::draw(this->__settings);
  sf::Renderable::draw(this->__pause);
  sf::Renderable::draw(this->__msgBox);
  this->MsgBoxText_act();
  for(auto& i : this->ska.__release)
    sf::Renderable::draw(i);
  for(auto& i : this->ska.__mask)
    sf::Renderable::draw(i);
  sf::Renderable::draw(this->ska.__prog);
  sf::Renderable::draw(this->sk.__mask);
  for(auto& i : this->sk.__skill_name)
    sf::Renderable::draw(i);
  for(auto& i : this->sk.__skill_attr)
    sf::Renderable::draw(i);
  sf::Renderable::draw(this->sk.__reject,
                       this->sk.__flash,
                       this->sk.__confirm);
  sf::Renderable::draw(this->co.__pic,
                       this->co.__num);
  sf::Renderable::draw(this->pause.__mask);
  if(this->__pausing) {
    sf::Renderable::draw(this->pause.__playerBox, this->pause.__player, this->pause.__weapon);
    sf::Renderable::draw(this->pause.__time, this->pause.__stateBox);
    sf::Renderable::draw(this->pause.__state_blood_text, this->pause.__state_blood_prog);
    sf::Renderable::draw(this->pause.__state_food_text,  this->pause.__state_food_prog);
    sf::Renderable::draw(this->pause.__state_level_text, this->pause.__state_level_prog);
    sf::Renderable::draw(this->pause.__valueBox, this->pause.__value);
    sf::Renderable::draw(this->pause.__flee, this->pause.__autophagy);
    sf::Renderable::draw(ui_m->__back);
  }
}

#include "./internal/Over.cpp"
#include "./internal/Pause.cpp"
#include "./internal/Coin.cpp"
#include "./internal/Level.cpp"
#include "./internal/Blood.cpp"
#include "./internal/Food.cpp"
#include "./internal/Equip.cpp"
#include "./internal/MsgBox.cpp"
#include "./internal/Skill.cpp"
#include "./internal/Skill_Actived.cpp"
