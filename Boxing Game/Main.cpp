#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

using std::vector;
using std::string;

struct Stats {
	int strength;
	int stamina;
	int speed;
	int constitution;
	int agility; 

};

struct Skills {

};

struct Injury {

};

struct Fighter {

	int health;
	Stats stats;
	Skills skills; 
	vector<Injury> injuries; 
};

struct Player {
	int money;
	int food;
	int energy;
	Fighter fighter;

};

// Override base class with your custom functionality
class BoxingGame : public olc::PixelGameEngine
{

	
	enum class MainStates { menu, game };

	enum class fightActions {
		dodgeLeft,
		dodgeRight,
		leftStep,
		rightStep, 
		forwardStep, 
		backStep,
		goLow,
		punchLow
	};

	enum class fightAttacks {
		leftJab, 
		rightJab,
		leftHook,
		rightHook,
		leftUppercut,
		rightUppercut,
		guard

	};

	MainStates mainState = MainStates::menu;
	

	int selection0 = 0;
	vector<string> menuOptions;
	std::map< fightActions, olc::Key> keyboardInputMapping;

	void optionDisplay(int selectedOption, vector<string>options, int x, int y, int width = 300, int height = 300, int scale = 2) {
		FillRect(x, y, width, height, olc::DARK_BLUE);
		int count = 0;

		for (string& option : options) {
			if (selectedOption == count) {
				DrawString(x + 3 * scale, y + 3 * scale + scale * 9 * count, ">", olc::WHITE, scale);
			}
			DrawString(x + 10 * scale, y + 3 * scale + scale * 9 * count, option, olc::WHITE, scale);
			count++;
		}
	}

	vector<fightActions> keyboardInput(std::map< fightActions, olc::Key> keyboardInputMapping) {
		vector<fightActions> output = {};

		for (auto keyMap : keyboardInputMapping) {
			
			if (GetKey(keyMap.second).bPressed) {
				output.push_back(keyMap.first);
			}

		}
		return output;
	}

public:
	BoxingGame()
	{
		// Name you application
		sAppName = "BoxingGame";
	}

public:
	bool OnUserCreate() override
	{
		keyboardInputMapping.insert_or_assign(fightActions::leftStep, olc::A);
		keyboardInputMapping.insert_or_assign(fightActions::rightStep, olc::D);
		keyboardInputMapping.insert_or_assign(fightActions::backStep, olc::S);
		keyboardInputMapping.insert_or_assign(fightActions::forwardStep, olc::W);
		keyboardInputMapping.insert_or_assign(fightActions::goLow, olc::CTRL);
		keyboardInputMapping.insert_or_assign(fightActions::punchLow, olc::SHIFT);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{

		

		switch (mainState) {
		case MainStates::menu:
			menuOptions = { "New Game", "test1", "exit"};
			
			selection0 = (selection0+ menuOptions.size()) % menuOptions.size();
			optionDisplay(selection0, menuOptions, 0, 0);

			if (GetKey(olc::UP).bPressed) selection0--;
			if (GetKey(olc::DOWN).bPressed) selection0++;
			if (GetKey(olc::ENTER).bPressed)
			{
				switch (selection0) {
				case 0 :
					mainState = MainStates::game;
					break;
				case 1:
					keyboardInput(keyboardInputMapping);
					break;
				default : 
					break;
				}
			}

			break;
			
		case MainStates::game:
			keyboardInput(keyboardInputMapping);
			FillRect(0,0, ScreenWidth(), ScreenHeight(), olc::BLACK);
			break;
		}

		
		return true;
	}
};

int main()
{
	BoxingGame demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}