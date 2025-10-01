inline func PlayView_M::Over_init(void) -> void {
  this->over.__text.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->over.__text.setText(L"游戏结束, 鸭子嘎了", res::__font_ac, 100);
  this->over.__text.setTextColor(sys::__darkMode
   ? __DARK_COLOR_TEXT__ : sf::Color::Black);
  this->over.__text.setBuilder(ui_m->__viewpos);
  this->over.__text.setTag<bool>(false);
  this->over.__text.mov.setAuto(true);
  this->over.__text.resizeByText();
  
  this->over.__settle.setStateColor(sf::Color::Green | 100, sf::BtnState::Pressed);
  this->over.__settle.setStateColor(sf::Color::Green | 140, sf::BtnState::None);
  this->over.__settle.getText().setStyle(sf::Text::Style::Underlined);
  this->over.__settle.setText(L"结算 >", res::__font_ac, 50);
  this->over.__settle.setBuilder(ui_m->__viewpos);
  this->over.__settle.setTextAlign(sf::Align::C);
  this->over.__settle.setTextColor(sf::Color::Black);
  this->over.__settle.mov.setAuto(true);
  
  this->over.__reborn.setBuilder(this->over.__settle, sf::Vector2f{0, 20}, sf::Vector2b{false, true});
  this->over.__reborn.setStateColor(sf::Color::Transparent);
  this->over.__reborn.getText().setStyle(sf::Text::Style::Underlined);
  this->over.__reborn.setText(L"复活 >", res::__font_ac, 50);
  this->over.__reborn.setTextAlign(sf::Align::C);
  this->over.__reborn.setTextColor(sys::__darkMode
   ? __DARK_COLOR_TEXT__ : sf::Color::Black);
  this->over.__reborn.setOutlineColor(sf::Color::Red);
  this->over.__reborn.setOutlineThickness(2);
}

inline func PlayView_M::Over_act(void) -> void {
  if(Char_M::Duck::__v->noBlood()
  && !this->over.__text.getTag<bool>()) {
      this->over.__text.setTag<bool>(true);
    this->over.__text.align(sf::Align::T) -= {0.0f, this->over.__text.getTextSize().y * 1.2f};
    this->over.__settle.align(sf::Align::RB) += {this->over.__settle.getSize().x * 1.1f, -200.0f};
    
    this->over.__text.  mov.apply(sf::MoveMethod::linear_down({0, ui_m->__viewpos.getSize().y / 3.0f},                {}, 120.0f * sys::tickSync()), true);
    this->over.__settle.mov.apply(sf::MoveMethod::linear_down({- 180.0f - this->over.__settle.getSize().x * 1.1f, 0}, {}, 120.0f * sys::tickSync()), true);
  }
}

inline func PlayView_M::requestSettle(const sf::Event& event) -> bool {
  return this->over.__settle.pollEvent_if(event);
}
