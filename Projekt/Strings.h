#ifndef STRINGS_H
#define STRINGS_H
#include <string>

class Strings
{
public:
	static Strings* Instance();
	inline std::wstring getNewGame() const { return new_game; }
	inline std::wstring getControls() const { return controls; }
	inline std::wstring getEditor() const { return editor; }
	inline std::wstring getExit() const { return exit; }
	inline std::wstring getMapMenuTitle() const { return map_menu_title; }
	inline std::wstring getMainMenu() const { return main_menu; }
	inline std::wstring getMap1() const { return map_1; }
	inline std::wstring getMap2() const { return map_2; }
	inline std::wstring getMap3() const { return map_3; }
	inline std::wstring getMap4() const { return map_4; }
	inline std::wstring getControlsTitle() const { return controls_title; }
	inline std::wstring getTurnLeft() const { return turn_left; }
	inline std::wstring getTurnRight() const { return turn_right; }
	inline std::wstring getCrouch() const { return crouch; }
	inline std::wstring getJump() const { return jump; }
	inline std::wstring getSave() const { return save; }
	inline std::wstring getMenu() const { return menu; }
	inline std::wstring getUndo() const { return undo; }
	inline std::wstring getGround() const { return ground; }
	inline std::wstring getPlayer() const { return player; }
	inline std::wstring getFinish() const { return finish; }
	inline std::wstring getEnemy() const { return enemy; }
	inline std::wstring getType1() const { return type_1; }
	inline std::wstring getType2() const { return type_2; }
	inline std::wstring getType3() const { return type_3; }
	inline std::wstring getType4() const { return type_4; }
	inline std::wstring getLoad() const { return load; }
	inline std::wstring getSaveMapTitle() const { return save_map_title; }
	inline std::wstring getLoadMapTitle() const { return load_map_title; }
	inline std::wstring getWin() const { return win; }
protected:
	Strings();
private:
	static Strings* instance;

	//main menu
	std::wstring new_game;
	std::wstring controls;
	std::wstring editor;
	std::wstring exit;

	//map menu
	std::wstring map_menu_title;
	std::wstring main_menu;
	std::wstring map_1;
	std::wstring map_2;
	std::wstring map_3;
	std::wstring map_4;

	//controls
	std::wstring controls_title;
	std::wstring turn_left;
	std::wstring turn_right;
	std::wstring crouch;
	std::wstring jump;
	std::wstring save;

	//editor
	std::wstring menu;
	std::wstring undo;
	std::wstring ground;
	std::wstring player;
	std::wstring finish;
	std::wstring enemy;
	std::wstring type_1;
	std::wstring type_2;
	std::wstring type_3;
	std::wstring type_4;
	std::wstring load;

	//save map
	std::wstring save_map_title;

	//load map
	std::wstring load_map_title;

	//game over
	std::wstring win;
};
#endif