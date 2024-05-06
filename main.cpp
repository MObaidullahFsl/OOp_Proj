#include<iostream>
#include<vector>
//#include"Header.h"
#include<fstream>
using namespace std;
class page;
class user {
protected:
	string id;
	string name;
	vector<string> friends_list;
	vector<string> pages_followed;
	bool has_page;
	page homepage;
	vector<string> posts;
	static int total_users;

public:
	user(string ID = "", string Name = "", vector<string> Friends = {}, vector<string> Pages = {}, vector<string> Posts = {}) : id(ID), name(Name), friends_list(Friends), pages_followed(Pages), posts(Posts) {
		
		has_page = false;
	}
};
class page {
protected:
	string id;
	string name;
	vector<string> posts;
	static int total_pages;
public : 
	page(string ID = "", string Name = "", vector<string> Posts = {}) : id(ID), name(Name), posts(Posts) {
	
	}



};
int user ::total_users = 0;


 class Runner : public user, public page {
 public:
	 vector<user>users_list;
	 vector<page>pages_list;
	void readUsers() {
	//vector<user> users_list;
	fstream users_file("Users.txt");
	

	users_file >> user::total_users;
		for (int i = 0; i < total_users; i++) {
			string id, name, a; vector<string> friends,pages,posts; 
			users_file >> id;
			users_file >> name;
			users_file >> a;
			while (a != "-1") {
				friends.push_back(a);
				users_file >> a;
					}
				users_file >> a;
			while (a != "-1") {
				pages.push_back(a);
				users_file >> a;
						}
			users_file >> a;
			while (a != "-1") {
				posts.push_back(a);
				users_file >> a;
			}

				users_list.push_back(user(id, name, friends, pages, posts));
	
		}
	
	}
	void readPages() {
		fstream pages_file("Pages.txt");
		pages_file >> page::total_pages;
		for (int i = 0; i < total_pages; i++) {
		string id, name, a; vector<string> posts;
		pages_file >> id;
		pages_file >> name;
		pages_file >> a;
			while (a != "-1") {
				posts.push_back(a);
				pages_file >> a;
			}
			pages_list.push_back(page(id, name, posts));
		}
	}
	// halo
 };


int main() {
	Runner r;
	r.readUsers();
//hehehe
}