typedef class System_Manager {
_data_public:
  inline static sf::Event __event;
  inline static sf::Clock __runTimeClock{};
  
  inline static float __fps{60};
  
  inline static unsigned    __apkVer{0};
  inline static std::string __build_id{""}, __device_id{""};
  
  inline static std::unique_ptr<Audio_Manager> __audio{nullptr};

  inline static rj::Document __jcontext, __jdevice;
  
  inline static std::vector<sf::Drawable*> __debugList{};
  
  inline static std::default_random_engine __rander{std::random_device{}()};

  // Signals
  inline static bool __cheat___allow_duck_through_obstacles__{false};
  inline static bool __cheat___allow_duck_unlimited_blood__  {false};
  inline static bool __smoothTex{false},
                     __activated{false},
                     __dataMode{false},
                     __darkMode{false},
                     __camShake{true},
                     __viwFixed{false};

_func_public:
  // Fps
  static func    tickSync(void) -> float;
  static func movtionSync(const sf::Vector2f&) -> sf::Vector2f;

  // Context
  static func loadJ(void) -> void;
  static func saveJ(bool reset = false) -> void;
  static func load_device_id(void) -> void;
  static func save_device_id(bool reset = false, const std::string& a_id = "") -> void;
  static func check_activation(void) -> bool;
  
  // Init
  static func init(sf::RenderWindow*) -> void;
  
  // Debug
  static func drawDebugList(void) -> void;
  static func flashDisplay (bool update_ui = true) -> void;
  static func fix_pollEvent(sf::Event&) -> bool;
  
  template<typename m_type>
  static func rand(const sf::Vector2<m_type>& range) -> m_type;
  static func rand_bool(void) -> bool;
  
  static func checkNavigationBar(void) -> void;

} sys;

#define __PACKAGE__ "com.gamexyrs.duckcross.mx"

#define __INITPOS_MOVE__     sf::Vector2f{400,  680}
#define __INITPOS_ATTACK__   sf::Vector2f{400,  400}
#define __INITPOS_OBSERVE__  sf::Vector2f{550, -255}
#define __INITPOS_SETTINGS__ sf::Vector2f{180, -40}
#define __INITPOS_PAUSE__    sf::Vector2f{650,  16}
#define __INITPOS_BLOOD__    sf::Vector2f{50,   30}
#define __INITPOS_EQUIP__    sf::Vector2f{20,  220}
#define __INITPOS_COIN__     sf::Vector2f{20,   80}
#define __INITPOS_SKILL__    sf::Vector2f{270, 230}
#define __GET_LAYOUT_POS__(name, STD) \
  if(!__CHECK_JVALUE__(sys::__jcontext["Control"]["Layout"], name, Array)    \
                   || !sys::__jcontext["Control"]["Layout"] [name].Size()) { \
    rj::Value arrV(rj::kArrayType); \
    arrV.PushBack(STD.x, sys::__jcontext.GetAllocator()); \
    arrV.PushBack(STD.y, sys::__jcontext.GetAllocator()); \
    sys::__jcontext["Control"]["Layout"].AddMember(name, arrV, sys::__jcontext.GetAllocator());  \
  } else if(rj::arrayToVector2(sys::__jcontext["Control"]["Layout"][name]) == sf::Vector2f{}) { \
        __SET_JVALUE_VECTOR2__(sys::__jcontext["Control"]["Layout"][name], Float, (STD)); }
