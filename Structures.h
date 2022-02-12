#include <time.h>

typedef struct User user;
typedef struct Message message;
typedef struct Group group;
typedef struct Members members;

struct User{
	char* user_name;
	char* password;
	char* phone_number;
	message* received_mess;
	time_t sign_up_time;
	int ID;
	user* next;		
};

struct Message{
	char* content;
	user* sender;
	time_t Date;
	message* next_receiver;		/*point to next message that has this receiver*/
	int read;
};

struct Members {
	user* member;
	members* next;
};

struct Group {
	char* name;
	user* admin;
	members* members;
	message* message;
	group* next;
};

