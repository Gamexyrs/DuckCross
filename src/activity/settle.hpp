func mathsPoints(void) -> unsigned long {
  unsigned long r{0};
  
  // 击杀
  r += Char_M::data.killedNum.__ordi * 20;
  r += Char_M::data.killedNum.__spec * 600;
  r += ChickBoss::__boss_died * 2000;
  
  // 等级
  r += Char_M::Value::__level * 150;
  
  // 金币
  r += Storage_M::__buf.size(sis::Item::Coin) * 2;
  
  // 存活
  r += Arc_M::__playTime.asSeconds();
  
  return r;
}

func mathsDetail(void) -> sf::String {
  return sf::String{std::wstring{}
    + L"\n击杀 ——————\n   "
    + L"普通 " + std::to_wstring(Char_M::data.killedNum.__ordi) + L" 只 → +"
    + std::to_wstring(static_cast<unsigned long>(Char_M::data.killedNum.__ordi * 20))
    + L"\n   精英 " + std::to_wstring(Char_M::data.killedNum.__spec) + L" 只 → +"
    + std::to_wstring(static_cast<unsigned long>(Char_M::data.killedNum.__spec * 600))
    + L"\n   首领 " + (ChickBoss::__boss_died ? L"鸡霸 已击杀" : L"未击杀") + L" → +"
    + std::to_wstring(static_cast<unsigned long>(ChickBoss::__boss_died * 2000))
    
    + L"\n等级 ——————\n   "
    + std::to_wstring(Char_M::Value::__level) + L" 级 → +"
    + std::to_wstring(static_cast<unsigned long>(Char_M::Value::__level * 150))

    + L"\n金币 ——————\n   "
    + std::to_wstring(Storage_M::__buf.size(sis::Item::Coin)) + L" 个 → +"
    + std::to_wstring(static_cast<unsigned long>(Storage_M::__buf.size(sis::Item::Coin) * 2))

    + L"\n存活 ——————\n   "
    + std::to_wstring(static_cast<unsigned long>(Arc_M::__playTime.asSeconds())) + L" 秒 → +"
    + std::to_wstring(static_cast<unsigned long>(Arc_M::__playTime.asSeconds()))};
}

func mathsDetail_data(void) -> sf::String {

  sf::String __hpa{};
  
  if(Char_M::Value::__total_attk
  == Char_M::Value::__total_hit) __hpa = L"100";
  else if(!Char_M::Value::__total_attk
       || !Char_M::Value::__total_hit) __hpa = L"0";
  else (__hpa = std::to_wstring(
    static_cast<int>(
      static_cast<float>(Char_M::Value::__total_hit)
    / static_cast<float>(Char_M::Value::__total_attk) * 1000))).insert(2, L".");
  
  return sf::String{std::wstring{}
    + L"        累计伤害量\t" + std::to_wstring(Char_M::Value::__total_attkV)
    + L"\n      累计治疗量\t" + std::to_wstring(Char_M::Value::__total_cureV)
    + L"\n    总移动距离\t" + std::to_wstring(static_cast<int>(Char_M::Value::__total_move))
    + L"\n  攻击命中率\t" + -__hpa + L"%"};
}

func settle(void) -> sys_acti::ActivityType {
  sys::__audio->call_next("bgm_backstage");

  FakePay __fakepay{res::__font_ac, res::__font_en, "./src/res/img/sgv/coin.png", "./src/res/img/sgv/ui/accept.png"};

  sf::TextDiv __points{}; {
    __points.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __points.getText().setStyle(sf::Text::Style::Bold);
    __points.setText(L"0", res::__font_en, 200);
    __points.resizeByText();
    __points.align(sf::Align::C) -= {40, 120};
    __points.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __points.mov.apply(sf::MoveMethod::quadratic_down(__points.getPosition(),
      {340, __points.getPosition().y - 160}, {}, 80.0f * sys::tickSync()));
  }
  
  unsigned long __points_count{mathsPoints()},
                __max_points_previ{Acc_M::getMaxPoints()};
  bool __signal_newRecord{Acc_M::checkMaxPoints(__points_count)};
  
  sf::Div __line{{{-600, __points.getRoot().y - 70}, {600, 0}}}; {
    __line.getBase().setOutlineColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __line.mov.apply(sf::MoveMethod::linear_down(
      {600, 0}, {}, 120.0f * sys::tickSync()));
  }
  
  sf::TextDiv __info{{{30, _RendererSize.y - 35}, {}}}; {
    __info.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __info.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | 160);
    __info.setText(std::wstring{L"2022-2025 Gamexyrs© all copyrights reserved"}
    + L"   _appVersion: " + std::to_wstring(sys::__apkVer)
    + L"   _UID: " + std::to_wstring(sys::__device_id), res::__font_en, 30);
  }
  
  sf::TextDiv __detail{{}, __line, 0, {40, -30}}; {
    __detail.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __detail.setTextColor(sf::Color::Black);
    __detail.getText().setLineSpacing(1.05);
    __detail.setText(mathsDetail(), res::__font_ac, 30);
    __detail.resizeByText();
    __detail.move({-__detail.getSize().x * 1.2f, 0});
    __detail.mov.apply(sf::MoveMethod::linear_down(
      {__detail.getSize().x * 1.4f, 0}, {}, 120.0f * sys::tickSync()));
  }
  
  sf::VertexArray __detailBkg{sf::PrimitiveType::TriangleStrip, 4};
  __detailBkg[0].position = {-680, __detail.getPosition().y + 38};
  __detailBkg[1].position = {0, __detail.getPosition().y + 38};
  __detailBkg[2].position = {-680, __detail.getRoot().y + 50};
  __detailBkg[3].position = {-140, __detail.getRoot().y + 50};
  __detailBkg[0].color = sf::Color::Red;
  __detailBkg[1].color = sf::Color::Blue;
  __detailBkg[2].color = sf::Color::Green;
  __detailBkg[3].color = sf::Color::Yellow;
  int ColorPer{0};
  
  sf::TextDiv __detail_data{}; {
    __detail_data.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
    __detail_data.setTextColor(sf::Color::Black | 0);
    __detail_data.getText().setLineSpacing(1.4f);
    __detail_data.setText(mathsDetail_data(), res::__font_ac, 50);
    __detail_data.resizeByText();
  }
  sf::VertexArray __detail_dataBkg{sf::PrimitiveType::TriangleStrip, 4};
  __detail_dataBkg[0].position = {_RendererSize.x + 140, __detailBkg[0].position.y};
  __detail_dataBkg[1].position = {_RendererSize.x + 140 + _RendererSize.x - 710, __detailBkg[1].position.y};
  __detail_dataBkg[2].position = {_RendererSize.x, __detailBkg[2].position.y};
  __detail_dataBkg[3].position = {_RendererSize.x + 140 + _RendererSize.x - 710, __detailBkg[3].position.y};
  __detail_dataBkg[0].color = __detailBkg[1].color;
  __detail_dataBkg[1].color = sf::Color::Transparent;
  __detail_dataBkg[2].color = __detailBkg[3].color;
  __detail_dataBkg[3].color = sf::Color::Transparent;
  
  Arc_M::clear();
  
  std::vector<sf::VertexArray> __sharpFlag{3}; int t{-1};
  for(auto& i : __sharpFlag) { ++t;
    i.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    i.resize(4);
    i[0].position = {__line.getSize().x + 400 + 400 * t, 0};
    i[1].position = {__line.getSize().x + 600 + 400 * t, 0};
    i[2].position = {__line.getSize().x + 200 + 400 * t, _RendererSize.y - 100 * t};
    i[3].position = {__line.getSize().x + 400 + 400 * t, _RendererSize.y - 100 * t};
    i[0].color = sf::Color::Yellow;
    i[1].color = sf::Color::Yellow;
    i[2].color = sf::Color::Transparent;
    i[3].color = sf::Color::Transparent;
  }
  
  sf::PushBtn __skip{{{}, {360, 80}}}; {
    __skip.setStateColor(sf::ColorEx::LightBlue | 100);
    __skip.align(sf::Align::LB);
    __skip.setText(L"跳过 >", res::__font_ac, 50);
    __skip.setTextAlign(sf::Align::C);
    __skip.setTextColor(sys::__darkMode
     ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __skip.mov.apply(sf::MoveMethod::linear_down(
      {0, 200}, {}, 120.0f * sys::tickSync()));
  }
  
  sf::PushBtn __capture{{{-200, 80}, {180, 40}}, 8}; {
    __capture.setText(L"截屏" , res::__font_ac, 26);
    __capture.setTextAlign(sf::Align::C);
    __capture.setTextColor((sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black) | 160);
    __capture.setStateColor(sf::Color::Transparent, sf::BtnState::None);
    __capture.setStateColor(sf::ColorEx::Grey, sf::BtnState::Pressed);
    __capture.setOutlineColor(sf::Color::Red);
    __capture.mov.apply(sf::MoveMethod::linear_down(
      {210, 0}, {}, 120.0f * sys::tickSync()));
  } bool __require_capture{false};
  
  sf::PushBtn __back{{{}, {360, 120}}}; {
    __back.setStateColor(sf::Color::Green | 100, sf::BtnState::Pressed);
    __back.setStateColor(sf::Color::Green | 140, sf::BtnState::None);
    __back.align(sf::Align::RB) += {__back.getSize().x * 1.2f, -270.0f};
    __back.getText().setStyle(sf::Text::Style::Underlined);
    __back.setText(L"支付测试 >", res::__font_ac, 50);
    // __back.setText(L"庇护所 >", res::__font_ac, 50);
    __back.setTextAlign(sf::Align::C);
    __back.setTextColor(sys::__darkMode
     ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __back.mov.apply(sf::MoveMethod::linear_down(
       {-180 - __back.getSize().x * 1.1f, 0}, {}, 120.0f * sys::tickSync()));
  }
  
  sf::PushBtn __restart{{{}, {360, 120}}}; {
    __restart.setStateColor(sf::Color::Green | 100, sf::BtnState::Pressed);
    __restart.setStateColor(sf::Color::Green | 140, sf::BtnState::None);
    __restart.align(sf::Align::RB) += {__restart.getSize().x * 1.2f, -100.0f};
    __restart.getText().setStyle(sf::Text::Style::Underlined);
    __restart.setText(L"重新开始 >", res::__font_ac, 50);
    __restart.setTextAlign(sf::Align::C);
    __restart.setTextColor(sys::__darkMode
     ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __restart.mov.apply(__back.mov.getPath());
  }
  
  sf::Clock __clock{}, __wait_for_capture{};
  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_CLR__ : sf::Color::White)) {
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event))
        return sys_acti::ActivityType::Exit;
      if(__skip.pollEvent_if(sys::__event)) {
        __points.setTextString(std::to_wstring(__points_count));
      }
      if(__capture.pollEvent_if(sys::__event)) {
        __wait_for_capture.restart();
        if(__capture.mov.isEnd() && __detail_data.getTextColor().a == 255)
           __require_capture = true;
        else ui_m->__msg.launchQueue({
          .title = L"提示", .info = L"界面动画正在进行中, 请稍后再试",
          .btn = {{L"确定", 0}},
          .btnTextSize = 60,
        }, true);
      }
      if(__back.pollEvent_if(sys::__event)) {
        // ui_m->__msg.launchQueue({
          // .title = L"提示", .info = L"暂未开放!",
          // .btn = {{L"确定", 0}},
          // .btnTextSize = 60,
        // }, true);
        __fakepay.call(L"648.00");
      }
      if(__restart.pollEvent_if(sys::__event)) {
        sys::__audio->call_next_play();
        Arc_M::__playTime = sf::Time::Zero;
        return sys_acti::ActivityType::Play;
      }
      if(ui_m->__msg.pollEvent(sys::__event)) {}
      
      __fakepay.pollEvent(sys::__event);
    }
    
    if(unsigned long __now{std::stoul(__points.getTextString().toAnsiString())},
      __dist{__points_count - __now}; __dist > 0) {
      if(__clock.getElapsedTime().asMilliseconds() >= 2) {
        int __plus{(__dist >= 1000) ? 51 : ((__dist >= 300) ? 11 : 1)};
        __clock.restart(); __points.setTextString(std::to_string(__now + __plus));
        __points.resizeByText(); __points.align(sf::Align::C) -= {40, 120};
        if(__signal_newRecord && !ui_m->bubble_is_lock() && __now + __plus > __max_points_previ) {
          ui_m->bubble(L"新历史高分!", sf::Color::Yellow);
          ui_m->bubble_lock();
        }
      }
    } else if(!__points.getTag<bool>()) {
               __points.setTag<bool>(true);
      __restart.mov.setAuto(true);
      __detail. mov.setAuto(true);
      __detail_data.mov.setAuto(true);
      __points. mov.setAuto(true);
      __capture.mov.setAuto(true);
      __skip.   mov.setAuto(true);
      __back.   mov.setAuto(true);
      __line.   mov.setAuto(true);
    }
    
    if(__detailBkg[0].position.x < 0 && __points.getTag<bool>()) {
       __detailBkg[0].position.x += 8.0f;
       __detailBkg[1].position.x += 8.0f;
       __detailBkg[2].position.x += 8.0f;
       __detailBkg[3].position.x += 8.0f;
    }
    if(__detail_dataBkg[0].position.x > 710 && __points.getTag<bool>()) {
       __detail_dataBkg[0].position.x -= 16.0f;
       __detail_dataBkg[1].position.x -= 16.0f;
       __detail_dataBkg[2].position.x -= 16.0f;
       __detail_dataBkg[3].position.x -= 16.0f;
    } else if(__detail_dataBkg[0].position.x < 710) {
       __detail_dataBkg[0].position.x = 710;
       __detail_dataBkg[1].position.x = _RendererSize.x;
       __detail_dataBkg[2].position.x = 710 - 140;
       __detail_dataBkg[3].position.x = _RendererSize.x;
    }
    if(__detail_data.getTextColor().a < 255 && __points.getTag<bool>() && __detail.mov.isEnd()) {
       __detail_data.setPosition({
         __detail_dataBkg[2].position.x,
         __detail_dataBkg[0].position.y + 48});
       __detail_data.setTextColor(
          __detail_data.getTextColor()
       | (__detail_data.getTextColor().a + 5));
    }
    switch(ColorPer) {
      case(0): {
        __detailBkg[0].color.r -= (__detailBkg[0].color.r ? 5 : 0); __detailBkg[0].color.b += 5;
        __detailBkg[1].color.b -= (__detailBkg[1].color.b ? 5 : 0); __detailBkg[1].color.r = (__detailBkg[1].color.g += 5);
        __detailBkg[2].color.g -= (__detailBkg[2].color.g ? 5 : 0); __detailBkg[2].color.r += 5;
        __detailBkg[3].color.r -= (__detailBkg[3].color.r ? 5 : 0);
        if(!(__detailBkg[0].color.r)) ++ColorPer;
      } break;
      case(1): {
        __detailBkg[0].color.b -= (__detailBkg[0].color.b ? 5 : 0); __detailBkg[0].color.r = (__detailBkg[0].color.g += 5);
        __detailBkg[1].color.r -= (__detailBkg[1].color.r ? 5 : 0);
        __detailBkg[2].color.r -= (__detailBkg[2].color.r ? 5 : 0); __detailBkg[2].color.b += 5;
        __detailBkg[3].color.g -= (__detailBkg[3].color.g ? 5 : 0); __detailBkg[3].color.r += 5;
        if(!(__detailBkg[0].color.b)) ++ColorPer;
      } break;
      case(2): {
        __detailBkg[0].color.r -= (__detailBkg[0].color.r ? 5 : 0);
        __detailBkg[1].color.g -= (__detailBkg[1].color.g ? 5 : 0); __detailBkg[1].color.r += 5;
        __detailBkg[2].color.b -= (__detailBkg[2].color.b ? 5 : 0); __detailBkg[2].color.r = (__detailBkg[2].color.g += 5);
        __detailBkg[3].color.r -= (__detailBkg[3].color.r ? 5 : 0); __detailBkg[3].color.b += 5;
        if(!(__detailBkg[0].color.r)) ++ColorPer;
      } break;
      case(3): {
        __detailBkg[0].color.g -= (__detailBkg[0].color.g ? 5 : 0); __detailBkg[0].color.r += 5;
        __detailBkg[1].color.r -= (__detailBkg[1].color.r ? 5 : 0); __detailBkg[1].color.b += 5;
        __detailBkg[2].color.r -= (__detailBkg[2].color.r ? 5 : 0);
        __detailBkg[3].color.b -= (__detailBkg[3].color.b ? 5 : 0); __detailBkg[3].color.r = (__detailBkg[3].color.g += 5);
        if(!(__detailBkg[0].color.g)) ColorPer = 0;
      } break;
    }
    __detail_dataBkg[0].color = __detailBkg[1].color;
    __detail_dataBkg[2].color = __detailBkg[3].color;
    
    sf::Renderable::draw(__line, __detailBkg, __info, __detail);
    
    for(auto& i : __sharpFlag) sf::Renderable::draw(i);
    
    sf::Renderable::draw(__detail_dataBkg, __detail_data);
    
    sf::Renderable::draw(__points);
    
    if(!__require_capture)
      sf::Renderable::draw(__skip, __back, __restart, __capture);
    
    __fakepay.draw();
    
    sys::flashDisplay();
    if(__require_capture && __wait_for_capture.getElapsedTime().asMilliseconds() >= 800) {
       __require_capture = false;
      system("mkdir -p /storage/emulated/0/Pictures/com.gamexyrs.duckcross.mx/");
      std::string __savePath{std::string{"/storage/emulated/0/Pictures/"} + __PACKAGE__ + "/__settle_capture_" + std::to_string(__points_count) + "_in" + std::to_string(std::time(0)) + ".png"};
      ui_m->__msg.launchQueue({
        .title = L"提示", .info = L"图片已保存为:\n" + std::to_wstring(__savePath),
        .btn = {{L"确定", 0}},
        .btnTextSize = 60,
      }, true);
      sf::Renderable::capture().saveToFile(__savePath);
    }
  } return sys_acti::ActivityType::Exit;
}
