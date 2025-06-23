#include<unistd.h>
#include<stdio.h>
#include<sys.syscall.h>

#define MY_SYS_PROCSCHED 549

int main(int argc, char *argv[]){
	int ret = syscall( MY_SYS_PROCSCHED, 1234);
	print("pcount of 1234 = %d \n", ret);
	return 0;
}
