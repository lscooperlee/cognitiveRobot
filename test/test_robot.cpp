
#include "filerobot.h"


int main(int argc, char **argv){
	
	FileRobot f("a");
	FileRobot c=FileRobot(f);
	FileRobot d=FileRobot("b");

	Robot &b=f;

}
