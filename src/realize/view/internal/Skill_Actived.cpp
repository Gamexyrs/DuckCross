inline func PlayView_M::Skill_actived_init(void) -> void {
  int t{0};
  for(auto i = this->ska.__release.begin(); i != this->ska.__release.end(); ++i, ++t) {
    i->setSize({128, 128});
    i->setOutlineThickness(5);
    i->setOutlineColor(sf::ColorEx::LightBlue);
    i->setFillColor(sf::Color::Black);
    i->setTextColor(sf::Color::White);
    i->setText(L"", res::__font_ac, 60);
    i->setTextAlign(sf::Align::C);
    i->setTag<bool>(false);
    
    if(!t) i->setBuilder(ui_m->__viewpos, rj::arrayToVector2(sys::__jcontext["Control"]["Layout"]["View_Skill"]));
    else   i->setBuilder(*(i - 1), sf::Vector2f{20, 0}, sf::Vector2b{true, false});
  } t = 0;
  
  for(auto& i : this->ska.__mask) {
    i.setOutlineThickness(0);
    i.setBuilder(this->ska.__release[t]);
    i.setSize(this->ska.__release.front().getSize());
    i.setFillColor(sf::ColorEx::makeTrs(sf::Color::Black, 120)); ++t;
  }
  
  this->ska.__prog.setSize(sf::Vector2f{_RendererSize.x * 0.5f, 20});
  this->ska.__prog.getInside().setFillColor(sf::ColorEx::makeTrs(sf::ColorEx::Grey, 160));
  this->ska.__prog.setOutlineColor(sf::ColorEx::makeTrs(sf::ColorEx::Grey, 170));
  this->ska.__prog.setFillColor(sf::Color::Transparent);
  this->ska.__prog.setBuilder(ui_m->__viewpos);
  this->ska.__prog.align(sf::Align::C) -= {0, 300};
  this->ska.__prog.setOutlineThickness(2);
  this->ska.__prog.__ATTRIBUTE__.__VISIBLE__ = false;
}

//>>>

inline func PlayView_M::Skill_actived_act(void) -> void {
  if(Char_M::Skill::__enable_actived_list.empty() && Char_M::Weapon::__weapon_code == __WCODE_PISTOL__)
     Char_M::Skill::require("bulletTime", true);
  else if(!Char_M::Skill::__enable_actived_list.empty() && Char_M::Weapon::__weapon_code == __WCODE_SCISSORS__) {
           Char_M::Skill::__signal_update_skills_actived = true;
           Char_M::Skill::__enable_actived_list.clear();
  } // 临时解决方案

  float __time_to_reload{0};
  for(size_t i{0}; i < 3; ++i) {
  
    if(Char_M::Skill::__signal_update_skills_actived) {
      if((this->ska.__release[i].__ATTRIBUTE__.__VISIBLE__ = (i < Char_M::Skill::__enable_actived_list.size()))) {
      
        __time_to_reload = std::get<1>(Char_M::Skill::__explain_actived.find(Char_M::Skill::__enable_actived_list[i])->second)
          - Char_M::Skill::__clock_actived.find(Char_M::Skill::__enable_actived_list[i])->second.getTime().asSeconds();
          
        this->ska.__release_t[i].loadFromFile(std::get<3>(Char_M::Skill::__explain_actived.find(Char_M::Skill::__enable_actived_list[i])->second));
        this->ska.__release[i].setTexture(&this->ska.__release_t[i]);
        this->ska.__release[i].setLabel(Char_M::Skill::__enable_actived_list[i]);
        this->ska.__release[i].setTag<bool>(__time_to_reload > 0);
      } this->ska.__mask[i].__ATTRIBUTE__.__VISIBLE__ = this->ska.__release[i].__ATTRIBUTE__.__VISIBLE__;
    }
    
    if(this->ska.__release[i].hasTexture()) {
    
      __time_to_reload = std::get<1>(Char_M::Skill::__explain_actived.find(Char_M::Skill::__enable_actived_list[i])->second)
        - Char_M::Skill::__clock_actived.find(Char_M::Skill::__enable_actived_list[i])->second.getTime().asSeconds();
        
      if(this->ska.__release[i].getTag<bool>() && __time_to_reload > 0) {
        this->ska.__release[i].setTextString(std::to_string(static_cast<int>(__time_to_reload)));
        this->ska.__mask[i].setSize({this->ska.__mask[i].getSize().x, this->ska.__release[i].getSize().y
          *        (1 - Char_M::Skill::__clock_actived  .find(Char_M::Skill::__enable_actived_list[i])->second.getTime().asSeconds()
          / std::get<1>(Char_M::Skill::__explain_actived.find(Char_M::Skill::__enable_actived_list[i])->second))});
          
      } else {
        this->ska.__release[i].setTag<bool>(false);
        this->ska.__release[i].setTextString("");
        this->ska.__mask[i].setSize({this->ska.__mask[i].getSize().x, 0});
      }
    }
    
  } Char_M::Skill::__signal_update_skills_actived = false;
  
  // time progress
  if(this->ska.__prog.getTag<float>()) {
     this->ska.__prog.__ATTRIBUTE__.__VISIBLE__ = true;
     
    if(!sf::Msgable::getLocked()) this->ska.__timer.start();
    
    if(this->ska.__timer.getTime().asSeconds() >= this->ska.__prog.getTag<float>() || !Char_M::Weapon::__is_remote || Char_M::Duck::__v->noBlood()) {
      this->ska.__prog.setTag<float>(0);
      this->ska.__prog.setProgress(0);
      Char_M::Skill::__bulletTime = false;
       
    } else {
      this->ska.__prog.setProgress(this->ska.__prog.getTag<float>() - this->ska.__timer.getTime().asSeconds(), this->ska.__prog.getTag<float>());
    }
  } else this->ska.__prog.__ATTRIBUTE__.__VISIBLE__ = false;
}

//>>>

inline func PlayView_M::requestSkill_actived(const sf::Event& event) -> void {
  for(auto& i : this->ska.__release) if(i.__ATTRIBUTE__.__VISIBLE__ && i.pollEvent_if(event) && !Char_M::Duck::__v->noBlood() && !i.getTag<bool>()) {
    Char_M::Skill::__clock_actived.find(i.getLabel())->second.restart();
    i.setTag<bool>(true);

    // 临时解决方案
    if(i.getLabel() == "bulletTime") {
      Char_M::Skill::__bulletTime = true;
      this->ska.__prog.setTag<float>(std::get<2>(Char_M::Skill::__explain_actived.find(i.getLabel())->second));
      this->ska.__prog.setProgress(1);
      this->ska.__timer.restart();
    }
  }
}
