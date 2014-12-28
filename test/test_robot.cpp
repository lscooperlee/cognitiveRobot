
#include "filerobot.h"
#include "view.h"
#include "display.h"
#include "map.h"

using namespace robot;

int main(int argc, char **argv){
	
	FileRobot f("/tmp/view.log");
	FileRobot c=FileRobot(f);
	FileRobot d=FileRobot("b");

	GnuplotDisplay display("filerobot","/tmp/img");

	Robot &b=f;
	while(1){
		View v;
		try {
			v=b.look();
		}catch(Robot::NoViewException e){
			break;
		}

		b.memorize(v);
		Map m=b.doMap();
		display(m);

	//	display(v);
	//	display(v.transform(-v.getPosition(),-v.getAngle()));
	}

//	Map m=b.doMap();
//	display(m);

}
