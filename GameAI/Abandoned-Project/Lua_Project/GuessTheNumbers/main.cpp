#include <iostream>
#include <lua.hpp>

// Lua ��ũ��Ʈ ���� �Լ�
void runLuaScript(lua_State* L, const std::string& script) {
    if (luaL_dofile(L, script.c_str()) != LUA_OK) {
        std::cerr << "��ũ��Ʈ ���� ����: " << lua_tostring(L, -1) <<"\n";
    }
}

// guessNumber �Լ� ȣ��
int callGuessNumber(lua_State* L, int guess) {
    // �Լ� �̸��� ���ÿ� �ø�
    lua_getglobal(L, "guessNumber");

    // ���ڸ� ���ÿ� �ø�
    lua_pushinteger(L, guess);

    // �Լ� ȣ�� (���� 1��, ��� 1��)
    if (lua_pcall(L, 1, 1, 0) != LUA_OK) {
        std::cerr << "�Լ� ȣ�� ����: " << lua_tostring(L, -1) << "\n";
        return -2; // ������ ǥ���ϴ� ��
    }

    // ��� ��������
    int result = lua_tointeger(L, -1);
    lua_pop(L, 1);  // ���ÿ��� ��� ����

    return result;
}

int main() {
    // Lua ���� ����
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Lua ��ũ��Ʈ ����
    runLuaScript(L, "script.lua");

    // ����� �Է� �� ���� ���� ����
    while (true) {
        int guess;
        std::cout << "���ڸ� �Է��ϼ���(1~100): ";
        std::cin >> guess;

        // Lua�� guessNumber �Լ� ȣ��
        int result = callGuessNumber(L, guess);
        if (result == 0) {
            std::cout << "������ϴ�!" << std::endl;
            break;
        }
        else if (result == -1) {
            std::cout << "Ʋ�Ƚ��ϴ�. ������ �� ū �����Դϴ�. �ٽ� �õ��ϼ���.\n";
        }
        else if (result == 1) {
            std::cout << "Ʋ�Ƚ��ϴ�. ������ �� ���� �����Դϴ�. �ٽ� �õ��ϼ���.\n";
        }
        else {
            std::cerr << "������ �߻��߽��ϴ�. �ٽ� �õ��ϼ���.\n";
        }
    }

    lua_close(L);
    return 0;
}
