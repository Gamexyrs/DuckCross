typedef class PlayView_Manager {
  friend class ChickBoss_Manager;
  friend func controlLayout(void) -> sys_acti::ActivityType;
  friend func play(void) -> sys_acti::ActivityType;

private:
  // Over
  struct {
    sf::TextDiv __text{};
    sf::PushBtn __settle{{{}, {360, 120}}};
    sf::PushBtn __reborn{{{}, {360, 120}}};
    
  }over;
  
  // Pause
  struct {
    sf::Div __mask{};
  
    sf::TextDiv __playerBox{{{}, {300, 500}}, 6};
    sf::Texture __player_t{};
    sf::Sprite  __player{};
    sf::Texture __weapon_t{};
    sf::Sprite  __weapon{};
    
    sf::TextDiv __time{};
    
    sf::TextDiv __stateBox{{}, 6};
    sf::TextDiv     __state_blood_text{{{}, {0, 40}}};
    sf::ProgressDiv __state_blood_prog{{}, 6};
    sf::TextDiv     __state_food_text{{{}, {0, 40}}, 6};
    sf::ProgressDiv __state_food_prog{{}, 6};
    sf::TextDiv     __state_level_text{{{}, {0, 40}}, 6};
    sf::ProgressDiv __state_level_prog{{}, 6};
    
    sf::TextDiv __valueBox{{}, 6};
    sf::TextDiv __value{{}};
    
    sf::PushButton __flee{{{}, {240, 100}}, 10};
    sf::PushButton __autophagy{{{}, {240, 100}}, 10};
  }pause;

  sf::ProgressDiv __fighting_prog{{{}, {200, 10}}};
  
  // Coin
  struct {
    sf::Image   __i{};
    sf::Texture __t{};
        
        sf::Div __pic{};
    sf::TextDiv __num{};
  }co;
  
  // Level
  struct {
    sf::ProgressDiv __prog{};
    sf::TextDiv     __text{};
    
    sf::PushBtn __cheatlv6{};
    sf::PushBtn __cheatboss{};
    
  }lv;
  
  // Skill_choose
  struct {
    std::vector<sf::CheckBtn>
      __skill_name{3},
      __skill_attr{3};
    sf::PushBtn __reject{{}, 15},
                __flash {{}, 15},
                __confirm{{}, 15};
    sf::CheckBtn* __choose{nullptr};
    sf::Div __mask{};
    
    bool __display{false},
         __signal_no_skills{false};
  }sk;
  
  // Skill_actived
  struct {
    std::vector<sf::Texture> __release_t{3};
    std::vector<sf::PushBtn> __release{3};
    std::vector<sf::Div> __mask{3};
    sf::ProgressDiv __prog{};
    sf::Timer __timer{};

  }ska;
  
  // Blood
  struct {
    sf::ProgressDiv __prog{{}, 5};
  }bl;
  
  // Food
  struct {
    sf::Texture __t{};
  
    sf::ProgressDiv __prog{{}, 3};
    sf::Div __pic{};
  }fd;
  
  // Equip
  struct {
    sf::Image   __eq0i{}, __eq1i{};
    sf::Texture __eq0t{}, __eq1t{};
    
    sf::PushBtn __box{}, __pic{};
  }eq;
  
  func Over_init(void) -> void;
  func Pause_init(void) -> void;
  func Coin_init(void) -> void;
  func Level_init(void) -> void;
  func Skill_init(void) -> void;
  func Skill_actived_init(void) -> void;
  func Blood_init(void) -> void;
  func Food_init (void) -> void;
  func State_init (void) -> void;
  func Equip_init(void) -> void;
  func MsgBox_init(void) -> void;
  
  func Over_act(void) -> void;
  func Pause_act(void) -> void;
  func Coin_act(void) -> void;
  func Level_act(void) -> void;
  func Skill_act(void) -> void;
  func Skill_actived_act(void) -> void;
  func Blood_act(void) -> void;
  func Food_act (void) -> void;
  func State_act (void) -> void;
  func Equip_act(void) -> void;
  func MsgBox_act(void) -> void;
  
  func require_pause(bool require = true) -> void;
  
  // use after draw()
  func MsgBoxText_act(void) -> void;
  
  bool __signal_reload__{true};
  
_data_public:
  inline static std::queue<std::pair<sf::String, size_t>> __msgBoxStr{};
  std::vector<
    std::pair<sf::TextDiv, sf::Clock>> __msgBoxText{};
  sf::Div __msgBox{{{}, {0, 2}}};
  
  sf::TextDiv __fps, __con, __time;
  
  sf::PushBtn __settings{{{}, {60, 60}}},
                 __pause{{{}, {120, 120}}};
  
  bool __pausing{false};
  
_func_public:
  func update(void) -> void;
  func requestPause (const sf::Event&) -> void;
  func requestEquip (const sf::Event&) -> void;
  func requestSkill (const sf::Event&) -> void;
  func requestSkill_actived(const sf::Event&) -> void;
  func requestSettle(const sf::Event&) -> bool;
  
  func draw      (void) -> void;
  func drawMsgBox(void) -> void;
  
  PlayView_Manager(void);
 ~PlayView_Manager(void) = default;
} PlayView_M;
