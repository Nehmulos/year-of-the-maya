#include "Utils.h"

void stackDump (lua_State *L) {
  int i;
  int top = lua_gettop(L);
  printf("luastacksize:%d\n",top);
  for (i = 1; i <= top; i++) {  /* repeat for each level */
	int t = lua_type(L, i);
	switch (t) {

	  case LUA_TSTRING:  /* strings */
		printf("`%s'", lua_tostring(L, i));
		break;

	  case LUA_TBOOLEAN:  /* booleans */
		printf(lua_toboolean(L, i) ? "true" : "false");
		break;

	  case LUA_TNUMBER:  /* numbers */
		printf("%g", lua_tonumber(L, i));
		break;

	  default:  /* other values */
		printf("%s", lua_typename(L, t));
		break;

	}
	printf("  ");  /* put a separator */
  }
  printf("\n");  /* end the listing */
}

void emptyInit(void* context) {}
void emptyUpdate(void* context, RawTime dt) {}
void emptyDraw(void* context, SDL_Surface* surface) {}
void emptyDestroy(void* context) {}
void emptyHandleEvent(void* context, SDL_Event*event) {}

bool SDL_Rect_touches(SDL_Rect* a, SDL_Rect* b) {
	return !(a->x      > b->x+b->w ||
			  a->x+a->w < b->x      ||
			  a->y      > b->y+b->h ||
			  a->y+a->h < b->y);
}

bool SDL_Rect_isInside(SDL_Rect* a, int x, int y) {
	return x > a->x && x < a->x + a->w &&
			y > a->y && y < a->y + a->h;
}

void* lua_checklightuserdata(lua_State* l, int idx){
	luaL_checktype(l, idx, LUA_TLIGHTUSERDATA);
	return lua_touserdata(l, idx);
}

void SDL_Rect_init(SDL_Rect* rect) {
	rect->x = 0;
	rect->y = 0;
	rect->w = 0;
	rect->h = 0;
}

void lua_createLib(lua_State* l, const char* tableName, const char* globalName, const luaL_Reg* functions, const luaL_Reg* methods, lua_CFunction destructor) {

	luaL_newmetatable(l, tableName); // push table to stack
	lua_pushvalue(l, -1); // push empy value to stack
	luaL_setfuncs(l, methods,0); // set top of stack to functions
	lua_setfield(l, -2, "__index"); // write top of stack into table -2 (before the functions)
	lua_pushcfunction(l, destructor);
	lua_setfield(l, -2, "__gc"); // write top of stack into table -2 (before the functions)
	lua_pop(l,1); // pop the table from stack, we no longer need it there

    luaL_newlib(l, functions);
    luaL_setmetatable(l, tableName);

    lua_setglobal(l, globalName);
}
