#define __VALUE__(K, JStr) \
  [](void) -> bool{return sys::__jcontext[K][JStr].GetBool();}, \
  []([[maybe_unused]] bool v) -> void{sys::__jcontext[K][JStr] = v; sys::saveJ();}
#define __VALUE_LOCAL__(value) \
  [](void) -> bool{return value;}, [](bool v) -> void{value = v;}
#define __ANY__ []([[maybe_unused]] bool v) -> void

/*             GetBool          SetBool        Any
  std::tuple<bool(*)(void), void(*)(bool), void(*)(bool)> */
const static std::unordered_map<int, std::tuple<bool(*)(void), void(*)(bool), void(*)(bool)>> __SETTINGS_TYPE_BUILD_SWITCH__ {
  {  2, { // 暗色模式
    __VALUE__("General", "DarkMode"),
    __ANY__{sys::__darkMode = v; ui_m->fix_darkMode(); rq_return = true;},
  }},
  {  3, { // 地图网格
    __VALUE__("General", "MapGrids"),
    __ANY__{},
  }},
  
  {101, { // 启用陀螺仪观察
    [](void) -> bool { return sys::__jcontext["Control"]["Gyroscope"].GetBool(); },
    __ANY__ {
      if(v && !sf::Sensor::isAvailable(sf::Sensor::Type::Gyroscope)) {
        confirm(L"无法找到该设备的陀螺仪."); return;
      }
      sf::Sensor::setEnabled(sf::Sensor::Type::Gyroscope, v);
      sys::__jcontext["Control"]["Gyroscope"] = v;
      sys::saveJ();
    },
    __ANY__{},
  }},
  {102, { // 显示消息框指示条
    __VALUE__("Control", "MsgBoxLine"),
    __ANY__{},
  }},
  {103, { // 启用摄像机抖动
    __VALUE__("Control", "CameraShake"),
    __ANY__{sys::__camShake = v;},
  }},
  
  {200, { // 抗锯齿
    __VALUE__("Graphics", "Antialiasing"),
    __ANY__{confirm(L"该选项需要重启游戏以执行, 现在退出？", 999, L"稍后");},
  }},
  {201, { // 平滑纹理
    __VALUE__("Graphics", "SmoothTexture"),
    __ANY__{sys::__smoothTex = v; res::update(); },
  }},
  {202, { // 垂直同步
    __VALUE__("Graphics", "VerticalSync"),
    __ANY__{_Renderer.setVerticalSyncEnabled(v);},
  }},
  {203, { // 显示帧率
    __VALUE__("Graphics", "DisplayFPS"),
    __ANY__{},
  }},
  
  {300, { // 背景音乐
    __VALUE__("Audio", "BackgroundMusic"),
    __ANY__{sys::__audio->__signal_music_update = true;},
  }},
  {301, { // 升级音效
    __VALUE__("Audio", "LevelupSound"),
    __ANY__{sys::__audio->__sound.__levelup.second = v;},
  }},
  {302, { // 击败音效
    __VALUE__("Audio", "KillSound"),
    __ANY__{sys::__audio->__sound.__kill.second = v;},
  }},
  {303, { // 武器音效: 剪刀
    __VALUE__("Audio", "ScissorsSound"),
    __ANY__{sys::__audio->__sound.__scissors.second = v;},
  }},
  {304, { // 武器音效: 手枪
    __VALUE__("Audio", "PistolSound"),
    __ANY__{sys::__audio->__sound.__pistol.second = v;},
  }},
  
  {600, { // 允许作弊
    __VALUE__("Debug", "AllowCheat"),
    __ANY__{if(!v) {
      sys::__cheat___allow_duck_through_obstacles__ = false;
      sys::__cheat___allow_duck_unlimited_blood__   = false;
    } rq_return = true;},
  }},
  {601, { // 观察者(数据)模式
    __VALUE__("Debug", "DataMode"),
    __ANY__{sys::__dataMode = v;},
  }},
  
  // {700, { // 无视障碍物
    // __VALUE_LOCAL__(sys::__cheat___allow_duck_through_obstacles__),
    // __ANY__{if(v) confirm(L"该设置仅在本次程序周期有效, 退出后失效"); sys::__cheat___allow_duck_through_obstacles__ = v;},
  // }},
  // {701, { // 无视死亡
    // __VALUE_LOCAL__(sys::__cheat___allow_duck_unlimited_blood__),
    // __ANY__{if(v) confirm(L"该设置仅在本次程序周期有效, 退出后失效"); sys::__cheat___allow_duck_unlimited_blood__ = v;},
  // }},
};

#undef __VALUE__
#undef __VALUE_LOCAL__
#undef __ANY__
