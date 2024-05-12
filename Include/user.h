#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "page.h"
using namespace std;
class user {
protected:
	string id;
	string name;
	vector<string> friends_list;
	vector<string> pages_followed; // liked
	bool has_page;
	page* homepage;
	vector<string> posts;
	static int total_users;

public:
	user(string ID = "", string Name = "", vector<string> Friends = {}, vector<string> Pages = {}, vector<string> Posts = {}, bool Has_page = false) : id(ID), name(Name), friends_list(Friends), pages_followed(Pages), posts(Posts), has_page(Has_page) {


	}

	string getName() { return name; }
	vector<string> getPosts() { return posts; }
	vector<string> getPages() { return pages_followed; }
	vector<string> getFriends() { return friends_list; }
	string getId() { return id; }
	bool getHasPage() { return has_page; }
	void setposts(vector<string>Posts) { posts = Posts; }

};