inline func PlayView_M::Equip_init(void) -> void {
  this->eq.__eq0i.loadFromFile("./src/res/img/duck/weapon/scissors/default/_N.png");
  this->eq.__eq1i.loadFromFile("./src/res/img/duck/weapon/pistol/default/_N.png");
  this->eq.__eq0t.loadFromImage(this->eq.__eq0i);
  this->eq.__eq1t.loadFromImage(this->eq.__eq1i);
  this->eq.__eq0t.setSmooth(sys::__smoothTex);
  this->eq.__eq1t.setSmooth(sys::__smoothTex);
  
  this->eq.__box.getBase().setOutlineColor(sf::ColorEx::makeTrs(sf::ColorEx::Grey, 120));
  this->eq.__box.setStateColor(sf::Color::White | 180, sf::BtnState::None);
  this->eq.__box.setStateColor(sf::Color::White, sf::BtnState::Pressed);
  this->eq.__box.setBuilder(ui_m->__viewpos,
    rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["View_Equip"]));
  this->eq.__box.getBase().setTexture(res::ui::__switch.get(), true);
  this->eq.__box.setOutlineThickness(2);
  this->eq.__box.setSize({230, 150});
  this->eq.__box.setRadius(10.0f);
  
  this->eq.__pic.setStateColor(sf::ColorEx::Grey | 180, sf::BtnState::None);
  this->eq.__pic.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
  this->eq.__pic.setBuilder(this->eq.__box);
  this->eq.__pic.setOutlineThickness(0);
  this->eq.__pic.setSize({200, 100});
  this->eq.__pic.align(sf::Align::C);
  
  if(Char_M::Weapon::__v.get() == nullptr)
    this->eq.__pic.getBase().setTexture(nullptr);
  else switch(Char_M::Weapon::__v->__weapon_code) {
    case(__WCODE_PISTOL__): {
      this->eq.__pic.getBase().setTexture(&this->eq.__eq0t);
    } break;
    case(__WCODE_SCISSORS__): default: {
      this->eq.__pic.getBase().setTexture(&this->eq.__eq1t);
    } break;
  }
}

inline func PlayView_M::Equip_act(void) -> void {
}

inline func PlayView_M::requestEquip(const sf::Event& event) -> void {
  if(this->eq.__box.pollEvent_if(event) && !Char_M::Duck::__v->noBlood()) {
    Json_M::__mutex.lock();
    switch(Char_M::Weapon::__v->__weapon_code) {
      case(__WCODE_PISTOL__): {
        Char_M::Weapon::__v.reset();
        Char_M::Weapon::__v = std::move(std::make_unique<Char_M::Weapon::Scissors>());
        this->eq.__pic.getBase().setTexture(&this->eq.__eq1t, true);
      } break;
      case(__WCODE_SCISSORS__): default: {
        if(Char_M::Value::__level >= 6) {
           Char_M::Weapon::__v.reset();
           Char_M::Weapon::__v = std::move(std::make_unique<Char_M::Weapon::Pistol>());
          this->eq.__pic.getBase().setTexture(&this->eq.__eq0t, true);
        } else __SEND_MSG__(L"⚠ Level6 解锁武器: \"小手枪\"", 0);
      } break;
    }
    Json_M::__mutex.unlock();
  }
  
  this->eq.__pic.pollEvent(event);
  
  if(this->eq.__box.getState() == sf::BtnState::Pressed)
       this->eq.__box.setOutlineColor(sf::Color::Blue | 120);
  else this->eq.__box.setOutlineColor(sf::ColorEx::Grey | 120);
}
