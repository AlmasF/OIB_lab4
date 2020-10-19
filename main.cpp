#include <bits/stdc++.h>
#include <ctime>
using namespace std;

string choice = "";
vector<string> usernames(100);
vector<string> passwords(100);
vector<string> questions(100);
vector<string> answers(100);
vector<int> counts(100);
vector<time_t> dates(100);
int db_it = 0;
bool cancel = 1;

void sign_up();
void sign_in();
void recover(int id);
int search(string str);
int check(string str);

	
int main(){
	while(cancel){
		printf("\nHello!\nEnter \"U\" to sign up\nEnter \"I\" to sign_in\n");
		cin >> choice;
		int ch_num = check(choice);
		
		switch(ch_num){
			case 1:
				sign_up();
				break;
			case 2:
				sign_in();
				break;
			default:
				printf("Either I or U!");
				break;	
		}
		
		printf("\n------------------------------------------------------\nEnter 1 to continue program: ");
		cin >> cancel;
		choice = "";
	}
	return 0;
}

void recover(int id){
	printf("Answer the question to recover\n");
	cout << questions[id] << "\n";
	printf("Answer: ");
	string ans = "";
	cin >> ans;
	if(answers[id] == ans) {
		counts[id] = 0;
		printf("User is unblocked!");
		dates[id] = time(NULL)/60;
	}
	else{
		printf("Wrong! Try next time!");
	}
}

int check(string str){
	if(str == "U" || str == "u") return 1;
	if(str == "I" || str == "i") return 2;
	return 0;
}

void sign_in(){
	string username = "", password = "";
	
	printf("Username: ");
	cin >> username;
	int id = search(username);
	if(id != -1){
		if(counts[id] >= 3){
			printf("The user is blocked! Want to recover? (Enter y to recover): ");
			string rec = "";
			cin >> rec;
			if(rec == "y" || rec == "Y") recover(id);
		}
		else{
			
			printf("Password: ");
			cin >> password;
			if(passwords[id] == password) {
				printf("Welcome!");
				counts[id] = 0;
				if(time(NULL)/60 - dates[id] >= 1){
					printf("Your password is too old! (1 minute old...)\nNeed to change\nEnter new password: ");
					string pass = "";
					cin >> pass;
					passwords[id] = pass;
					printf("Password have changed successfully!");
					dates[id] = time(NULL)/60;
				} 
			}
			else{
				printf("Wrong password");
				counts[id]++;
			}
		}
	}
	else{
		printf("No such a username");
	}
}

int search(string str){
	for(int i = 0; i < 100; i++){
		if(usernames[i] == str) return i;
	}
	return -1;
}

void sign_up(){
	string username = "", password = "", question = "", answer = "";
	printf("Enter username: ");
	cin >> username;
	printf("Enter password: ");
	cin >> password;
	printf("Enter secret question: ");
	cin >> question;
	printf("Enter answer to question: ");
	cin >> answer;
	
	usernames[db_it] = username;
	passwords[db_it] = password;
	questions[db_it] = question;
	answers[db_it] = answer;
	dates[db_it] = time(NULL) / 60;
	db_it++;
}

