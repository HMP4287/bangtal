#include <bangtal>
using namespace bangtal;

int main()
{
	auto room1 = Scene::create("룸1", "Images/배경-1.png");
	auto door1 = Object::create("Images/문-오른쪽-닫힘.png", room1, 800, 270);
	auto closed1 = true;
	auto key = Object::create("Images/열쇠.png", room1, 600, 150);
	key->setScale(0.2f);


	auto room2 = Scene::create("룸2", "Images/배경-2.png");
	auto button1 = Object::create("Images/스위치.png", room2, 800, 470);
	auto button1_is_off = true;
	button1->setScale(3.0f);

	auto door2 = Object::create("Images/문-오른쪽-열림.png", room2, 1000, 270);
	door2->hide(); 

	key->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
		object->pick();
		return true;
		});

	door1->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
		if (closed1) {
			if (key->isHanded()) {
				object->setImage("Images/문-오른쪽-열림.png");
				closed1 = false;
			}
			else {
				showMessage("열쇠가 필요해~~~");
			}
		}
		else {
			room2->enter();
		}
		return true;
		});

	button1->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
		if (button1_is_off) {
			door2->show();
			button1_is_off = false; 
		}
		else {
			door2->hide(); 
			button1_is_off = true; 
		}
		return true;
		});

	door2->setOnMouseCallback([&](auto object, auto x, auto y, auto action) -> bool {
		endGame();
		return true;
		});

	startGame(room1);
}
