typedef class Control_Manager {
  friend class PlayView_Manager;
  friend class UiView_Manager;
  friend func controlLayout(void) -> sys_acti::ActivityType;

private:
  inline static sf::VJoystick __move{{}, 110, 18, 50},
                              __attk{{}, 80, 2, 80},
                              __obsr{{}, 26, 2, 26};

_data_public:
  inline static sf::Vector2f __gyroscope_move{};

  inline static sf::Vector2f __move_move{},
                             __move_attk{},
                             __move_obsr{};
  inline static float        __angle_attk{};
  
  inline static bool __enabled_gyroscope{false};
  inline static bool __once_hide{false};
  
_func_public:
  static func init (void) -> void;
  static func draw (void) -> void;
  static func event(void) -> void;
  
} Control_M;
