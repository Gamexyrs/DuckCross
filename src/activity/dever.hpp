#define __MAX_TYPES__ 3

const static std::unordered_map<int, std::pair<sf::String, std::vector<sf::String>>> __memberList {
  {0, {L"开发 Developer  /", {
    L"",
    L"GyPro",
  }}},
  
  {1, {L"美术 Artist  /", {
    L"GyPro Art+",
    L"嘎鸭",
  }}},
  
  {2, {L"高级测试 Senior-Tester  /", {
    L"柠猫ฅ(=ＴェＴ=)ฅ",
    L"秘制蘑菇炖排骨",
    L"次元胶囊",
    L"真好君",
  }}},
  
  {__MAX_TYPES__, {L"测试 Tester  /", {
    L"蓝染",
    L"江别",
    L"Aurora",
  }}},
};

func dever(bool inline_call = false) -> sys_acti::ActivityType {
  ui_m->__back.setTouchEnable((ui_m->__back.__ATTRIBUTE__.__VISIBLE__ = inline_call));

  splash_PSEwarning();
  splash_cameraShakeWarning();
  sf::TextDiv __type; {
    __type.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __type.setTextColor(sf::ColorEx::Orange);
    __type.setText(L"", res::__font_ac, 80);
    __type.setPosition({200, 200});
    __type.setTag<int>(-1);
  }
  std::vector<std::pair<sf::TextDiv, float>> __member;
  
reload:
     __type.setTag<int>(__type.getTag<int>() + 1);
  if(__type.getTag<int>() > __MAX_TYPES__) {
    sf::sleep(sf::milliseconds(200));
    if(!inline_call) {
      splash_wait();
      ui_m->__msg.launchQueue({
        .title = L"提示",
        .info  = L"攻击请拖动攻击键进行瞄准，要注意只有在剪刀闭合的那一刻才会对敌人造成伤害",
        .btnTextSize = 60, });
      ui_m->__msg.launchQueue({
        .title = L"提示",
        .info  = L"更多功能详见 右上角→游戏设置 ",
        .btnTextSize = 60, });
           return sys_acti::ActivityType::Play;
    } else return sys_acti::ActivityType::Settings;
  }

  __type.setTextString(__memberList.find(
  __type.getTag<int>())->second.first);
  __type.resizeByText();
  
  __member.clear();
  __member.resize(__memberList.find(__type.getTag<int>())->second.second.size()); int t{-1}; bool __show{true};
  for(auto& i : __member) { ++t;
    i.first.setText(__memberList.find(__type.getTag<int>())->second.second.at(t), res::__font_ac, 110);
    i.first.setTag<int>(__type.getTag<int>() ? ((t % 2) ? -1 : 1) : 1);
    i.first.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    i.first.setTextColor(sys::__darkMode
  ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    i.first.getText().setStyle(
            sf::Text::Style::Italic
          | sf::Text::Style::Bold);
    i.first.resizeByText();
    
    if(i.first.getTag<int>() > 0)
       i.first.setPosition({-i.first.getSize().x - 80.0f,
         __type.getRoot().y + 60.0f + (160.0f * t)});
    else
      i.first.setPosition({_RendererSize.x + 80.0f,
        __type.getRoot().y + 60.0f + (160.0f * t)});
    
    i.second = sf::align(i.first.getSize(), _RendererRect).x
      - 80.0f + 160.0f * -i.first.getTag<int>();
  }

//>>>
  
  sf::Clock __clock;
  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_CLR__ : sf::Color::White)) {
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event))
        return sys_acti::ActivityType::Exit;
      if(ui_m->__back.pollEvent_if(sys::__event))
        return sys_acti::ActivityType::Settings;
    }
    
    bool __has_view{false};
    for(auto& i : __member) {
      if(__show) {
        if(i.first.getTag<int>() > 0) {
          if(float __distance; (__distance = i.second - i.first.getPosition().x) > 0)
               i.first.move((__distance >= 30) ? sys::movtionSync({30, 0}) : sf::Vector2f{__distance, 0});
          else i.first.move({2, 0}); // 滑行
        } else {
          if(float __distance; (__distance = i.first.getPosition().x - i.second) > 0)
               i.first.move((__distance >= 30) ? sys::movtionSync({-30, 0}) : sf::Vector2f{-__distance, 0});
          else i.first.move({-2, 0}); // 滑行
        } __has_view = true;
      } else if(i.first.inView()) {
                i.first.move({55.0f * i.first.getTag<int>(), 0});
        __has_view = true;
      } else if(!__type.getTag<int>()) {
        __has_view = false;
      } sf::Renderable::draw(i.first);
    } if(!__has_view) goto reload;
    
    sf::Renderable::draw(__type);
    sf::Renderable::draw(ui_m->__back);
    
    if(__clock.getElapsedTime().asSeconds() > 3) __show = false;
    
           sys::flashDisplay();
  } return sys_acti::ActivityType::Exit;
}

#undef __MAX_TYPES__