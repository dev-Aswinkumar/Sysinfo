#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
char* failed="cannot detect";
char*  get_hostname(){
  static char hostname[256];
  if(gethostname(hostname,sizeof(hostname))==0){
    return hostname;
  }
  else{
    return failed;
  }
}


int main(){
  struct utsname getme;
  char* hostname = get_hostname();
  char* kernel;
  char* os;
  char* architecture;
  if(uname(&getme)==0){
    kernel=getme.release;
    os=getme.sysname;
    architecture=getme.machine;
  }
  else{
    kernel=failed;
    os=failed;
    architecture=failed;
  }
  printf("System Information\n");
  printf("------------------\n");
  printf("Hostname: %s\n",hostname);
  printf("Os: %s\n",os);
  printf("Kernel: %s\n",kernel);
  printf("Architecture: %s\n",architecture);
  return 0;
}
