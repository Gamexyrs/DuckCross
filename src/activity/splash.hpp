func splash(void) -> sys_acti::ActivityType {
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
  sf::TextDiv __testO{{{}, _RendererSize}}; {
    __testO.setText(L"- [test only] -" , res::__font_en, 60);
    __testO.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __testO.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __testO.setTextAlign(sf::Align::C);
    __testO.setTextDeviat({-60, 60});
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
  
  sf::ProgressDiv __prog({{}, {500, 20}}); {
    __prog.setText(L"正在准备...", res::__font_ac, 40);
    __prog.setTextAlign(sf::Align::B) += {0, 50};
    __prog.setTextColor(sys::__darkMode ?
      sf::Color::White : sf::Color::Black);
    __prog.getInside().setFillColor(sys::__darkMode ?
      sf::Color::White : sf::Color::Black);
    __prog.setFillColor(sf::Color::Transparent);
    __prog.align(sf::Align::B) -= {60, 300};
    __prog.setBusyRunning(true);
    __prog.setProgress(-1);
    __prog.setTag<int>(0);
  }
  sf::PushButton __delA({180, 40}, __CADPA, 10, sf::Vector2f{80, 5}, sf::Vector2b{true, false}); {
    __delA.setText(L"!删除存档!" , res::__font_ac, 26);
    __delA.setTextAlign(sf::Align::C);
    __delA.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | 160);
    __delA.setStateColor(sf::Color::Transparent, sf::BtnState::None);
    __delA.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
    __delA.setOutlineColor(sf::Color::Red);
  }
  sf::PushButton __delC({180, 40}, __delA, 10, sf::Vector2f{0, 10}, sf::Vector2b{false, true}); {
    __delC.setText(L"!重置设置!" , res::__font_ac, 26);
    __delC.setTextAlign(sf::Align::C);
    __delC.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | 160);
    __delC.setStateColor(sf::Color::Transparent, sf::BtnState::None);
    __delC.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
    __delC.setOutlineColor(sf::Color::Red);
  }
  
  if(sys::__activated && !sys::__device_id.empty() && __acidData.find(sys::__device_id) != __acidData.end())
    ui_m->bubble(L"欢迎 " + __acidData.find(sys::__device_id)->second + L" !", sf::ColorEx::LightPink);
  
  bool __quick_reload{Arc_M::loadJ_t()};
  bool __require_reload{false};
  sf::Clock __clock{};
  
  // 无法找到默认字体
  if(res::__regular_font_load_fault)
    ui_m->__msg.launchQueue({
      .title = L"Error:Res(UB)",
      .info  = L"cannot load system default font:\n  \"NotoSansCJK-Regular.ttc\"\nplease download the full package.",
      .font = &res::__font_en,
      .btn = {{{L"Exit"}, 999}},
      .btnTextSize = 60,
    }, true);
  
  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_CLR__ : sf::Color::White)) {
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event)
      || ui_m->__msg.pollEvent(sys::__event))
        return sys_acti::ActivityType::Exit;
      if(__delA.pollEvent_if(sys::__event)) {
        Arc_M::clear(); __clock.restart();
        ui_m->bubble(L"已删除存档!", sf::ColorEx::Orange);
      }
      if(__delC.pollEvent_if(sys::__event)) {
        sys::saveJ(true); __clock.restart();
        ui_m->fix_darkMode(); res::update();
        ui_m->bubble(L"已重置设置!", sf::ColorEx::Orange);
      }
    }
    
    sf::Renderable::draw(__CADPA,
      __duckC, __testO, __copyR,
      __prog, __delA, __delC);
    
    if(!sf::Msgable::getLocked()) {
      sys::checkNavigationBar();
      
      if(__quick_reload) {
        Arc_M::__trRun_l = true;
            
        while(!Arc_M::__load_ok) {}
               Arc_M::__load_ok = false;
           
        if(__require_reload) { __prog.setTag<int>(0); __clock.restart(); __require_reload = false; } // 清除存档
           
        sys_acti::__isLoading = false;
        return sys_acti::ActivityType::Unknown;
        
      }
      else {
        if(__prog.getTag<int>() == 2 && __clock.getElapsedTime().asSeconds() >= 2.0f) {
          if(__require_reload) { __prog.setTag<int>(0); __clock.restart(); __require_reload = false; } // 清除存档
          
                 sys_acti::__isLoading = false;
          return sys_acti::ActivityType::Unknown;
        }
        else if(__prog.getTag<int>() == 1) {
          if(Arc_M::__load_ok) {
             Arc_M::__load_ok = false;
             
             __prog.setTextString(L"准备就绪");
             __prog.setTag<int>(2);
             __prog.setProgress(-1);
             __clock.restart();
          } else if(Arc_M::__all_process) {
            __prog.setTextString(L"正在加载...[" + std::to_wstring(Arc_M::__process)
                                          + L"/" + std::to_wstring(Arc_M::__all_process) + L"]");
            __prog.setProgress(Arc_M::__process, Arc_M::__all_process);
          } else {
            __prog.setTextString(L"正在加载...");
            __prog.setProgress(-1);
          }
        }
        else if(__prog.getTag<int>() == 0 && __clock.getElapsedTime().asSeconds() >= 0.5f) {
          __prog.setTextString(L"正在加载...");
          __prog.setTag<int>(1);
          
          Arc_M::__trRun_l = true;
        }
      }
    }
    
           sys::flashDisplay();
  } return sys_acti::ActivityType::Exit;
}
