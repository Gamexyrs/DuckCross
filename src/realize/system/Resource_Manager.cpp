#define __LOAD_ENEMY_TEX__(type)  \
  res::enemy::__i_##type[0].resize(3); res::enemy::__i_##type[1].resize(3); \
  res::enemy::__t_##type[0].resize(6); res::enemy::__t_##type[1].resize(6); \
  for(size_t i{0}; i < 3; ++i) { \
    res::enemy::__i_##type[0][i].loadFromFile(std::string{"./src/res/img/enemy/"} + fn(i, #type)); \
    res::enemy::__i_##type[1][i].loadFromFile(std::string{"./src/res/img/enemy/"} + fn(i + 3, #type)); \
    res::enemy::__i_##type[0][i].flipHorizontally(); \
    res::enemy::__i_##type[1][i].flipHorizontally(); \
    (res::enemy::__t_##type[0][i] = std::make_unique<sf::Texture>())->loadFromImage(res::enemy::__i_##type[0][i]); \
    (res::enemy::__t_##type[1][i] = std::make_unique<sf::Texture>())->loadFromImage(res::enemy::__i_##type[1][i]); \
    (res::enemy::__t_##type[0][i + 3] = std::make_unique<sf::Texture>())->loadFromFile(std::string{"./src/res/img/enemy/"} + fn(i, #type)); \
    (res::enemy::__t_##type[1][i + 3] = std::make_unique<sf::Texture>())->loadFromFile(std::string{"./src/res/img/enemy/"} + fn(i + 3, #type)); }


inline func res::update(void) -> void {
  res::__tex_tree->setSmooth(sys::__smoothTex);
  res::__tex_ctrl_attk->setSmooth(sys::__smoothTex);
  res::__tex_ctrl_obsr->setSmooth(sys::__smoothTex);
  
  res::ui::__settings->setSmooth(sys::__smoothTex);
  res::ui::__switch  ->setSmooth(sys::__smoothTex);
  res::ui::__accept  ->setSmooth(sys::__smoothTex);
  res::ui::__refuse  ->setSmooth(sys::__smoothTex);
  res::ui::__step[0] ->setSmooth(sys::__smoothTex);
  res::ui::__step[1] ->setSmooth(sys::__smoothTex);
  res::ui::__back[0] ->setSmooth(sys::__smoothTex);
  res::ui::__back[1] ->setSmooth(sys::__smoothTex);
  
  for(auto& i : res::__tex_item) i.second->setSmooth(sys::__smoothTex);

  for(auto& i : Char_M::Duck::__v->__t)
    i.setSmooth(sys::__smoothTex);

  if(Char_M::Weapon::__v.get() != nullptr)
    for(auto& i : Char_M::Weapon::__v->__t)
      i.setSmooth(sys::__smoothTex);
  
  for(auto& i : res::enemy::__t_chick)     for(auto& j : i) j->setSmooth(sys::__smoothTex);
  for(auto& i : res::enemy::__t_bombChick) for(auto& j : i) j->setSmooth(sys::__smoothTex);
  for(auto& i : res::enemy::__t_shellPig)  for(auto& j : i) j->setSmooth(sys::__smoothTex);
}

inline func res::load(void) -> void {
  if((res::__regular_font_load_fault =
     !res::__font.loadFromFile("/system/fonts/NotoSansCJK-Regular.ttc")))
      res::__regular_font_load_fault =
     !res::__font.loadFromFile("./src/res/font/NotoSansCJK-Regular.ttc");
 
  res::__font_en.loadFromFile("./src/res/font/iosevka-n-regular.ttf");
#ifdef __LITE__
  res::__font_ac.loadFromFile("/system/fonts/NotoSansCJK-Regular.ttc");
#else
  res::__font_ac.loadFromFile("./src/res/font/汉仪文黑-85W_Heavy.ttf");
#endif
  sf::Renderable::setDefaultFont(res::__font);
  
  (res::__soundbf_levelup  = std::make_unique<sf::SoundBuffer>())->loadFromFile("./src/res/audio/sounds/levelup.wav");
  (res::__soundbf_kill     = std::make_unique<sf::SoundBuffer>())->loadFromFile("./src/res/audio/sounds/kill.wav");
  (res::__soundbf_scissors = std::make_unique<sf::SoundBuffer>())->loadFromFile("./src/res/audio/sounds/scissors.wav");
  (res::__soundbf_pistol   = std::make_unique<sf::SoundBuffer>())->loadFromFile("./src/res/audio/sounds/pistol.wav");
  
  res::ui::__i_step[0].loadFromFile("./src/res/img/sgv/ui/step.png");
  res::ui::__i_step[1].loadFromFile("./src/res/img/sgv/ui/step.png");
  res::ui::__i_step[1].flipHorizontally();
  res::ui::__i_back[0].loadFromFile("./src/res/img/sgv/ui/back.png");
  res::ui::__i_back[1].loadFromFile("./src/res/img/sgv/ui/back.png");
  res::ui::__i_back[1].flipHorizontally();
  (res::ui::__settings = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/ui/settings.png");
  (res::ui::__pause    = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/ui/pause.png");
  (res::ui::__switch   = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/ui/switch.png");
  (res::ui::__accept   = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/ui/accept.png");
  (res::ui::__refuse   = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/ui/refuse.png");
  (res::ui::__step[0]  = std::make_unique<sf::Texture>())->loadFromImage(res::ui::__i_step[0]);
  (res::ui::__step[1]  = std::make_unique<sf::Texture>())->loadFromImage(res::ui::__i_step[1]);
  (res::ui::__back[0]  = std::make_unique<sf::Texture>())->loadFromImage(res::ui::__i_back[0]);
  (res::ui::__back[1]  = std::make_unique<sf::Texture>())->loadFromImage(res::ui::__i_back[1]);
  
  // 0-> _NA, 1->_NR, 2->_NL, 3->_YA, 4->_YR, 5->_YL
  const static func fn = [](int v, std::string __type) -> std::string {
    switch(v) {
      case(0): return __type + "/_NA.png";
      case(1): return __type + "/_NR.png";
      case(2): return __type + "/_NL.png";
      case(3): return __type + "/_YA.png";
      case(4): return __type + "/_YR.png";
      case(5): return __type + "/_YL.png";
      default: return "";
    }
  };
  
  __LOAD_ENEMY_TEX__(chick);
  __LOAD_ENEMY_TEX__(bombChick);
  __LOAD_ENEMY_TEX__(shellPig);
  
  (res::enemy::__t_chickEgg = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/enemy/chick/_egg.png");

  (res::__tex_tree = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/tree.png");
  
  (res::__tex_ctrl_attk = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/surface/attk.png");
  (res::__tex_ctrl_obsr = std::make_unique<sf::Texture>())->loadFromFile("./src/res/img/sgv/surface/obsr.png");
  
  // for(const auto& i : sis::ItemName) {
    // std::unique_ptr<sf::Texture> __tex{std::make_unique<sf::Texture>()};
    // const bool __isToken{i.second.second.find("_token") != sf::String::InvalidPos};
    
    // __tex->loadFromFile(sf::String("./src/res/img/item/")
      // + (__isToken ? "token/" : "") + i.second.second.substring(0,
         // __isToken ? i.second.second.getSize() - 5 : sf::String::InvalidPos));

    // res::__tex_item.insert({i.first, std::move(__tex)});
  // }
  
  res::update();
}

#undef __LOAD_ENEMY_TEX__