inline func PlayView_M::MsgBox_init(void) -> void {
  this->__msgBox.__ATTRIBUTE__.__VISIBLE_BASE__
  = sys::__jcontext["Control"]["MsgBoxLine"].GetBool();
  this->__msgBox.setFillColor((sys::__darkMode
  ? __DARK_COLOR_TEXT__ : sf::Color::Black));
  this->__msgBox.setBuilder(ui_m->__viewpos);
  this->__msgBox.setOutlineThickness(0);
  this->__msgBox.align(sf::Align::L) += {0, 120};
  this->__msgBox.setPerWidth("14%");
}

inline func PlayView_M::MsgBox_act(void) -> void {
  while(!this->__msgBoxStr.empty() && this->__msgBoxText.size() < 14) {
    this->__msgBoxText.resize(this->__msgBoxText.size() + 1);
    
    this->__msgBoxText.back().first.setTextString(this->__msgBoxStr.front().first
      + (this->__msgBoxStr.front().second
      ? (L" * " + sf::String(std::to_wstring(this->__msgBoxStr.front().second))) : L""));
    if(this->__msgBoxStr.front().first.find(L"⚠") != sf::String::InvalidPos)
         this->__msgBoxText.back().first.setTextColor(sf::Color::Red);
    else this->__msgBoxText.back().first.setTextColor(sys::__darkMode ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    this->__msgBoxText.back().first.setSize({this->__msgBoxText.back().first.getText(false).getGlobalBounds().width,
                                             this->__msgBoxText.back().first.getText(false).getCharacterSize() + 4.0f});
    this->__msgBoxText.back().first.setBuilder(this->__msgBox, sf::Vector2f{-this->__msgBoxText.back().first.getSize().x,
    this->__msgBoxText.back().first.getSize().y * (this->__msgBoxText.size() - 1) + 5.0f});
    this->__msgBoxText.back().first.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    this->__msgBoxText.back().first.__ATTRIBUTE__.__VISIBLE_TEXT__ = false;
    this->__msgBoxStr.pop();
  }
  if(this->__msgBox.__ATTRIBUTE__.__VISIBLE_BASE__) {
    if(!this->__msgBoxText.size()) {
      if(const sf::Color& cr{this->__msgBox.getFillColor()}; cr.a > 0)
         this->__msgBox.setFillColor(cr | (cr.a - 5));
    } else {
      if(const sf::Color& cr{this->__msgBox.getFillColor()}; cr.a < 255)
         this->__msgBox.setFillColor(cr | (cr.a + 5));
    }
  }
}

inline func PlayView_M::MsgBoxText_act(void) -> void {
  if(!this->__msgBoxText.size()) { return; } int t = 0;
  for(auto i = this->__msgBoxText.begin(); i != this->__msgBoxText.end(); ++t, ++i) {
    sf::Renderable::draw(i->first);
    if(!i->first.hasTag()) {
        i->first.setTag<int>(0);
        i->first.__ATTRIBUTE__.__VISIBLE_TEXT__ = true;
    } else if(i->first.getTag<int>() == 0) {
      if(i->first.getPosition().x < ui_m->__viewpos.getPosition().x + 5)
         i->first.move(sys::movtionSync({12, 0}));
      else {
        i->first.setPosition({ui_m->__viewpos.getPosition().x + 5, i->first.getPosition().y});
        i->first.setTag<int>(1);
      }
    } else {
      if((t && i->first.getPosition().y > (i-1)->first.getRoot().y)
      ||(!t && i->first.getPosition().y > this->__msgBox.getRoot().y)) {
               i->first.move(sys::movtionSync({0, -3}));
      } if(i->second.getElapsedTime().asSeconds() > 2.8) {
        if(i->first.inView())
           i->first.move(sys::movtionSync({-12, 0}));
        else {
           i->first.delBuilder();
          (i = this->__msgBoxText.erase(i))--;
        }
      }
    }
  }
}
