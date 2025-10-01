#define __ANY__ [](void) -> std::optional<sys_acti::ActivityType>
#define __RN__  return std::nullopt

const static std::unordered_map<int, std::optional<sys_acti::ActivityType>(*)(void)> __SETTINGS_TYPE_BUILD_ENTRY__ {
  {  0, // 重置存档
    __ANY__{confirm(L"确定要清空存档？", 1000); __RN__;},
  },
  {  1, // 重置设置
    __ANY__{confirm(L"确定要恢复默认设置？", 1001); __RN__;},
  },
  {  4, // 读取存档
    __ANY__{
    if(std::wstring __path =
       -gy_plugin::Filer::activity_start(
        gy_plugin::Filer::ActivitySettings{
          .require = gy_plugin::DocType::File,
          .display_hiddenFile = true,
    }); !__path.empty()) {
      
      confirm(L"未开放此功能", 1004);
    } __RN__;},
  },
  {  5, // 导出存档
    __ANY__{
    if(std::wstring __path =
       -gy_plugin::Filer::activity_start(
        gy_plugin::Filer::ActivitySettings{
          .require = gy_plugin::DocType::Dir,
          .display_hiddenFile = true,
    }); !__path.empty()) {
      
      confirm(L"未开放此功能", 1005);
      // confirm(L"已导出存档为 " + std::to_wstring(std::time(0)) + L"_DuckCrossAC.json", 1005);
    } __RN__;},
  },
  
  {100, // 调整布局
    __ANY__{return sys_acti::ActivityType::ControlLayout;},
  },
  
  {400, // 开发人员
    __ANY__{dever(true); __RN__;},
  },
  {401, // 更新日志
    __ANY__{return sys_acti::ActivityType::UpdateLog;},
  },
  {402, // 测试人员
    __ANY__{confirm(L"加入测试人员并获得定期更新，请向开发者申请"); __RN__;},
  },
};

#undef __ANY__
#undef __RN__
