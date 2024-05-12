#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;
class page {
protected:
	string id;
	string name;
	string owner;
	vector<string> posts;
	int followers;
	static int total_pages;
public:
	page(string ID = "", string Name = "", vector<string> Posts = {}, string Owner = "", int Followers = 0) : id(ID), name(Name), posts(Posts), owner(Owner), followers(Followers) {

	}
	vector<string> getPosts() { return posts; }
	string getId() { return id; }
	string getName() { return name; }
	string getOwner() { return owner; }
	int getFollowers() { return followers; }
};
