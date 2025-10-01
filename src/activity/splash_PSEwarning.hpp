func splash_PSEwarning(void) -> void {
  sf::TextDiv __title{{{}, _RendererSize}}; {
    __title.setText(L"⚠光敏性癫痫警告: 请在游戏前阅读" , res::__font, 100);
    __title.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __title.setTextColor(sf::Color::Red);
    __title.setTextAlign(sf::Align::C);
    __title.setTextDeviat({-20, -280});
  }
  sf::TextDiv __text{{{}, _RendererSize * sf::Vector2f{0.9f, 1.0f}}}; {
    __text.setText(L"　　当暴露在特定光影图案或闪光光亮下时，有极小部分人群会引发癫痫。这种情形可能是由于某些未查出的癫痫症状引起，即使该人员并没有患癫痫病史也有可能造成此类病症。如果您的家人或任何家庭成员曾有过类似症状，请在进行游戏前咨询您的医生或医师。如果您在游戏过程中出现任何症状，包括头晕、目眩、眼部或肌肉抽搐、失去意识、失去方向感、抽搐或出现任何自己无法控制的动作，请立即停止游戏井在继续游戏前咨询您的医生或医师。"
    , res::__font_ac, 60);
    __text.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __text.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __text.setAutoLineBreakEnable(true);
    __text.setTextAlign(sf::Align::C);
    __text.setTextDeviat({0, 200});
    __text.align(sf::Align::C);
  }
  
  sf::Clock __clock{};
  std::pair<sf::Uint8, bool> __ColorPer{0, true};
  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_CLR__ : sf::Color::White)) {
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event)) return;
    }
    
         if( __ColorPer.second && __ColorPer.first < 255) { if(__clock.getElapsedTime().asSeconds() >= 0.5f) __ColorPer.first += 5; }
    else if(!__ColorPer.second && __ColorPer.first > 0)   { if(__clock.getElapsedTime().asSeconds() >= 5.0f) __ColorPer.first -= 5; }
    else {
      if((__ColorPer.second = !__ColorPer.second)) return;
      __clock.restart();
    }
    
    __title.setTextColor(sf::Color::Red | __ColorPer.first);
    __text.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | __ColorPer.first);
    
    sf::Renderable::draw(__title, __text);
    sys::flashDisplay();
  };
}
