inline func Char_M::Explode::reset(void) -> void {
  Char_M::Explode::__active.clear();
}

inline func Char_M::Explode::make(const sf::Vector2f& ctPos, float radius, bool skillMode, Char_M::Enemy* __protected) -> void {
  Char_M::Explode::__active.resize(Char_M::Explode::__active.size() + 1);
  Char_M::Explode::__active.back().__skillMode = skillMode && __protected == nullptr;
  
  Char_M::Explode::__active.back().__shape.setSize({radius * 2, radius * 2});
  Char_M::Explode::__active.back().__shape.setCenter(ctPos);
  Char_M::Explode::__active.back().__shape.setRadius(-1);
  
  if(!skillMode || __protected != nullptr) {
    Char_M::Explode::__active.back().__shape.setTextAlign(sf::Align::C);
 // Char_M::Explode::__active.back().__shape.setTextString(L"[QuackImage: 未完成工程]");
    Char_M::Explode::__active.back().__shape.setFillColor(sf::ColorEx::makeTrs(sf::Color::Red, 100));
  } else {
    Char_M::Explode::__active.back().__shape.setOutlineThickness(0);
    Char_M::Explode::__active.back().__shape.setFillColor(sf::ColorEx::makeTrs(sf::ColorEx::Grey, 10));
  }
  
  // hit enemy
  for(auto& i : Char_M::Enemy::Alloter::__active) {
    if(i.get() == __protected) continue;
    if(i->__realRect.intersects(Char_M::Explode::__active.back().__shape.getRect())) {
      if(!skillMode) {
        if(i->__bombState == BombState::Kindling) {
           i->__bombState =  BombState::Exploded;
           Char_M::Explode::make(sf::Fm::getCenter(i->__realRect));
        }  i->__cast_exp = 0;
      }
      i->hurt(30, sf::geometry::parse_circle_point({._radius = radius * 0.08f, ._center = Char_M::Explode::__active.back().__shape.getCenter(),
        ._allow_in = false}, sf::Fm::getCenter(i->__realRect)).v_LengthToCenter_Coordinates, true);
      __AUDIO__CHECK_SOUND__(kill);
    }
  }
  // hit duck
  if(!skillMode && Char_M::Explode::__active.back().__shape.getRect().intersects(Char_M::Duck::__v->__realRect)) {
    if(Char_M::Duck::__v->__last.getElapsedTime().asSeconds() >= 0.8) {
       Char_M::Duck::__v->__last.restart();
       Char_M::Value::effect.__blood -= 20;
    }  Char_M::Duck::__v->__repel =
      sf::geometry::parse_circle_point({._radius = radius * 0.3f, ._center = Char_M::Explode::__active.back().__shape.getCenter(),
        ._allow_in = false}, sf::Fm::getCenter(Char_M::Duck::__v->__realRect)).v_LengthToCenter_Coordinates;
  }
}

inline func Char_M::Explode::make_boss(const sf::Vector2f& ctPos) -> void {
  // hit enemy
  for(auto& i : Char_M::Enemy::Alloter::__active)
    i->hurt(-1, sf::geometry::parse_circle_point({._radius = 8.0f, ._center = ctPos,
      ._allow_in = false}, sf::Fm::getCenter(i->__realRect)).v_LengthToCenter_Coordinates, true, false);
}

inline func Char_M::Explode::make_poison(void) -> void {
  // hit enemy
  for(auto& i : Char_M::Enemy::Alloter::__active)
    i->hurt(2.0f * Char_M::Element::attCast(Char_M::Element::Poison, i->__element), sf::geometry::parse_circle_point({._radius = 8.0f,
      ._center = sf::Fm::getCenter(Char_M::Duck::__v->__realRect),
      ._allow_in = false}, sf::Fm::getCenter(i->__realRect)).v_LengthToCenter_Coordinates);
}

inline func Char_M::Explode::act(void) -> void {
  for(auto i = Explode::__active.begin(); i != Explode::__active.end();) {
    if(i->__clock.getElapsedTime().asSeconds() >= (i->__skillMode ? 0.2f : 2.0f)) {
       i = Explode::__active.erase(i);
    } else {
      if(i->__skillMode) i->__shape.setCenter(sf::Fm::getCenter(Char_M::Duck::__v->__realRect));
      if(i->__shape.inView()) {
        sf::Renderable::draw(i->__shape);
      } ++i;
    }
  }
  
  if(Char_M::Skill::taken("poison")) {
    if(Explode::__active_poison.operator bool()) {
      sf::Renderable::draw(Explode::__active_poison->__shape);
    } else {
      Explode::__active_poison = std::make_unique<Explode>();
      Explode::__active_poison->__shape.setFillColor(sf::ColorEx::LightGreen | 10);
      Explode::__active_poison->__shape.setOutlineThickness(0);
      Explode::__active_poison->__shape.setSize({200, 200});
      Explode::__active_poison->__shape.setRadius(-1);
    }
  }
  
  if(ChickBoss::__flashHint.operator bool())
    sf::Renderable::draw(*ChickBoss::__flashHint);
}
