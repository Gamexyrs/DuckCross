#include "./internal/controlLayout.hpp"
#include "./internal/updateLog.hpp"

enum class settings_LineType : int {
  None,
  Input,
  Entry,
  Switch,
};

inline static func confirm(const sf::String& inf, int btnY_code = 0,
                           const sf::String& btnN_str = L"") -> void {
  ui_m->__msg.launchQueue({
    .title = L"提示", .info = inf,
    .btn = {{L"确定", btnY_code}, {(btnY_code
      && btnN_str.isEmpty()) ? L"取消" : btnN_str, 0}},
    .btnTextSize = 60,
  }, true);
}

static bool rq_return{false};

inline static func rq_input(const sf::String& range,
    const sf::String& tit = L"",
    const sf::String& inf = L"", int btnY_code = 0) {
  sf::KbEvent::setSettings(range);
  ui_m->__ipt.launchQueue({
    .title = tit, .info  = inf,
    .btn   = {{L"确定", btnY_code}, {L"取消", 0}},
    .btnTextSize = 50,
  }, true);
}

#include "./build/col.hpp"
#include "./build/none.hpp"
#include "./build/input.hpp"
#include "./build/entry.hpp"
#include "./build/switch.hpp"

//>>>

func settings(void) -> sys_acti::ActivityType {
  static int __save_type{0};
  
  sys::__audio->call_next("bgm_backstage");

  sf::Div __typeDiv{{{}, {300, _RendererSize.y}}}; {
    __typeDiv.setFillColor(sys::__darkMode
    ? __DARK_COLOR_CLR__ : sf::Color::White);
    __typeDiv.setOutlineColor(sf::ColorEx::Pink);
    __typeDiv.setOutlineThickness(10);
  }
  
  ui_m->__back.setBuilder(__typeDiv);
  
  // 报告程序
  sf::Image __report_i; {
    __report_i.loadFromFile("./src/res/img/report.png");
  }
  sf::Texture __report_t; {
    __report_t.loadFromImage(__report_i);
    __report_t.setSmooth(true); // mandatory
  }
  sf::PushBtn __report({220, 60}, __typeDiv, 5); {
    __report.align(sf::Align::B) -= {0, 25};
    __report.setTextAlign(sf::Align::C);
    __report.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    __report.setText(L"遇到问题？", res::__font, 30);
    __report.setOutlineColor(__report.getTextColor());
    __report.setStateColor(sf::Color::Transparent, sf::BtnState::None);
  }
  sf::Div __report_tex({200, 200}, __typeDiv, 0, sf::Vector2f{}, sf::Vector2b{false, true}); {
    __report_tex.getBase().setTexture(&__report_t);
    __report_tex.setTag<bool>(false);
    __report_tex.mov.setAuto(true);
  }
  sf::PushBtn __report_back({40, 200}, __report_tex, -1, sf::Vector2f{}, sf::Vector2b{true, false}); {
    __report_tex.align(sf::Align::LB) -= {__report_tex.getSize().x
      + 8.0f + __report_back.getSize().x, __report.getSize().y + 40};
    
    __report_back.setRounded(false, sf::Align::L);
    
    __report_back.setText(L"<", res::__font_en, 30);
    __report_back.setTextDeviat({0, -10});
    __report_back.setTextAlign(sf::Align::C);
    __report_back.setTextColor(sys::__darkMode
    ? __DARK_COLOR_TEXT__ : sf::Color::Black);
    
    __report_tex. setOutlineColor(__report.getTextColor());
    __report_back.setOutlineColor(__report.getTextColor());
    __report_back.setStateColor(sf::Color::Transparent, sf::BtnState::None);
  }
  
  // 设置分类
  std::vector<sf::PushBtn> __typeSelect{__SETTINGS_TYPE__.size()};
  int t = 0; for(auto i =  __typeSelect.begin(); i != __typeSelect.end(); ++i, ++t) {
    if(__SETTINGS_TYPE__[t].first == 07 && !sys::__jcontext["Debug"]["AllowCheat"].GetBool()) continue;
  
    i->setSize({__typeDiv.getSize().x * 0.9f, 90.0f});
    i->setOutlineThickness(0);
    i->setBuilder(__typeDiv);
    i->align(sf::Align::T);
    i->setRadius(14);
    
    i->move({0.0f, 105.0f + (i->getSize().y + 2.0f) * t});
    i->setStateColor((__save_type == t)
    ? sf::ColorEx::Grey | 80
    : sf::Color::Transparent, sf::BtnState::None);
    i->setStateColor(sf::ColorEx::Grey | 60, sf::BtnState::Pressed);
    
    i->setText(__SETTINGS_TYPE__[t].second, res::__font, 50);
    i->getText().setStyle(sf::Text::Style::Bold);
    i->setTextColor(sys::__darkMode ?
      __DARK_COLOR_TEXT__ : sf::Color::Black);
    i->setTextAlign(sf::Align::C);
    i->setTextDeviat({0, -5});
    
    i->setTag<int>(__SETTINGS_TYPE__[t].first);
  }
  
  sf::TextDiv __inf{{_RendererSize.x - __typeDiv.getSize().x - __typeDiv.getBase(false).getOutlineThickness(), 40},
    __typeDiv, 0, {__typeDiv.getBase(false).getOutlineThickness(), 0}, {true, false}}; {
    __inf.setText(L" ⚠ 警告: 这是 DuckCross 的测试版本, 不代表最终效果", res::__font, 30);
    __inf.setFillColor(sf::ColorEx::Orange);
    __inf.setTextColor(sf::Color::Black);
    __inf.setTextAlign(sf::Align::C);
  }
  sf::TextDiv __catch{{_RendererSize.x - __typeDiv.getSize().x - __typeDiv.getBase(false).getOutlineThickness(), 40},
    __typeDiv, 0, {__typeDiv.getBase(false).getOutlineThickness(), __inf.getSize().y}, {true, false}}; {
    __catch.setText(L" ! Err: [ALSOFT] (EE) Failed to set real-time priority for thread: Operation not permitted (1)", res::__font_en, 30);
    __catch.setFillColor(sf::Color::Red);
    __catch.setTextColor(sf::Color::Black);
    __catch.setTextAlign(sf::Align::C);
  }

  sf::ScrollableView::setVerticalMoveEnable(true);
  sf::ScrollableView::setVerticalMax({0, _RendererSize.y * 2.0f});
  
rebuild:
  const auto& __refer = __SETTINGS_TYPE_BUILD__.find(__save_type)->second;
  
  bool __col_initable{!rq_return};
                       rq_return = false; // to slide or not
  std::deque<sf::PushBtn> __col{__refer.size()};
  const float __default_col_x{__typeDiv.getSize().x + 20};
  
  std::deque<std::pair<sf::TextDiv, sf::PushBtn*>> __etr{}, __ipt;
  sf::TextDiv* __iptting{};
  
  std::deque<sf::CheckBtn*>              __btn_color{};
  std::deque<std::pair<sf::Div*, bool>>  __btn_movement{};
  std::deque<std::pair<sf::CheckBtn, sf::Div>> __btn{};
  const sf::Uint8 __btnColorAlpha{140};
  
  for(t = 0; auto& i : __col) {
    i.setRadius(20);
    i.mov.setAuto(true);
    i.setSize({_RendererSize.x - __typeDiv.getSize().x - 40 - sys::__jcontext["Control"]["ViewAdapt"].GetUint(), 100.0f});
    i.setPosition({__default_col_x + (__col_initable ? (80 + 20 * t) : 0), 105.0f + (i.getSize().y + 10.0f) * t});
    i.setTag<int>(std::get<0>(__refer[t]));
    i.setStateColor(sf::ColorEx::Grey | 160, sf::BtnState::None);
    i.setStateColor(sf::ColorEx::Grey | 120, sf::BtnState::Pressed);
    
    i.setText(std::get<1>(__refer[t]), res::__font, 40);
    i.setTextColor(sys::__darkMode ?
      __DARK_COLOR_TEXT__ : sf::Color::Black);
    i.setTextAlign(sf::Align::L);

    switch(std::get<2>(__refer[t])) {
      case(settings_LineType::Input): {
        __ipt.resize(__ipt.size() + 1);
        
        __ipt.back().second = &i;
        __ipt.back().first.setBuilder(i);
        __ipt.back().first.getText().setStyle(sf::Text::Style::Bold);
        __ipt.back().first.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
        __ipt.back().first.setTextColor(sf::ColorEx::makeTrs(sf::Color::Green,
       (__ipt.back().first.getTextString().find(L"(locked)")
             == sf::String::InvalidPos) ? 255 : 130));
        __ipt.back().first.setText(std::get<0>(__SETTINGS_TYPE_BUILD_INPUT__
             .find(std::get<0>(__refer[t]))->second)(&__ipt.back().first), res::__font, 50);
        __ipt.back().first.setTextAlign(sf::Align::R);
        if(__ipt.back().first.getTextDeviat() == sf::Vector2f{})
           __ipt.back().first.setTextDeviat({-50, -10});
        __ipt.back().first.setFrame(i.getFrame());
      } break;
      
      case(settings_LineType::Entry): {
        __etr.resize(__etr.size() + 1);
        
        __etr.back().second = &i;
        __etr.back().first.setBuilder(i);
        __etr.back().first.getText().setStyle(sf::Text::Style::Bold);
        __etr.back().first.__ATTRIBUTE__.__VISIBLE_BASE__ = false;
        __etr.back().first.setText(L">     ", res::__font, 45);
        __etr.back().first.setTextAlign(sf::Align::R);
        __etr.back().first.setTextDeviat({0, -10});
        __etr.back().first.setTextColor(sys::__darkMode
        ? __DARK_COLOR_TEXT__ : sf::Color::Black);
        __etr.back().first.setFrame(i.getFrame());
      } break;
      
      case(settings_LineType::Switch): {
        i.setTouchEnable(false);
        const bool __btnstate = std::get<0>(__SETTINGS_TYPE_BUILD_SWITCH__
             .find(std::get<0>(__refer[t]))->second)();
        __btn.resize(__btn.size() + 1);
        
        __btn.back().first.setRadius(-1);
        __btn.back().first.setBuilder(i);
        __btn.back().first.setSize({150, 60});
        __btn.back().first.align(sf::Align::R) += sf::Vector2f{-20, 0};
        __btn.back().first.setStateColor(sf::ColorEx::makeTrs(sf::Color::Yellow,
          __btnstate ? 0 : __btnColorAlpha));
        __btn.back().first.setChecked(__btnstate);
        
        __btn.back().second.
          setFillColor(sf::Color::White);
        __btn.back().second.setRadius(-1);
        __btn.back().second.setSize({40, 40});
        __btn.back().second.setBuilder(__btn.back().first);
        __btn.back().second.align(__btnstate ? sf::Align::L
        : sf::Align::R) += {__btnstate ? 10.0f : -10.0f, 0.0f};
        __btn.back().second.setFillColor(sf::ColorEx::Silver);
        
        __btn_movement.emplace_back(&__btn.back().second, __btnstate);
        __btn_color.   emplace_back(&__btn.back().first);
      } break;
      
      case(settings_LineType::None): default: {
        i.setTouchEnable(false);
        __SETTINGS_TYPE_BUILD_NONE__
          .find(std::get<0>(__refer[t]))->second(i);
      } break;
    } ++t;
  }

//>>>

  while(sf::Renderable::loopBegin(sys::__darkMode
  ? __DARK_COLOR_CLR__ : sf::Color::White)) {
    sf::TouchEvent::pollEvent(sys::__event);
    while(_Renderer.pollEvent(sys::__event)) {
      if(__ACTIV_EXIT__      (sys::__event)
      || ui_m->__back.pollEvent_if(sys::__event)) {
        sys::saveJ(); __save_type = 0; return sys_acti::ActivityType::Play;
      }
      if(__report.pollEvent_if(sys::__event)
      &&!__report_tex.getTag<bool>()) {
         __report_tex.setTag<bool>(true);
         __report_tex.mov.apply(sf::MoveMethod::linear_down(
               __report_tex.getPosition(),
           {0, __report_tex.getPosition().y},
           {}, 60 / sys::tickSync()), true);
         goto event_end;
      }
      if(__report_back.pollEvent_if(sys::__event)
      && __report_tex.getTag<bool>()) {
         __report_tex.setTag<bool>(false);
         __report_tex.mov.apply(sf::MoveMethod::linear_down(
             __report_tex.getPosition(),
           {-__report_tex.getSize().x - 8.0f
            -__report_back.getSize().x,
             __report_tex.getPosition().y},
           {}, 60 / sys::tickSync()), true);
         goto event_end;
      }
      if(auto r = ui_m->__msg.pollEvent(sys::__event)) {
        if(r.has_value()) switch(r.value()) {
          case(999):  /* 退出 */ return sys_acti::ActivityType::Exit;
          
          case(1000): /* 重置存档 */ Arc_M::clear(); break;
          case(1001): /* 重置设置 */ sys::saveJ(true);
            ui_m->fix_darkMode(); res::update();
            return sys_acti::ActivityType::Settings;
          
          case(0): default: break;
        }
      }
      // 输入支持
      sf::KbEvent::pollEvent(sys::__event);
      if(std::optional<int> r; __iptting != nullptr
      && (r = ui_m->__ipt.pollEvent(sys::__event)).has_value()) {
        if(!r.value()) __iptting = nullptr;
        else if(ui_m->__ipt.getInputString().isEmpty()) {
                ui_m->__ipt.setInfoTextColor(sf::Color::Red);
        } else {
          std::get<2>(__SETTINGS_TYPE_BUILD_INPUT__
             .find(r.value() - 1000)->second)();
          __iptting->setTextString(
            std::get<0>(__SETTINGS_TYPE_BUILD_INPUT__
               .find(r.value() - 1000)->second)(__iptting));
          __iptting = nullptr;
        } goto event_end;
      }
      
      // 触控支持
      if(ui_m->__ipt.isPushing()
      || ui_m->__msg.isPushing()) goto event_end;
      for(auto& i : __ipt) {
        if(i.second->pollEvent_if(sys::__event)) {
          std::get<1>(__SETTINGS_TYPE_BUILD_INPUT__
            .find(i.second->getTag<int>())->second)();
          __iptting = &i.first; goto event_end;
        }
      }
      for(auto& i : __etr) {
        if(i.second->pollEvent_if(sys::__event)) {
          if(auto r = __SETTINGS_TYPE_BUILD_ENTRY__
            .find(i.second->getTag<int>())->second(); r.has_value())
          return r.value(); else goto event_end;
        }
      }
      for(auto& i : __btn) {
        if(i.first.pollEvent(sys::__event)) {
          __btn_movement.emplace_back(&i.second, i.first.getChecked());
          __btn_color.   emplace_back(&i.first);
          std::get<1>(__SETTINGS_TYPE_BUILD_SWITCH__
             .find(i.first.getBuilder()->getTag<int>())->second)(i.first.getChecked());
          std::get<2>(__SETTINGS_TYPE_BUILD_SWITCH__
             .find(i.first.getBuilder()->getTag<int>())->second)(i.first.getChecked());
          goto event_end;
        }
      }
      for(auto& i : __typeSelect) {
        if(i.pollEvent_if(sys::__event)) {
          if(__save_type == i.getTag<int>()) goto event_end;
          for(auto& j : __typeSelect) if(&i != &j)
                    j.setStateColor(sf::Color::Transparent, sf::BtnState::None);
          i.setStateColor(sf::ColorEx::Grey | 80, sf::BtnState::None);
          __save_type = i.getTag<int>();
          goto rebuild;
        }
      }
    } event_end:
    
    // 弹窗检测
    if(ui_m->__ipt.isPushing()) {
      if(sf::Msgable::getLocked()) {
        if(ui_m->__ipt.getInput().getChecked()) {
           ui_m->__ipt.setAlignLock(sf::Align::T);
        } else if(!ui_m->__ipt.buttonIsDown().has_value())
                   ui_m->__ipt.setAlignLock(sf::Align::C);
      }
      if(__iptting == nullptr) {
         ui_m->__ipt.stopPushing();
         ui_m->__ipt.setInfoTextColor(sys::__darkMode
         ? __DARK_COLOR_TEXT__ : sf::Color::Black);
      }
    }
    
    // 退出检测
    if(rq_return)
          return sys_acti::ActivityType::Settings;
    
    // 滑动按钮
    float __distance{};
    for(auto i = __btn_movement.begin(); i != __btn_movement.end(); ) {
      if(i->second && (__distance = (i->first->getPosition().x - sf::align(i->first->getSize(),
         i->first->getBuilder()->getRect(), sf::Align::R).x + 10)) < 0)
         i->first->move((__distance <= -10) ? sys::movtionSync({ 10, 0}) : sf::Vector2f{-__distance, 0});
      else if(!i->second && (__distance = (i->first->getPosition().x - sf::align(i->first->getSize(),
               i->first->getBuilder()->getRect(), sf::Align::L).x - 10)) > 0)
               i->first->move((__distance >= 10) ? sys::movtionSync({-10, 0}) : sf::Vector2f{-__distance, 0});
      else { i = __btn_movement.erase(i); continue; } ++i;
    }
    for(auto i = __btn_color.begin(); i != __btn_color.end(); ) {
      const sf::Color& __ori_c = (*i)->getStateColor(sf::BtnState::None);
      if((*i)->getChecked() && (__distance = __btnColorAlpha - __ori_c.a) > 0)
         (*i)->setStateColor(sf::ColorEx::makeTrs(__ori_c, (__distance <= 7) ? __btnColorAlpha : (__ori_c.a + 7)));
      else if(!(*i)->getChecked() && __ori_c.a > 0)
               (*i)->setStateColor(sf::ColorEx::makeTrs(__ori_c, (__ori_c.a <= 7) ? 0 : (__ori_c.a - 7)));
      else { i = __btn_color.erase(i); continue; } ++i;
    }
    
    // 滑动 col
    if(__col_initable) {
      for(auto& i : __col)
                i.mov.apply(sf::MoveMethod::linear_down(i.getPosition(),
       {__default_col_x, i.getPosition().y}, {}, 40.0f * sys::tickSync()));
      __col_initable = false;
    }
    
    // 固定报告程序
    if(__report_tex.mov.isEnd())
       __report_tex.setPosition({__report_tex.getTag<bool>() ? 0
       : (-__report_tex.getSize().x - 8.0f
          -__report_back.getSize().x),
           __report_tex.getPosition().y});
    
    // 渲染
    sf::Renderable::draw(__typeDiv);
    for(auto& i : __typeSelect)
      sf::Renderable::draw(i);
      
    for(auto& i : __col)
      sf::Renderable::draw(i);
    
    for(auto& i : __ipt)
      sf::Renderable::draw(i.first);
    
    for(auto& i : __etr)
      sf::Renderable::draw(i.first);
    
    for(auto& i : __btn)
      sf::Renderable::draw(i.first, i.second);
    
    sf::Renderable::draw(__inf, __catch);
    
    sf::Renderable::draw(ui_m->__back, __report, __report_tex, __report_back);
    
    sf::ScrollableView::setSlideAttenuate(0.5f / sys::tickSync());
    sf::ScrollableView::pollEvent(); __typeDiv.align(sf::Align::LT);
    
                sys::flashDisplay();
  } return sys_acti::ActivityType::Exit;
}
