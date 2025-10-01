inline func sys::loadJ(void) -> void {
  if(!sys::__apkVer) {
    if(Json_M::parseJ(sys::__jcontext, "./src/res/package.json")) {
       __GET_JVALUE__(sys::__jcontext, "version_code", Uint, sys::__apkVer);
       __GET_JVALUE__(sys::__jcontext, "build_id",   String, sys::__build_id);
    }
  }
  
  if(Json_M::parseJ(sys::__jcontext, __PATH_CONTEXT_JSON__)) {
    auto& A_ = sys::__jcontext.GetAllocator();
    
    __SET_JVALUE_IF_NULL__(sys::__jcontext, "Actype", Uint, static_cast<unsigned>(sys_acti::ActivityType::Unknown));
     
    if(!__CHECK_JVALUE__(sys::__jcontext, "_Version", Uint)
    || sys::__jcontext["_Version"].GetUint() < sys::__apkVer) goto error;
    
    if(__CHECK_JVALUE__(sys::__jcontext, "Audio", Object)) {
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Audio"], "BackgroundMusic", Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Audio"], "LevelupSound",    Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Audio"], "KillSound",       Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Audio"], "ScissorsSound",   Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Audio"], "PistolSound",     Bool, true);
    } else goto error;
    
    if(__CHECK_JVALUE__(sys::__jcontext,  "Control", Object)) {
      if(__CHECK_JVALUE__(sys::__jcontext["Control"], "Layout", Object)) {
        __GET_LAYOUT_POS__("Control_Move",    __INITPOS_MOVE__);
        __GET_LAYOUT_POS__("Control_Attack",  __INITPOS_ATTACK__);
        __GET_LAYOUT_POS__("Control_Observe", __INITPOS_OBSERVE__);
        __GET_LAYOUT_POS__("View_Settings",   __INITPOS_SETTINGS__);
        __GET_LAYOUT_POS__("View_Pause",      __INITPOS_PAUSE__);
        __GET_LAYOUT_POS__("View_Blood",      __INITPOS_BLOOD__);
        __GET_LAYOUT_POS__("View_Skill",      __INITPOS_SKILL__);
        __GET_LAYOUT_POS__("View_Equip",      __INITPOS_EQUIP__);
        __GET_LAYOUT_POS__("View_Coin",       __INITPOS_COIN__);
      } else goto error;
      __SET_JVALUE_IF_NULL__(sys::__jcontext["Control"], "MsgBoxLine", Bool, true);
      __SET_JVALUE_IF_NULL__(sys::__jcontext["Control"], "ViewAdapt", Uint, 0);
      __SET_JVALUE_IF_NULL__(sys::__jcontext["Control"], "Gyroscope", Bool, false);
      __SET_JVALUE_IF_NULL__(sys::__jcontext["Control"], "CameraShake", Bool, true);
       sys::__viwFixed = sys::__jcontext["Control"]["ViewAdapt"].GetUint();
       sys::__camShake = sys::__jcontext["Control"]["CameraShake"].GetBool();
    } else goto error;
    
    if(__CHECK_JVALUE__(sys::__jcontext, "Debug", Object)) {
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Debug"], "AllowCheat", Bool, false);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Debug"], "DataMode",   Bool, false);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Debug"], "BanSplash",  Bool, false);
       sys::__dataMode = sys::__jcontext["Debug"]["DataMode"].GetBool();
    } else goto error;
    
    if(__CHECK_JVALUE__(sys::__jcontext, "General", Object)) {
       __SET_JVALUE_IF_NULL__(sys::__jcontext["General"], "DarkMode", Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["General"], "MapGrids", Bool, true);
       sys::__darkMode = sys::__jcontext["General"]["DarkMode"].GetBool();
    } else goto error;
    
    if(__CHECK_JVALUE__(sys::__jcontext, "Graphics", Object)) {
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Graphics"], "Antialiasing",  Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Graphics"], "SmoothTexture", Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Graphics"], "VerticalSync",  Bool, true);
       __SET_JVALUE_IF_NULL__(sys::__jcontext["Graphics"], "DisplayFPS",    Bool, false);
       sys::__smoothTex = sys::__jcontext["Graphics"]["SmoothTexture"].GetBool();
    } else goto error;
    
  } else goto error;
  
  sys::saveJ();
  return;
  
error: sys::saveJ(true);
}

inline func sys::saveJ(bool reset) -> void {
  if(reset) {
    __NEW_OBJECT__({
      Json_M::writer.Key("Actype"); Json_M::writer.Uint(static_cast<unsigned>(sys_acti::ActivityType::Unknown));
      
      Json_M::writer.Key("Audio");    __NEW_OBJECT__({});
      Json_M::writer.Key("Control");  __NEW_OBJECT__({
        Json_M::writer.Key("Layout"); __NEW_OBJECT__({});
      });
      Json_M::writer.Key("Debug");    __NEW_OBJECT__({});
      Json_M::writer.Key("General");  __NEW_OBJECT__({});
      Json_M::writer.Key("Graphics"); __NEW_OBJECT__({});
      
      Json_M::writer.Key("_Version"); Json_M::writer.Uint(sys::__apkVer);
    });
    Json_M::writeJ(__PATH_CONTEXT_JSON__); sys::loadJ();
  } else {
    sys::__jcontext["_Version"].SetUint(sys::__apkVer);
    sys::__jcontext.Accept(Json_M::writer);
    Json_M::writeJ(__PATH_CONTEXT_JSON__);
  }
}

inline func sys::check_activation(void) -> bool {
  std::stringstream ss{""}; int d_code{}, a_code{};
  ss << std::hex << sys::__jdevice["activation_id"].GetString();
  ss >> a_code; ss.clear();
  ss << std::hex << sys::__device_id;
  ss >> d_code;
  
  return(static_cast<int>(static_cast<float>(d_code) * 123.0f / 456.0f * 789.0f / 100.0f) == a_code);
}

inline func sys::load_device_id(void) -> void {
  std::string str{""};
  if(Json_M::parseJ(sys::__jdevice, __PATH_CONTEXT_DEVICE_JSON__)
  && __CHECK_JVALUE__(sys::__jdevice, "device_id", String)) {
       __GET_JVALUE__(sys::__jdevice, "device_id", String, sys::__device_id);
       __GET_JVALUE__(sys::__jdevice, "activation_id", String, str);
    sys::__activated = sys::check_activation(); return;
  } sys::save_device_id(true);
}

inline func sys::save_device_id(bool reset, const std::string& a_id) -> void {
  if(reset) {
    std::stringstream sid{""};
    sid << std::hex << static_cast<int>(sys::rand<int>({1000, 100000}) * std::time(0) / sys::__apkVer);
    sid >> sys::__device_id;
    std::transform(sys::__device_id.begin(), sys::__device_id.end(), sys::__device_id.begin(), ::toupper);
  }

  const std::basic_string<char>& str_d{sys::__device_id};
  __NEW_OBJECT__({
    Json_M::writer.Key("device_id"); Json_M::writer.String(str_d.c_str());
    Json_M::writer.Key("activation_id"); Json_M::writer.String(a_id.c_str());
  });
  
  Json_M::writeJ(__PATH_CONTEXT_DEVICE_JSON__);
}
