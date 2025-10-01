inline func PlayView_M::Pause_init(void) -> void {
  this->pause.__mask.setSize(_RendererSize);
  this->pause.__mask.setOutlineThickness(0);
  this->pause.__mask.setFillColor(sf::Color::Black | 0);
  this->pause.__mask.setCenter(_Renderer.getView().getCenter());
  
  this->pause.__playerBox.setBuilder(ui_m->__viewpos, sf::Vector2f{50, 100});
  this->pause.__playerBox.setOutlineColor(__DARK_COLOR_TEXT__);
  this->pause.__playerBox.setFillColor(sf::Color::Transparent);
  this->pause.__playerBox.setText(L"人物" , res::__font_ac, 25);
  this->pause.__playerBox.setTextAlign(sf::Align::RT) += {-8, 5};
  this->pause.__playerBox.setTextColor(sf::ColorEx::Grey);
  
  this->pause.__player_t.loadFromFile("./src/res/img/duck/default/_A.png");
  this->pause.__player_t.setSmooth(sys::__smoothTex);
  this->pause.__player.scale({0.2, 0.2});
  this->pause.__player.setTexture(this->pause.__player_t);
  
  this->pause.__weapon_t.setSmooth(sys::__smoothTex);
  this->pause.__weapon.scale({0.2f, 0.2f});
  this->pause.__weapon.setOrigin(sf::Fm::getSize(this->pause.__player).x / -2.0f,
                                       this->pause.__weapon_t.getSize().y / 2.0f);
  
  this->pause.__stateBox.setSize({(_RendererSize.x - this->pause.__playerBox.getSize().x - 120) * 0.75f, this->pause.__playerBox.getSize().y});
  this->pause.__stateBox.setBuilder(this->pause.__playerBox, sf::Vector2f{10, 0}, sf::Vector2b{true, false});
  this->pause.__stateBox.setOutlineColor(__DARK_COLOR_TEXT__);
  this->pause.__stateBox.setFillColor(sf::Color::Transparent);
  this->pause.__stateBox.setText(L"状态" , res::__font_ac, 25);
  this->pause.__stateBox.setTextAlign(sf::Align::RT) += {-8, 5};
  this->pause.__stateBox.setTextColor(sf::ColorEx::Grey);

  this->pause.__time.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->pause.__time.setBuilder(this->pause.__stateBox, sf::Vector2f{0, -40});
  this->pause.__time.setText(L"[Time: -- s]", res::__font_en, 30);
  this->pause.__time.setTextColor(sf::Color::White);

  sf::Vector2f __prog_size{this->pause.__stateBox.getSize().x - 100, 26};
  this->pause.__state_blood_text.setBuilder(this->pause.__stateBox, sf::Vector2f{50, 50});
  this->pause.__state_blood_text.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->pause.__state_blood_text.setText(L"--", res::__font_ac, 30);
  this->pause.__state_blood_text.setTextColor(__DARK_COLOR_TEXT__);
  this->pause.__state_blood_text.setTextAlign(sf::Align::L);

  this->pause.__state_blood_prog.setSize(__prog_size);
  this->pause.__state_blood_prog.setBuilder(this->pause.__state_blood_text, sf::Vector2f{0, 5}, sf::Vector2b{false, true});
  this->pause.__state_blood_prog.setFillColor(sf::ColorEx::LightPink | 70);
  this->pause.__state_blood_prog.getInside().setFillColor(sf::Color::Red);

  this->pause.__state_food_text.setBuilder(this->pause.__state_blood_prog, sf::Vector2f{0, 20}, sf::Vector2b{false, true});
  this->pause.__state_food_text.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->pause.__state_food_text.setText(L"--", res::__font_ac, 30);
  this->pause.__state_food_text.setTextColor(__DARK_COLOR_TEXT__);
  this->pause.__state_food_text.setTextAlign(sf::Align::L);

  this->pause.__state_food_prog.setSize(__prog_size);
  this->pause.__state_food_prog.setBuilder(this->pause.__state_food_text, sf::Vector2f{0, 5}, sf::Vector2b{false, true});
  this->pause.__state_food_prog.getInside().setFillColor(sf::ColorEx::Orange);
  this->pause.__state_food_prog.setFillColor(sf::ColorEx::Orange | 70);

  this->pause.__state_level_text.setBuilder(this->pause.__state_food_prog, sf::Vector2f{0, 20}, sf::Vector2b{false, true});
  this->pause.__state_level_text.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->pause.__state_level_text.setText(L"--", res::__font_ac, 30);
  this->pause.__state_level_text.setTextColor(__DARK_COLOR_TEXT__);
  this->pause.__state_level_text.setTextAlign(sf::Align::L);

  this->pause.__state_level_prog.setSize(__prog_size);
  this->pause.__state_level_prog.setBuilder(this->pause.__state_level_text, sf::Vector2f{0, 5}, sf::Vector2b{false, true});
  this->pause.__state_level_prog.getInside().setFillColor(sf::ColorEx::LightBlue);
  this->pause.__state_level_prog.setFillColor(sf::ColorEx::LightBlue | 70);
  
  this->pause.__valueBox.setSize({(_RendererSize.x - this->pause.__playerBox.getSize().x - this->pause.__stateBox.getSize().x - 140), this->pause.__playerBox.getSize().y});
  this->pause.__valueBox.setBuilder(this->pause.__stateBox, sf::Vector2f{10, 0}, sf::Vector2b{true, false});
  this->pause.__valueBox.setOutlineColor(__DARK_COLOR_TEXT__);
  this->pause.__valueBox.setFillColor(sf::Color::Transparent);
  this->pause.__valueBox.setText(L"数据" , res::__font_ac, 25);
  this->pause.__valueBox.setTextAlign(sf::Align::RT) += {-8, 5};
  this->pause.__valueBox.setTextColor(sf::ColorEx::Grey);

  this->pause.__value.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  this->pause.__value.setBuilder(this->pause.__valueBox);
  this->pause.__value.setText("", res::__font_ac, 25);
  this->pause.__value.setTextAlign(sf::Align::T);
  this->pause.__value.setTextColor(sf::ColorEx::Grey);
  
  this->pause.__flee.setBuilder(this->pause.__playerBox, sf::Vector2f{0, 50}, sf::Vector2b{false, true});
  this->pause.__flee.__ATTRIBUTE__.__ALWAYS_TOUCHABLE__ = true;
  this->pause.__flee.setText(L"卡住脱离" , res::__font_ac, 40);
  this->pause.__flee.setTextAlign(sf::Align::C);
  this->pause.__flee.setTextColor(__DARK_COLOR_TEXT__);
  this->pause.__flee.setStateColor(sf::Color::Transparent, sf::BtnState::None);
  this->pause.__flee.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
  this->pause.__flee.setOutlineColor(sf::Color::Red);

  this->pause.__autophagy.setBuilder(this->pause.__flee, sf::Vector2f{0, 10}, sf::Vector2b{false, true});
  this->pause.__autophagy.__ATTRIBUTE__.__ALWAYS_TOUCHABLE__ = true;
  this->pause.__autophagy.setText(L"自噬" , res::__font_ac, 40);
  this->pause.__autophagy.setTextAlign(sf::Align::C);
  this->pause.__autophagy.setTextColor(__DARK_COLOR_TEXT__);
  this->pause.__autophagy.setStateColor(sf::Color::Transparent, sf::BtnState::None);
  this->pause.__autophagy.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
  this->pause.__autophagy.setOutlineColor(sf::Color::Red);
}

inline func PlayView_M::Pause_act(void) -> void {
  // Mask
  this->pause.__mask.setCenter(_Renderer.getView().getCenter());
  if(!this->__pausing) {
    if(this->pause.__mask.getFillColor().a > 0) {
     const_cast<sf::Color&>(this->pause.__mask.getFillColor()).a -= 5;
    } return;
  } else if(this->pause.__mask.getFillColor().a < 225) {
    const_cast<sf::Color&>(this->pause.__mask.getFillColor()).a += 5;
  }
  
  if(this->__pausing) {
    this->require_pause(true);
  
    this->pause.__player.setPosition(sf::align(sf::Fm::getSize(this->pause.__player.getGlobalBounds()), this->pause.__playerBox.getRect(), sf::Align::C));
    
    switch(Char_M::Weapon::__weapon_code) {
      case(__WCODE_PISTOL__):            this->pause.__weapon_t.loadFromFile("./src/res/img/duck/weapon/pistol/default/_N.png"); break;
      case(__WCODE_SCISSORS__): default: this->pause.__weapon_t.loadFromFile("./src/res/img/duck/weapon/scissors/default/_N.png"); break;
    }
    this->pause.__weapon.setTexture(this->pause.__weapon_t);
    this->pause.__weapon.setPosition(sf::align({}, this->pause.__player.getGlobalBounds()) - sf::Vector2f{0, 40});
    ui_m->__back.setTouchEnable((ui_m->__back.__ATTRIBUTE__.__VISIBLE__ = true));
    ui_m->__back.setBuilder(ui_m->__viewpos);
    
    this->pause.__time.setTextString(L"[Time: "
    + std::to_wstring(static_cast<unsigned>(Arc_M::__playTime.asSeconds())) + L" s]");
    
    this->pause.__state_blood_text.setTextString(L"血量: "
      + std::to_wstring(Char_M::Value::__blood) + L" / "
      + std::to_wstring(Char_M::Value::__blood_max));
    this->pause.__state_blood_prog.setProgress(Char_M::Value::__blood, Char_M::Value::__blood_max);
      
    if(Char_M::Value::__food <= 0) {
      this->pause.__state_food_text.setTextString(L"0 %");
      this->pause.__state_food_prog.setProgress(0);
    } else {
      this->pause.__state_food_text.setTextString(L"饱食: " + std::to_wstring(
        static_cast<int>(Char_M::Value::__food)) + L" %");
      this->pause.__state_food_prog.setProgress(Char_M::Value::__food, 100);
    }
  
    this->pause.__state_level_text.setTextString(L"等级: Lv." + std::to_wstring(Char_M::Value::__level)
      + L" , " + std::to_wstring(static_cast<int>(static_cast<float>(Char_M::Value::__exp)
      / static_cast<float>(Char_M::mathsLevelExp(Char_M::Value::__level + 1)) * 100)) + L" %");
    this->pause.__state_level_prog.setProgress(Char_M::Value::__exp, Char_M::mathsLevelExp(Char_M::Value::__level + 1));
  }

  this->pause.__value.setTextString(sf::String{}
  + L"\n最高血量 　　= " + std::to_wstring(Char_M::Value::__blood_max)
  + L"\n饱食消耗 　　× " + sf::Fm::toString(Char_M::Value::__food_f)
  + L"\n速度加成 　　× " + sf::Fm::toString(Char_M::Value::__speed_f)
  + L"\n经验加成 　　× " + sf::Fm::toString(Char_M::Value::__exp_f)
  + L"\n金币加成 　　× " + sf::Fm::toString(Char_M::Value::__coin_f)
  + L"\n攻击伤害加成 × " + sf::Fm::toString(Char_M::Value::__attack_f)
  + L"\n暴击伤害概率 = " + sf::Fm::toString(Char_M::Value::__attack_crit_p)
  + L"\n暴击伤害加成 × " + sf::Fm::toString(Char_M::Value::__attack_crit_f)
  + L"\n远程伤害加成 × " + sf::Fm::toString(Char_M::Value::__attack_r_f)
  + L"\n近战伤害加成 × " + sf::Fm::toString(Char_M::Value::__attack_c_f)
  + L"\n远程攻速加成 × " + sf::Fm::toString(Char_M::Value::__attack_speed_r_f)
  + L"\n近战攻速加成 × " + sf::Fm::toString(Char_M::Value::__attack_speed_c_f)
  + L"\n吸血比例　　 = " + sf::Fm::toString(Char_M::Value::__vampirism_f - 1.0f)
  + L"\n荆棘比例 　　= " + sf::Fm::toString(Char_M::Value::__thorns_f - 1.0f)
  + L"\n幸运 　　　　= " + std::to_wstring(Char_M::Value::__luck));
  this->pause.__value.resizeByText();
  this->pause.__value.align(sf::Align::T);
}

inline func PlayView_M::requestPause(const sf::Event& __event) -> void {
  if(!this->__pausing) return;
  
  if(this->__pausing && ui_m->__back.pollEvent_if(__event)) {
    ui_m->__back.setTouchEnable((ui_m->__back.__ATTRIBUTE__.__VISIBLE__ = false));
    this->require_pause((this->__pausing = false));
  }
  if(this->pause.__flee.pollEvent_if(__event)) {
    switch(Map_M::mathsObsSide(Char_M::Duck::__v->__realRect)) {
      case(sf::Align::L): Char_M::Duck::__v->__s.move({-50, 0}); break;
      case(sf::Align::R): Char_M::Duck::__v->__s.move({ 50, 0}); break;
      case(sf::Align::T): Char_M::Duck::__v->__s.move({0, -50}); break;
      case(sf::Align::B): Char_M::Duck::__v->__s.move({0,  50}); break;
      default: ui_m->bubble(L"未检测到卡住"); return;
    }          ui_m->bubble(L"已尝试脱离");
  }
  if(this->pause.__autophagy.pollEvent_if(__event)) {
    ui_m->__msg.launchQueue({
      .title = L"警告", .info = L"确定要自噬?",
      .btn = {{L"确定", 202},
              {L"取消", 0}},
      .btnTextSize = 60,
    }, true);
  }
}
