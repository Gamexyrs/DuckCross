#include "init.hpp"

func _app_(main)(void) -> int {
  std::ios_base::sync_with_stdio(false);

  // 检测存档
  Json_M::checkJ();
  
  // 系统服务
  sys::loadJ();
  
  // 账号服务
  Acc_M::loadJ();
  Acc_M::saveJ();
  
  // 窗口模式
  sf::VideoMode _vd{sf::VideoMode::getDesktopMode()};
                _vd.width += sys::__jcontext["Control"]["ViewAdapt"].GetUint();
  // 渲染设置
  sf::ContextSettings __settings(0, 0, sys::__jcontext["Graphics"]["Antialiasing"].GetBool());
  // 渲染窗口
  sf::RenderWindow    __window(_vd, "AndroidRW-DuckCross", sf::Style::Default, __settings);

  // 系统配置
  sys::init(&__window);
  
  // 控件服务
  Control_M::init();
  
  // 资源与活体
  Char_M::Duck::__v = std::move(std::make_unique<Char_M::Duck>());
  Char_M::Weapon::__v = std::move(std::make_unique<Char_M::Weapon::Scissors>());
  res::load();
  
  // 系统服务
          ui_m = std::make_unique<UiView_M>();
  sys::__audio = std::make_unique<Audio_Manager>();

  if(!Arc_M::__trRun) {
      Arc_M::__trRun = true;
      Arc_M::tr_save.detach();
  }
  
  // 开屏界面
  if(splash() == sys_acti::ActivityType::Exit) __window.close();

  sys::__audio->call_next_play();
  
  sys_acti::call();
  
  sys::__audio->__music.stop();
  
  if(__window.isOpen())
     __window.close();
  
  return EXIT_SUCCESS;
}

