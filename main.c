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


char* get_kernel(){
  if (uname(&getme)==0){
    char* kernel=getme.release;
    return kernel;
  }
  else{
    return "cannot detect";
  }
}


char* get_os(){
  if (uname(&getme)==0){
    char* os=getme.sysname;
    return os;
  }
  else{
    return "cannot detect";
  }
}


char* get_architecture(){
  if (uname(&getme)==0){
    char* os=getme.machine;
    return os;
  }
  else{
    return "cannot detect";
  }
}


int main(){
  printf("System Information\n");
  printf("------------------\n");
  char* hostname = get_hostname();
  char* kernel=get_kernel();
  char* os=get_os();
  char* architecture=get_architecture();
  printf("Hostname: %s\n",hostname);
  printf("Os: %s\n",os);
  printf("Kernel: %s\n",kernel);
  printf("Architecture: %s\n",architecture);
  return 0;
}
