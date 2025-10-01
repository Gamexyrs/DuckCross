typedef enum class ChickBossState : int {
  None = 0,
  
  Ani_Move_to = 1,
  Ani_Scale,
  Ani_Blood,
  Ani_Move_back,
  
  Live = 10,
  Ready_to_rush,
  Rushing,
  Ready_to_flash,
  Flashing,
  
  BeatAni_Move_to = 20,
  BeatAni_Fade,
  BeatAni_Move_back,
  
} ChickBossState;

typedef class ChickBoss_Manager {
  friend class Archive_Manager;
  friend class Char_M::Weapon; // call_func_hurt

protected:
  static func start(void) -> void;
  static func startInit(void) -> void;
  
  static func ani_update(void) -> void;
  
  static func beatAni_update(void) -> void;
  
  static func live_update(void) -> void;
  static func live_proceed_update(void) -> void;
  static func live_putEnemy_update(bool force) -> void;
  
  // ememy function
  static func moveToDuck(void) -> void;
  static func setTexture(void) -> void;
  static func adaptRect (void) -> void;
  static func pushList  (void) -> void;
  static func initData  (void) -> void;
  static func hurt(int) -> void;
  
_data_public:
  inline static std::unique_ptr<Char_M::Enemy> __this{nullptr}; // 本体
  inline static ChickBossState __proceed{ChickBossState::None}; // 状态
  
  inline static bool __boss_died{false};      // Boss死亡
  inline static bool __boss_living{false};    // Boss存活
  inline static sf::Vector2f __scaleCenter{}; // 缩放中心
  
  inline static sf::Vector2f __rushTowards{}; // 冲撞方向
  inline static sf::Clock    __rushClock{};   // 冲刺时钟
  inline static sf::Clock    __putEClock{};   // 产蛋时钟
  
  // draw in Char_M::Explode
  inline static std::unique_ptr<sf::Div> __flashHint{nullptr}; // 闪现暗示

  inline static std::unique_ptr<sf::TextDiv> __name{nullptr}; // 名称
  
  inline static std::unique_ptr<sf::ProgressDiv> __blood_prog{nullptr}; // 血条
  inline static std::unique_ptr<sf::Div> __defence_div{nullptr}; // 防御条
  inline static std::deque<sf::Color> __BLOOD_LAYERS_COLOR__{}; // 血条颜色
  
_func_public:
  static func update(void) -> void;
  
} ChickBoss;
