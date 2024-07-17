#include <iostream>
#include <lua.hpp>

// Lua ��ũ��Ʈ ������ �����ϴ� �Լ�
void runLuaScript(lua_State* L, const std::string& script) {
    if (luaL_dofile(L, script.c_str()) != LUA_OK) {
        std::cerr << "lua ��ũ��Ʈ ���� ����: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }
}

// Lua �Լ� ȣ���� ���� ���� �Լ�
void callLuaFunction(lua_State* L, const std::string& func) {
    lua_getglobal(L, func.c_str());
    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        std::cerr << "�Լ� ȣ�� ���� [" << func << "]: " << lua_tostring(L, -1) << "\n";
        lua_pop(L, 1);
    }
}

// Lua ���±� �ʱ�ȭ �� ����� �Է� ó��
int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Lua ��ũ��Ʈ ����
    runLuaScript(L, "game.lua");

    // ���� �ʱ�ȭ
    callLuaFunction(L, "startGame");

    // ���� ����
    while (true) {
        std::cout << "\n";
        std::cout << "---------------------------\n";
        std::cout << "1. ����\n";
        std::cout << "2. ������ ���\n";
        std::cout << "3. �κ��丮 ����\n";
        std::cout << "4. ����\n";
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
            std::cout << "������ �����մϴ�.\n";
            break;
        }
        else {
            std::cout << "�߸��� �����Դϴ�.\n";
        }

        // ���� ���� Ȯ��
        callLuaFunction(L, "checkEndCondition");
    }

    lua_close(L);
    return 0;
}
