#pragma once
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define TRUE 1
#define FALSE 0



void Color_green(HANDLE hConsole);

void Color_normal(HANDLE hConsole, WORD saved_attributes);

char* Scan();			/*input from user*/



int Size(char* string);					/*return size of a string*/

char* String_copy(char* source);		/*build a string and copy the source in it*/

int	Similarity(char* string1, char* string2); /*check if two string are the same*/

void Print_time(time_t now);		/*printint time*/

int Uniqueness_user_name(user* head, char* user_name);			/*check if inputed user name is unique or not*/

int Password_format(char* password);							/*check if password length is bigger than 6*/

int Uniqueness_phone_number(user* head, char* phone_number);	/*check if inputed phone number is unique*/

int Uniqueness_group_name(group* head, char* name);				/*check if inputed group name is unique or not*/

int Is_number(char* string);				/*check if string is all number*/

int Check_phone_number_format(char* phone_number);		/*check if phone number format is correct*/

user* Find_user(char* user_name, user* head);			/*check if user name exists*/

group* Find_group(char* group_name, group* head_group);					/*find a group by its name*/

user* Dummy();											/*make first node of the user linked list*/

message* Dummy_mess();						/*make first node of message link list*/

members* Dummy_members();					/*making first node of members linked list*/

group* Dummy_group();							/*making first node of group linked list*/

int Number_of_part(char* string);				/*counting number of parts in command line*/

char* Split_by_space(char* string, int part_number);	/*find different part in a string that splited by space*/

void Change_user_name(user* head, user* selected_user);			/*changin user name*/

void change_password(user* head, user* selected_user);		/*this function is for changing password*/

user* Last_user(user* dummy);	/*find the last created account*/

message* Last_receiver_message(message* head);		 /*find last message that has the same receiver as head */

group* Last_group(group* head);			/*finding last group of link list*/

user* New_user(user* head);				/*Creating new user in end of linked list*/

message* new_message(message* head);			/*creating new message*/

group*	New_group(group* head,user* admin);					/*creating new group*/

members* New_members(members* head, user* member);			/*creating new member*/

members* Last_members(members* head);			/*finding last member of link list*/

int Check_information(user* head, group* head_group, char* user_name, char* password, char* phone_number);			/*checking inputed data from user*/

void Info(user* head, char* string);									/*showing all user names*/

void About(user* head, char* string);		/*show full information of user*/

void Creat_group(user* admin, user* head, group* head_group, char* string);			/*creating new group*/

int Membership(user* loged_in_user, group* selected);			/*check membership of a user*/

void Add_to_group(user* loged_in_user, user* head, group* head_group, char* string);			/*adding new memeber to a group*/

void Send_message(user* sender, char* string, user* head_user,group* head_group);			/*sending messgae*/

void Show_sent_message_to_user(user* receiver, user* sender);		/*showign messages that sent to another user*/

void Show_sent_message_to_group(group* receiver_group, user* sender);				/*show messages that sent to a group*/

void Show_sent_message(user* head, group* head_group, user* sender, char* string);				/*showing sent message*/

void Show_received_message_pm(user* receiver, user* sender);			/*show private messages*/

void Show_received_message_group(user* receiver, group* sender_group);				/*show messages in group*/

void Show_received_message(user* head, group* head_group, user* receiver, char* string);			/*showing received message*/

int Show_unread_message_pm(user* loged_in_user);							/*showing unread message of a user*/

int Show_unread_group_message(user* loged_in_user, group* head);			/*unread message in group*/

int User_area(user* loged_in_user, user* head, group* head_group);					/*when user logged in or sign up */

int Sign_up(user* head, group* head_group, char* string);				/*function for adding new user*/

int Login(user* head, group* head_group,char* string);					/*function  for logging in*/

char* Read_line(FILE* file);					/*read on line of file*/

void Save_user_info(user* head);					/*savign user information in a file*/

user* Load_user_info();								/*load user information from file*/

void Save_messages(user* head);				/*saving message in file*/

void Load_messages(user* head);				/*loading messages from file*/

void Save_group_info(group* head);						/*saving group information*/

group* Load_group_info(user* head);				/*loading group information*/

void Save_group_message(group* head);			/*saving group messages*/

void Load_group_messages(group* head_group, user* head);		/*loading messages in group*/

void Save_all(user* dummy, group* dummy_group);			/*save all thing*/

void Get_input(user* dummy, group* dummy_group);			/*get commad from user*/