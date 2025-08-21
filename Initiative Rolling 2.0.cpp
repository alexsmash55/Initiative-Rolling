#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

using namespace std;

void InitiativeList()
{
	random_device rd;
	uniform_int_distribution<short> d20(1, 20);

	bool DoInitiative = true;
	short creatures_amount = 0;
	short init_mod = 0;
	string name{};

	unordered_map <string, short> umInitiative;
	vector <pair<string, short>> vInitiativeOrdered;
	vector <short> vInitiativeValue;

	while (DoInitiative == true)
	{
		cout << "\nType a creature name (or stop/STOP to roll the initiative): ";
		cin >> name;

		if (name == "stop" || name == "STOP" || name == "Stop") { break; }

		cout << "Type creature's initiative mod: ";
		cin >> init_mod;

		cout << "How many of them take a fight? ";
		cin >> creatures_amount;

		for (short i = 0; i < creatures_amount; i++)
		{
			if (creatures_amount == 1)
			{
				string newName = name;

				umInitiative.insert(pair<string, short>(newName, init_mod));
				vInitiativeValue.push_back(init_mod);
			}
			else
			{
				string newName = name + to_string((i + 1));

				umInitiative.insert(pair<string, short>(newName, init_mod));
				vInitiativeValue.push_back(init_mod);
			}
		}
	}

	for (auto& j : umInitiative)
	{
		j.second = j.second + d20(rd);	//RollDice20()

		if (j.second <= 0) { j.second = 1; }

		vInitiativeValue.push_back(j.second);
	}

	sort(vInitiativeValue.begin(), vInitiativeValue.end(), greater<short>());

	for (short i = 0; i < vInitiativeValue.size(); i++)
	{
		if (i + 1 != vInitiativeValue.size())
		{
			if (vInitiativeValue[i] == vInitiativeValue[i + 1])
			{
				continue;
			}
		}

		for (auto& j : umInitiative)
		{
			if (vInitiativeValue[i] == j.second)
			{
				vInitiativeOrdered.push_back({ j.first, j.second });
			}
		}

	}

	cout << endl << "[INITIATIVE LIST]" << endl;
	for (auto& pair : vInitiativeOrdered)
	{
		cout << "(" << pair.second << ") " << pair.first << endl;
	}

};

int main()
{
	cout << "You are about to roll the initiative for a bunch of NPCs.";
	cout << "\nFirst, type a creature class name (like 'orc'), then type it's initiative mode and finally how many of them do you have.";
	cout << "\nYou can add as many reoccuring NPSs as you like. Let's begin :)" << endl;

	InitiativeList();
	cout << endl;
	system("pause");
	return 0;
}
