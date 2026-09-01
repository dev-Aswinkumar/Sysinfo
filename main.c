#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
char* failed="cannot detect";
//function to get the hostname
char*  get_hostname(){
  static char hostname[256];
  if(gethostname(hostname,sizeof(hostname))==0){
    return hostname;
  }
  else{
    return failed;
  }
}
//function to get the total memory
char* get_memtot(){
  FILE *file=fopen("/proc/meminfo","r");
  static char line[256];
  if(file==NULL){
    return failed;
  }
  else{
    while(fgets(line,sizeof(line),file)){
      if(strncmp(line,"MemTotal:",9)==0){
        fclose(file);
        return line+17;
      }
    }
    fclose(file);
    return failed;
  }
}

//function to get the memory available
char* get_memavai(){
  FILE *file=fopen("/proc/meminfo","r");
  static char line[256];
  if(file==NULL){
    return failed;
  }
  else{
    while(fgets(line,sizeof(line),file)){
      if(strncmp(line,"MemAvailable:",13)==0){
        fclose(file);
        return line+17;
      }
    }
    fclose(file);
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
  char* memtot=get_memtot();
  char* memavai=get_memavai();
  printf("System Information\n");
  printf("------------------\n");
  printf("Hostname: %s\n",hostname);
  printf("Os: %s\n",os);
  printf("Kernel: %s\n",kernel);
  printf("Architecture: %s\n",architecture);
  printf("Total Memory: %.7s\n",memtot);
  printf("Total Available: %.7s\n",memavai);
  return 0;
}
