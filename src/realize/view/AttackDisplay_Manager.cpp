inline func AttackDisplay_M::call(sf::String __str, std::optional<sf::Vector2f> __pos, sf::Color __color) -> void {
  if(__str.isEmpty()) return;
  if(__str[0] == L'-') __str.erase(0);
  if(__str.find(L".") != sf::String::InvalidPos) __str = __str.substring(0, __str.find(L"."));

  if(!__pos.has_value()) {
    if(AttackDisplay_M::__text.empty()) return;
    __pos = AttackDisplay_M::__text.back()->getCenter();
  }
  if(!AttackDisplay_M::__text.empty()
   && AttackDisplay_M::__text.back()->getCenter() == __pos.value()) __pos.value() -= {10, 40};

  if(__color == sf::Color{}) __color = (sys::__darkMode ? __DARK_COLOR_TEXT__ : sf::Color::Black);

  AttackDisplay_M::__text.emplace_back(std::make_unique<sf::TextDiv>());
  AttackDisplay_M::__text.back()->setCenter(__pos.value_or(sf::Vector2f{}));
  AttackDisplay_M::__text.back()->__ATTRIBUTE__.__VISIBLE_BASE__ = false;
  AttackDisplay_M::__text.back()->setText(__str, res::__font_ac, 50);
  AttackDisplay_M::__text.back()->setTextColor(__color);
}

inline func AttackDisplay_M::draw(void) -> void {
  for(auto i{AttackDisplay_M::__text.begin()};
        i != AttackDisplay_M::__text.end(); ) {
    if((*i)->getTextColor().a == 0) {
       i->release();
       i = AttackDisplay_M::__text.erase(i);
    } else {
      (*i)->move(sys::movtionSync({0, -2}));
      (*i)->setTextColor(
           (*i)->getTextColor()
        | ((*i)->getTextColor().a - 3));
      sf::Renderable::draw(**i); ++i;
    }
  }
}
