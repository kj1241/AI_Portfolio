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

// Lua 라이브러리 열기 함수
void OpenLuaLibraries(lua_State* pL) {
    luaL_openlibs(pL);
}

// Lua 스크립트 실행 함수
void RunLuaScript(lua_State* pL, const string& filename) {
    if (luaL_dofile(pL, filename.c_str()) != LUA_OK) {
        cerr << "[C++]: 에러: " << lua_tostring(pL, -1) << "\n";
        lua_pop(pL, 1);
    }
}

int main() {
    // Lua 상태 생성
    lua_State* pL = luaL_newstate();

    // 라이브러리 열기
    OpenLuaLibraries(pL);
    RunLuaScript(pL, "script.lua");

    cout << "\n";
    cout << "Lua 문자열 및 숫자 타입을 C++ std::string 및 int 타입에 할당하기\n";

    // 스택 인덱스 재설정
    lua_settop(pL, 0);

    // 전역 변수 'age'와 'name'을 스택에 올리기
    lua_getglobal(pL, "age");
    lua_getglobal(pL, "name");

    // 변수들이 올바른 타입인지 확인 (스택 인덱스가 1부터 시작하는 것에 주의)
    if (!lua_isnumber(pL, 1) || !lua_isstring(pL, 2)) {
        cout << "[C++] 에러: 잘못된 타입!\n";
    }

    // 이제 값을 C++ 변수에 할당
    string name = lua_tostring(pL, 2);
    // int로 캐스팅
    int age = (int)lua_tonumber(pL, 1);

    cout << "[C++]: name = " << name << "\n"
        << "[C++]: age  = " << age << "\n";

    cout << "\n";
    cout << "간단한 테이블 가져오기\n";

    // 테이블을 스택에 올리기
    lua_getglobal(pL, "simple_table");

    if (!lua_istable(pL, -1)) {
        cout << "[C++] 에러: simple_table이 유효한 테이블이 아닙니다\n";
    }
    else {
        // 키를 스택에 올리기
        lua_pushstring(pL, "name");

        // 테이블은 이제 -2에 있음 (키는 -1에 있음). lua_gettable은 이제 키를 스택에서 팝하고
        // 키 위치에서 데이터를 스택에 올림
        lua_gettable(pL, -2);

        // 올바른 타입인지 확인
        if (!lua_isstring(pL, -1)) {
            cout << "[C++] 에러: 잘못된 타입\n";
        }

        // 데이터 가져오기
        name = lua_tostring(pL, -1);

        cout << "[C++]: name = " << name << "\n";

        lua_pop(pL, 1);

        // 이제 age에 대해서도 동일하게 수행
        lua_pushstring(pL, "age");
        lua_gettable(pL, -2);
        if (!lua_isnumber(pL, -1)) {
            cout << "[C++] 에러: 잘못된 타입\n" << endl;
        }

        // 데이터 가져오기
        age = (int)lua_tonumber(pL, -1);

        lua_pop(pL, 1);

        cout << "[C++]: age  = " << age << "\n";
    }

    cout << "\n";
    cout << "간단한 Lua 함수 호출: add(a, b)\n";

    // 전역 테이블에서 함수 가져와서 스택에 올리기
    lua_getglobal(pL, "add");

    // 함수가 있는지 확인
    if (!lua_isfunction(pL, -1)) {
        cout << "[C++] Lua 함수 'add'가 정의되지 않았습니다\n";
    }

    // Lua 스택에 변수들 푸시
    lua_pushnumber(pL, 5);
    lua_pushnumber(pL, 8);

    // 파라미터와 함께 함수 호출, Lua 함수의 파라미터 개수와 반환 값의 개수를 설정.
    // 결과를 스택의 상단에 올림
    lua_call(pL, 2, 1);

    // 스택의 상단에서 결과 가져오기
    int result = (int)lua_tonumber(pL, -1);

    lua_pop(pL, 1);

    cout << "[C++] <lua>add(5,8) = " << result << "\n";

    cout << "\n";
    cout << "새로운 Lua 함수 호출: print_message(message)\n";

    // Lua 스택에 print_message 함수 올리기
    lua_getglobal(pL, "print_message");

    // 함수가 있는지 확인
    if (!lua_isfunction(pL, -1)) {
        cout << "[C++] Lua 함수 'print_message'가 정의되지 않았습니다\n";
    }

    // Lua 스택에 변수들 푸시
    lua_pushstring(pL, "Hello from C++!");

    // 함수 호출
    lua_call(pL, 1, 0);

    cout << "\n";
    cout << "테이블에 요소 추가: add_to_table(tbl, key, value)\n";

    // Lua 스택에 add_to_table 함수 올리기
    lua_getglobal(pL, "add_to_table");

    // 함수가 있는지 확인
    if (!lua_isfunction(pL, -1)) {
        cout << "[C++] Lua 함수 'add_to_table'가 정의되지 않았습니다\n";
    }

    // Lua 스택에 변수들 푸시
    lua_getglobal(pL, "simple_table");  // 테이블
    lua_pushstring(pL, "new_key");      // 키
    lua_pushnumber(pL, 12345);          // 값

    // 함수 호출
    lua_call(pL, 3, 0);

    // 새로 추가된 요소를 확인하기 위해 simple_table의 내용을 다시 가져오기
    lua_getglobal(pL, "simple_table");
    lua_pushstring(pL, "new_key");
    lua_gettable(pL, -2);

    if (!lua_isnumber(pL, -1)) {
        cout << "[C++] 에러: 잘못된 타입\n";
    }
    else {
        int new_value = (int)lua_tonumber(pL, -1);
        cout << "[C++]: new_key = " << new_value << "\n";
    }

    lua_pop(pL, 1);

    // 정리
    lua_close(pL);
    return 0;
}
