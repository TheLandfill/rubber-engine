#include "olcPixelGameEngine/olcPixelGameEngine.h"
#include "olcPGEX_AnimatedSprite/olcPGEX_AnimatedSprite.h"

class Example : public olc::PixelGameEngine
{
public:
	Example() {
		sAppName = "Example";
		resources_path = __FILE__;
		auto slash = resources_path.rfind('/');
		slash = resources_path.rfind('/', slash - 1);
		resources_path = resources_path.substr(0, slash);
		resources_path += "/resources/";
	}

public:
	bool OnUserCreate() override {
		// Called once at the start, so create things here
		spritesheet = new olc::Renderable();
		spritesheet->Load(resources_path + "pngfind.com-ayy-lmao-png-6422951.png");
		sprite.mode = olc::AnimatedSprite::SPRITE_MODE::SINGLE;
		sprite.spriteSheet = spritesheet;
		sprite.SetSpriteSize({80, 108});
		sprite.SetSpriteScale(0.25f);
		float walking_speed = 0.25f;
		sprite.AddState("idle down king", walking_speed, olc::AnimatedSprite::PLAY_MODE::LOOP,
		std::vector<olc::vi2d>({ { 80, 0 } }));
		sprite.AddState("idle left king", walking_speed, olc::AnimatedSprite::PLAY_MODE::LOOP,
		std::vector<olc::vi2d>({ { 80, 108 } }));
		sprite.AddState("idle right king", walking_speed, olc::AnimatedSprite::PLAY_MODE::LOOP,
		std::vector<olc::vi2d>({ { 80, 216 } }));
		sprite.AddState("idle up king", walking_speed, olc::AnimatedSprite::PLAY_MODE::LOOP,
		std::vector<olc::vi2d>({ { 80, 324 } }));
		sprite.AddState("walking down king", walking_speed, olc::AnimatedSprite::PLAY_MODE::PING_PONG, std::vector<olc::vi2d>({
			{   0,   0 },
			{  80,   0 },
			{ 160,   0 }
		}));
		sprite.AddState("walking left king", walking_speed, olc::AnimatedSprite::PLAY_MODE::PING_PONG, std::vector<olc::vi2d>({
			{   0, 108 },
			{  80, 108 },
			{ 160, 108 }
		}));
		sprite.AddState("walking right king", walking_speed, olc::AnimatedSprite::PLAY_MODE::PING_PONG, std::vector<olc::vi2d>({
			{   0, 216 },
			{  80, 216 },
			{ 160, 216 }
		}));
		sprite.AddState("walking up king", walking_speed, olc::AnimatedSprite::PLAY_MODE::PING_PONG, std::vector<olc::vi2d>({
			{   0, 324 },
			{  80, 324 },
			{ 160, 324 }
		}));
		sprite.SetState("idle down king");
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand()% 256));
		SetPixelMode(olc::Pixel::MASK);
		control_sprite_movement(fElapsedTime);
		sprite.Draw(fElapsedTime, sprite_pos);
		return true;
	}

	~Example() {
		delete spritesheet;
	}
private:
	void control_sprite_movement(float fElapsedTime) {
		olc::HWButton left = GetKey(olc::Key::LEFT);
		olc::HWButton right = GetKey(olc::Key::RIGHT);
		olc::HWButton up = GetKey(olc::Key::UP);
		olc::HWButton down = GetKey(olc::Key::DOWN);
		bool any_movement = left.bHeld || right.bHeld || up.bHeld || down.bHeld;
		if (!any_movement) {
			cur_movement_state = MOVEMENT_STATE::IDLE;
		} else {
			cur_movement_state = MOVEMENT_STATE::WALKING;
			sprite_pos += sprite_speed * fElapsedTime * directions[cur_direction];
		}
		if (left.bPressed) {
			cur_direction = DIRECTION::LEFT;
		} else if (up.bPressed) {
			cur_direction = DIRECTION::UP;
		} else if (right.bPressed) {
			cur_direction = DIRECTION::RIGHT;
		} else if (down.bPressed) {
			cur_direction = DIRECTION::DOWN;
		}
		sprite.SetState(sprite_movement[cur_movement_state][cur_direction]);
	}
private:
	std::string resources_path;
	enum DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	} cur_direction = DIRECTION::DOWN;
	enum MOVEMENT_STATE {
		IDLE,
		WALKING
	} cur_movement_state = MOVEMENT_STATE::IDLE;
	std::string sprite_movement[2][4] = {
		{
			"idle up king",
			"idle down king",
			"idle left king",
			"idle right king"
		},
		{
			"walking up king",
			"walking down king",
			"walking left king",
			"walking right king"
		}
	};
	olc::vf2d directions[4] = {
		{  0.f, -1.f },
		{  0.f,  1.f },
		{ -1.f,  0.f },
		{  1.f,  0.f }
	};
	olc::AnimatedSprite sprite;
	olc::Renderable * spritesheet;
	olc::vf2d sprite_pos = { 64.f, 80.f };
	float sprite_speed = 100.0f;
};


int main() {
	Example demo;
	if (demo.Construct(512, 480, 2, 2))
		demo.Start();

	return 0;
}
