#define __ACC_UPDATE__(__sc) {__sc; Acc_M::__signal_update = true;}

typedef class Account_Manager {
private:
  inline static rj::Document dom{};
  
  inline static sf::Clock __runTimeClock{};
  
_data_public:
  inline static bool __signal_update{false};

  inline static std::unordered_map<std::string, size_t> __enemy_data {
    {"kill_chick",             0},
    {"kill_bombChick",         0},
    {"kill_shellPig",          0},
    {"kill_chickBoss",         0},
  };
  inline static std::unordered_map<std::string, size_t> __play_data {
    {"max_points",             0},
    {"time_play",              0},
  };
  
_func_public:
  static func checkMaxPoints(size_t) -> bool;
  static func getMaxPoints(void) -> size_t;

  // JsonSupport
  static func clear(void) -> void;
  static func loadJ(void) -> void;
  static func saveJ(void) -> void;
  
} Acc_M;
