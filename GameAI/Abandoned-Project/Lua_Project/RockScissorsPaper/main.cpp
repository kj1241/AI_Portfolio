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
const string MOVES[NUM_MOVES] = { "����", "����", "��" };

// Lua ���̺귯�� ���� �Լ�
void OpenLuaLibraries(lua_State* L) {
    luaL_openlibs(L);
}

// Lua ��ũ��Ʈ ���� �Լ�
void RunLuaScript(lua_State* L, const string& filename) {
    if (luaL_dofile(L, filename.c_str()) != LUA_OK) {
        cerr << "[C++]: ����: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }
}

// GetRandomInt �Լ� ����
int GetRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// GetComputerMove �Լ� ����
string GetComputerMove() {
    return MOVES[GetRandomInt(0, NUM_MOVES - 1)];
}

// Lua���� ȣ���� GetComputerMove �Լ� ����
int Lua_GetComputerMove(lua_State* L) {
    lua_pushstring(L, GetComputerMove().c_str());
    return 1;
}

// MoveToIndex �Լ� ����
int MoveToIndex(const string& move) {
    for (int i = 0; i < NUM_MOVES; ++i) {
        if (move == MOVES[i]) return i;
    }
    return -1;
}

// EvaluateMoves �Լ� ����
void EvaluateMoves(const string& player_move, const string& computer_move, int& player_score, int& computer_score) {
    static const int SCORE_TABLE[NUM_MOVES][NUM_MOVES] = {
        {0, -1, 1},
        {1, 0, -1},
        {-1, 1, 0}
    };

    cout << "\n����� ����: " << player_move << "  ��ǻ�� ����: " << computer_move;

    int result = SCORE_TABLE[MoveToIndex(player_move)][MoveToIndex(computer_move)];

    if (result == 1) {
        cout << "\n�� ���忡�� �¸��߽��ϴ�!";
        ++player_score;
    }
    else if (result == -1) {
        cout << "\n��ǻ�Ͱ� �� ���忡�� �¸��߽��ϴ�.";
        ++computer_score;
    }
    else {
        cout << "\n�����ϴ�!";
    }
}

// Lua���� ȣ���� EvaluateMoves �Լ� ����
int Lua_EvaluateMoves(lua_State* L) {
    if (lua_gettop(L) != 4 ||
        !lua_isstring(L, 1) ||
        !lua_isstring(L, 2) ||
        !lua_isnumber(L, 3) ||
        !lua_isnumber(L, 4)) {
        cerr << "[C++]: ����: �߸��� �μ� ���� (EvaluateMoves)" << "\n";
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
    srand(static_cast<unsigned int>(time(0))); // �õ� ����

    lua_State* L = luaL_newstate(); // Lua ���� ����
    OpenLuaLibraries(L);

    // �Լ� ���
    lua_register(L, "GetComputerMove", Lua_GetComputerMove);
    lua_register(L, "EvaluateMoves", Lua_EvaluateMoves);

    // ��ũ��Ʈ ����
    RunLuaScript(L, "script.lua");

    lua_close(L); // ����
    return 0;
}
