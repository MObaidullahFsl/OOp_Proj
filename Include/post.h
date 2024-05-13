#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "page.h"
#include "MinorClasses.h";
using namespace std;

class post {
protected:
	string id;
	kronos time_added;
	string content;
	activ* activity;
	string owner; // user needed
	int likes;
	static int total_posts;
	vector<string> comments;
	vector<string> likers;

public:
	post(string ID = "", int Date = 0, int Month = 0, string Content = "", string Owner = "", int Likes = 0, int activnumber = 0, string activcontent = "", vector<string> Comments = {}, int year = 0, vector<string> Likers = {}) : id(ID), content(Content), owner(Owner), likes(Likes), comments(Comments),	likers(Likers) {
		activity = new activ(activcontent, activnumber);
		time_added = kronos(year, Month, Date);
	}
	~post() {};

	string getOwner() { return owner; }
	string getId() { return id; }
	int getDate() { return time_added.getDate(); }
	int getMonth() { return time_added.getMonth(); }
	int getYear() { return time_added.getYear(); }
	string getContent() { return content; }
	int getLikes() { return likes; }
	vector<string> getComments() { return comments; }
	activ* getActivity() { return activity; }
	void setlikes(int x) { likes = x; }
	vector<string> getLikers() { return likers; }
	void setLikers(vector<string> x) { likers = x; }


};
