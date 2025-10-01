typedef class Activity_Selector {
_data_public:
  inline static enum class ActivityType : unsigned {
    Exit = 0,
    
    Play,
    Dever,
    Settle,
    Settings,
    UpdateLog,
    ControlLayout,
    
    Unknown = Dever,
  }__actype{ActivityType::Unknown};

  inline static bool __isLoading{true};

_func_public:
  static func call(void) -> void;

} sys_acti;
