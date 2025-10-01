typedef class Json_Manager {
  friend class Account_Manager;
  friend class Storage_Manager;
  friend class Archive_Manager;
  friend class System_Manager;

private:
  inline static std::ifstream ifs;
  inline static std::ofstream ofs;
  inline static            rj::StringBuffer  buf{};
  inline static rj::Writer<rj::StringBuffer> writer{buf};
    
_data_public:
  inline static std::mutex __mutex;
  
_func_public:
  static func parseJ(rj::Document& dom, const std::string& path) -> bool;
  static func writeJ(const std::string& path) -> void;
  static func checkJ(void) -> void;
  
} Json_M;

#define __PATH_CONTEXT_JSON__ \
  "/storage/emulated/0/.gyplay/com.gamexyrs.duckcross.mx/context.json"
#define __PATH_CONTEXT_DEVICE_JSON__ \
  "/storage/emulated/0/.gyplay/com.gamexyrs.duckcross.mx/.device"
#define __PATH_ACCOUNT_JSON__ \
  "/storage/emulated/0/.gyplay/com.gamexyrs.duckcross.mx/account.json"
#define __PATH_ARCHIVE_JSON__ \
  "/storage/emulated/0/.gyplay/com.gamexyrs.duckcross.mx/archive.json"
#define __PATH_STORAGE_JSON__ \
  "/storage/emulated/0/.gyplay/com.gamexyrs.duckcross.mx/storage_safe.json"
#define __PATH_STORBUF_JSON__ \
  "/storage/emulated/0/.gyplay/com.gamexyrs.duckcross.mx/storage_buffer.json"
