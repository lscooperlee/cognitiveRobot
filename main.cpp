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

	int opt,count=0;
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

	try{
		FileRobot fr(logfile);

		Robot &b=fr;
		GnuplotDisplay display("filerobot",outdir);

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
			std::cout<<"producing the "<<++count<<"th map"<<std::endl;
		}

	}catch(...){
		return usage(argv[0]);
	}

}


