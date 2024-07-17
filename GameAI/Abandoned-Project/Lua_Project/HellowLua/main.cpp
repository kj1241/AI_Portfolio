#include <iostream>
#include <lua.hpp>

int main() {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    // Lua ��ũ��Ʈ ���ڿ�
    const char* lua_script = R"(
        -- Lua 5.4.2 ���� ��ũ��Ʈ

        -- ���� ����� ���
        local message = "Hello from Lua!"
        print(message)

        -- �Լ� ���� �� ȣ��
        function add(a, b)
            return a + b
        end

        local result = add(10, 20)
        print("Result:", result)
    )";

    // Lua ��ũ��Ʈ ����
    if (luaL_dostring(L, lua_script)) {
        std::cerr << "[C++]: ����: " << lua_tostring(L, -1) << "\n";
        lua_close(L);
        return 1;
    }

    lua_close(L);
    return 0;
}
