#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include "Structures.h"

#define TRUE 1
#define FALSE 0
#define TIME_FORMAT 26
#define ZERO_ASCII 48
#define NINE_ASCII 58

void Color_green(HANDLE hConsole) {
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}

void Color_normal(HANDLE hConsole,WORD saved_attributes) {
	
	SetConsoleTextAttribute(hConsole, saved_attributes);
}

char* Scan() {									/*input from user*/
	char* string = (char*)malloc(sizeof(char));
	char temp;
	int size = 1;
	while ((temp = getchar()) != '\n' && temp != EOF ) {
		string = (char*)realloc(string, size * sizeof(char));
		*(string + size - 1) = temp;
		size++;
	}
	string = (char*)realloc(string, size * sizeof(char));
	*(string + size-1) = '\0';
	return string;
}

int Size(char* string) {					/*return size of a string*/
	int size = 0;
	while (*(string + size) != '\0') {
		size++;
	}
	return size;
}

char* String_copy(char* source) {		/*build a string and copy the source in it*/
	int size = Size(source);
	char* dest = (char*)malloc(((size+1)*sizeof(char)));
	int i;
	for (i = 0; i < size; i++) {
		*(dest + i) = *(source + i);
	}
	*(dest + size) = '\0';
	return dest;
}

int	Similarity(char* string1, char* string2) {
	if (string1 == NULL || string2 == NULL)
		return FALSE;
	if (*string1 == '\0' && *string2 == '\0')
		return TRUE;									/*indicate that the two strings are the same*/
	if (*string1 == *string2)
		return Similarity(string1 + 1, string2 + 1);
	return FALSE;
}

void Print_time(time_t now) {
	struct tm * timeinfo = (struct tm*) malloc(sizeof(struct tm));
	localtime_s(timeinfo, &now);
	char string[TIME_FORMAT];
	strftime(string, TIME_FORMAT, "%Y/%m/%d %H:%M:%S\n", timeinfo);
	printf("%s", string);
}

int Uniqueness_user_name(user* head , char* user_name ) {							/*check if inputed user name is unique or not*/
	if (head == NULL)
		return TRUE;
	if (Similarity(head->user_name, user_name) == FALSE)
		return Uniqueness_user_name(head->next , user_name);
	return FALSE;																/*indicate that the inputed user name is not unique*/
}

int Uniqueness_group_name(group* head, char* name) {				/*check if inputed group name is unique or not*/
	if (head == NULL)
		return TRUE;
	if (Similarity(head->name, name) == FALSE)
		return Uniqueness_group_name(head->next, name);
	return FALSE;
}

int Password_format(char* password) {										/*check password length if it's bigger than 6*/
	if (Size(password) < 6) {
		return FALSE;
	}
	return TRUE;
}

int Uniqueness_phone_number(user* head, char* phone_number) {							/*check if inputed phone number is unique or not*/
	if (head == NULL)
		return TRUE;
	if (Similarity(head->phone_number, phone_number) == FALSE)
		return Uniqueness_phone_number(head->next, phone_number);
	return FALSE;																/*indicate that the inputed phone number is not unique*/
}

int Is_number(char* string) {				/*check if string is all number*/
	if (*string == '\0')
		return TRUE;
	if ((int)(*string) > ZERO_ASCII-1 && (int)(*string) < NINE_ASCII+1) {
		return Is_number(string + 1);
	}
	return FALSE;
}

int Check_phone_number_format(char* phone_number) {				/*check if phone number format is correct*/
	if (*phone_number != '0') {
		printf("		phone number should start with zero\n");
		return -1;
	}
	if (Is_number(phone_number) == FALSE) {
		printf("		phone number should be all number\n");
		return -3;
	}
	if (Size(phone_number) != 11) {
		printf("		phone number has to be 11 digits\n");
			return -2;
	}
	return TRUE;
}

user* Find_user(char* user_name , user* head) {			/*check if user name exists*/
	user* temp = head;
	while (temp != NULL) {
		if (Similarity(temp->user_name, user_name) == TRUE)
			return temp;
		temp = temp->next;
	}
	return NULL;				/*indicate that user name not exist*/
}

group* Find_group(char* group_name, group* head_group) {					/*find a group by its name*/
	group* temp = head_group;
	while (temp != NULL) {
		if (Similarity(temp->name, group_name) == TRUE)
			return temp;
		temp = temp->next;
	}
	return NULL;			/*indicate that group doesn't exist*/
}

user* Dummy() {															/*make first node of the user linked list*/
	user* dummy = (user*)malloc(sizeof(user));
	dummy->user_name = NULL;
	dummy->phone_number = NULL;
	dummy->next = NULL;
	dummy->ID = 0;
	return dummy;
}

message* Dummy_mess() {				/*make first node of message link list*/
	message* dummy = (message*)malloc(sizeof(message));
	dummy->next_receiver = NULL;
	return dummy;
}

members* Dummy_members() {					/*making first node of members linked list*/
	members* dummy = (members*)malloc(sizeof(members));
	dummy->next = NULL;
	return dummy;
}

group* Dummy_group() {							/*making first node of group linked list*/
	group* dummy = (group*)malloc(sizeof(group));
	dummy->next = NULL;
	dummy->name = NULL;
	dummy->members = Dummy_members();
	dummy->message = Dummy_mess();
	return dummy;
}

int Number_of_part(char* string) {					/*counting number of parts in command line*/
	int number = 0;
	int size = Size(string);
	int i;
	for (i = 0; i < size; i++) {
		if (*(string + i) == ' ')
			number++;
	}
	return number + 1;
}

char* Split_by_space(char* string, int part_number) {				/*find different part in a string that splited by space*/
	int count = 1;
	char* part = (char*)malloc(sizeof(char));
	char temp;
	int i = 0;
	int size = Size(string);
	while (count != part_number) {
		for (i; i < size; i++) {
			temp = *(string + i);
			if (temp == ' ') {
				count++;
				i++;
				break;
			}
		}
		if (i == size) {
			return NULL;				/*indicate that this string has not this many part*/
		}
	}
	int part_size = 1;
	while ((temp = *(string + i)) != ' ' && temp != '\0') {
		part = (char*)realloc(part, sizeof(char)*part_size);
		*(part + part_size - 1) = temp;
		part_size++;
		i++;
	}
	part = (char*)realloc(part, sizeof(char)*part_size);
	*(part + part_size - 1) = '\0';
	return part;
}

void Change_user_name(user* head  ,user* selected_user ,char* string) {			/*changin user name*/
	if (Number_of_part(string) != 2) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* new_user_name;
	new_user_name = Split_by_space(string, 2);
	if (Similarity(selected_user->user_name, new_user_name) == TRUE) {
		printf("		it's the same username\n");
		free(new_user_name);
		return;
	}
	if (Uniqueness_user_name(head, new_user_name) == FALSE) {
		printf("		username exist\n");
		free(new_user_name);
		return;
	}
	free(selected_user->user_name);
	selected_user->user_name = new_user_name;
	printf("		username changed successfully\n");
	return;
}

void Change_password(user* head, user* selected_user, char* string) {				/*this function is for changing password*/
	if (Number_of_part(string) != 2) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* new_password;
	new_password = Split_by_space(string, 2);
	if (Similarity(new_password, selected_user->password) == TRUE) {
		printf("		password is the same\n");
		free(new_password);
		return;
	}
	if (Password_format(new_password) == FALSE) {
		printf("		password should be atleast 6 character\n");
		free(new_password);
		return;
	}
	free(selected_user->password);
	selected_user->password = new_password;
	printf("		your password changed successfully\n");
	return;
}

user* Last_user(user* dummy) {					/*find the last created account*/
	user* temp = dummy;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	return temp;
}

message* Last_receiver_message(message* head) { /*find last message that has the same receiver as head */
	message* temp = head;
	while (temp->next_receiver != NULL) {
		temp = temp->next_receiver;
	}
	return temp;
}

group* Last_group(group* head) {			/*finding last group of link list*/
	group* temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

members* Last_members(members* head) {				/*finding last member of link list*/
	members* temp = head;
	while (temp->next != NULL)
		temp = temp->next;
	return temp;
}

user* New_user(user* head) {			/*Creating new user in end of linked list*/
	user* new = (user*)malloc(sizeof(user));
	new->next = NULL;
	user* Last = Last_user(head);
	Last->next = new;
	new->ID = (Last->ID) + 1;
	return new;
}
	
message* new_message(message* head) {			/*creating new message*/
	message* new = (message*)malloc(sizeof(message));
	new->next_receiver = NULL;
	Last_receiver_message(head)->next_receiver = new;
	return new;
}

group*	New_group(group* head , user* admin) {				/*creating new group*/
	group* new = (group*)malloc(sizeof(group));
	new->next = NULL;
	Last_group(head)->next = new;
	new->admin = admin;
	new->message = Dummy_mess();
	new->members = Dummy_members();
	return new;
}

members* New_members(members* head, user* member) {			/*creating new member*/
	members* new = (members*)malloc(sizeof(members));
	new->next = NULL;
	new->member = member;
	Last_members(head)->next = new;
	return new;
}

int Check_information(user* head, group* head_group, char* user_name, char* password, char* phone_number) {			/*checking inputed data from user*/
	if (Uniqueness_user_name(head, user_name) == FALSE || Uniqueness_group_name(head_group, user_name) == FALSE) {
		printf("		\"%s\" is already exists\n", user_name);
		return FALSE;
	}
	if (Password_format(password) == FALSE) {
		printf("		password is too short\n");
		return FALSE;
	}
	if (Check_phone_number_format(phone_number) != TRUE) {
		return FALSE;
	}
	if (Uniqueness_phone_number(head , phone_number) == FALSE) {
		printf("		phone number exists\n");
		return FALSE;
	}
	return TRUE;
}

void Info(user* head, char* string) {											/*showing all user names*/
	if (Number_of_part(string) != 1) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	user* current = head->next;
	if (current == NULL)
		printf("		no user has been registered yet\n");
	while (current != NULL) {
		printf("		%s\n", current->user_name);
		current = current->next;
	}

}

void About(user* head, char* string) {			/*show full information of user*/
	if (Number_of_part(string) != 2) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* user_name = Split_by_space(string, 2);
	user* temp = Find_user(user_name,head->next);
	free(user_name);
	if (temp == NULL) {
		printf("		user does not found!\n");
		return;
	}
	printf("		user name   : %s\n" , temp->user_name);
	printf("		phone number: %s\n" , temp->phone_number);
	printf("		signup time : ");
	Print_time(temp->sign_up_time);
	printf("\n");
}

void Creat_group(user* admin,user* head,group* head_group, char* string) {			/*creating new group*/
	if (Number_of_part(string) != 2) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* group_name = Split_by_space(string, 2);

	if (Uniqueness_group_name(head_group, group_name) == FALSE || Uniqueness_user_name(head,group_name) == FALSE) {
		printf("		this name is exist\n");
		free(group_name);
		return;
	}
	printf("		group created successfully\n");
	group* new = New_group(head_group,admin);
	new->name = group_name;
	
}

int Membership(user* check, group* selected) {			/*check membership of a user*/
	members* member = selected->members->next;
	while(member != NULL) {
		if (member->member == check)
			return TRUE;
		member = member->next;
	}
	return FALSE;
}

void Add_to_group(user* loged_in_user,user* head,group* head_group,char* string) {			/*adding new memeber to a group*/
	if (Number_of_part(string) != 3) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* user_name = Split_by_space(string, 3);
	char* group_name = Split_by_space(string, 2);
	group* selected_group = Find_group(group_name, head_group);
	user* selected_user = Find_user(user_name, head);
	free(user_name);										/*we don't want this allocated memory anymore */
	free(group_name);
	if (selected_group == NULL) {
		printf("		group dosn't exist\n");
		return;
	}
	if (loged_in_user != selected_group->admin) {						/*just admin can add user*/
		printf("		you are not admin of this group\n");
		return;
	}
	if (selected_user == NULL) {
		printf("		user doesn't exist\n");
		return;
	}
	if (Membership(selected_user, selected_group) == TRUE || selected_user == loged_in_user) {
		printf("		this user is a member already\n");
		return;
	}
	printf("		user added successfully\n");
	New_members(selected_group->members, selected_user);
}

void Send_message(user* sender, char* string, user* head_user,group* head_group) {			/*sending messgae*/
	if (Number_of_part(string) != 3) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* receiver_user_name = Split_by_space(string, 2);
	user* receiver = Find_user(receiver_user_name, head_user);
	group* receiver_group = Find_group(receiver_user_name, head_group);
	if (receiver == NULL && receiver_group == NULL) {
		printf("		wrong user name or group name\n");
		free(receiver_user_name);
		return;
	}
	free(receiver_user_name);
	char* content = Split_by_space(string, 3);
	printf("		message sent successfully\n");
	message* new = (message*)malloc(sizeof(message));
	new->content = content;
	new->Date = time(0);
	new->next_receiver = NULL;
	new->sender = sender;
	new->read = FALSE;
	if (receiver_group != NULL) {
		Last_receiver_message(receiver_group->message)->next_receiver = new;
		return;
	}
	Last_receiver_message(receiver->received_mess)->next_receiver = new;	/*add the new message to the end of the messages that has this receiver*/
}

void Show_sent_message_to_user(user* receiver,user* sender) {		/*showign messages that sent to another user*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	message* temp = receiver->received_mess->next_receiver;

	int flag = FALSE;						/*for check if user has send any message to that person or not*/
	while (temp != NULL) {
		if (temp->sender == sender) {
			if (temp->read == FALSE)
				Color_green(hConsole);
			printf("		message: %s\n", temp->content);
			printf("		to: %s Time: ", receiver->user_name);
			Print_time(temp->Date);
			Color_normal(hConsole, saved_attributes);
			flag = TRUE;
		}
		temp = temp->next_receiver;
	}
	if (flag == FALSE) {																	/*if user don't sent any message*/
		printf("		you haven't send any message to this user or group\n");
	}
}

void Show_sent_message_to_group(group* receiver_group, user* sender) {				/*show messages that sent to a group*/
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD saved_attributes;
	GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
	saved_attributes = consoleInfo.wAttributes;

	message* temp = receiver_group->message->next_receiver;

	int flag = FALSE;						/*for check if user has send any message to that group or not*/
	while (temp != NULL) {
		if (temp->sender == sender) {
			if (temp->read == FALSE)
				Color_green(hConsole);
			printf("		message: %s\n", temp->content);
			printf("		in group : %s Time: ", receiver_group->name);
			Print_time(temp->Date);
			Color_normal(hConsole, saved_attributes);
			flag = TRUE;
		}
		temp = temp->next_receiver;
	}
	if (flag == FALSE) {																	/*if user don't sent any message*/
		printf("		you haven't send any message to this user or group\n");
	}
}

void Show_sent_message(user* head,group* head_group,user* sender , char* string) {				/*showing sent message*/
	if (Number_of_part(string) != 2) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* name = Split_by_space(string, 2);
	user* receiver = Find_user(name, head);
	group* receiver_group = Find_group(name, head_group);
	if (receiver == NULL && receiver_group == NULL) {
		printf("		user of group does not exists\n");
		free(name);
		return;
	}
	free(name);
	if (receiver != NULL) {
		Show_sent_message_to_user(receiver,sender);
	}
	else {
		if (Membership(sender, receiver_group) == FALSE && receiver_group->admin != sender) {
			printf("		your not a member of this group\n");
			return;
		}
		Show_sent_message_to_group(receiver_group, sender);
	}
	
}

void Show_received_message_pm(user* receiver,user* sender) {			/*show private messages*/
	message* temp = receiver->received_mess->next_receiver;
	int flag = FALSE;												/*to check if user has received any message from this user or not*/
	while (temp != NULL) {
		if (temp->sender == sender) {
			printf("		message: %s\n", temp->content);
			printf("		from: %s Time: ", sender->user_name);
			Print_time(temp->Date);
			temp->read = TRUE;
			flag = TRUE;
		}
		temp = temp->next_receiver;
	}
	if (flag == FALSE) {
		printf("		user hasn't sent you any messages yet\n");
	}
}

void Show_received_message_group(user* receiver,group* sender_group) {				/*show messages in group*/
	message* temp = sender_group->message->next_receiver;
	int flag = FALSE;												/*to check if user has received any message from this user or not*/
	while (temp != NULL) {
		printf("		message: %s\n", temp->content);
		printf("		from: %s in group : %s Time: ",temp->sender->user_name, sender_group->name);
		Print_time(temp->Date);
		flag = TRUE;
		temp->read = TRUE;
		temp = temp->next_receiver;
	}
	if (flag == FALSE) {
		printf("		user hasn't sent you any messages yet\n");
	}
}

void Show_received_message(user* head , group* head_group, user* receiver, char* string) {			/*showing received message*/
	if (Number_of_part(string) != 2) {
		printf("		The number of inputed information isn't right\n");
		return;
	}
	char* name = Split_by_space(string, 2);
	user* sender = Find_user(name, head);
	group* sender_group = Find_group(name, head_group);
	if (sender == NULL && sender_group == NULL) {
		printf("		user name or group does not exist\n");
		free(name);
		return;
	}
	free(name);
	if (sender != NULL)
		Show_received_message_pm(receiver,sender);
	else {
		if (Membership(receiver, sender_group) == FALSE && sender_group->admin != receiver) {
			printf("		your not a member of this group\n");
			return;
		}
		Show_received_message_group(receiver, sender_group);
	}
	
}

int Show_unread_message_pm(user* loged_in_user) {																/*showing unread message of a user*/
	int flag = FALSE;									/*for check if there is any unread message or not*/
	message* current = loged_in_user->received_mess->next_receiver;
	while (current != NULL) {
		if (current->read == FALSE) {
			printf("		message form: %s   at:",current->sender->user_name);
			Print_time(current->Date);
			flag = TRUE;
		}
		current = current->next_receiver;
	}
	return flag;
}

int Show_unread_group_message(user* loged_in_user,group* head) {			/*unread message in group*/
	int flag = FALSE;
	group* temp = head->next;
	message* temp_mess;
	while (temp != NULL) {
		if (Membership(loged_in_user, temp) == TRUE || loged_in_user == temp->admin) {
			temp_mess = temp->message->next_receiver;
			while (temp_mess != NULL) {
				if (temp_mess->read == FALSE) {
					printf("		message in group: %s   at:", temp->name);
					Print_time(temp_mess->Date);
					flag = TRUE;
				}
				temp_mess = temp_mess->next_receiver;
			}
		}
		temp = temp->next;
	}
	return flag;
}

int User_area(user* loged_in_user, user* head, group* head_group) {						/*when user logged in or sign up */
	printf("		Unread messages:\n");
	int unread_pm = Show_unread_message_pm(loged_in_user);
	int unread_group = Show_unread_group_message(loged_in_user, head_group);
	if ( unread_pm == FALSE && unread_group == FALSE ) {
		printf("		Empty\n");
	}
	
	char* command;
	char* string;
	while (TRUE) {
		printf(">> ");
		string = Scan();
		command = Split_by_space(string, 1);
		if (Similarity(command, "logout") == TRUE) {
			printf("	%s logged out Successfully\n", loged_in_user->user_name);
			free(string);
			free(command);
			return 1;
		}
		else if (Similarity(command, "signup") == TRUE) {
			printf("	you should logout first\n");
		}
		else if (Similarity(command, "login") == TRUE) {
			printf("	you should logout first\n");
		}
		else if (Similarity(command, "info") == TRUE) {
			Info(head, string);
		}
		else if (Similarity(command, "edit_username") == TRUE) {
			Change_user_name(head, loged_in_user, string);
		}
		else if (Similarity(command, "edit_pass") == TRUE) {
			Change_password(head, loged_in_user, string);
		}
		else if (Similarity(command, "about") == TRUE) {
			About(head, string);
		}
		else if (Similarity(command, "send") == TRUE) {
			Send_message(loged_in_user , string ,head,head_group);
		}
		else if (Similarity(command, "show_sent") == TRUE) {
			Show_sent_message(head,head_group, loged_in_user, string);
		}
		else if (Similarity(command, "show_received") == TRUE) {
			Show_received_message(head,head_group, loged_in_user, string);
		}
		else if (Similarity(command, "creat_group") == TRUE) {
			Creat_group(loged_in_user,head, head_group,string);
		}
		else if (Similarity(command, "add_to") == TRUE) {
			Add_to_group(loged_in_user, head, head_group, string);
		}
		else if (Similarity(command, "close") == TRUE) {
			free(string);
			free(command);
			return -1;
		}
		else {
			printf("	Wrong command!\n");
		}
		free(string);
		free(command);
	}
}

int Sign_up(user* head, group* head_group, char* string) {							/*function for adding new user*/
	if (Number_of_part(string) != 4) {
		printf("		The number of inputed information isn't right\n");
		return 0;
	}
	char* user_name = Split_by_space(string , 2);
	char* password = Split_by_space(string, 3);
	char* phone_number = Split_by_space(string, 4);
	if (Check_information(head,head_group, user_name, password, phone_number) == FALSE) {
		free(user_name);
		free(password);
		free(phone_number);
		return 0;
	}
	user* new = (user*)malloc(sizeof(user));
	new->next = NULL;
	Last_user(head)->next = new;
	new->user_name = user_name;
	new->password = password;
	new->phone_number = phone_number;
	new->sign_up_time = time(0);
	new->received_mess = Dummy_mess();
	new->received_mess->next_receiver = NULL;
	printf("		Successfully registered\n");
	if (User_area(new, head,head_group) == -1)
		return -1;										/*indicate that user input close*/
	return 0;
}

int Login(user* head, group* head_group, char* string) {					/*function  for logging in*/
	if (Number_of_part(string) != 3) {
		printf("		The number of inputed information isn't right\n");
		return 0;
	}
	char* user_name = Split_by_space(string, 2);
	user* temp = Find_user(user_name, head);
	if (temp == NULL) {
		printf("		user does not found!\n");
		free(user_name);
		return 0;
	}
	char* password = Split_by_space(string, 3);
	if (Similarity(password, temp->password) == FALSE) {
		printf("		wrong password\n");
		free(user_name);
		free(password);
		return 0;
	}
	free(user_name);
	free(password);
	printf("		successfully logged in\n");
	if (User_area(temp, head,head_group) == -1)
		return -1;
	return 0;
}

user* Find_user_by_ID(user* head, int ID) {
	user* temp = head->next;
	while (temp != NULL) {
		if (temp->ID == ID)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

char* Read_line(FILE* file) {					/*read on line of file*/
	char* line = (char*)malloc(sizeof(char));
	char temp;
	int size = 1;
	if (file != NULL) {
		while ((temp = fgetc(file)) != '\n' && temp != EOF) {
			line = (char*)realloc(line, size * sizeof(char));
			*(line + size - 1) = temp;
			size++;
		}
		line = (char*)realloc(line, size*sizeof(char));
		*(line + size - 1) = '\0';
	}
	if (size == 1)
		return NULL;					/*if line was empty it means file is over*/
	return line;
}

void Save_user_info(user* head) {				/*savign user information in a file*/
	FILE* output;
	fopen_s(&output, "users_info.txt", "w");
	user* current = head->next;
	
	while (current != NULL) {
		fprintf(output, "%s %s %s %d\n" , current->user_name,current->password,current->phone_number,(int)(current->sign_up_time));
		current = current->next;
	}
	fclose(output);
}

user* Load_user_info() {					/*load user information from file*/
	FILE* file;
	fopen_s(&file, "users_info.txt", "r");
	user* dummy = Dummy();
	user* new;
	char* line;
	if (file != NULL) {
		while ((line = Read_line(file)) != NULL) {
			new = New_user(dummy);
			new->user_name = Split_by_space(line, 1);
			new->password = Split_by_space(line, 2);
			new->phone_number = Split_by_space(line, 3);
			char* date = Split_by_space(line, 4);
			new->sign_up_time = atoi(date);
			free(date);
			new->received_mess = Dummy_mess();
			free(line);
		}
		fclose(file);
	}
	return dummy;
}

void Save_messages(user* head) {				/*saving message in file*/
	FILE* output;
	fopen_s(&output, "message_info.txt", "w");
	user* current = head->next;
	message* temp;
	while (current != NULL) {
		temp = current->received_mess->next_receiver;
		while (temp != NULL) {
			fprintf(output, "%d %d %d %d %s\n",temp->sender->ID , current->ID ,temp->read,(int)(temp->Date),temp->content);
			temp = temp->next_receiver;
		}
		current = current->next;
	}
	fclose(output);
}

void Load_messages(user* head) {				/*loading messages from file*/
	int sender_id;
	int receiver_id;
	FILE* file;
	fopen_s(&file, "message_info.txt", "r");
	user* current;
	message* new;
	char* line;
	char* part;				/*one part of the line*/
	if (file != NULL) {
		while ((line = Read_line(file)) != NULL) {
			part = Split_by_space(line, 1);
			sender_id = atoi(part);
			free(part);
			part = Split_by_space(line, 2);
			receiver_id = atoi(part);
			free(part);
			current = Find_user_by_ID(head , receiver_id);
			new = new_message(current->received_mess);
			new->sender = Find_user_by_ID(head, sender_id);
			part = Split_by_space(line, 3);
			new->read = atoi(part);
			free(part);
			part = Split_by_space(line, 4);
			new->Date = atoi(part);
			free(part);
			new->content = Split_by_space(line, 5);
		}
		fclose(file);
	}
}

void Save_group_info(group* head) {						/*saving group information*/
	FILE* output;
	fopen_s(&output, "groups_info.txt", "w");
	group* current = head->next;

	while (current != NULL) {
		fprintf(output, "%s %d", current->name,current->admin->ID);
		members* curr_member = current->members->next;
		while (curr_member != NULL) {
			fprintf(output, " %d", curr_member->member->ID);
			curr_member = curr_member->next;
		}
		fprintf(output, "\n");
		current = current->next;
	}
	fclose(output);
}

group* Load_group_info(user* head) {				/*loading group information*/
	FILE* file;
	fopen_s(&file, "groups_info.txt", "r");
	group* dummy = Dummy_group();
	group* new;
	char* line;
	char* part;						/*one part of the line*/
	if (file != NULL) {
		while ((line = Read_line(file)) != NULL) {
			part = Split_by_space(line, 2);
			user* admin = Find_user_by_ID(head, atoi(part));
			free(part);
			new = New_group(dummy,admin);
			new->name = Split_by_space(line, 1);
			int parts = Number_of_part(line);
			int i;
			for (i = 3; i <= parts; i++) {
				part = Split_by_space(line, i);
				New_members(new->members , Find_user_by_ID(head, atoi(part)));
				free(part);
			}
			free(line);
		}
		fclose(file);
	}
	return dummy;
}

void Save_group_message(group* head) {			/*saving group messages*/
	FILE* output;
	fopen_s(&output, "group_message_info.txt", "w");
	group* current = head->next;
	message* temp;
	while (current != NULL) {
		temp = current->message->next_receiver;
		while (temp != NULL) {
			fprintf(output, "%s %d %d %d %s\n", current->name, temp->sender->ID, temp->read, (int)(temp->Date), temp->content);
			temp = temp->next_receiver;
		}
		current = current->next;
	}
	fclose(output);
}

void Load_group_messages(group* head_group , user* head) {			/*loading messages in group*/
	int sender_id;
	user* sender;
	FILE* file;
	fopen_s(&file, "group_message_info.txt", "r");
	group* current;
	message* new;
	char* line;
	char* part;					/*one part of the line*/
	if (file != NULL) {
		while ((line = Read_line(file)) != NULL) {
			part = Split_by_space(line, 1);
			current = Find_group(part, head_group);
			free(part);
			part = Split_by_space(line, 2);
			sender_id = atoi(part);
			free(part);
			sender = Find_user_by_ID(head, sender_id);
			new = new_message(current->message);
			new->sender = sender;
			part = Split_by_space(line, 3);
			new->read = atoi(part);
			free(part);
			part = Split_by_space(line, 4);
			new->Date = atoi(part);
			free(part);
			new->content = Split_by_space(line, 5);
		}
		fclose(file);
	}
}

void Save_all(user* dummy, group* dummy_group) {			/*save all thing*/
	Save_user_info(dummy);
	Save_messages(dummy);
	Save_group_info(dummy_group);
	Save_group_message(dummy_group);
}

void Get_input(user* dummy, group* dummy_group) {			/*get commad from user*/
	char* command;
	char* string;
	while (TRUE) {
		printf(">> ");
		string = Scan();
		command = Split_by_space(string, 1);

		if (Similarity(command, "signup") == TRUE) {
			if (Sign_up(dummy, dummy_group, string) == -1)
				break;
		}
		else if (Similarity(command, "login") == TRUE) {
			if (Login(dummy, dummy_group, string) == -1)
				break;
		}
		else if (Similarity(command, "info") == TRUE) {
			Info(dummy, string);
		}
		else if (Similarity(command, "close") == TRUE) {
			break;
		}
		else {
			printf("		Wrong command!\n");
		}

		free(string);
		free(command);
	}
	free(string);
	free(command);
}