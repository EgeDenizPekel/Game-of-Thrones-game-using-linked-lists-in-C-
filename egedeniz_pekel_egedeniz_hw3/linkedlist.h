#ifndef linkedlist_h
#define linkedlist_h

using namespace std;

struct neighborNode{
	string neighborName;
	neighborNode *next;
};

struct houseNode{
	string houseName;
	neighborNode *neighborListHead;
	houseNode *next;
};

class linkedlist
{
public:
	linkedlist();
	void addHouseNode(string hname);
	void addNeighborNode(string hname, string nname);
	void printAll();
	bool hnExists(string hname);
	bool nnExists(string hname, string nname);
	void deleteAll();
	void FirstAnnexSecond(string annexer, string annexed);
private:
	houseNode *head;
};

#endif