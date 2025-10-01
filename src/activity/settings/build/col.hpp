const static std::vector<std::pair<int, sf::String>> __SETTINGS_TYPE__ {
  {00, L"通用"},
  {01, L"控制"},
  {02, L"显示"},
  {03, L"音频"},
  {04, L"关于"},
  {05, L"账号"},
  {06, L"调试"},
  {07, L"作弊"},
};

const static std::unordered_map<int, std::vector<std::tuple<int, sf::String, settings_LineType>>> __SETTINGS_TYPE_BUILD__ {
  {00, {
    {  0, L"重置存档", settings_LineType::Entry},
    {  1, L"重置设置", settings_LineType::Entry},
    {  2, L"暗色模式", settings_LineType::Switch},
    {  3, L"地图网格", settings_LineType::Switch},
    {  4, L"读取存档", settings_LineType::Entry},
    {  5, L"导出存档", settings_LineType::Entry},
  }},
  
  {01, {
    {100, L"调整布局", settings_LineType::Entry},
    {101, L"启用陀螺仪观察", settings_LineType::Switch},
    {102, L"显示消息框指示条", settings_LineType::Switch},
    {103, L"启用摄像机抖动", settings_LineType::Switch},
  }},
  
  {02, {
    {200, L"抗锯齿",   settings_LineType::Switch},
    {201, L"平滑纹理", settings_LineType::Switch},
    {202, L"垂直同步", settings_LineType::Switch},
    {203, L"显示帧率 (FPS)", settings_LineType::Switch},
  }},

  {03, {
    {300, L"背景音乐", settings_LineType::Switch},
    {301, L"升级音效", settings_LineType::Switch},
    {302, L"击败音效", settings_LineType::Switch},
    {303, L"武器音效: 剪刀", settings_LineType::Switch},
    {304, L"武器音效: 小手枪", settings_LineType::Switch},
  }},
  
  {04, {
    {400, L"开发人员", settings_LineType::Entry},
    {401, L"更新日志", settings_LineType::Entry},
    {402, L"成为测试人员", settings_LineType::Entry},
    {403, L"渲染引擎 OpenGL ES 版本", settings_LineType::Input},
    {404, L"图形引擎 SFML 版本", settings_LineType::Input},
    {405, L"界面引擎 SFUI 版本 (自研)", settings_LineType::Input},
  }},
  
  {05, {
    {500, L"", settings_LineType::None},
    {501, L"账号激活情况", settings_LineType::Input},
    {502, L"游戏总时长",       settings_LineType::Input},
    {503, L"历史最高分",       settings_LineType::Input},
    {504, L"累计击杀<咬鸭鸡>", settings_LineType::Input},
    {505, L"累计击杀<炸弹鸡>", settings_LineType::Input},
    {506, L"累计击杀<甲壳猪>", settings_LineType::Input},
    {507, L"累计击杀Boss<鸡霸>", settings_LineType::Input},
  }},
  
  {06, {
    {600, L"允许作弊",         settings_LineType::Switch},
    {601, L"观察者(数据)模式", settings_LineType::Switch},
  }},
  
  {07, {
    // {700, L"无视障碍物", settings_LineType::Switch},
    // {701, L"无视死亡",   settings_LineType::Switch},
    // {702, L"游戏数据可在外置数据修改器中修改", settings_LineType::None},
  }},
};
