UiView_M::UiView_Manager(void) {
  this->__viewpos.setSize(
 (this->__view = _Renderer.getDefaultView()).getSize());
  this->__viewpos.setFillColor(sf::Color::Transparent);
  this->__viewpos.setOutlineThickness(0);
  this->__viewpos.setTag<float>(0.0f);

  this->__msg.setTitleTextColor(sf::Color::Red);
  this->__msg.setRounded(false, sf::Align::RB);
  this->__msg.setRounded(false, sf::Align::L);
  this->__msg.getBase().setOutlineThickness(3);
  this->__msg.getInfo().setFont(res::__font);
  this->__msg.getInfo().setAutoLineBreakEnable(true);
  
  this->__ipt.setRounded(false, sf::Align::RB);
  this->__ipt.setRounded(false, sf::Align::L);
  this->__ipt.getInput().move({0, 40});
  this->__ipt.getInput().setPerHeight("30%");
  this->__ipt.getInput().setTextAlign(sf::Align::T);
  this->__ipt.getInput().getText().setCharacterSize(120);
  this->__ipt.getInput().setTextColor(sf::ColorEx::LightBlue);
  this->__ipt.getBase().setOutlineThickness(3);
  
  this->fix_darkMode();
  
  this->__back.setSize(static_cast<sf::Vector2f>(res::ui::__back[0]->getSize()) / 7.0f);
  this->__back.getBase().setTexture(res::ui::__back[0].get(), true);
  this->__back.__ATTRIBUTE__.__ALWAYS_TOUCHABLE__ = true;
  this->__back.setOutlineThickness(0);
  
  this->__bubble_msg.setSize({500, 100});
  this->__bubble_msg.setBuilder(this->__viewpos, sf::Vector2f{0, 200}, sf::Vector2b{true, false});
  this->__bubble_msg.setText(L"", res::__font, 50);
  this->__bubble_msg.setTextAlign(sf::Align::L) += {50, 0};
  this->__bubble_msg.setTextColor(sf::Color::Black);
  this->__bubble_msg.setFillColor(sf::ColorEx::LightBlue);
  this->__bubble_msg.mov.setAuto(true);
  this->__bubble_msg.setTag<int>(0);
  
  this->__bubble_msg_blinker.setSize({500, 100});
  this->__bubble_msg_blinker.setBuilder(this->__viewpos, sf::Vector2f{0, 200}, sf::Vector2b{true, false});
  this->__bubble_msg_blinker.setFillColor(
    sys::__darkMode ? sf::Color::White : sf::Color::Black);
  this->__bubble_msg_blinker.mov.setAuto(true);
}

inline func UiView_M::update(void) -> void {
  // camera
  if(!this->__cameraOnceUnlock) {
    if(sys_acti::__actype == sys_acti::ActivityType::Play && !sys_acti::__isLoading && Char_M::Duck::__v.operator bool()) {
      this->__view.setCenter(sf::Fm::getCenter(Char_M::Duck::__v->__s) + Control_M::__move_obsr * 180.0f);
      _Renderer.setView(this->__view);
    }
  } else {
    this->__cameraOnceUnlock = false;
    if(!this->__cameraMovePath.empty()) {
        this->__view.move({this->__cameraMovePath.front()});
        this->__cameraMovePath.pop();
        _Renderer.setView(this->__view);
    }
  }
  
  // view
  this->__view = _Renderer.getView();
  this->__viewpos.setPosition(sf::Renderable::getViewPosition());
  
  if(sys::__camShake
  && sys_acti::__actype == sys_acti::ActivityType::Play
  && !sys_acti::__isLoading && Char_M::Duck::__v.operator bool())
    this->__viewpos.move(Control_M::__move_move * Char_M::Value::__speed_f * 2.0f);
  
  this->__msg.setCenter(_Renderer.getView().getCenter());
  
  // bubble
  if(this->__bubble_msg_queue.size() && !this->__bubble_msg.getTag<int>()) {
     this->__bubble_msg.setTextString(this->__bubble_msg_queue.front().first);
     this->__bubble_msg.setFillColor (this->__bubble_msg_queue.front().second);
                                      this->__bubble_msg_queue.pop();
     this->__bubble_msg_clock.restart();
     this->__bubble_msg.setTag<int>(1);
     
     this->__bubble_msg.mov.apply(sf::MoveMethod::linear_down(
       {-this->__bubble_msg.getSize().x, 0}, {-36, 0}, 25.0f * sys::tickSync()));
     this->__bubble_msg_blinker.mov.apply(sf::MoveMethod::linear_down(
       {-this->__bubble_msg_blinker.getSize().x - 10, 0}, {-50, 0}, 25.0f * sys::tickSync()));
  }
  else if(this->__bubble_msg.getTag<int>() == 1 && this->__bubble_msg_clock.getElapsedTime().asSeconds() >= 4 && this->__bubble_msg.mov.isEnd() && !this->__bubble_locked) {
    this->__bubble_msg.setTag<int>(2);
    
    this->__bubble_msg.mov.apply(sf::MoveMethod::linear_down(
      {this->__bubble_msg.getSize().x + 50, 0}, {50, 0}, 25.0f * sys::tickSync()));
    this->__bubble_msg_blinker.mov.apply(sf::MoveMethod::linear_down(
      {this->__bubble_msg_blinker.getSize().x + 80, 0}, {36, 0}, 25.0f * sys::tickSync()));
  }
  else if(this->__bubble_msg.getTag<int>() == 2 && this->__bubble_msg.mov.isEnd()) {
     this->__bubble_msg_blinker.setBuildPosition({0.0f, this->__bubble_msg_blinker.getBuildPosition().y});
     this->__bubble_msg.setBuildPosition({0.0f, this->__bubble_msg.getBuildPosition().y});
     this->__bubble_msg.setTag<int>(0);
  }
}

inline func UiView_M::reset(void) -> void {
  sf::ScrollableView::setHorizontalMoveEnable(false);
  sf::ScrollableView::  setVerticalMoveEnable(false);
  _Renderer.setView(_Renderer.getDefaultView());
  
  this->__bubble_locked = false;
  this->__back.setTouchEnable((this->__back.__ATTRIBUTE__.__VISIBLE__ = true));
  this->__back.setPosition({});
  this->__back.delBuilder();
}

inline func UiView_M::draw(void) -> void {
  static sf::Clock __wait_for_msg{};
  if(this->__msg.getQueueSize() && __wait_for_msg.getElapsedTime().asSeconds() >= 1)
     this->__msg.pushQueue();
  if(this->__msg.isPushing()) __wait_for_msg.restart();
  
  sf::Renderable::draw(this->__msg, this->__ipt);
     
  if(this->__bubble_msg.getTag<int>())
    sf::Renderable::draw(this->__bubble_msg_blinker, this->__bubble_msg);
   
  if(this->__flashClock.getElapsedTime().asSeconds() <= this->__viewpos.getTag<float>())
    sf::Renderable::draw(this->__viewpos);
}

inline func UiView_M::flashScreen(const sf::Color& __flashColor, float __flashTime) -> void {
  this->__viewpos.setFillColor(__flashColor);
  this->__viewpos.setTag<float>(__flashTime);
  this->__flashClock.restart();
}

inline func UiView_M::bubble(const sf::String& __s, const sf::Color& __c, bool __repeatable) -> void {
  this->__bubble_locked = false;
  if(__repeatable || this->__bubble_msg_queue.empty() || this->__bubble_msg_queue.back().first != __s)
    this->__bubble_msg_queue.push({__s, __c});
}
inline func UiView_M::bubble_is_lock(void) -> bool {
  return this->__bubble_locked;
}
inline func UiView_M::bubble_lock(void) -> void {
  this->__bubble_locked = true;
}
inline func UiView_M::bubble_unlock(void) -> void {
  this->__bubble_locked = false;
}

inline func UiView_M::fix_darkMode(void) -> void {
  this->__msg.setMaskColor((sys::__darkMode
  ? sf::Color::Black : sf::Color::White) | 155);
  this->__msg.getBase().setFillColor(sys::__darkMode
  ? __DARK_COLOR_MSG__ : sf::Color::White);
  this->__msg.getInfo().setTextColor(sys::__darkMode
  ? __DARK_COLOR_TEXT__ : sf::Color::Black);
  
  this->__ipt.setMaskColor((
    sys::__darkMode ? sf::Color::Black : sf::Color::White) | 155);
  this->__ipt.getInput().setStateColor(
    sys::__darkMode ? __DARK_COLOR_COL__ : sf::Color::White);
  this->__ipt.getInput().getFlasher().getBase().setFillColor(
    sys::__darkMode ? sf::Color::White : sf::Color::Black);
  this->__ipt.getBase().setFillColor(
    sys::__darkMode ? __DARK_COLOR_MSG__ : sf::Color::White);
  this->__ipt.setTextColor(
    sys::__darkMode ? __DARK_COLOR_TEXT__ : sf::Color::Black);
  this->__ipt.setInfoTextColor(
    sys::__darkMode ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    
  this->__bubble_msg_blinker.setFillColor(
    sys::__darkMode ? sf::Color::White : sf::Color::Black);
}
