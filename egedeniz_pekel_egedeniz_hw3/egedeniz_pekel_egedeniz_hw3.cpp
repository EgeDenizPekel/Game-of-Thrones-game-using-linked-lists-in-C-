#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>
#include "linkedlist.h"

using namespace std;

bool CheckChoice(int choice)
{
	if (choice == 3)
		return true;
	else if (choice == 2)
		return true;
	else if (choice == 1)
		return true;
	else
		return false;
}

int main()
{
	string filename = "westeros.txt";
	ifstream inFile;
	inFile.open(filename.c_str());
	cout << "######## TOPOLOGY ########" << endl << endl;
	///////////////////////////////////////////////////////////////////////////////////////

	linkedlist list;

	string line;
	while (getline(inFile,line))
	{
		istringstream iss(line);
		string word,house,nei;
		bool flag = true;
		while (iss >> word)
		{
			if (flag)
			{
				house = word;
				flag = false;
			}
			else
				nei = word;
		}
		cout << "Processing " << house << ", " << nei << endl;
		////////////////////////////////////////////////////////
		bool goon = true;
		//ADD HOUSE IF IT WAS NOT ALREADY ADDED AND ADD ITS NEIGBOR
		if (!(list.hnExists(house)))
		{
			list.addHouseNode(house);
			list.addNeighborNode(house,nei);
			cout << "Topology information successfully added." << endl << endl;
		}
		//IF HOUSE IS ALREADY ADDED ADD ITS NEIGBOR
		else
		{
			if (!(list.nnExists(house,nei)))
			{
				list.addNeighborNode(house,nei);
				cout << "Topology information successfully added." << endl << endl;
			}
			else
			{
				cout << "Redundant information! An entry with " << house << " and " << nei << " is already processed." << endl << endl;
				goon = false;
			}
		}
		//IF NEIGBOR DOES NOT EXIST IN HOUSES LIST ADD NEIGBOR TO HOUSES LIST
		if (!(list.hnExists(nei)) && goon)
		{
			list.addHouseNode(nei);
			list.addNeighborNode(nei,house);			
		}
		//IF NEIGBOR EXIST IN HOUSES LIST ADD HOUSE TO ITS NEIGBORS NEIGBOR LIST
		else
		{
			if (!(list.nnExists(nei,house)) && goon)
			{
				list.addNeighborNode(nei,house);
			}
		}
	}
	cout << "######## MAP ########" << endl << endl; 
	list.printAll(); //Displayed Map
	cout << endl;
	bool game = true;
	while (game)
	{
		int choice;
		cout << "Please select an option [1-2-3]." << endl << "1. Annexation! War for the iron throne continues..." << endl << "2. Tyrion must travel, do a path check for the famous imp." << endl << "3. Exit" << endl;
		cin >> choice;
		while (!(CheckChoice(choice))) // While choice is not one of 1-2-3 ask again and again
		{
			cout << "Invalid option please select from the menu." << endl << endl;
			cout << "Please select an option [1-2-3]." << endl << "1. Annexation! War for the iron throne continues..." << endl << "2. Tyrion must travel, do a path check for the famous imp." << endl << "3. Exit" << endl;
			cin >> choice;
		}
		//IF THE OPTION IS 1
		if (choice == 1)
		{
			string annexer, annexed;
			cout << "Please enter two houses first the annexer and the annexed. (ex: Tyrell Stark)." << endl;
			cin >> annexer >> annexed;

			bool goon = true;
			//CHECKING IF ANNEXER AND ANNEXED ARE NOT THE SAME
			if (annexed == annexer)
			{
				cout << "A House cannot conquer itself!" << endl << "Update failed." << endl << endl;
				goon = false;
			}
			//CHECKING IF ANNEXER AND ANNEXED ARE AT THE HOUSES LIST
			if (goon)
			{
				if (!(list.hnExists(annexer)))
				{
					cout << annexer << " does not exist!" << endl << "Update failed." << endl << endl;
					goon = false;
				}
			}
			if (goon)
			{
				if (!(list.hnExists(annexed)))
				{
					cout << annexed << " does not exist!" << endl << "Update failed." << endl << endl;
					goon = false;
				}
			}
			//CHECKING IF ANNEXER AND ANNEXED ARE NEIGHBORS
			if (goon)
			{
				if (!(list.nnExists(annexer,annexed)))
				{
					cout << "A house can only conquer a neighboring house! " << annexed << " is not a neighbor of " << annexer << "." << endl << "Update failed." << endl << endl;
					goon = false;
				}
			}
			//IF ABOVE IS FULFILLED THAN LET THE CONQUER BEGINS
			if (goon)
			{
				cout << annexer << " conquered " << annexed << "!" << endl;
				list.FirstAnnexSecond(annexer,annexed);
				cout << "######## MAP ########" << endl;
				list.printAll();
			}
		}
		//IF THE OPTION IS 2
		if (choice == 2)
		{
			cout << "Please enter a path. (ex: Tyrell Martell Tully)" << endl;
			string house, path, firststop, secondstop;
			cin.ignore();
			getline(cin,path);
			istringstream iss(path);
			bool flag1 = false;
			bool goon = true;
			
			iss >> firststop;

			while (iss >> house)
			{		
				bool samename = false;
				//STOP CHANGE
				if (flag1)
				{
					firststop = house;
					flag1 = false;
				}
				else
				{
					secondstop = house;
					flag1 = true;
				}
				//IF EXIST IN THE MAP
				if (!(list.hnExists(firststop)))
				{
					cout << firststop << " does not exist in the map." << endl;
					goon = false;
				}
				else if (!(list.hnExists(secondstop)) && goon)
				{
					cout << secondstop << " does not exist in the map." << endl;
					goon = false;					
				}
				//IF SAME
				if (goon)
				{
					if (firststop == secondstop)
					{
						cout << "You are already in " << firststop << endl;
						samename = true;
					}
				}
				//IF NEIGHBOR
				if (goon && !samename)
				{
					if (list.nnExists(firststop,secondstop))
					{
						if (flag1)
							cout << "Path found between " << firststop << " and " << secondstop << endl;
						else
							cout << "Path found between " << secondstop << " and " << firststop << endl;
					}
					else
					{
						if (flag1)
							cout << secondstop << " is not a neighbor of " << firststop << endl;
						else
							cout << firststop << " is not a neighbor of " << secondstop << endl;
						goon = false;
					}
				}

			}
			if (goon)
				cout << "Path search succeeded." << endl << endl;
			else
				cout << "Path search failed!" << endl << endl;
		}
		//IF THE OPTION IS 3
		if (choice == 3)
		{
			cout << "List deleted and program ended." << endl;
			list.deleteAll();
			game = false;
		}
	}

	return 0;
}