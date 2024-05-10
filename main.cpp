#include<iostream>
#include<vector>
//#include"Header.h"
#include<fstream>
#include<string>
#include<ctime>
using namespace std;
class page;
class activ;
class post;
class comment;
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

		string getName() { return name; }
		vector<string> getPosts() { return posts; }
		vector<string> getPages() { return pages_followed; }
		vector<string> getFriends() { return friends_list; }
		string getId() { return id; }
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

	string getContent() { return content; }
	int getNumber() { return number; }
};
class kronos {
protected:
	//string timeString;
	int month, date,year, hour, min;

public:
	kronos(struct tm* localTime) {

		date = localTime->tm_mday;
		month = localTime->tm_mon + 1; // tm_mon is 0-indexed, so add 1
		year = localTime->tm_year + 1900; // tm_year is years since 1900
		hour = localTime->tm_hour;
		min = localTime->tm_min;
		/*time_t now = time(0);
		char buffer[30] = {};
		
	timeString = ctime_s(buffer, 30, &now);
	timeString = buffer;*/

	}
	kronos(int Year = 0, int Month = 0, int Date = 0, int Hour = 0, int Min = 0): year(Year), month(Month), date(Date), hour(Hour), min(Min) {

	}
	int getDate() { return date; }
	int getMonth() { return month; }
	int getYear() { return year; }
	//void displayTime() const {
	//	std::cout << "Current date and time: " << timeString;
	//}
};
class post {
protected:
	string id;
	kronos time_added;
	string content;
	activ *activity;
	string owner; // user needed
	int likes;
	static int total_posts;
	vector<string> comments;

public:
	post(string ID = "", int Date = 0, int Month = 0, string Content = "", string Owner = "", int Likes = 0, int activnumber=0, string activcontent = "",vector<string> Comments = {} , int hours = 0, int min = 0, int year =0) : id(ID), content(Content), owner(Owner), likes(Likes), comments(Comments) {
		activity = new activ(activcontent, activnumber);
		time_added = kronos(year,Month, Date, hours, min);
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
	



};
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
int post::total_posts = 0;
int user ::total_users = 0;
int page ::total_pages = 0;
int comment ::total_comments = 0;
 class Runner : public user, public page, public post ,public comment {
 public:
	 vector<user>users_list;
	 vector<page>pages_list;
	 vector<post>posts_list;
	 vector<comment>comments_list;
	 vector<post>home_posts;
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
			string id, content, activ_content, a, owner;
			int date, month, likes, activ_number, hours, min,year;
			vector<string> comments;

			posts_file>>id;
			posts_file >> likes;
			posts_file >> year;
			posts_file >> month;
			posts_file >> date;
			posts_file >> hours;
			posts_file >> min;
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

			posts_list.push_back(post(id, date, month, content, owner, likes, activ_number, activ_content, comments, hours, min, year));


		}
	}
	void readComments() {
		fstream comments_file("Comments.txt");
		comments_file >> comment::total_comments;
		for (int i = 0; i < total_comments; i++) {
			string id, owner_post, owner_user, content;
			comments_file >> id;
			comments_file >> owner_post;
			comments_file >> owner_user;
			getline(comments_file, content, '\n');

			comments_list.push_back(comment(id, owner_post, owner_user, content));
		}
	}

	int UserAuth() {

		cout << "Enter Your Username or Id:				-1 to exit \n";
		string id; cin >> id;
		int a=0;int c = 0;
		while (true) {

			for (int i = 0; i < total_users; i++) {
				if (users_list[i].getId() == id || users_list[i].getName() == id) {
					a = i;
					c++;
					break;
				}
			}

			if (id == "-1") {
				c = -1;
			}
			switch (c) {
			case 0:
				cout << "User Not Found" << endl;
				UserAuth();
				break;
			case 1:
				cout << "Logged in Successfully" << endl;
				cout << "Welcome " << users_list[a].getName() << endl;
				return a;
				break;
			case -1:
				return -1;
			default:
				cout << "Unexpected Error!" << endl;
				UserAuth();
				break;
			}
		}
	}
	bool DateAuthHome(post i) {
		time_t now = time(0);
		struct tm ltm;
		localtime_s(&ltm, &now); // Corrected usage of localtime_s
		int date = ltm.tm_mday;int month=ltm.tm_mon + 1; int year=ltm.tm_year + 1900;
		
		if (year == i.getYear() && month == i.getMonth() && (date == i.getDate()) || (date == i.getDate() - 1)) {
			return true;
		}
		else 
			return false;



	}
	void MakeHome(int userNo) {
		vector<string> friends = users_list[userNo].getFriends();
		vector<string> pages = users_list[userNo].getPages();
		
		for (auto& i : posts_list) {
			if (DateAuthHome(i)) {
				for (auto& j : friends) {

					if (j == i.getOwner() ) {
						home_posts.push_back(i);
					}
				}
				for (auto& j : pages) {

					if (j == i.getOwner() ) {
						home_posts.push_back(i);
					}

				}

			}
		}



	}
	void printHome(int userno) {
		cout << "================================================================================================================\n";
		cout<<"	\t\t\t\tHome Page \n";
		cout << "================================================================================================================\n";
		cout << "User: "<<users_list[userno].getName() << endl;
		cout << "These are the latest Posts in your feed: \n";
		if (home_posts.size()==0) {
			cout << "\n\tnothing in your feed follow more pages\n";
		}
		else {
			for (auto& i : home_posts) {
				activ* a = i.getActivity();
				string name;
				for (auto & j:users_list) {
					
					if(i.getOwner()==j.getId()){
					
					 name = j.getName();
					break;
					}
				
				}
				cout << "\n\n" << name << " said: \n " << i.getContent() << "			likes: " << i.getLikes() << "\n " << a->getContent() << " " << a->getNumber() << " \n\n comments : ";

			}

		}
	
	}
	void MainMenu() {
		cout << "================================================================================================================";
		cout<<"	\t\t\t\tWELCOME TO OOP PROJECT"<<endl;
		cout << "================================================================================================================\n";
		int userN0=UserAuth();
		if (userN0 == -1) {
			cout << "Exiting!"; 
		}
		else {
		// Found user
				user u = users_list[userN0];

				MakeHome(userN0);
				cout<<"Select an option: \n 1. Go Home \n 2. Explore \n 3. View Profile \n 4. Share Memories  \n 5. View Followed Pages \n 6. View Friends \n any another to exit\n";

				int a; cin >> a;
				switch (a)
				{
				case 1:
					printHome(userN0);
					break;

				default:
					exit;
				}
				





		}
	}
	// halo
	
 };


int main() {
	Runner r;
	
	r.readUsers();
	r.readPages();
	r.readPosts();
	r.readComments();
	r.MainMenu();
//hehehe
}