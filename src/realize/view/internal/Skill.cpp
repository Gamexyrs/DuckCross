inline func PlayView_M::Skill_init(void) -> void {
  int t{0};
  for(auto i = this->sk.__skill_name.begin(); i != this->sk.__skill_name.end(); ++i, ++t) {
    i->__ATTRIBUTE__.__ALWAYS_TOUCHABLE__ = true;
    i->setRadius(15.0f);
    i->setPerWidth ("20%");
    i->setPerHeight("70%");
    i->setOutlineThickness(3.0f);
    i->setRounded(false, sf::Align::RB);
    i->setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black, 0));
    i->setStateColor(sf::ColorEx::makeTrs(sys::__darkMode
      ? __DARK_COLOR_MSG__ : sf::Color::White, 0));
    i->setTextColor(sf::ColorEx::makeTrs(sys::__darkMode
      ? __DARK_COLOR_TEXT__ : sf::Color::Black, 0));
    i->setText(L"", res::__font_ac, 60);
    i->setTextAlign(sf::Align::T);
    i->setTextDeviat({0, 80});
    
    if(!t) {
      i->setBuilder(ui_m->__viewpos);
      i->align(sf::Align::LT) +=
       {(_RendererSize.x - i->getSize().x * 3) / 4.0f,
        (_RendererSize.y - i->getSize().y) / 5.0f};
    } else i->setBuilder(*(i - 1),
      sf::Vector2f{(_RendererSize.x - i->getSize().x * 3) / 4.0f, 0},
      sf::Vector2b{true, false});
  } t = 0;
  for(auto i = this->sk.__skill_attr.begin(); i != this->sk.__skill_attr.end(); ++i, ++t) {
    i->__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    i->setPerWidth ("18%");
    i->setPerHeight("70%");
    i->setTextColor(sf::ColorEx::makeTrs(sys::__darkMode
      ? __DARK_COLOR_TEXT__ : sf::Color::Black, 0));
    i->setBuilder(this->sk.__skill_name.at(t));
    i->setText(L"", res::__font_ac, 40);
    i->align(sf::Align::T) += {0, 200};
    i->setAutoLineBreakEnable(true);
  }
  
  this->sk.__reject.__ATTRIBUTE__.__ALWAYS_TOUCHABLE__ = true;
  this->sk.__reject.setSize({300, 140});
  this->sk.__reject.setBuilder(ui_m->__viewpos);
  this->sk.__reject.align(sf::Align::B) -= {380 /* == 80 + 300 */, 80};
  this->sk.__reject.setText(L"弃选(+80金币)", res::__font_ac, 30);
  this->sk.__reject.setTextAlign(sf::Align::C);
  this->sk.__reject.setOutlineThickness(3.0f);
  this->sk.__reject.setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black, 0));
  this->sk.__reject.setStateColor(sf::ColorEx::makeTrs(sf::Color::Red, 0));
  this->sk.__reject.setTextColor (sf::ColorEx::makeTrs(sf::Color::Black, 0));
  
  this->sk.__flash.__ATTRIBUTE__.__ALWAYS_TOUCHABLE__ = true;
  this->sk.__flash.setSize({300, 140});
  this->sk.__flash.setBuilder(ui_m->__viewpos);
  this->sk.__flash.align(sf::Align::B) -= {0, 80};
  this->sk.__flash.setText(L"刷新(-100金币)", res::__font_ac, 30);
  this->sk.__flash.setTextAlign(sf::Align::C);
  this->sk.__flash.setOutlineThickness(3.0f);
  this->sk.__flash.setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black, 0));
  this->sk.__flash.setStateColor(sf::ColorEx::makeTrs(sf::ColorEx::Orange, 0));
  this->sk.__flash.setTextColor (sf::ColorEx::makeTrs(sf::Color::Black, 0));
  
  this->sk.__confirm.__ATTRIBUTE__.__ALWAYS_TOUCHABLE__ = true;
  this->sk.__confirm.setSize({300, 140});
  this->sk.__confirm.setBuilder(ui_m->__viewpos);
  this->sk.__confirm.align(sf::Align::B) -= {-380 /* == 300 + 80 */, 80};
  this->sk.__confirm.setText(L"确定", res::__font_ac, 60);
  this->sk.__confirm.setTextAlign(sf::Align::C);
  this->sk.__confirm.setOutlineThickness(3.0f);
  this->sk.__confirm.setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black, 0));
  this->sk.__confirm.setStateColor(sf::ColorEx::makeTrs(sf::Color::Green, 0));
  this->sk.__confirm.setTextColor (sf::ColorEx::makeTrs(sf::Color::Black, 0));
  
  this->sk.__mask.setSize(_RendererSize);
  this->sk.__mask.setOutlineThickness(0);
  this->sk.__mask.setCenter(_Renderer.getView().getCenter());
  this->sk.__mask.setFillColor(sf::ColorEx::makeTrs(sf::ColorEx::Grey, 0));
}

//>>>

inline func PlayView_M::Skill_act(void) -> void {
  sf::Uint8 __color_outline_alpha = this->sk.__skill_name[0].getBase().getOutlineColor().a;
  sf::Color __color = this->sk.__skill_name[0].getStateColor(sf::BtnState::None);
  bool __flash_enable{(Storage_M::__buf.size(sis::Item::Coin) >= 100)};
  
  // Mask
  this->sk.__mask.setCenter(_Renderer.getView().getCenter());
  if(!this->sk.__display) {
    if(this->sk.__mask.getBase().getFillColor().a > 0) {
     const_cast<sf::Color&>(this->sk.__mask.getFillColor()).a -= 5;
    }
  } else if(this->sk.__mask.getBase().getFillColor().a < 155) {
    const_cast<sf::Color&>(this->sk.__mask.getFillColor()).a += 5;
  }
  
  // Box
  if(Char_M::Value::__update_level) {
     Char_M::Value::__update_level = false;
    
    if(!this->sk.__display) {
      const auto& __result = Char_M::Skill::randOut();
      
      if(!__result.size()) {
        this->sk.__signal_no_skills = true; return;
      }
      
      for(size_t t{0}; t < 3; ++t) {
        if(__result.at(t).empty()) { __flash_enable = false; break; }
        
        this->sk.__skill_name[t].setTag<std::string>(__result.at(t));
        this->sk.__skill_name[t].setTextString(
          std::get<0>(Char_M::Skill::__explain_passive.find(__result.at(t))->second));
        this->sk.__skill_attr[t].setTextString(
          std::get<1>(Char_M::Skill::__explain_passive.find(__result.at(t))->second));
      } this->sk.__display = true;
    }
    
    this->require_pause();
    
  } else if(!this->sk.__display
         && !__color_outline_alpha
         && !__color.a) {
    if(!this->sk.__skill_name[0].getTextString().isEmpty()) {
      for(auto& i : this->sk.__skill_name) i.setTextString(L"");
      for(auto& i : this->sk.__skill_attr) i.setTextString(L"");
    } return; // No update
  } else if(this->sk.__display) {
    __color_outline_alpha = std::fmin(__color_outline_alpha + 5, 255);
    __color.a = std::fmin(__color.a + 5, 220);
  } else {
      if(__color_outline_alpha >= 5)
         __color_outline_alpha -= 5;
    else __color_outline_alpha  = 0;
      if(__color.a >= 10)
         __color.a -= 10;
    else __color.a = 0;
  }
  
  this->sk.__reject.setTextColor(sf::ColorEx::makeTrs(
  this->sk.__reject.getTextColor(), __color_outline_alpha));
  this->sk.__reject.setOutlineColor(sf::ColorEx::makeTrs(
  this->sk.__reject.getOutlineColor(), __color_outline_alpha));
  this->sk.__reject.setStateColor(sf::ColorEx::makeTrs(
  this->sk.__reject.getStateColor(sf::BtnState::None), __color_outline_alpha));
  
  this->sk.__flash.setTextColor(sf::ColorEx::makeTrs(
  __flash_enable ? sf::Color::Black : sf::Color::Red, __color_outline_alpha));
  this->sk.__flash.setOutlineColor(sf::ColorEx::makeTrs(
  __flash_enable ? sf::Color::Black : sf::Color::Red, __color_outline_alpha));
  this->sk.__flash.setStateColor(sf::ColorEx::makeTrs(
  __flash_enable ? sf::ColorEx::Orange : sf::ColorEx::Grey, __color_outline_alpha));
  this->sk.__flash.setTag<bool>(__flash_enable);
  
  this->sk.__confirm.setTextColor(sf::ColorEx::makeTrs(
  this->sk.__confirm.getTextColor(), __color_outline_alpha));
  this->sk.__confirm.setOutlineColor(sf::ColorEx::makeTrs(
  this->sk.__confirm.getOutlineColor(), __color_outline_alpha));
  this->sk.__confirm.setStateColor(sf::ColorEx::makeTrs(
  this->sk.__confirm.getStateColor(sf::BtnState::None), __color_outline_alpha));
  for(auto& i : this->sk.__skill_name) {
    if(i.getTextString().isEmpty()) break;
    i.setTextColor(sf::ColorEx::makeTrs(i.getTextColor(), __color_outline_alpha));
    i.setOutlineColor(sf::ColorEx::makeTrs(
    i.getOutlineColor(), __color_outline_alpha));
    i.setStateColor(__color);
  }
  for(auto& i : this->sk.__skill_attr)
    i.setTextColor(sf::ColorEx::makeTrs(i.getTextColor(), __color_outline_alpha));
}

//>>>

inline func PlayView_M::requestSkill(const sf::Event& event) -> void {
  if(!this->sk.__display) return;
  
  sf::Uint8 __alpha{this->sk.__confirm.getBase().getOutlineColor().a};
  
  if(this->sk.__reject.pollEvent_if(event)) {
    Storage_M::__buf.size(sis::Item::Coin) += 80;
    Storage_M::__buf.__signal_update = true;
    
    Char_M::Explode::make(sf::Fm::getCenter(Char_M::Duck::__v->__realRect), 200, true);
    Char_M::Duck::__v->__last.restart();
    Char_M::Skill::__reload_list.clear();
    this->sk.__signal_no_skills = true;
  }
  if(this->sk.__flash.getTag<bool>() && this->sk.__flash.pollEvent_if(event)) {
    Storage_M::__buf.size(sis::Item::Coin) -= 100;
    Storage_M::__buf.__signal_update = true;
    
    Char_M::Value::__update_level = true;
    Char_M::Skill::__reload_list.clear();
    this->sk.__signal_no_skills = true;
  }
  if(this->sk.__confirm.pollEvent_if(event) && this->sk.__choose != nullptr) {
    Char_M::Explode::make(sf::Fm::getCenter(Char_M::Duck::__v->__realRect), 200, true);
    Char_M::Skill::require(this->sk.__choose->getTag<std::string>());
    Char_M::Duck::__v->__last.restart();
    Char_M::Skill::__reload_list.clear();
     this->sk.__signal_no_skills = true;
  }
  
  if(this->sk.__signal_no_skills || Char_M::Duck::__v->noBlood()) {
     this->sk.__display = false;
     this->sk.__signal_no_skills = false;
     this->require_pause(false);
  }
  
  if(this->sk.__reject.getState() == sf::BtnState::Pressed)
       this->sk.__reject.setOutlineColor(sf::ColorEx::makeTrs(sf::ColorEx::Orange, __alpha));
  else this->sk.__reject.setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black,    __alpha));
  
  if(this->sk.__flash.getTag<bool>()) {
    if(this->sk.__flash.getState() == sf::BtnState::Pressed)
         this->sk.__flash.setOutlineColor(sf::ColorEx::makeTrs(sf::ColorEx::Orange, __alpha));
    else this->sk.__flash.setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black,    __alpha));
  }
  
  if(this->sk.__confirm.getState() == sf::BtnState::Pressed)
       this->sk.__confirm.setOutlineColor(sf::ColorEx::makeTrs(sf::ColorEx::Orange, __alpha));
  else this->sk.__confirm.setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black,    __alpha));
  
  for(auto& i : this->sk.__skill_name) {
    if(i.getTextString().isEmpty()) break;
    if(i.pollEvent(event)) {
      if(i.getChecked()) {
          if(this->sk.__choose != nullptr) {
             this->sk.__choose->setChecked(false);
          }  this->sk.__choose = &i;
      } else this->sk.__choose = nullptr;
    }
  }
  for(auto& i : this->sk.__skill_name) {
    __alpha = i.getOutlineColor().a;
    if(i.getTextString().isEmpty()) break;
    if(i.getChecked())
         i.setOutlineColor(sf::ColorEx::makeTrs(sf::ColorEx::Orange, __alpha));
    else i.setOutlineColor(sf::ColorEx::makeTrs(sf::Color::Black,    __alpha));
  }
}
