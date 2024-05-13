#pragma once
#include<iostream>
#include<vector>
#include"user.h"
#include"page.h"
#include"comment.h"
#include"post.h"
#include"MinorClasses.h"
#include<fstream>
#include<string>
#include<ctime>

using namespace std;
int post::total_posts = 0;
int user::total_users = 0;
int page::total_pages = 0;
int comment::total_comments = 0;
class Runner : public user, public page, public post, public comment {
public:
	Runner() {
		readUsers();
		readPages();
		readPosts();
		readComments();
	}
	vector<user*>users_list;
	vector<page*>pages_list;
	vector<post*>posts_list;
	vector<comment*>comments_list;
	vector<post*>home_posts;
	bool ended = false;
	void readUsers() {
		//vector<user> users_list;
		fstream users_file("C:\\Users\\HP\\Documents\\Repos\\oop_Proj\\Oop_project\\Final\\txt\\Users.txt");
		if (users_file.is_open()) {

			users_file >> user::total_users;
			for (int i = 0; i < total_users; i++) {
			string id, name, a; vector<string> friends, pages, posts; bool has_page;
			users_file >> id;
			users_file >> name;
			users_file >> a;
				while (a != ";") {
				friends.push_back(a);
				users_file >> a;
				}
			users_file >> a;
				while (a != ";") {
				pages.push_back(a);
				users_file >> a;
				}
			users_file >> a;
				while (a != ";") {
				posts.push_back(a);
				users_file >> a;
				}
			users_file >> has_page;

			users_list.push_back(new user(id, name, friends, pages, posts, has_page));

			}

			
		}
		else {
			cout << "FATAL: user file not found!!";
			exit(0);
		}

	}
	void readPages() {
		fstream pages_file("C:\\Users\\HP\\Documents\\Repos\\oop_Proj\\Oop_project\\Final\\txt\\Pages.txt");
		if (pages_file.is_open())
		{

			pages_file >> page::total_pages;
			for (int i = 0; i < total_pages; i++) {
				string id, name, a, owner; vector<string> posts; int followers;
				pages_file >> id;
				getline(pages_file, name, '1');
				//pages_file >> name;
				pages_file >> a;
				while (a != "-1") {
					posts.push_back(a);
					pages_file >> a;
				}
				pages_file >> owner; pages_file >> followers;

				pages_list.push_back(new page(id, name, posts, owner, followers));

			}




		}
		else
		{
			cout << "FATAL: pages file not found!!";
			exit(0);
		}
		
	}
	void readPosts() {
		fstream posts_file("C:\\Users\\HP\\Documents\\Repos\\oop_Proj\\Oop_project\\Final\\txt\\Posts.txt");
		if (posts_file.is_open())
		{
			
			posts_file >> post::total_posts;
			for (int i = 0; i < total_posts; i++) {

				string id, content, activ_content, a, owner;
				int date, month, likes, activ_number, hours, min, year;
				vector<string> comments;vector<string> likers;

				time_t now = time(0);
				struct tm ltm;
				localtime_s(&ltm, &now); 
				int Date = ltm.tm_mday; int Month = ltm.tm_mon + 1; int Year = ltm.tm_year + 1900;


				posts_file >> id;
				posts_file >> likes;
				posts_file >> year;
				if (year > Year ) {
					year = Year;
				}
				posts_file >> month;
				if (month > Month && year == Year) {
				month = Month;
				}
				posts_file >> date;
				if (date > Date && year == Year && month == Month) {
					date = Date;
				}
			
				//posts_file.ignore(256, '\n');
				getline(posts_file, content,';');
				posts_file >> activ_number;
				if (activ_number > 0) {
					
				getline(posts_file, activ_content, ';');
				}
				else {
					activ_number = 0;
					string b;
					posts_file >> b;
					activ_content = "";
				}
				//posts_file >> activ_content;
				//posts_file.ignore(256, '\n');
				posts_file >> owner;

				posts_file >> a;
				while (a != ";") {
					comments.push_back(a);
					posts_file >> a;
				}
				posts_file >> a;
				while (a != ";") {
					likers.push_back(a);
					posts_file >> a;
				}


				posts_list.push_back(new post(id, date, month, content, owner, likes, activ_number, activ_content, comments, year, likers));


			}




		}
		else {
			cout << "FATAL: posts file not found!!";
			exit(0);
		}

		
	}
	void readComments() {
		fstream comments_file("C:\\Users\\HP\\Documents\\Repos\\oop_Proj\\Oop_project\\Final\\txt\\Comments.txt");


		if (comments_file.is_open())
		{
			comments_file >> comment::total_comments;
			for (int i = 0; i < total_comments; i++) {
				string id, owner_post, owner_user, content;
				comments_file >> id;
				comments_file >> owner_post;
				comments_file >> owner_user;
				getline(comments_file, content, '\n');

				comments_list.push_back(new comment(id, owner_post, owner_user, content));
			}
		}
		else {
			cout << "FATAL: comments file not found!!";
			exit(0);
		}
		
	}

	~Runner();

	string getUserName(string id) {
		int count = 0;
		for (auto& i : users_list) {
			if (id == i->getId()) {
				count++;
				return i->getName();
			}
		}
		if (count == 0) {
			return "user not found err";
		}
	}
	string getPageName(string id) {
		int count = 0;
		for (auto& i : pages_list) {
			if (id == i->getId()) {
				count++;
				return i->getName();
			}
		}
		if (count == 0) {
			return "page not found err";
		}
	}

	int UserAuth() {

		cout << "Enter Your Username or Id:				-1 to exit \n";
		string id; cin >> id;
		int a = 0; int c = 0; bool condition = true;
		while (condition) {
			c = 0;
			for (auto& i : users_list) {
				a++;
				if (i->getId() == id || i->getName() == id) {

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
				return 0;
				break;
			case 1:
				cout << "Logged in Successfully" << endl;
				cout << "Welcome " << users_list[a - 1]->getName() << endl;

				return a;
				break;
			case -1:
				return -1;
			default:
				cout << "Unexpected Error!" << endl;
				return 0;
				break;
			}
		}
	}
	bool DateAuthHome(post *i) {
		time_t now = time(0);
		struct tm ltm;
		localtime_s(&ltm, &now); // Corrected usage of localtime_s
		int date = ltm.tm_mday; int month = ltm.tm_mon + 1; int year = ltm.tm_year + 1900;

		if (year == i->getYear() && month == i->getMonth() &&( (date == i->getDate()) || (date - 1 == i->getDate() ) ) ) {
			return true;
		}
		else
			return false;



	}

	void MakeHome(int userNo,user* u) {

		vector<string> friends = u->getFriends();
		vector<page> followed_pages;
		for (auto& j : pages_list) {
			for (auto& k : users_list[userNo]->getPages()) {
				if (j->getId() == k) {
					followed_pages.push_back(*j);
				}
			}

		}

		int count = 0;
		for (auto& i : posts_list) {
			count = 0;
			if (DateAuthHome(i)) {
				for (auto& j : friends) {

					if (j == i->getOwner()) {
						home_posts.push_back(i);
						count++;
						break;
					}

				}
				if (count == 0) {
					for (auto& j : followed_pages) {
						for (auto& k : j.getPosts()) {
							if (i->getId() == k) {
								home_posts.push_back(i);
							}
						}

					}
				}
			}
		}



	}
	string getPostUser(string id) {
		int count = 0;
		for (auto& i : posts_list) {
			if (id == i->getId()) {
				count++;
				return i->getOwner();
			}
		}
		if (count == 0) {
			return "user not found err";
		}
	}
	void getName(string id, user* u, bool& isPage, string& ownername, string& pagename) {
		// is this post of our friend?

		for (auto& i : u->getFriends()) {
			if (id == i) {
				// is our friend
				string name = getUserName(id);
				ownername = name ;
				isPage = false;
				return;

			}
		}

		// must be a page we follows post
		vector<page> followed_pages;
		for (auto& j : pages_list) {
			for (auto& k : u->getPages()) {
				if (j->getId() == k) {
					followed_pages.push_back(*j);
				}
			}

		}
		for (auto& j : followed_pages) {
			for (auto& k : j.getPosts()) {
				string ownerpost = getPostUser(k);
				if (id == ownerpost) {
					pagename = j.getName();
					ownername = getUserName(ownerpost);
					isPage = true;
					return;
				}

			}
		}


	}
	bool cinDiag() {
		if (cin.fail()) {
			cin.clear(); // Clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
			
		return false;
		}
		else {
			return true;
			// Process the input as needed
		}
	}

	void AddCommentToFile() {
		fstream comments_file("Comments.txt", ios::app);
		comments_file.seekp(0, ios::end);
		int size = comments_list.size();
		comments_file << comments_list[size - 1]->getId() << " " << comments_list[size - 1]->getOwnerPost() << " " << comments_list[size - 1]->getOwnerUser() << " " << comments_list[size - 1]->getContent() << endl;

	}
	void ComposePost(user* &u, int userno) {
		time_t now = time(0); struct tm ltm; localtime_s(&ltm, &now);
		int date = ltm.tm_mday; int month = ltm.tm_mon + 1; int year = ltm.tm_year + 1900;	string description;
		cout << "Enter description: \n";
		cin.ignore();
		getline(cin, description);
		vector<string> empty;
		posts_list.push_back(new post(("m" + to_string(posts_list.size() + 1)), date, month, description, u->getId(), 0, 0, "", empty, year,empty));
		vector<string> newposts = u->getPosts();
		newposts.push_back("m" + to_string(posts_list.size()));
		u->setposts(newposts);
	
		system("pause");
		system("cls");
		MainMenu(u, userno);

	}
	void PrintPostComments(string id) {

		int count = 0;
		for (auto& j : comments_list) {
			if (j->getOwnerPost() == id) {

				//get owner name
				string name = getUserName(j->getOwnerUser());
				count++;
				if (name != "") {
					cout << name << " commented :\t " << j->getContent() << "\n\n";
				}
			}
		}
		if (count == 0) {
			cout << "no comments to show" << endl;
		}
		/*for (int p = 0; p < 100; p++) { cout << "-"; }
		cout << endl;*/

	}
	void printHome(int userno, user* u) {
		system("cls");

		for (int p = 0; p < 100; p++) { cout << "="; }
		cout << endl; cout << "	\t\t\t\tHome Page \n";
		for (int p = 0; p < 100; p++) { cout << "="; }
		cout << endl; cout << "User: " << users_list[userno]->getName() << endl;
		cout << "\t\tThese are the latest Posts in your feed: \n\n";
		if (home_posts.size() == 0) {
			cout << "\n\tnothing to show here follow more pages or make more friends :)\n";
		}
		else {
			for (auto& i : home_posts) {
				bool isFromPage = false;
				activ* a = i->getActivity();
				string pagename, ownername; int c = 0;
				getName(i->getOwner(), u, isFromPage, ownername, pagename);

				if (!isFromPage) {
					for (int p = 0; p < 100; p++) { cout << "-"; }
					cout << endl;
					cout << "\n\nPost id: " << i->getId() << "\t\t\t\t Dated : " << i->getDate() << "/" << i->getMonth() << "/" << i->getYear() << "\n\nYour Friend " << ownername << " said: \t\t " << i->getContent() << "\t\tlikes: " << i->getLikes() << "\n ";
					
					switch (a->getNumber())
					{
					case 1:
						cout << ownername << " is feeling " << a->getContent() << " \n";
						break;
					case 2:
						cout << ownername << " is thinking about " << a->getContent() << " \n";
						break;
					case 3:
						cout << ownername << " is Making " << a->getContent() << " \n";
						break;
					case 4:
						cout << ownername << " is celebrating a " << a->getContent() << " \n";
						break;
					default:
						break;
					}
					

				}
				else {
					for (int p = 0; p < 100; p++) { cout << "-"; }
					cout << endl;
					cout << "\n\nPost id: " << i->getId() << "\t\t\t\t Dated : " << i->getDate() << "/" << i->getMonth() << "/" << i->getYear() << "\n\n posted by " << ownername << " on " << pagename << "  :  " << i->getContent() << "\t\tlikes: " << i->getLikes() << "\n ";
					switch (a->getNumber())
					{
					case 1:
						cout << ownername << " is feeling " << a->getContent() << " \n";
						break;
					case 2:
						cout << ownername << " is thinking about " << a->getContent() << " \n";
						break;
					case 3:
						cout << ownername << " is Making " << a->getContent() << " \n";
						break;
					case 4:
						cout << ownername << " is celebrating a " << a->getContent() << " \n";
						break;
					default:
						break;
					}
				}

				PrintPostComments(i->getId());


			}


		

		cout << "\nEnter 1 to like a post, 2 to add a comment, 3 to view likes, any other number to exit\n";
		int b; cin >> b; vector<string> likers; post* p = nullptr;
		bool works = cinDiag();
		while (!works) {
			cout << "Invalid input. Please enter a number." << endl;
			cin >> b;
			works = cinDiag();
		}
		if (b>0 && b<4) {
			cout << "Enter Post Id: \n"; string id; cin >> id;

			for (auto& i : posts_list) {
				if (i->getId() == id) {
					p = i;
					likers = p->getLikers();
					break;
				}
			}
		}
		else if (b>10) {
			cout << endl;
			cin.ignore();
		}
		 int count = 0; 
		switch (b)
		{
		case 1:
			count = 0;
			for (auto& i : p->getLikers()) {
				if (i == u->getId())
				{
					cout << "Already Liked by you!\n";
					count++;
					break;
				}
			}
			if (count == 0) {
				cout << "\t Liked!! \n\n";
				likers.push_back(u->getId());
				p->setLikers(likers);
				p->setlikes(p->getLikes() + 1);
				break;
			}
		case 2:
			addCommentPopUp(userno);
			break;
		case 3:
			viewLikers(p->getId());
			break;
		default:

			
			
			break;
		}
		}


		cin.ignore();
		system("cls");
		MainMenu(u, userno);
	}
	void addCommentPopUp(int userno) {
	 string choice; cin >> choice;
		if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y") {

			cout << "Enter comment: \n";
			cin.ignore();
			string content; getline(cin, content);
			cout << "Enter post id: \t";
			string id;
			getline(cin, id);
			comments_list.push_back(new comment("c" + to_string(comments_list.size() + 1), id, users_list[userno]->getId(), content));


			AddCommentToFile();
		}
		else {

		}
	}


	void viewLikers(string id) {
		cout << endl << endl;
		post* p=nullptr;
		for (auto& i : posts_list) {
			if (i->getId() == id) {
				p = i;
				break;
			}
		}
		cout << p->getId() << " Liked by: \n";
		vector<string>likers = p->getLikers();
			for (auto& i : likers) {
				string name = getUserName(i);
				cout << name<<endl;
			}
	}
	void ComposePage() {

	}
	void Signup(user * u, int userno) {


	}


	void PageView(string id, int userno, user* u) {
		system("cls");
		page* p = nullptr;
		int count = 0;
		for (auto& i : pages_list) {
			if (i->getId() == id) {
				p = i;
				count++;
				break;
			}
		}
		if (count ==1) {
			cout << "Id: " << p->getId() << "\t\tName: " << p->getName() << "\t\t" << p->getFollowers() << " Followers" << endl;
			cout << "\nPosts: \n\n";
			for (auto& i : p->getPosts()) {
				post* b = nullptr;
				for (auto& j : posts_list) {
					if (j->getId() == i)
					{
						b = j;
					}
				}
				for (int i = 0; i < 100; i++) { cout << "-"; };
				
				activ * a = b->getActivity();
				string name = getUserName(b->getId());
				cout << "\nPost id: " << b->getId() << "\t\t\t\t Dated : " << b->getDate() << "/" << b->getMonth() << "/" << b->getYear() << "\n\nPosted by " << name << " : \t\t " << b->getContent() << "\t\tlikes: " << b->getLikes() << "\n ";
				switch (a->getNumber())
				{
				case 1:
					cout << name << " is feeling " << a->getContent() << " \n";
					break;
				case 2:
					cout << name << " is thinking about " << a->getContent() << " \n";
					break;
				case 3:
					cout << name << " is Making " << a->getContent() << " \n";
					break;
				case 4:
					cout << name << " is celebrating a " << a->getContent() << " \n";
					break;
				default:
					break;
				}

				cout << "\n comments : \n";
				PrintPostComments(b->getId());

				cout << "\nEnter 1 to like the post, 2 to add a comment, 3 to view likes, anyother to exit\n";
				int c; cin >> c; int count = 0; vector<string> likers = b->getLikers();
				switch (c)
				{
				case 1:
					count = 0;
					for (auto& i : b->getLikers()) {
						if (i == u->getId())
						{
							cout << "Already Liked by you!\n";
							count++;
							break;
						}
					}
					if (count == 0) {
						cout << "\t Liked!! \n\n";
						likers.push_back(u->getId());
						b->setLikers(likers);
						b->setlikes(b->getLikes() + 1);
						break;
					}
				case 2:
					addCommentPopUp(userno);
					break;
				case 3:
					viewLikers(p->getId());
					break;
				default:

					break;
				}
				
			}
		}
		else {
			cout << "page not found" << endl;
		}
		cout << "\n\n";
		system("pause");
		MainMenu(u, userno);
	}
	void viewPost (user* u,int userno, string postid) {
		post* p=nullptr;
		int count = 0;
		for (auto& i : posts_list) {
			if (i->getId() == postid) {
				p = i;
				count++;
			break;
			}
		}
		if (count == 1) {
		activ* a = p->getActivity();
		string name = getUserName(p->getOwner());
		for (int i = 0; i < 100; i++) { cout << "-"; };
		cout << "\nPost id: " << p->getId() << "\t\t\t\t Dated : " << p->getDate() << "/" << p->getMonth() << "/" << p->getYear() << "\n\nPosted by " << name << " : \t\t " << p->getContent() << "\t\tlikes: " << p->getLikes() << "\n ";
		switch (a->getNumber())
		{
		case 1:
			cout << name << " is feeling " << a->getContent() << " \n";
				break;
		case 2:
			cout << name << " is thinking about " << a->getContent() << " \n";
			break;
		case 3:
			cout << name << " is Making " << a->getContent() << " \n";
			break;
		case 4:
			cout << name << " is celebrating a " << a->getContent() << " \n";
			break;
		default:
			break;
		}
	
		cout<<"\n comments : \n";
	PrintPostComments(p->getId());

		cout<<"\nEnter 1 to like the post, 2 to add a comment, 3 to view likes, anyother to exit\n";
		int b; cin >> b; int count = 0; vector<string> likers = p->getLikers();
		switch (b)
		{
		case 1:
			count = 0;
			for (auto& i : p->getLikers()) {
				if (i==u->getId())
				{
					cout << "Already Liked by you!\n";
					count++;
					break;
				}
			}
			if (count ==0) {
				cout << "\t Liked!! \n\n";
				likers.push_back(u->getId());
				p->setLikers(likers);
			p->setlikes(p->getLikes() + 1);
			break;
			}
		case 2:
			addCommentPopUp(userno);
			break;
		case 3:
			viewLikers(p->getId());
			break;
		default:

			break;
		}

		}else
			cout<<	"post not found!!"<<"\n\n";
system("pause");
		MainMenu(u, userno);
		
	}


	void Explore(int userno, user* u) {
		system("cls");
		cout << "Explore Other Pages!!\n\n";
		for (auto& i : pages_list) {
			cout << "Id: " << i->getId() << "\t\tName: " << i->getName() << "\t\t" << i->getFollowers() << " Followers" << endl;
		}
		cout << "Enter page id to visit or -1 to exit: \n"; string id; cin >> id;
		if (id == "-1")
		{
			MainMenu(u, userno);
		}
		else
			PageView(id, userno, u);
		system("cls");
		MainMenu(u, userno);

	}
	void shareMemories( user* & u, int userno) {

		// getting post 
		//post* p=nullptr;
		//for (auto& i : posts_list) { if (i.getId() == postid) {p = &i;} }
		int count = 0;
		for (auto& i : posts_list) {
			time_t now = time(0); struct tm ltm; localtime_s(&ltm, &now); 
			
			int date = ltm.tm_mday; int month = ltm.tm_mon + 1; int year = ltm.tm_year + 1900;

			if (i->getDate() == date && i->getMonth() == month && i->getYear() != year && i->getOwner() == u->getId()) {
				// memory found
				cout << "Memory found! \n\n On this day "<<(year-i->getYear())<<" years ago \n you posted: \n\t\t"<<i->getContent();
				PrintPostComments(i->getId());
				
				cout << "Do u want to Share this memory?"<<endl; 
			
					string choice; cin >> choice;
					
					if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y")
					{	string description;
						cout << "Enter description: \n";
						cin.ignore();
						getline(cin,description); 
						vector<string> empty;
						string content = "On this day " + to_string(year - i->getYear()) + " years ago " + u->getId() + " posted: \n\t\t" + i->getContent() + "\n\n" + description;
						posts_list.push_back(new post( ("m" + to_string(posts_list.size() + 1) ), date,month,content,u->getId(),0,0,"",empty, year,empty));
						vector<string> newposts = u->getPosts();
						newposts.push_back("m" + to_string(posts_list.size()));
						u->setposts(newposts);
					}
					count++;
					
			}
			
		}
		if (count == 0) {
			cout << "No Memories Found!\n"<<endl;
		}
		    cin.ignore();
			system("pause");
			system("cls");
			MainMenu(u, userno);
	}
	void ViewProfile(int userno, user* u) {

		for (int i = 0; i < 100; i++) { cout << "="; }
		cout << "\n";
		cout << "User: " << users_list[userno]->getName() << endl;
		cout << "Id: " << users_list[userno]->getId() << endl << endl;
		cout << "Friends list: \n";
		for (auto& i : users_list[userno]->getFriends()) { cout << getUserName(i) << "\n"; }
		cout << "\nFollowed Pages list: \n";
		for (auto& i : users_list[userno]->getPages()) { cout << getPageName(i) << "\n\n"; }
		if (u->getHasPage()) {
			cout << "Your are the Admin of Following Pages: \n"; 
			for(auto& i : pages_list)
			{
				if (i->getOwner() == u->getId()) {
				cout<<i->getName()<<"\n";
				}
			}
		}
		else {
			cout<<"You do not have any pages\nMake new page?\n";
			string choice; cin >> choice;
			/*if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y") {
			{

				}
			else
			{
			}*/
		}
		cout << "\n\t\tDo u want to see ur posts?\n";
		string choice; cin >> choice;
		if (choice == "yes" || choice == "y" || choice == "YES" || choice == "Y")
		{
			viewTimeline(userno, u);
		}
		else {
			system("pause");
			system("cls");
			MainMenu(u, userno);
		}
	}
	void viewTimeline(int userno, user* u) {
		system("cls");
		cout << "This is your Posts TimeLine \n\n";
		int count = 0;
		for (auto& i : posts_list) {
			for (auto& j : u->getPosts()) {
				if (i->getId() == j) {
					cout << "You posted: (" << i->getDate() << "/" << i->getMonth() << "/" << i->getYear() << ")\t" << i->getContent() << "\t\tLikes: " << i->getLikes() << "\n\nComments:\n";
					PrintPostComments(i->getId());
						count++;
				}
			}

		}
		cout << "\n\t\t\tYou Have No Posts!!\n";
		system("pause");
		system("cls");
		cin.ignore();
		MainMenu(u, userno);
	}


	void MainMenu(user* u, int userN0) {
		
		system("cls");
		cout << "\t\t\t\t****MAIN MENU****\n"; for (int i = 0; i < 100; i++) { cout << "="; }; cout << "\n\t\tSelect an option: \n 1. Go Home \n 2. Explore \n 3. View Profile \n 4. Share Memories  \n 5. View a Page \n 6. View TimeLine \n 7.Compose Post \n 8. View a Post \n 9. LogOut\n any another to exit\n";
		//cin.ignore();
		int a; cin >> a;
		string id;
		switch (a)
		{
		case 1:
			printHome(userN0, u);
			break;
		case 2:
			Explore(userN0, u);
			break;
		case 3:
			ViewProfile(userN0, u);
		case 4:
			shareMemories( u, userN0);
			break;
		case 5:
			cout << "Enter page id: \n";
			cin >> id;
			PageView(id, userN0, u);
			break;
		case 6:
			viewTimeline(userN0, u);
		case 7:
			ComposePost(u, userN0);
			break;
		case 9:
			StartApp();
			break;
		case 8:
			cout << "Enter post id: \n";
			cin >> id;
			viewPost(u, userN0,id);
				break;
		default:
			exit(0);
		}

	}
	void StartApp() {
		system("cls");
		cout << "================================================================================================================";
		cout << "	\t\t\t\t\tWELCOME TO OOP PROJECT" << endl;
		cout << "================================================================================================================\n";
		int userN0 = UserAuth();
		if (userN0 == -1) {
			cout << "Exiting!";
		}
		else if (userN0 == 0) {
			userN0 = UserAuth();
		}

		// Found user
		user* u = users_list[userN0 - 1];
		userN0 = userN0 - 1;
		system("pause");
		MakeHome(userN0,u);
		MainMenu(u, userN0);


	}
	// halo

};
Runner::~Runner() {
	if (ended) {
		if (!users_list.empty()) {
			for (auto& d:users_list) {
				delete d;
			}
			users_list.clear();
		}
		if (!pages_list.empty()) {
			for (auto& d : pages_list) {
				delete d;
			}
			pages_list.clear();
		}
		if (!posts_list.empty()) {
			for (auto& d : posts_list) {
				delete d;
			}
			posts_list.clear();
		}
		if (!comments_list.empty()) {
			for (auto& d : comments_list) {
				delete d;
			}
			comments_list.clear();
		}
	}
}
