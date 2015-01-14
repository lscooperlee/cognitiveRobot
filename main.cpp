#include <iostream>
#include <unistd.h>
#include <libgen.h>
#include "robot.h"
#include "filerobot.h"
#include "display.h"
#include "map.h"
#include "debug.h"

using namespace robot;
using std::string;

int usage(char *self){
	std::cout<<basename(self)<<" <options>"<<std::endl;
	std::cout<<"options:"<<std::endl;
	std::cout<<"  "<<"-f logfilename:\tspecify the logfile. default is /tmp/view.log"<<std::endl;
	std::cout<<"  "<<"-d outputdir:  \tspecify the output directory. default is /tmp/img"<<std::endl;
//	std::cout<<"  "<<"-s :           \tgenerate the map step by step for final view, rather than one map for each view"<<std::endl;
	std::cout<<"  "<<"-r :           \tshow robots on the Map"<<std::endl;
	std::cout<<"  "<<"-h :           \tshow this help"<<std::endl;
	return 0;
}

int main(int argc, char **argv){

	int opt,drawrobot=0;
	string logfile="/tmp/view.log";
	string outdir="/tmp/img/";
	while ((opt = getopt(argc, argv, "f:d:hsr")) != -1) {
		switch (opt) {
		case 'f':
			logfile=optarg;
			break;
		case 'd':
			outdir=optarg;
			break;
		case 'r':
			drawrobot=1;
			break;
		case 'h':
			return usage(argv[0]);
		}
	}

	FileRobot *p;
	try{
		p=new FileRobot(logfile);
	}catch(...){
		return usage(argv[0]);
	}

	FileRobot &b=*p;
	GnuplotDisplay display("filerobot",outdir);
	if(drawrobot==1)
		display.displayRobot(true);

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
		static int lookcount=0;
		std::cout<<"producing the "<<++lookcount<<"th map"<<std::endl;

	}

	delete p;
	return 0;
}


