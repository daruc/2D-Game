#include "Strings.h"

Strings* Strings::instance = nullptr;

Strings* Strings::Instance()
{
	if (instance == nullptr)
	{
		instance = new Strings();
	}
	return instance;
}

Strings::Strings()
	: new_game(L"Nowa gra"),
	controls(L"Sterowanie"),
	editor(L"Edytor"),
	exit(L"Wyjœcie"),
	map_menu_title(L"Wybór mapy"),
	main_menu(L"Menu g³ówne"),
	map_1(L"Mapa 1"),
	map_2(L"Mapa 2"),
	map_3(L"Mapa 3"),
	map_4(L"Mapa 4"),
	controls_title(L"Sterowanie"),
	turn_left(L"W lewo"),
	turn_right(L"W prawo"),
	crouch(L"Kucanie"),
	jump(L"Skakanie"),
	save(L"Zapisz"),
	menu(L"Menu"),
	undo(L"Confij"),
	ground(L"Ziemia"),
	fire(L"Ogieñ"),
	player(L"Gracz"),
	finish(L"Meta"),
	enemy(L"Przeciwnik"),
	type_1(L"Typ 1"),
	type_2(L"Typ 2"),
	type_3(L"Typ 3"),
	type_4(L"Typ 4"),
	load(L"Wczytaj"),
	save_map_title(L"Zapisywanie mapy"),
	load_map_title(L"Wczytywanie mapy"),
	win(L"Wygrana"),
	defeat(L"Przegrana")

	/*std::wstring menu;
	std::wstring undo;
	std::wstring ground;
	std::wstring player;
	std::wstring finish;
	std::wstring enemy;
	std::wstring type_1;
	std::wstring type_2;
	std::wstring type_3;
	std::wstring type_4;
	std::wstring load;*/
{

}