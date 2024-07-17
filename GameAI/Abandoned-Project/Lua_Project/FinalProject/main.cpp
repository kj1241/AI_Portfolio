#include <iostream>
#include <lua.hpp>

// Lua 스크립트 파일을 실행하는 함수
void runLuaScript(lua_State* L, const std::string& script) {
    if (luaL_dofile(L, script.c_str()) != LUA_OK) {
        std::cerr << "lua 스크립트 실행 실패: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }
}

// Lua 함수 호출을 위한 헬퍼 함수
void callLuaFunction(lua_State* L, const std::string& func) {
    lua_getglobal(L, func.c_str());
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        std::cerr << "함수 호출 실패 [" << func << "]: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }
}

// Lua 상태기 초기화 및 사용자 입력 처리
int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Lua 스크립트 실행
    runLuaScript(L, "game.lua");

    // 게임 초기화
    callLuaFunction(L, "startGame");

    // 게임 루프
    while (true) {
        std::cout << "\n";
        std::cout << "---------------------------\n";
        std::cout << "1. 공격\n";
        std::cout << "2. 아이템 사용\n";
        std::cout << "3. 인벤토리 보기\n";
        std::cout << "4. 종료\n";
        std::cout << "---------------------------\n";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            callLuaFunction(L, "attack");
        }
        else if (choice == 2) {
            callLuaFunction(L, "useItem");
        }
        else if (choice == 3) {
            callLuaFunction(L, "showInventory");
        }
        else if (choice == 4) {
            std::cout << "게임을 종료합니다.\n";
            break;
        }
        else {
            std::cout << "잘못된 선택입니다.\n";
        }

        // 종료 조건 확인
        callLuaFunction(L, "checkEndCondition");
    }

    lua_close(L);
    return 0;
}
