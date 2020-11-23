#include "App.h"

#include "Cube.h"
#include "Ball.h"
#include "Pyramid.h"
#include "SkinnedCube.h"
#include "Cylinder.h"

#include <memory>
#include <algorithm>
#include <iterator>
#include "Maths.h"
#include "Surface.h"
#include "GDIPlusManager.h"

#include "GameObjects.h"
#include "Grid.h"

GDIPlusManager gdipm;

App::App() :
	wnd(800, 600, "DemoWindow"),
	light(wnd.getRenderer())
{
	wnd.getRenderer().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	wnd.getRenderer().setCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f));

	_GD.game_objects = &game_objects;

	light.setPos(10, 10, 3);
	world = new Grid(wnd.getRenderer());

	Turret* debug_boi = new TurretGun(wnd.getRenderer(), Vector3(4, 4, 0));
	game_objects.emplace_back(debug_boi);
	debug_boi = new TurretGun(wnd.getRenderer(), Vector3(3, 3, 0));
	game_objects.emplace_back(debug_boi);
	debug_boi = new TurretGun(wnd.getRenderer(), Vector3(4, 2, 0));
	game_objects.emplace_back(debug_boi);
	debug_boi = new TurretGun(wnd.getRenderer(), Vector3(15, 5, 0));
	game_objects.emplace_back(debug_boi);
	debug_boi = new TurretLaser(wnd.getRenderer(), Vector3(7, 4, 0));
	game_objects.emplace_back(debug_boi);
	debug_boi = new TurretLaser(wnd.getRenderer(), Vector3(15, 2, 0));
	game_objects.emplace_back(debug_boi);
}

App::~App()
{
	for (auto& go : game_objects)
	{
		delete go;
		go = nullptr;
	}
	game_objects.clear();
}

int App::run()
{
	MSG msg;
	BOOL gResult;
	while (true)
	{
		if (std::optional<int> exit = Window::readMsgs())
		{
			return exit.value();
		}
		tick();
	}

	if (gResult == -1)
	{
		return -1;
	}
	return msg.wParam;
}

void App::tick()
{
	_GD.dt = timer.mark();

	//Keyboard::Event e = wnd.kbd.readKey();
	//if (e.IsPress() && e.GetCode() == 'A')
	//{
	//	//Factory f(wnd.getRenderer());
	//	//std::generate_n(std::back_inserter(drawables), 1, f);
	//}

#pragma region lazy cam

	float wish_y = 0;
	float wish_x = 0;
	float wish_z = 0;
	if (wnd.kbd.getKey('I'))
	{
		wish_y--;
	}
	if (wnd.kbd.getKey('K'))
	{
		wish_y++;
	}
	if (wnd.kbd.getKey('L'))
	{
		wish_x--;
	}
	if (wnd.kbd.getKey('J'))
	{
		wish_x++;
	}
	if (wnd.kbd.getKey('U'))
	{
		wish_z--;
	}
	if (wnd.kbd.getKey('M'))
	{
		wish_z++;
	}
	wish_x *= _GD.dt * 10;
	wish_y *= _GD.dt * 10;
	wish_z *= _GD.dt * 10;
	cam.moveCam(wish_x, wish_y, wish_z);
#pragma endregion

	// UPDATE
	for (auto& it : game_objects)
	{
		it->update(&_GD);
	}

	// Delete objects listed for deletion
	std::vector<GameObject*>& d_list = GameObject::fetchDestroyList();
	while (d_list.size())
	{
		GameObject* ptr = d_list.back();
		d_list.pop_back();
		for (std::vector<GameObject*>::iterator it = game_objects.begin(); it != game_objects.end(); it++)
		{
			if ((*it) == ptr)
			{
				delete (*it);
				(*it) = nullptr;
				game_objects.erase(it);
				break;
			}
		}
	}
	std::vector<GameObject*>& c_list = GameObject::fetchCreateList();
	while (c_list.size())
	{
		GameObject* ptr = c_list.back();
		c_list.pop_back();
		game_objects.emplace_back(ptr);
	}

	// RENDER
	wnd.getRenderer().wipe(0.07f, 0.0f, 0.12f);
	wnd.getRenderer().setCamera(cam.getMatrix());
	light.Bind(wnd.getRenderer(), cam.getMatrix());
	world->draw(wnd.getRenderer());
	for (auto& it : game_objects)
	{
		it->draw(&wnd.getRenderer());
	}
	wnd.getRenderer().present();
}
