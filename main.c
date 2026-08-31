#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
struct utsname getme;
char*  get_hostname(){
  static char hostname[256];
  if(gethostname(hostname,sizeof(hostname))==0){
    return hostname;
  }
  else{
    return "cannot detect";
  }
}

int sysd_info(){
  if (uname(&getme)==0){
    return 0;
  }
  else{
    return -1;
  }
}


int main(){
  printf("System Information\n");
  printf("------------------\n");
  char* hostname = get_hostname();
  char* kernel;
  char* os;
  char* architecture;
  if(sysd_info()==-1){
    char* failed="cannot detect";
    kernel=failed;
    os=failed;
    architecture=failed;
  }
  else{
   kernel=getme.release;
   os=getme.sysname;
   architecture=getme.machine;
  }
  printf("Hostname: %s\n",hostname);
  printf("Os: %s\n",os);
  printf("Kernel: %s\n",kernel);
  printf("Architecture: %s\n",architecture);
  return 0;
}
