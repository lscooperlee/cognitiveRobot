
#include "filerobot.h"
#include "view.h"
#include "display.h"

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
//		std::cout<<v<<"\n"<<std::endl;

		b.memorize(v);

		Map m=b.doMap(2);
		display.display(m.toView());

	//	display.display(v.transform(-v.getPosition(),-v.getAngle()));
	}

}
