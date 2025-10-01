typedef class Archive_Manager {
private:
  inline static rj::Document dom{};
  
_data_public:
  inline static bool __joinable{false},
                     __trRun{false},
                     __trRun_l{false},
                     __load_ok{false};
  
  inline static sf::Time  __playTime{sf::Time::Zero};
  inline static sf::Clock __playTimeClock{};
  
  inline static size_t __process{0}, __all_process{0};
  
_func_public:
  // JsonSupport
  static func clear(void) -> void;
  static func loadJ(void) -> bool;
  static func loadJ_t(void) -> bool;
  static func saveJ(void) -> void;
  
  static func saveJ_overrideMode(void) -> bool;
//static func saveJ_modifiedMode(void) -> void;

  inline static std::thread tr_save{saveJ};
  
} Arc_M;

