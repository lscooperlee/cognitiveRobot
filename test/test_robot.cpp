
#include "filerobot.h"
#include "view.h"
#include "display.h"



int main(int argc, char **argv){
	
	FileRobot f("/tmp/view.log");
	FileRobot c=FileRobot(f);
	FileRobot d=FileRobot("b");

	Robot &b=f;
	
	View v=b.look();
	std::cout<<v<<std::endl;

	b.memorize(v);

	GnuplotDisplay display;
	display.display(v);
}
