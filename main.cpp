#include<iostream>
#include<vector>
//#include"Header.h"
#include<fstream>
#include<string>
using namespace std;
class page;
class activ;
class post;
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
class activ {
	protected:
		string content;
		int number;
public:
	activ(string Content = "", int Number = 0) : content(Content), number(Number) {}
};
class post {
protected:
	string id;
	int date, month;
	string content;
	activ *activity;
	string owner; // user needed
	int likes;
	static int total_posts;
	vector<string> comments;

public:
	post(string ID = "", int Date = 0, int Month = 0, string Content = "", string Owner = "", int Likes = 0, int activnumber=0, string activcontent = "",vector<string> Comments = {} ) : id(ID), date(Date), month(Month), content(Content), owner(Owner), likes(Likes), comments(Comments) {
		activity = new activ(activcontent, activnumber);
	}
	~post() {};


	



};
int post::total_posts = 0;
int user ::total_users = 0;
int page ::total_pages = 0;

 class Runner : public user, public page, public post {
 public:
	 vector<user>users_list;
	 vector<page>pages_list;
	 vector<post>posts_list;
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
		getline(pages_file,name,'1');
		//pages_file >> name;
		pages_file >> a;
			while (a != "-1") {
				posts.push_back(a);
				pages_file >> a;
			}
			pages_list.push_back(page(id, name, posts));
			
		}
	}
	void readPosts() {
		fstream posts_file("Posts.txt");
		posts_file >> post::total_posts;
		for (int i = 0; i < total_posts; i++) {
			string id, content,activ_content,a,owner;
			int date, month, likes, activ_number;
			vector<string> comments;

			posts_file>>id;
			posts_file >> likes;
			posts_file >> date;
			posts_file >> month;
			//posts_file.ignore(256, '\n');
			getline(posts_file, content, '1');
			getline(posts_file, activ_content,'1');
			if (activ_content != " ") {
				posts_file >> activ_number;
			}else
				activ_number = 0;
			//posts_file >> activ_content;
			//posts_file.ignore(256, '\n');
			posts_file >> owner;
			
			posts_file >> a;
			while (a != "-1") {
				comments.push_back(a);
				posts_file >> a;
			}

			posts_list.push_back(post(id, date, month, content, owner, likes, activ_number, activ_content, comments));


		}
	}
	// halo
	void a() {
	cout<<"halo";
	};
 };


int main() {
	Runner r;
	r.readUsers();
	r.readPages();
	r.readPosts();
//hehehe
}