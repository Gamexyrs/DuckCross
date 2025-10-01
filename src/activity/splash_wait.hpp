func splash_wait(void) -> void {
  sf::Image   cadpa_i; cadpa_i.loadFromFile("./src/res/img/cadpa12+.png");
  sf::Texture cadpa_t; cadpa_t.loadFromImage(cadpa_i); cadpa_t.setSmooth(sys::__smoothTex);
  sf::Div __CADPA{{{20, 20}, cadpa_i.getSize()}}; {
    __CADPA.getBase().setTexture(&cadpa_t);
    __CADPA.setOutlineThickness(0);
  }
  
  sf::TextDiv __duckC{{{}, _RendererSize}}; {
    __duckC.setText(L"DuckCross ©" , res::__font_en, 180);
    __duckC.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __duckC.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __duckC.setTextAlign(sf::Align::C);
    __duckC.setTextDeviat({-60, -80});
  }
  sf::TextDiv __wait{{{}, _RendererSize}}; {
    __wait.setText(L"- 轻触任意区域进入 -" , res::__font_ac, 60);
    __wait.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __wait.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __wait.setTextAlign(sf::Align::C);
    __wait.setTextDeviat({-60, 200});
  }
  sf::TextDiv __copyR{{{}, _RendererSize}}; {
    __copyR.setText(std::wstring{L"2022-2025 Gamexyrs© all copyrights reserved"}
    + L"   _appVersion: " + std::to_wstring(sys::__apkVer)
    + L"   _UID: " + std::to_wstring(sys::__device_id), res::__font_en, 30);
    __copyR.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | 160);
    __copyR.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __copyR.setTextAlign(sf::Align::LB);
    __copyR.setTextDeviat({30, -5});
  }
  
  std::pair<sf::Uint8, bool> __ColorPer{255, true};
  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_CLR__ : sf::Color::White)) {
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event)
      || sys::__event.type == sf::Event::TouchEnded) return;
    }
    
         if( __ColorPer.second && __ColorPer.first > 0)   __ColorPer.first -= 5;
    else if(!__ColorPer.second && __ColorPer.first < 255) __ColorPer.first += 5;
    else __ColorPer.second = !__ColorPer.second;
    
    __wait.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | __ColorPer.first);
    
    sf::Renderable::draw(__CADPA, __duckC, __wait, __copyR);
    sys::flashDisplay();
  };
}
