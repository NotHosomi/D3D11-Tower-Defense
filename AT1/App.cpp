#include "App.h"

#include "Cube.h"
#include "Ball.h"
#include "Pyramid.h"
#include "Sheet.h"
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
	light(wnd.getRenderer()),
	terrain(wnd.getRenderer(), "Terrain", 20, 15)
{
	class Factory
	{
	public:
		Factory(Renderer& renderer)
			:
			renderer(renderer)
		{}
		std::unique_ptr<Drawable> operator()()
		{
			switch (typedist(rng))
			{
			case 1:
			{
				const DirectX::XMFLOAT3 mat = { cdist(rng),cdist(rng),cdist(rng) };
				return std::make_unique<Cube>(
					renderer, rng, adist, ddist,
					odist, rdist, bdist, mat
					);
			}
			case 2:
				return std::make_unique<Cylinder>(
					renderer, rng, adist, ddist, odist,
					rdist, bdist, tdist
					);
			case 3:
				return std::make_unique<Pyramid>(
					renderer, rng, adist, ddist, odist,
					rdist, tdist
					);
			default:
				assert(false && "bad drawable type in factory");
				return {};
			}
		}
	private:
		Renderer& renderer;
		std::mt19937 rng{ std::random_device{}() };
		std::uniform_int_distribution<int> typedist{ 1,3 };
		std::uniform_real_distribution<float> adist{ 0.0f,PI * 2.0f };
		std::uniform_real_distribution<float> ddist{ 0.0f,PI * 0.5f };
		std::uniform_real_distribution<float> odist{ 0.0f,PI * 0.08f };
		std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
		std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
		std::uniform_real_distribution<float> cdist{ 0.0f,1.0f };
		std::uniform_int_distribution<int> latdist{ 5,20 };
		std::uniform_int_distribution<int> longdist{ 10,40 };
		std::uniform_int_distribution<int> tdist{ 3,30 };
	};
	
	Factory f(wnd.getRenderer());
	drawables.reserve(50);
	std::generate_n(std::back_inserter(drawables), 50, f);
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			Vector3 pos(i, j, 0);
			Marker* m = new Marker(wnd.getRenderer(), pos);
			game_objects.emplace_back(m);
		}
	}
	wnd.getRenderer().setProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
	wnd.getRenderer().setCamera(DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f));

	_GD.game_objects = &game_objects;

	debug_boi = new SkinnedCube(wnd.getRenderer(), "Terrain");
	//debug_boi_2 = new Ball(wnd.getRenderer(), 10, 10, Vector3(2, 0, 0));

	light.setPos(-5, 2, 10);
	world = new Grid(wnd.getRenderer());
}

App::~App()
{}

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

	// camera move
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

	for (auto& it : game_objects)
	{
		it->update(_GD);
	}

	// RENDER
	wnd.getRenderer().wipe(0.07f, 0.0f, 0.12f);
	cam.moveCam(wish_x, wish_y, wish_z);
	wnd.getRenderer().setCamera(cam.getMatrix());
	light.Bind(wnd.getRenderer(), cam.getMatrix());

	// old
	for (auto& b : drawables)
	{
		b->update(_GD.dt);
		b->draw(wnd.getRenderer());
	}

	/// RENDER
	//terrain.draw(wnd.getRenderer());
	world.draw(wnd.getRenderer());
	debug_boi->draw(wnd.getRenderer());
	//debug_boi_2->draw(wnd.getRenderer());
	for (auto& it : game_objects)
	{
		it->draw(&wnd.getRenderer());
	}
	wnd.getRenderer().present();
}
