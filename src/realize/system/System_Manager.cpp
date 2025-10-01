inline func sys::tickSync(void) -> float {
  return (sys::__fps ?: 60.0f) / 60.0f;
}

inline func sys::movtionSync(const sf::Vector2f& mov) -> sf::Vector2f {
  return mov * (60.0f / (sys::__fps ?: 60.0f));
}

inline func sys::init(sf::RenderWindow* __token) -> void {
  sf::Renderable::setRenderer(*__token);

  __token->setVerticalSyncEnabled(
    sys::__jcontext["Graphics"]["VerticalSync"].GetBool());
  
  sys_acti::__actype = static_cast<sys_acti::ActivityType>(sys::__jcontext["Actype"].GetUint());
  if(sys_acti::__actype == sys_acti::ActivityType::Settle)
     sys_acti::__actype =  sys_acti::ActivityType::Play;

  // sys::__rander.seed(std::time(0));
  std::srand(std::time(0));
  sys::load_device_id();
}

inline func sys::drawDebugList(void) -> void {
  for(auto& i : sys::__debugList) {
    sf::Renderable::draw(*i);
  } sys::__debugList.clear();
}

inline func sys::flashDisplay(bool update_ui) -> void {
  if(update_ui) {
    ui_m->update();
    ui_m->draw();
  }
  
  sys::__audio->update();
  _Renderer.display();
  sys::__fps = sf::Renderable::getFPS_loopEndf();
  
  // 检查激活
  if(!sys::__activated && Arc_M::__joinable && !ui_m->__msg.getQueueSize()) {
    ui_m->__msg.launchQueue({
      .title = L"提示",
      .info  = L"该设备未激活！请前往 设置→账户 进行激活",
      .btn = {{L"设置", 101}}, .btnTextSize = 60, });
  }
}

inline func sys::fix_pollEvent(sf::Event& event) -> bool {
  bool __v{_Renderer.pollEvent(event)};
  
  if(__v && event.type == sf::Event::SensorChanged) {
    static size_t __fingerNum{0};
    
    size_t __now_n{0};
    for(int i{0}; sf::Touch::isDown(i); ++i) __now_n++;
    
         if(__now_n > __fingerNum) event.type = sf::Event::TouchBegan;
    else if(__now_n < __fingerNum) event.type = sf::Event::TouchEnded;
    
    __fingerNum = __now_n;
  }
  
  return __v;
}

template<typename m_type>
inline func sys::rand(const sf::Vector2<m_type>& range) -> m_type {
  if(std::numeric_limits<m_type>::is_integer) {
    std::uniform_int_distribution<m_type> __range{/* [ */ range.x, range.y /* ] */};
    return __range(sys::__rander);
  } else {
    std::uniform_real_distribution<m_type> __range{/* [ */ range.x, range.y /* ] */};
    return __range(sys::__rander);
  }
}
inline func sys::rand_bool(void) -> bool {
  std::bernoulli_distribution __range{};
  return __range(sys::__rander);
}

inline func sys::checkNavigationBar(void) -> void {
  if(_Renderer.getSize().x != _Renderer.getView().getSize().x) {
    if(sys::__viwFixed) {
        sys::__jcontext["Control"]["ViewAdapt"].SetUint(0);
        sys::saveJ(); ui_m->__msg.launchQueue({
          .title = L"提示",
          .info  = L"检测到窗口可能被缩放，重启以重新适配。为了最佳体验，该适配可能进行多次",
          .btn = {{L"确定", -1}}, .btnTextSize = 60, }, true);
    } else if(sys::__runTimeClock.getElapsedTime().asSeconds() >= 1) {
      sys::__jcontext["Control"]["ViewAdapt"].SetUint(
        _Renderer.getSize().x - static_cast<int>(_Renderer.getView().getSize().x));
      sys::saveJ(); ui_m->__msg.launchQueue({
        .title = L"提示",
        .info  = L"检测到窗口可能被缩放，重启以重新适配。为了最佳体验，该适配可能进行多次",
        .btn = {{L"确定", -1}}, .btnTextSize = 60, }, true);
    }
  }
}
