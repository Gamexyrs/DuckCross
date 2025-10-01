func updateLog(void) -> sys_acti::ActivityType {
  std::vector<std::pair<sf::TextDiv, sf::TextDiv>> __block{__UPDATE_LOG_BLOCK_STR__.size()};
  std::vector<sf::VertexArray> __co_block{}; int ColorPer{0};
  
  int t{0}; for(auto i = __block.begin(); i != __block.end(); ++i, ++t) {
    bool __versionBlock{__UPDATE_LOG_BLOCK_STR__[t].first.find("Version --") != sf::String::InvalidPos};
    if(i == __block.begin())
         i->first.setPosition({0, 150});
    else i->first.setBuilder((i - 1)->second, sf::Vector2f{0, 40}, sf::Vector2b{false, true});
    i->first.setText(__UPDATE_LOG_BLOCK_STR__[t].first, res::__font_en, 50);
    i->first.getText().setStyle(sf::Text::Style::Bold);
    i->first.setSize({_RendererSize.x, 80});
    
    if(__versionBlock) {
      i->first.setTextAlign(sf::Align::C);
      i->first.setTextDeviat({-70.0f, -4.0f});
      i->first.setTextColor(sf::Color::Black);
      i->first.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
      
      __co_block.emplace_back(sf::VertexArray{sf::PrimitiveType::TriangleStrip, 4});
      __co_block.back()[0].position =  i->first.getPosition();
      __co_block.back()[1].position = {i->first.getPosition().x, i->first.getRoot().y};
      __co_block.back()[2].position = {i->first.getRoot().x, i->first.getPosition().y};
      __co_block.back()[3].position =  i->first.getRoot();
      __co_block.back()[0].color = sf::Color::Red;
      __co_block.back()[1].color = sf::Color::Blue;
      __co_block.back()[2].color = sf::Color::Green;
      __co_block.back()[3].color = sf::Color::Yellow;
    } else {
      i->first.getBase().setFillColor(sys::__darkMode
        ? __DARK_COLOR_COL__ : sf::ColorEx::LightPink);
      i->first.getBase().setOutlineThickness(0);
      i->first.setTextAlign(sf::Align::L);
      i->first.setTextDeviat({50.0f, -4.0f});
      i->first.setTextColor(sys::__darkMode
        ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    }
    
    sf::String   __strFix = __UPDATE_LOG_BLOCK_STR__[t].second; std::size_t pos;
    while((pos = __strFix.find(L".>")) != sf::String::InvalidPos
       || (pos = __strFix.find(L")>")) != sf::String::InvalidPos
       || (pos = __strFix.find(L"—>")) != sf::String::InvalidPos)
                 __strFix.insert(pos + 1, L"\n");
    
    i->second.setBuilder(i->first, sf::Vector2f{}, sf::Vector2b{false, true});
      if(__UPDATE_LOG_BLOCK_STR__[t].second.isEmpty()) continue;
    i->second.setText(__strFix, res::__font);
    i->second.setTextColor(sys::__darkMode
      ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    i->second.getBase().setFillColor(sys::__darkMode
      ? __DARK_COLOR_COL__ : sf::ColorEx::LightPink);
    i->second.getBase().setOutlineThickness(0);
    i->second.setTextDeviat({10, 5});
    i->second.setPerWidth("100%");
    i->second.setAutoLineBreakEnable(true);
    i->second.setSize({_RendererSize.x,
    i->second.getNextPosition().y + 60});
  }
  
  sf::ScrollableView::setVerticalMoveEnable(true);
  sf::ScrollableView::setVerticalMax({0, __block.back().second.getRoot().y + _RendererSize.y / 4.0f});
  
//>>>

  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_CLR__ : sf::Color::White)) {
    sf::TouchEvent::pollEvent(sys::__event);
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event)
      || ui_m->__back.pollEvent_if(sys::__event)) {
        return sys_acti::ActivityType::Settings;
      }
    }
    
    //     0      1      2       3
    // R G ⇒ B R ⇒ Y B ⇒ G Y  |
    // B Y ⇒ Y G ⇒ G R ⇒ R B  |
    for(auto& i : __co_block) {
      sf::Renderable::draw(i);
      switch(ColorPer) {
        case(0): {
          i[0].color.r -= (i[0].color.r ? 1 : 0); ++i[0].color.b;
          i[1].color.b -= (i[1].color.b ? 1 : 0);   i[1].color.r = ++i[1].color.g;
          i[2].color.g -= (i[2].color.g ? 1 : 0); ++i[2].color.r;
          i[3].color.r -= (i[3].color.r ? 1 : 0);
          if(!(i[0].color.r)) ++ColorPer;
        } break;
        case(1): {
          i[0].color.b -= (i[0].color.b ? 1 : 0);   i[0].color.r = ++i[0].color.g;
          i[1].color.r -= (i[1].color.r ? 1 : 0);
          i[2].color.r -= (i[2].color.r ? 1 : 0); ++i[2].color.b;
          i[3].color.g -= (i[3].color.g ? 1 : 0); ++i[3].color.r;
          if(!(i[0].color.b)) ++ColorPer;
        } break;
        case(2): {
          i[0].color.r -= (i[0].color.r ? 1 : 0);
          i[1].color.g -= (i[1].color.g ? 1 : 0); ++i[1].color.r;
          i[2].color.b -= (i[2].color.b ? 1 : 0);   i[2].color.r = ++i[2].color.g;
          i[3].color.r -= (i[3].color.r ? 1 : 0); ++i[3].color.b;
          if(!(i[0].color.r)) ++ColorPer;
        } break;
        case(3): {
          i[0].color.g -= (i[0].color.g ? 1 : 0); ++i[0].color.r;
          i[1].color.r -= (i[1].color.r ? 1 : 0); ++i[1].color.b;
          i[2].color.r -= (i[2].color.r ? 1 : 0);
          i[3].color.b -= (i[3].color.b ? 1 : 0);   i[3].color.r = ++i[3].color.g;
          if(!(i[0].color.g)) ColorPer = 0;
        } break;
      }
    }
    for(auto& i : __block)
      sf::Renderable::draw(i.second, i.first);
      
    sf::Renderable::draw(ui_m->__back);
    
    sf::ScrollableView::setSlideAttenuate(0.5f / sys::tickSync());
    sf::ScrollableView::pollEvent(); ui_m->__back.align(sf::Align::LT);
                sys::flashDisplay();
  } return sys_acti::ActivityType::Exit;
}
