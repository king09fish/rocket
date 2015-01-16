#include<iostream>
#include"luaengine.h"

void setLuaPath(lua_State* L)
{
	lua_getglobal(L, "package");
	lua_getfield(L, -1, "path"); // get field "path" from table at top of stack (-1)
	std::string cur_path = lua_tostring(L, -1); // grab path string from top of stack
	cur_path.append(";"); // do your path magic here
	std::string path_lua = "../script";
	cur_path.append(path_lua);
	lua_pop(L, 1); // get rid of the string on the stack we just pushed on line 5
	lua_pushstring(L, cur_path.c_str()); // push the new one
	lua_setfield(L, -2, "path"); // set the field "path" in table at -2 with value at top of stack
	lua_pop(L, 1); // get rid of package table from top of stack
}

int main(int argc, char *argv[])
{

	printf("hello world");
	lua_State *L = luaL_newstate();  /* create state */
	if (L == NULL)
	{
		return EXIT_FAILURE;
	}
	luaL_openlibs(L);	// link lua lib

	setLuaPath(L);

	return 0;


}