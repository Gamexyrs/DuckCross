typedef class Audio_Manager {
private:
  sf::Clock __waitForMusic{};
  
_data_public:
  bool __signal_music_update{true};
  
  sf::Time    __music_play_offset{sf::Time::Zero};
  std::string __music_inline{""},
              __music_now{""};
  int __play_music_code{-1};
  
  sf::Music __music{};
  
  struct {
    std::pair<sf::Sound, bool>
      __levelup {{}, true},
      __kill    {{}, true},
      __scissors{{}, true},
      __pistol  {{}, true};
    
  }__sound;
  
_func_public:
  func update(void) -> void;
  
  func call_next(const std::string& __n = ".stop") -> void;
  
  func call_next_play(void) -> void;
  
           Audio_Manager(void);
  virtual ~Audio_Manager(void) = default;
} Audio_M;

#define __AUDIO__CHECK_SOUND__(name) {      \
  if(sys::__audio->__sound.__##name.second) \
     sys::__audio->__sound.__##name.first.play(); }
