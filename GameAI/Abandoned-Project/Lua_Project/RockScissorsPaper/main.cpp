extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

const int NUM_MOVES = 3;
const string MOVES[NUM_MOVES] = { "가위", "바위", "보" };

// Lua 라이브러리 열기 함수
void OpenLuaLibraries(lua_State* L) {
    luaL_openlibs(L);
}

// Lua 스크립트 실행 함수
void RunLuaScript(lua_State* L, const string& filename) {
    if (luaL_dofile(L, filename.c_str()) != LUA_OK) {
        cerr << "[C++]: 에러: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }
}

// GetRandomInt 함수 정의
int GetRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// GetComputerMove 함수 정의
string GetComputerMove() {
    return MOVES[GetRandomInt(0, NUM_MOVES - 1)];
}

// Lua에서 호출할 GetComputerMove 함수 정의
int Lua_GetComputerMove(lua_State* L) {
    lua_pushstring(L, GetComputerMove().c_str());
    return 1;
}

// MoveToIndex 함수 정의
int MoveToIndex(const string& move) {
    for (int i = 0; i < NUM_MOVES; ++i) {
        if (move == MOVES[i]) return i;
    }
    return -1;
}

// EvaluateMoves 함수 정의
void EvaluateMoves(const string& player_move, const string& computer_move, int& player_score, int& computer_score) {
    static const int SCORE_TABLE[NUM_MOVES][NUM_MOVES] = {
        {0, -1, 1},
        {1, 0, -1},
        {-1, 1, 0}
    };

    cout << "\n사용자 선택: " << player_move << "  컴퓨터 선택: " << computer_move;

    int result = SCORE_TABLE[MoveToIndex(player_move)][MoveToIndex(computer_move)];

    if (result == 1) {
        cout << "\n이 라운드에서 승리했습니다!";
        ++player_score;
    }
    else if (result == -1) {
        cout << "\n컴퓨터가 이 라운드에서 승리했습니다.";
        ++computer_score;
    }
    else {
        cout << "\n비겼습니다!";
    }
}

// Lua에서 호출할 EvaluateMoves 함수 정의
int Lua_EvaluateMoves(lua_State* L) {
    if (lua_gettop(L) != 4 ||
        !lua_isstring(L, 1) ||
        !lua_isstring(L, 2) ||
        !lua_isnumber(L, 3) ||
        !lua_isnumber(L, 4)) {
        cerr << "[C++]: 오류: 잘못된 인수 전달 (EvaluateMoves)" << "\n";
        return 0;
    }

    string player_move = lua_tostring(L, 1);
    string computer_move = lua_tostring(L, 2);
    int player_score = static_cast<int>(lua_tonumber(L, 3));
    int computer_score = static_cast<int>(lua_tonumber(L, 4));

    EvaluateMoves(player_move, computer_move, player_score, computer_score);

    lua_pushnumber(L, player_score);
    lua_pushnumber(L, computer_score);

    return 2;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // 시드 설정

    lua_State* L = luaL_newstate(); // Lua 상태 생성
    OpenLuaLibraries(L);

    // 함수 등록
    lua_register(L, "GetComputerMove", Lua_GetComputerMove);
    lua_register(L, "EvaluateMoves", Lua_EvaluateMoves);

    // 스크립트 실행
    RunLuaScript(L, "script.lua");

    lua_close(L); // 정리
    return 0;
}
