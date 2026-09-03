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

char* get_os(){
  FILE *file=fopen("/etc/os-release","r");
  static char os_name[256];
  static char os_version[256];
  char line[256];
  int final=-1;
  if(file==NULL){
    return failed;
  }
  else{
    while(fgets(line,sizeof(line),file)){
      if (strncmp(line, "NAME=", 5) == 0){
        strcpy(os_name, line + 6);
        os_name[strlen(os_name)-2]=0;
        final=1;
      }
      if (strncmp(line, "VERSION=", 8) == 0){
        strcpy(os_version, line + 9);
        os_version[strlen(os_version) - 2] = '\0';
        final=final+1;
      }
    }
  }
  if(final==2){
    return strcat(os_name,os_version);
  }
  else{
    return failed;
  }
}

int main(){
  struct utsname getme;
  char* hostname = get_hostname();
  char* kernel;
  char* os=get_os();
  char* architecture;
  if(uname(&getme)==0){
    kernel=getme.release;
    architecture=getme.machine;
  }
  else{
    kernel=failed;
    architecture=failed;
  }
  char* memtotval=get_memtot();
  char* memavaival=get_memavai();
  char* memtyp=get_memtype();
  char* memspd=get_memspeed();
  printf("\t\tSystem Information\n");
  printf("\t\t------------------\n\n");
  printf("Hostname: %s\n",hostname);
  printf("Os: %s\n",os);
  printf("Kernel: Linux %s\n",kernel);
  printf("Architecture: %s\n\n",architecture);
  printf("\t\t      Memory\n");
  printf("\t\t      ------\n\n");
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
