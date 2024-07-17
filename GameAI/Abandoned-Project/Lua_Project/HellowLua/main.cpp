#include <iostream>
#include <lua.hpp>

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Lua 스크립트 문자열
    const char* lua_script = R"(
        -- Lua 5.4.2 예제 스크립트

        -- 변수 선언과 출력
        local message = "Hello from Lua!"
        print(message)

        -- 함수 정의 및 호출
        function add(a, b)
            return a + b
        end

        local result = add(10, 20)
        print("Result:", result)
    )";

    // Lua 스크립트 실행
    if (luaL_dostring(L, lua_script)) {
        std::cerr << "[C++]: 에러: " << lua_tostring(L, -1) << "\n";
        lua_close(L);
        return 1;
    }

    lua_close(L);
    return 0;
}
