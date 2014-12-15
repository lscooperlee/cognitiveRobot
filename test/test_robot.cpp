
#include "filerobot.h"
#include "view.h"
#include "display.h"

using namespace robot;

int main(int argc, char **argv){
	
	FileRobot f("/tmp/view.log");
	FileRobot c=FileRobot(f);
	FileRobot d=FileRobot("b");

	GnuplotDisplay<Map> display;

	Robot &b=f;
	while(1){
		View v;
		try {
			v=b.look();
		}catch(...){
			break;
		}
		std::cout<<v<<std::endl;

		b.memorize(v);

//		display.display(v);
	}
	Map m=b.doMap();
	display.display(m);

}
