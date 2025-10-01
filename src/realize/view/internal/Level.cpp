#define __EXP_PROGRESS__                          \
  (static_cast<float>(Char_M::Value::__exp) \
 / static_cast<float>(Char_M::mathsLevelExp(Char_M::Value::__level + 1)))

inline func PlayView_M::Level_init(void) -> void {
  this->lv.__prog.getInside().setFillColor(sf::ColorEx::LightBlue);
  this->lv.__prog.setFillColor(sf::ColorEx::LightBlue | 70);
  this->lv.__prog.setSize({_RendererSize.x, 15});
  this->lv.__prog.setBuilder(ui_m->__viewpos,
            sf::Vector2f{0, -this->lv.__prog.getSize().y},
            sf::Vector2b{false, true});
  this->lv.__prog.setTag<bool>(false);
  this->lv.__prog.mov.setAuto(true);
  
  this->lv.__text.setSize({0, 60});
  this->lv.__text.setBuilder(this->lv.__prog,
      sf::Vector2f(10, -60 - this->lv.__prog.getSize().y));
  this->lv.__text.setText(L"Level: ", res::__font_en, 55);
  this->lv.__text.setOutlineColor(sys::__darkMode
   ? __DARK_COLOR_TEXT__ : sf::Color::Black);
  this->lv.__text.setTextColor(sys::__darkMode
   ? __DARK_COLOR_TEXT__ : sf::Color::Black);
  this->lv.__text.setTextAlign(sf::Align::L);
  
  if(sys_acti::__actype == sys_acti::ActivityType::Play)
       this->lv.__prog.setProgress(0);
  else this->lv.__prog.setProgress(__EXP_PROGRESS__);
  
  this->lv.__cheatlv6.setSize({200, 50});
  this->lv.__cheatlv6.setRadius(10);
  this->lv.__cheatlv6.setBuilder(this->lv.__text, sf::Vector2f{400, 0}, sf::Vector2b{true, false});
  this->lv.__cheatlv6.setText(L"快速直升 Lv6" , res::__font_ac, 26);
  this->lv.__cheatlv6.setTextAlign(sf::Align::C);
  this->lv.__cheatlv6.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | 160);
  this->lv.__cheatlv6.setStateColor(sf::Color::Transparent, sf::BtnState::None);
  this->lv.__cheatlv6.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
  this->lv.__cheatlv6.setOutlineColor(sf::Color::Red);
  
  this->lv.__cheatboss.setSize({200, 50});
  this->lv.__cheatboss.setRadius(10);
  this->lv.__cheatboss.setBuilder(this->lv.__text, sf::Vector2f{610, 0}, sf::Vector2b{true, false});
  this->lv.__cheatboss.setText(L"快速召唤 Boss" , res::__font_ac, 26);
  this->lv.__cheatboss.setTextAlign(sf::Align::C);
  this->lv.__cheatboss.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | 160);
  this->lv.__cheatboss.setStateColor(sf::Color::Transparent, sf::BtnState::None);
  this->lv.__cheatboss.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
  this->lv.__cheatboss.setOutlineColor(sf::Color::Red);
}

//>>>

inline func PlayView_M::Level_act(void) -> void {
  static bool __nMove{false};
  
  if(Char_M::Value::__update_exp) {
     Char_M::Value::__update_exp = false;
    if(this->__signal_reload__) {
      this->lv.__prog.setProgress(__EXP_PROGRESS__);
    } else __nMove = true;
    this->lv.__text.setTextString(L"Level: "
      + std::to_wstring(Char_M::Value::__level));
  }
  if(__nMove) {
         if(this->lv.__prog.getProgress() < __EXP_PROGRESS__)
            this->lv.__prog.movProgress(0.007f / sys::tickSync());
    else if(this->lv.__prog.getProgress() - __EXP_PROGRESS__ > 0.0255f) {
      if(   this->lv.__prog.getProgress() < 1)
            this->lv.__prog.movProgress(0.007f / sys::tickSync());
      else  this->lv.__prog.setProgress(0);
    } else __nMove = false;
  }
  if(Char_M::Duck::__v->noBlood() && !this->lv.__prog.getTag<bool>()) {
    this->lv.__prog.mov.apply(sf::MoveMethod::linear_up({0, 90.0f}, {}, 50.0f * sys::tickSync()));
    this->lv.__prog.setTag<bool>(true);
  }
}

#undef __EXP_PROGRESS__
