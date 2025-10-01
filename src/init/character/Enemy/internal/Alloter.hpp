class Char_M::Enemy::Alloter {
  friend func settings(void) -> sys_acti::ActivityType;

  static func update_active(void) -> void;

_data_public:
  inline static struct {
    unsigned __chick;
    unsigned __bombChick;
    unsigned __shellPig;
  }enemyNum{0, 0, 0};

  inline static bool __need_update{true};
  
  inline static std::vector<std::unique_ptr<Char_M::Enemy>>
    __active{}
    // ,
    // __active_inview{},
    // __active_inzone{}
    ;

_func_public:
  static func reset(void) -> void;
  static func update(void) -> void;
  
};
