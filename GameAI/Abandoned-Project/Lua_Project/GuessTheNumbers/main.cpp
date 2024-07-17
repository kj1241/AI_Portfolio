#include <iostream>
#include <lua.hpp>

// Lua 스크립트 실행 함수
void runLuaScript(lua_State* L, const std::string& script) {
    if (luaL_dofile(L, script.c_str()) != LUA_OK) {
        std::cerr << "스크립트 실행 실패: " << lua_tostring(L, -1) <<"\n";
    }
}

// guessNumber 함수 호출
int callGuessNumber(lua_State* L, int guess) {
    // 함수 이름을 스택에 올림
    lua_getglobal(L, "guessNumber");

    // 인자를 스택에 올림
    lua_pushinteger(L, guess);

    // 함수 호출 (인자 1개, 결과 1개)
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        std::cerr << "함수 호출 실패: " << lua_tostring(L, -1) << "\n";
        return -2; // 에러를 표시하는 값
    }

    // 결과 가져오기
    int result = lua_tointeger(L, -1);
    lua_pop(L, 1);  // 스택에서 결과 제거

    return result;
}

int main() {
    // Lua 상태 생성
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Lua 스크립트 실행
    runLuaScript(L, "script.lua");

    // 사용자 입력 및 게임 실행 루프
    while (true) {
        int guess;
        std::cout << "숫자를 입력하세요(1~100): ";
        std::cin >> guess;

        // Lua의 guessNumber 함수 호출
        int result = callGuessNumber(L, guess);
        if (result == 0) {
            std::cout << "맞췄습니다!" << std::endl;
            break;
        }
        else if (result == -1) {
            std::cout << "틀렸습니다. 정답은 더 큰 숫자입니다. 다시 시도하세요.\n";
        }
        else if (result == 1) {
            std::cout << "틀렸습니다. 정답은 더 작은 숫자입니다. 다시 시도하세요.\n";
        }
        else {
            std::cerr << "에러가 발생했습니다. 다시 시도하세요.\n";
        }
    }

    lua_close(L);
    return 0;
}
