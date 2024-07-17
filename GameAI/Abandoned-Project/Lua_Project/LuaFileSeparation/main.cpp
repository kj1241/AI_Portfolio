#include <iostream>
#include <lua.hpp>
#include <fstream>
#include <sstream>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Lua 스크립트 파일 읽기
    const std::string lua_script = readFile("script.lua");

    // Lua 스크립트 실행
    if (luaL_dostring(L, lua_script.c_str())) {
        std::cerr << "[C++]: 에러: " << lua_tostring(L, -1) << "\n";
        lua_close(L);
        return 1;
    }

    lua_close(L);
    return 0;
}
