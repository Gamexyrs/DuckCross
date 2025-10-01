#pragma once

#include <SFUI/Graphics.hpp>
#include <SFUI/VirtualInput/VJoystick.hpp>
#include <unordered_map>
#include <FakePay.hpp>
#include <Filer.hpp>
#include <unistd.h>
#include <fstream>
#include <thread>
#include <random>

#include "./res/update.log.hpp"
#include "./lib/load_json.hpp"

#include "./init/storage/Storage_Manager.hpp"

#include "./init/system/Resource_Manager.hpp"

#include "./init/system/Audio_Manager.hpp"
#include "./init/system/System_Manager.hpp"
#include "./init/system/Activity_Selector.hpp"
#include "./init/system/Json_Manager.hpp"
#include "./init/system/Account_Manager.hpp"
#include "./init/system/Archiver_Manager.hpp"

#include "./init/view/Map_Manager.hpp"
#include "./init/view/UiView_Manager.hpp"
#include "./init/view/PlayView_Manager.hpp"
#include "./init/view/AttackDisplay_Manager.hpp"

#include "./init/control/Control_Manager.hpp"

#include "./init/character/Char_Manager.hpp"

#include "./ini/acid.ini"
#include "./ini/enemy.ini"
#include "./ini/weapon.ini"

#include "./realize/storage/Storage_Manager.cpp"

#include "./realize/system/Resource_Manager.cpp"

#include "./realize/system/Audio_Manager.cpp"
#include "./realize/system/System_Manager.cpp"
#include "./realize/system/Context.cpp"
#include "./realize/system/Json_Manager.cpp"
#include "./realize/system/Account_Manager.cpp"
#include "./realize/system/Archiver_Manager.cpp"

#include "./realize/view/Map_Manager.cpp"
#include "./realize/view/UiView_Manager.cpp"
#include "./realize/view/PlayView_Manager.cpp"
#include "./realize/view/AttackDisplay_Manager.cpp"

#include "./realize/control/Control_Manager.cpp"

#include "./realize/character/Char_Manager.cpp"

#include "./activity/splash.hpp"
#include "./activity/splash_wait.hpp"
#include "./activity/splash_PSEwarning.hpp"
#include "./activity/splash_cameraShakeWarning.hpp"
#include "./activity/settle.hpp"
#include "./activity/dever.hpp"
#include "./activity/play.hpp"
#include "./activity/settings/.hpp"
#include "./realize/system/Activity_Selector.cpp"
