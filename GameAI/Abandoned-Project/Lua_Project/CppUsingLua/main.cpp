extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Lua ���̺귯�� ���� �Լ�
void OpenLuaLibraries(lua_State* pL) {
    luaL_openlibs(pL);
}

// Lua ��ũ��Ʈ ���� �Լ�
void RunLuaScript(lua_State* pL, const string& filename) {
    if (luaL_dofile(pL, filename.c_str()) != LUA_OK) {
        cerr << "[C++]: ����: " << lua_tostring(pL, -1) << "\n";
        lua_pop(pL, 1);
    }
}

int main() {
    // Lua ���� ����
    lua_State* pL = luaL_newstate();

    // ���̺귯�� ����
    OpenLuaLibraries(pL);
    RunLuaScript(pL, "script.lua");

    cout << "\n";
    cout << "Lua ���ڿ� �� ���� Ÿ���� C++ std::string �� int Ÿ�Կ� �Ҵ��ϱ�\n";

    // ���� �ε��� �缳��
    lua_settop(pL, 0);

    // ���� ���� 'age'�� 'name'�� ���ÿ� �ø���
    lua_getglobal(pL, "age");
    lua_getglobal(pL, "name");

    // �������� �ùٸ� Ÿ������ Ȯ�� (���� �ε����� 1���� �����ϴ� �Ϳ� ����)
    if (!lua_isnumber(pL, 1) || !lua_isstring(pL, 2)) {
        cout << "[C++] ����: �߸��� Ÿ��!\n";
    }

    // ���� ���� C++ ������ �Ҵ�
    string name = lua_tostring(pL, 2);
    // int�� ĳ����
    int age = (int)lua_tonumber(pL, 1);

    cout << "[C++]: name = " << name << "\n"
        << "[C++]: age  = " << age << "\n";

    cout << "\n";
    cout << "������ ���̺� ��������\n";

    // ���̺��� ���ÿ� �ø���
    lua_getglobal(pL, "simple_table");

    if (!lua_istable(pL, -1)) {
        cout << "[C++] ����: simple_table�� ��ȿ�� ���̺��� �ƴմϴ�\n";
    }
    else {
        // Ű�� ���ÿ� �ø���
        lua_pushstring(pL, "name");

        // ���̺��� ���� -2�� ���� (Ű�� -1�� ����). lua_gettable�� ���� Ű�� ���ÿ��� ���ϰ�
        // Ű ��ġ���� �����͸� ���ÿ� �ø�
        lua_gettable(pL, -2);

        // �ùٸ� Ÿ������ Ȯ��
        if (!lua_isstring(pL, -1)) {
            cout << "[C++] ����: �߸��� Ÿ��\n";
        }

        // ������ ��������
        name = lua_tostring(pL, -1);

        cout << "[C++]: name = " << name << "\n";

        lua_pop(pL, 1);

        // ���� age�� ���ؼ��� �����ϰ� ����
        lua_pushstring(pL, "age");
        lua_gettable(pL, -2);
        if (!lua_isnumber(pL, -1)) {
            cout << "[C++] ����: �߸��� Ÿ��\n" << endl;
        }

        // ������ ��������
        age = (int)lua_tonumber(pL, -1);

        lua_pop(pL, 1);

        cout << "[C++]: age  = " << age << "\n";
    }

    cout << "\n";
    cout << "������ Lua �Լ� ȣ��: add(a, b)\n";

    // ���� ���̺��� �Լ� �����ͼ� ���ÿ� �ø���
    lua_getglobal(pL, "add");

    // �Լ��� �ִ��� Ȯ��
    if (!lua_isfunction(pL, -1)) {
        cout << "[C++] Lua �Լ� 'add'�� ���ǵ��� �ʾҽ��ϴ�\n";
    }

    // Lua ���ÿ� ������ Ǫ��
    lua_pushnumber(pL, 5);
    lua_pushnumber(pL, 8);

    // �Ķ���Ϳ� �Բ� �Լ� ȣ��, Lua �Լ��� �Ķ���� ������ ��ȯ ���� ������ ����.
    // ����� ������ ��ܿ� �ø�
    lua_call(pL, 2, 1);

    // ������ ��ܿ��� ��� ��������
    int result = (int)lua_tonumber(pL, -1);

    lua_pop(pL, 1);

    cout << "[C++] <lua>add(5,8) = " << result << "\n";

    cout << "\n";
    cout << "���ο� Lua �Լ� ȣ��: print_message(message)\n";

    // Lua ���ÿ� print_message �Լ� �ø���
    lua_getglobal(pL, "print_message");

    // �Լ��� �ִ��� Ȯ��
    if (!lua_isfunction(pL, -1)) {
        cout << "[C++] Lua �Լ� 'print_message'�� ���ǵ��� �ʾҽ��ϴ�\n";
    }

    // Lua ���ÿ� ������ Ǫ��
    lua_pushstring(pL, "Hello from C++!");

    // �Լ� ȣ��
    lua_call(pL, 1, 0);

    cout << "\n";
    cout << "���̺� ��� �߰�: add_to_table(tbl, key, value)\n";

    // Lua ���ÿ� add_to_table �Լ� �ø���
    lua_getglobal(pL, "add_to_table");

    // �Լ��� �ִ��� Ȯ��
    if (!lua_isfunction(pL, -1)) {
        cout << "[C++] Lua �Լ� 'add_to_table'�� ���ǵ��� �ʾҽ��ϴ�\n";
    }

    // Lua ���ÿ� ������ Ǫ��
    lua_getglobal(pL, "simple_table");  // ���̺�
    lua_pushstring(pL, "new_key");      // Ű
    lua_pushnumber(pL, 12345);          // ��

    // �Լ� ȣ��
    lua_call(pL, 3, 0);

    // ���� �߰��� ��Ҹ� Ȯ���ϱ� ���� simple_table�� ������ �ٽ� ��������
    lua_getglobal(pL, "simple_table");
    lua_pushstring(pL, "new_key");
    lua_gettable(pL, -2);

    if (!lua_isnumber(pL, -1)) {
        cout << "[C++] ����: �߸��� Ÿ��\n";
    }
    else {
        int new_value = (int)lua_tonumber(pL, -1);
        cout << "[C++]: new_key = " << new_value << "\n";
    }

    lua_pop(pL, 1);

    // ����
    lua_close(pL);
    return 0;
}
