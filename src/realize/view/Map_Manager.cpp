Map_M::Map_Manager(void) {
  // 边界
  this->__map_boundary.setOutlineColor(sf::Color::Red | 100);
  this->__map_boundary.setFillColor(sf::Color::Transparent);
  this->__map_boundary.setRect(__MAX_MAP_RECT__);
  this->__map_boundary.setOutlineThickness(5);

  // 树
  for(  float x{__MAX_MAP_RECT__.left}; x < __MAX_MAP_RECT__.width;  x += _RendererSize.x * 1.2) {
    for(float y{__MAX_MAP_RECT__.top};  y < __MAX_MAP_RECT__.height; y += _RendererSize.y * 1.5) {
      this->__s_tree.resize(this->__s_tree.size() + 1);
      this->__s_tree.back().setTexture(*res::__tex_tree);
      this->__s_tree.back().setScale({0.35, 0.35});
      this->__s_tree.back().setPosition({x, y});
    }
  }
  // 网格
  if(sys::__jcontext["General"]["MapGrids"].GetBool()) {
    this->__grid.first. resize(__MAX_MAP_RECT__.width  / 100);
    this->__grid.second.resize(__MAX_MAP_RECT__.height / 100);
    
    const sf::Color& __tmp_color{(sys::__darkMode ? sf::Color::White : sf::Color::Black) | 40};
    
    int t{0};
    for(auto& i : this->__grid.first) {
      i.setPrimitiveType(sf::PrimitiveType::Lines); i.resize(2);
      i[0].position = {__MAX_MAP_RECT__.left + t * 100, __MAX_MAP_RECT__.top};
      i[1].position = {i[0].position.x, __MAX_MAP_RECT__.top + __MAX_MAP_RECT__.height};
      i[0].color = __tmp_color; i[1].color = __tmp_color; ++t;
    } t = 0;
    for(auto& i : this->__grid.second) {
      i.setPrimitiveType(sf::PrimitiveType::Lines); i.resize(2);
      i[0].position = {__MAX_MAP_RECT__.left, __MAX_MAP_RECT__.top + t * 100};
      i[1].position = {__MAX_MAP_RECT__.left + __MAX_MAP_RECT__.width, i[0].position.y};
      i[0].color = __tmp_color; i[1].color = __tmp_color; ++t;
    }
  }
}

inline func Map_M::findActiveObstacle(void) -> void {
  Map_M::__active_obstacle.clear();
  for(const auto& i : Map_M::__obstacle)
    if(i.intersects(sf::Renderable::getViewRect())) Map_M::__active_obstacle.emplace_back(i);
}

inline func Map_M::mathsObsPath(const sf::Align& _side, const sf::Vector2f& _forw) -> sf::Vector2f {
  switch(_side) {
    case(sf::Align::L): case(sf::Align::R): return{0, ((_forw.y < 0) ? -std::fabs(_forw.x) : std::fabs(_forw.x)) + _forw.y};
    case(sf::Align::T): case(sf::Align::B): return{_forw.x + ((_forw.x < 0) ? -std::fabs(_forw.y) : std::fabs(_forw.y)), 0};
    default: return _forw;
  }
}

inline func Map_M::mathsObsSide(const sf::FloatRect& _this) -> sf::Align {
  if(_this.intersects(sf::Renderable::getViewRect())) {
    sf::FloatRect __rinter{};
    for(const auto& i : Map_M::__active_obstacle) {
      if(_this.intersects(i, __rinter))  {
             if(__rinter.width == __rinter.height) break;
        else if(__rinter.width <  __rinter.height)
             return (_this.left < i.left) ? sf::Align::L : sf::Align::R;
        else return (_this.top  < i.top)  ? sf::Align::T : sf::Align::B;
      }
    }
  } return sf::Align::C;
}

inline func Map_M::inMap(void) -> bool {
  return Char_M::Duck::__v->__realRect.intersects(this->__map_boundary.getRect());
}

inline func Map_M::draw(void) -> void {
  this->findActiveObstacle();
  
  static size_t __sec_saver{0};
  if(!this->inMap() && !Char_M::Duck::__v->noBlood()) {
    if(__sec_saver > 5) {
      __SEND_MSG__(L"⚠ 已超出地图边界过久, 脑神经信号丢失", 0);
      Char_M::Value::autophagy();
    }
    else if(__sec_saver != static_cast<size_t>(__outMapTimer.getTime().asSeconds())) {
            __sec_saver  = static_cast<size_t>(__outMapTimer.getTime().asSeconds());
      __SEND_MSG__(L"⚠ 已超出地图边界, 需在 " + std::to_wstring(5 - static_cast<int>(__sec_saver)) + L"s 内返回", 0);
    } __outMapTimer.start();
  } else {
    __outMapTimer.reset();
    __sec_saver = 0;
  }
  
  for(auto& i : this->__s_tree) if(i.getGlobalBounds().intersects(sf::Renderable::getViewRect())) {
    // 遮挡
    if((i.getGlobalBounds() + sf::FloatRect{170, 160, -400, -400})
       .intersects(Char_M::Duck::__v->__s.getGlobalBounds()))
         i.setColor(i.getColor() | 100);
    else i.setColor(i.getColor() | 255);
    // 绘制
    Char_M::__drawList.emplace_back(
      std::make_pair<const sf::Vector2f&, sf::Drawable*>(
        sf::align({}, i.getGlobalBounds(), sf::Align::B) - sf::Vector2f{0, 80}, &i));
    // 活跃的障碍物
    Map_M::__active_obstacle.emplace_back(sf::FloatRect{
    i.getPosition().x + 220,
    i.getPosition().y + 420,
    sf::Fm::getSize(i).x - 450,
    sf::Fm::getSize(i).y - 520});
  }
  
  size_t __left{0}, __right{0};
  if(sys::__jcontext["General"]["MapGrids"].GetBool()) {
    __left  = this->dichotomy(true);
    __right = __left + static_cast<int>((_RendererSize.x / 100) + 2);
    if(__right >= this->__grid.first.size()) __right = this->__grid.first.size();
    for(size_t i{__left}; i < __right; ++i)
      _Renderer.draw(this->__grid.first.at(i));
    
    __left  = this->dichotomy(false);
    __right = __left + static_cast<int>((_RendererSize.y / 100) + 2);
    if(__right >= this->__grid.second.size()) __right = this->__grid.second.size();
    for(size_t i{__left}; i < __right; ++i)
      _Renderer.draw(this->__grid.second.at(i));
  }
  
  _Renderer.draw(this->__map_boundary);
}

inline func Map_M::dichotomy(bool is_first) -> size_t {
  size_t left{0};
  size_t right{is_first ? this->__grid.first.size() 
                        : this->__grid.second.size()};
  float target{is_first ? sf::Renderable::getViewPosition().x
                        : sf::Renderable::getViewPosition().y};
  
  const static func fn = [this](int i, bool is) -> float {
    return is ? this->__grid.first [i][0].position.x
              : this->__grid.second[i][0].position.y;
  };
  
  int middle{0};
  while(left < right) {
    middle = left + ((right - left) / 2);
         if(fn(middle, is_first) - target >  50) right = middle;
    else if(fn(middle, is_first) - target < -50) left  = middle + 1;
    else return middle;
  }      return middle;
}
