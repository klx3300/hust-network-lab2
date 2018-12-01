

#include "simu/Base.h"
#include "simu/Global.h"
#include "simu/RdtSender.h"
#include "simu/RdtReceiver.h"
// #include "stopwait/StopWaitRdtSender.h"
// #include "stopwait/StopWaitRdtReceiver.h"
#include "goback/Sender.h"
#include "goback/Receiver.h"
#include <unistd.h>
#include <dirent.h>
#include "format/log.h"
#include <cstdio>

void forced_sync(){
	int fd_count = 0;
	struct dirent *dp;
	DIR *dir = opendir("/proc/self/fd/");
	while ((dp = readdir(dir)) != NULL) {
		string fdstr(dp->d_name);
		if(fdstr == "." || fdstr == "..") continue;
		int tryfd = 0;
		sscanf(fdstr.c_str(), "%d", &tryfd);
		if(tryfd == dirfd(dir)) continue;
		fsync(tryfd);
		qLogSuccfmt("ForceSyncer: forcefully synchronized descriptor %d", tryfd);
	}
	closedir(dir);
}

int main(int argc, char* argv[])
{
	RdtSender *ps = new GBNSender(4);
	RdtReceiver * pr = new GBNReceiver();
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("input.txt");
	pns->setOutputFile("output.txt");
	pns->start();

	forced_sync();

	delete ps;
	delete pr;
	delete pUtils;
	delete pns;
	
	return 0;
}

