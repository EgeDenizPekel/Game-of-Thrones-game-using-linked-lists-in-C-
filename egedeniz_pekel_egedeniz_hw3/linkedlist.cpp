#include <string>
#include "linkedlist.h"
#include <iostream>

using namespace std;

linkedlist::linkedlist()
{
	head = NULL;
}

void linkedlist::addHouseNode(string hname)
{
	houseNode *ptr = head;
	houseNode *temp = head;
	if (ptr == NULL)
	{
		ptr = new houseNode;
		ptr->houseName = hname;
		ptr->next = NULL;
		ptr->neighborListHead = NULL;
		head = ptr;
	}
	else 
	{
		while (ptr != NULL)
		{
			if (ptr->next == NULL)
			{
				temp = ptr;
				ptr = ptr->next;
				ptr = new houseNode;
				ptr->houseName = hname;
				ptr->next = NULL;
				ptr->neighborListHead = NULL;
				temp->next = ptr;
			}
			ptr = ptr->next;
		}
	}
}

void linkedlist::addNeighborNode(string hname,string nname)
{
	houseNode *ptr = head;
	neighborNode *n = NULL;
	neighborNode *temp = NULL;
	while (ptr != NULL)
	{
		if (ptr->houseName == hname)
		{
			n = ptr->neighborListHead;
			if (n == NULL)
			{
				n = new neighborNode;
				ptr->neighborListHead = n;
				n->neighborName = nname;
				n->next = NULL;
			}
			else
			{
				while (n != NULL)
				{
					if (n->next == NULL)
					{
						temp = n;
						n = n->next;
						n = new neighborNode;
						n->neighborName = nname;
						n->next = NULL;
						temp->next = n;
					}
					n = n->next;
				}
			}
		}
		ptr = ptr->next;
	}
}

void linkedlist::printAll()
{
	houseNode *ptr = head;
	neighborNode *n;
	while (ptr != NULL)
	{
		cout << ptr->houseName << ": ";
		n = ptr->neighborListHead;
		while (n != NULL)
		{
			cout << n->neighborName << ", ";
			n = n->next;
		}
		cout << endl;
		ptr = ptr->next;
	}
	cout << endl;
}

bool linkedlist::hnExists(string hname)
{
	houseNode *ptr = head;
	while (ptr != NULL)
	{
		if (ptr->houseName == hname)
			return true;
		ptr = ptr->next;
	}
	return false;
}

bool linkedlist::nnExists(string hname, string nname)
{
	houseNode *ptr = head;
	neighborNode *n;
	while (ptr != NULL)
	{
		if (ptr->houseName == hname)
		{
			n = ptr->neighborListHead;
			while (n != NULL)
			{
				if (n->neighborName == nname)
					return true;
				n = n->next;
			}
		}
		ptr = ptr->next;
	}
	return false;
}

void linkedlist::deleteAll()
{
	houseNode *ptr = head;
	houseNode *p = head;
	houseNode *z = head;
	neighborNode *temp = NULL;
	neighborNode *n = NULL;
	neighborNode *x = NULL;
	while (ptr != NULL)
	{
		p = ptr->next;
		temp = ptr->neighborListHead;
		while (temp != NULL)
		{
			n = temp->next;
			delete(temp);
			temp = n;
		}
		delete(ptr);
		ptr = p;
	}
	head = NULL;
}

void linkedlist::FirstAnnexSecond(string annexer, string annexed)
{
	houseNode *ptr = head;
	houseNode *p = head;
	houseNode *z = head;
	neighborNode *temp = NULL;
	neighborNode *n = NULL;
	neighborNode *x = NULL;
	//Delete annexed in annexers neighbor list
	while (ptr != NULL)
	{
		if (ptr->houseName == annexer)
		{
			temp = ptr->neighborListHead;
			while (temp != NULL)
			{
				if (temp->neighborName == annexed)
				{
					if (ptr->neighborListHead->neighborName == annexed) // IF IT IS THE FIRST NEIGHBOR IN THE LIST
					{
						n = temp->next;
						delete(temp);
						ptr->neighborListHead = n;
						break;
					}
					else //IT IS NOT THE FIRST NEIGHBOR IN THE LIST
					{
						x = temp->next;
						delete(temp);
						n->next = x;
						break;
					}
				}
				n = temp;
				temp = temp->next;
			}
		}
		ptr = ptr->next;
	}
	//Delete annexed houses houses and neighbors list
	ptr = head;
	temp = NULL;
	n = NULL;
	x = NULL;
	p = head;
	z = head;
	int count = 0;
	while (ptr != NULL)
	{
		bool housedelete = false;
		if (ptr->houseName == annexed)
		{
			temp = ptr->neighborListHead;
			while (temp != NULL)
			{
				n = temp->next;
				delete(temp);
				temp = n;
			}
			housedelete = true;
		}
		if (housedelete)
		{
			z = ptr->next;
			delete(ptr);
			p->next = z;
			if (count == 0)
				head = z;
			break;
		}
		count++;
		p = ptr;
		ptr = ptr->next;
	}
	//IF A HOUSE HAS A NEIGHBOR AS ANNEXED AND ANNEXER WAS NOT IN A NEIGHBORSHIP WITH HIM ADD THAT HOUSE TO ANNEXERS NEIGHBOR LIST
	ptr = head;
	p = head;
	temp = NULL;
	n = NULL;
	x = NULL;
	z = head;
	while (ptr != NULL)
	{
		if (nnExists(ptr->houseName,annexed) && ptr->houseName != annexer && !(nnExists(annexer,ptr->houseName)))
		{
			addNeighborNode(annexer,ptr->houseName);
		}
		ptr = ptr->next;
	}
	//Change every neighbor name that is annexed name with annexers name if it is not already in there
	ptr = head;
	p = head;
	temp = NULL;
	n = NULL;
	x = NULL;
	z = head;
	while (ptr != NULL)
	{
		bool as = false;
		temp = ptr->neighborListHead;
		while (temp != NULL) //CHECK IF ANNEXER NAME IS IN HOUSE NEIGHBORS LIST
		{
			if (temp->neighborName == annexer)
				as = true;
			temp = temp->next;
		}
		if (!(as)) //CHANGE ANNEXED NAME WITH THE ANNEXERS IF ANNEXERS NAME DOES NOT EXIST BEFORE
		{
			temp = ptr->neighborListHead;
			while (temp != NULL)
			{
				if (temp->neighborName == annexed)
					temp->neighborName = annexer;
				temp = temp->next;
			}
		}
		else //IF ANNEXERS NAME EXISTS BEFORE CHANGING THAN DELETE ANNEXED NAME IN NEIGHBORS LIST
		{
			temp = ptr->neighborListHead;
			count = 0;
			while (temp != NULL)
			{
				if (temp->neighborName == annexed)
				{
					if (count == 0)
					{
						x = temp->next;
						ptr->neighborListHead = x;
						delete(temp);
						break;
					}
					else
					{
						x = temp->next;
						n->next = x;
						delete(temp);
						break;
					}
				}
				count++;
				n = temp;
				temp = temp->next;
			}
		}
		ptr = ptr->next;
	}
}