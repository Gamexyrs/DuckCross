func splash_cameraShakeWarning(void) -> void {
  sf::TextDiv __title{{{}, _RendererSize}}; {
    __title.setText(L"⚠摄像机抖动警告: 请在游戏前阅读" , res::__font, 100);
    __title.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __title.setTextColor(sf::Color::Red);
    __title.setTextAlign(sf::Align::C);
    __title.setTextDeviat({-20, -280});
  }
  sf::TextDiv __text{{{}, _RendererSize * sf::Vector2f{0.9f, 1.0f}}}; {
    __text.setText(L"　　为了更逼真、更沉浸的游戏体验，游戏中部分场景可能会包含摄像机抖动效果以增强游戏的真实感和紧张感。摄像机抖动可能会对部分玩家产生眩晕或恶心、视觉疲劳、头痛或其他不适。如果您在游戏过程中感到任何不适，请立即暂停游戏，休息片刻，并调整游戏设置以关闭摄像机抖动效果。由于儿童的身体和视觉系统仍在发育中，他们可能对摄像机抖动更为敏感。建议家长密切监督儿童的游戏时间，并根据孩子的反应调整游戏设置。如果您或您的家人有类似症状的历史，或者对摄像机抖动的耐受性较低，请在开始游戏前咨询医生的意见。如果您在游戏过程中感到任何不适，请立即暂停游戏。如果症状持续或加重，请咨询专业医疗人员。"
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
