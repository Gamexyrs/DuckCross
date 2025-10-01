class Char_M::Value {
  friend func mathsPoints(void) -> unsigned long;
  friend func mathsDetail(void) -> sf::String;
  friend func mathsDetail_data(void) -> sf::String;
  friend func play(void) -> sys_acti::ActivityType;
  friend class Map_Manager;
  friend class UiView_Manager;
  friend class ChickBoss_Manager;
  friend class PlayView_Manager;
  friend class Archive_Manager;
  friend class sis::ItemVector;
  friend class Char_M::Duck;
  friend class Char_M::Skill;
  friend class Char_M::Enemy;
  friend class Char_M::Weapon;
  friend class Char_M::Explode;
  friend class Char_M::Element;
  
protected:
  inline static struct {
    float __blood{0};
    float __food {0};
    float __exp  {0};
    
  } effect{0, 0, 0};
  
  // Duck
  inline static float    __speed_f   {1};
  inline static unsigned __blood_max {50};
  inline static unsigned __blood     {__blood_max}; inline static bool __update_blood{true};
  inline static float    __food_f    {1};
  inline static float    __food      {100};
  inline static unsigned __level     {0};           inline static bool __update_level{false};
  inline static float    __exp_f     {1};
  inline static float    __exp       {0};           inline static bool __update_exp{true};
  
  // Weapon
  inline static float __attack_f{1.0f};         // 加成倍数
  inline static float __attack_crit_p{0.15f};   // 暴击概率
  inline static float __attack_crit_f{1.8f};    // 暴击倍数
  inline static float __attack_r_f{1.0f};       // 远程加成倍数
  inline static float __attack_c_f{1.0f};       // 近程加成倍数
  inline static float __attack_speed_r_f{1.0f}; // 远程攻速倍数
  inline static float __attack_speed_c_f{1.0f}; // 近程攻速倍数
  
  inline static float __attack_e_fire{1.0f};    // 火加成倍数
  inline static float __attack_e_ice{1.0f};     // 冰加成倍数
  inline static float __attack_e_water{1.0f};   // 水加成倍数
  inline static float __attack_e_poison{1.0f};  // 毒加成倍数
  
  // Enemy
  inline static float __vampirism_f{1.0f}, // 吸血
                      __thorns_f{1.0f};    // 荆棘
  
  // Storage
  inline static float __coin_f{1.0f}; // 金币收益
  inline static int __luck{0}; // 幸运
  
  // Record
  inline static size_t __total_attkV{}; // 累计攻击量
  inline static size_t __total_cureV{}; // 累计治疗量
  inline static float  __total_move{}; // 总移动距离
  inline static size_t __total_attk{}; // 攻击次数
  inline static size_t __total_hit{}; // 命中次数
  
_func_public:
  static func autophagy(void) -> void;
  static func reset(void) -> void;

};
