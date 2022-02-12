/*UT Messenger by AliRanjbari
student ID: 810190570
computer engineering 
university of tehran*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "Structures.h"
#include "Function.h"
#include <string.h>

int main() {
	printf("Welcome to UT Messanger\n");
	Print_time(time(0));
	printf("\n\n");

	/*load all the information*/
	user* dummy = Load_user_info();
	Load_messages(dummy);
	group* dummy_group =Load_group_info(dummy);
	Load_group_messages(dummy_group, dummy);

	Get_input(dummy, dummy_group);						/*getting more information form user*/

	Save_all(dummy, dummy_group);				/*saving all the information*/

	return 0;
}