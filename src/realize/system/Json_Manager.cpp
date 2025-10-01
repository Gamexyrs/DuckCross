inline func Json_M::parseJ(rj::Document& dom, const std::string& path) -> bool {
  Json_M::ifs.open(path); if(!Json_M::ifs.is_open()) return false;
  std::string isw{std::istreambuf_iterator<char>(Json_M::ifs),
                  std::istreambuf_iterator<char>()};
  Json_M::ifs.close(); return !dom.Parse(isw.c_str()).HasParseError();
}

inline func Json_M::writeJ(const std::string& path) -> void {
  Json_M::ofs.open(path, std::ios::trunc);
  Json_M::ofs << Json_M::buf.GetString();   Json_M::ofs.close();
  Json_M::buf.Clear(); Json_M::writer.Reset(Json_M::buf);
}

inline func Json_M::checkJ(void) -> void {
  system("mkdir -p /storage/emulated/0/.gyplay/com.gamexyrs.duckcross.mx/");
}
