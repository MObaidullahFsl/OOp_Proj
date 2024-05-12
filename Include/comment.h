#pragma once


#include <iostream>
#include <vector>
#include <string>
#include "page.h"
using namespace std;

class comment {
protected:
	string id, owner_post, owner_user, content;
	static int total_comments;
public:
	comment(string ID = "", string Owner_Post = "", string Owner_User = "", string Content = "") : id(ID), owner_post(Owner_Post), owner_user(Owner_User), content(Content) {}
	~comment() {};
	string getId() { return id; }
	string getOwnerPost() { return owner_post; }
	string getOwnerUser() { return owner_user; }
	string getContent() { return content; }
};