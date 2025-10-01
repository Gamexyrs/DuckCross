#define __STR__ []([[maybe_unused]] sf::TextDiv* v) -> sf::String
#define __ANY__ [](void) -> void

/*                   GetString                Call         SetValue
  std::tuple<sf::String(*)(sf::TextDiv*), void(*)(void), void(*)(void) */
const static std::unordered_map<int, std::tuple<sf::String(*)(sf::TextDiv*), void(*)(void), void(*)(void)>> __SETTINGS_TYPE_BUILD_INPUT__ {
  {403, { // OpenGL ES
    __STR__{return "2.0";},
    __ANY__{}, __ANY__{},
  }},
  
  {404, { // SFML
    __STR__{return std::to_string(SFML_VERSION_MAJOR) + "." + std::to_string(SFML_VERSION_MINOR) + "." + std::to_string(SFML_VERSION_PATCH);},
    __ANY__{}, __ANY__{},
  }},
  
  {405, { // SFUI
    __STR__{return __SFUI_VERSION__;},
    __ANY__{}, __ANY__{},
  }},
  
  {501, { // 激活
    __STR__{v->setTextColor(sys::__activated ? sf::Color::Green : sf::Color::Red);
            v->setTextDeviat({-50, 2}); return sys::__activated ? (L"已激活: " + ((__acidData.find(sys::__device_id) == __acidData.end()) ? L"未知用户" : __acidData.find(sys::__device_id)->second)) : L"未激活";},
    __ANY__{if(!sys::__activated) rq_input("NLA-", L"请输入激活码", L"设备编码：" + std::to_wstring(sys::__device_id), 1501);
      else confirm(L"用户名仅在版本更新时更新");},
    __ANY__{sys::save_device_id(false, ui_m->__ipt.getInputString().toAnsiString()); sys::load_device_id();
      if(!(sys::__activated = sys::check_activation())) confirm(L"该激活码无效");
      else { rq_return = true; }
    },
  }},
  {502, { // 游戏总时长
    __STR__{v->setTextDeviat({-50, 0}); return std::to_wstring(Acc_M::__play_data.find("time_play")->second) + L" 秒";},
    __ANY__{confirm(L"游戏总时长在每次有效操作时才会计算");}, __ANY__{},
  }},
  {503, { // 历史最高分
    __STR__{v->setTextDeviat({-50, 0}); return std::to_wstring(Acc_M::getMaxPoints()) + L" 分";},
    __ANY__{}, __ANY__{},
  }},
  {504, { // 击杀: 咬鸭鸡
    __STR__{v->setTextDeviat({-50, -4}); return std::to_wstring(Acc_M::__enemy_data.find("kill_chick")->second);},
    __ANY__{}, __ANY__{},
  }},
  {505, { // 击杀: 炸弹鸡
    __STR__{v->setTextDeviat({-50, -4}); return std::to_wstring(Acc_M::__enemy_data.find("kill_bombChick")->second);},
    __ANY__{}, __ANY__{},
  }},
  {506, { // 击杀: 甲壳猪
    __STR__{v->setTextDeviat({-50, -4}); return std::to_wstring(Acc_M::__enemy_data.find("kill_shellPig")->second);},
    __ANY__{}, __ANY__{},
  }},
  {507, { // 击杀: 鸡霸
    __STR__{v->setTextDeviat({-50, -4}); return std::to_wstring(Acc_M::__enemy_data.find("kill_chickBoss")->second);},
    __ANY__{}, __ANY__{},
  }},
};

#undef __STR__
#undef __ANY__
