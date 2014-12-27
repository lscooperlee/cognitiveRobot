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
	return 0;
}

int main(int argc, char **argv){

	int opt;
	string logfile="/tmp/view.log";
	string outdir="/tmp/img/";
	while ((opt = getopt(argc, argv, "f:d:h")) != -1) {
		switch (opt) {
		case 'f':
			logfile=optarg;
			break;
		case 'd':
			outdir=optarg;
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
//	b.setDisplay(&display);

	while(1){
		View v;
		try {
			v=b.look();
		}catch(Robot::NoViewException e){
			break;
		}

		b.memorize(v);

		Map m=b.doMap();
		display.display(m);
		static int lookcount=0;
//		std::cout<<"keeping the "<<++lookcount<<"th view in memory"<<std::endl;
		std::cout<<"producing the "<<++lookcount<<"th map"<<std::endl;

	}

//	Map m=b.doMap();
//	display.display(m);

	delete p;
	return 0;
}


