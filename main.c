#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
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

//function to get memory type
char* get_memtype(){
  FILE *cmd=popen("dmidecode --type memory", "r");
  static char line[256];
  if(cmd==NULL){
    return failed;
  }
  else{
    while(fgets(line,sizeof(line),cmd)){
      if(strncmp(line,"\tType:",6)==0){
        pclose(cmd);
        return line+7;
      }
    }
    pclose(cmd);
    return failed;
  }
}
char* get_memspeed(){
  FILE *cmd=popen("dmidecode --type memory", "r");
  static char line[256];
  if(cmd==NULL){
    return failed;
  }
  else{
    while(fgets(line,sizeof(line),cmd)){
      if(strncmp(line,"\tSpeed:",7)==0){
        pclose(cmd);
        return line+8;
      }
    }
    pclose(cmd);
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
  char* memtotval=get_memtot();
  char* memavaival=get_memavai();
  char* memtyp=get_memtype();
  char* memspd=get_memspeed();
  printf("System Information\n");
  printf("------------------\n");
  printf("Hostname: %s\n",hostname);
  printf("Os: %s\n",os);
  printf("Kernel: %s\n",kernel);
  printf("Architecture: %s\n\n",architecture);
  printf("Memory\n");
  printf("------\n");
  if (memtotval!=failed){
    double memtot=(strtoul(memtotval,NULL,10)/1024.0)/1024.0;
    printf("Total Memory: %.1f GB\n",memtot);
  }
  else{
    printf("Total Memory: %s \n",failed);
  }
  if (memavaival!=failed){
    double memavai=(strtoul(memavaival,NULL,10)/1024.0)/1024.0;
    printf("Memory Available: %.1f GB\n",memavai);
  }
  else{
    printf("Memory Available: %s \n",failed);
  }
  printf("Memory type: %s",memtyp);
  printf("Memory speed: %s",memspd);
  return 0;
}
