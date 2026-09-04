#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
char* failed="cannot detect";
//array for the logo
char *logo[]={
    "                 ↑↑↑↑↑↑↑↑",
    "             ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "          ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "        ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "       ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "       ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "       ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "       ↑↑↑↑↑   ↑↑↑       ↑↑↑↑↑↑       ",
    "    ↑  ↑↑↑    ↑↑↑  ↑↑↑↑    ↑↑↑   ↑↑↑↑ ",
    "    ↑  ↑   ↑↑↑↑↑↑↑↑↑↑↑↑↑↑  ↑↑↑   ↑↑↑↑↑",
    "    ↑    ↑↑↑↑↑↑↑↑          ↑↑↑↑       ",
    "       ↑   ↑↑↑↑↑↑  ↑↑↑↑↑↑  ↑↑↑↑↑↑↑↑↑  ",
    "       ↑↑↑   ↑↑↑↑  ↑↑↑↑↑   ↑↑↑↑↑↑↑↑↑↑ ",
    "       ↑↑↑↑↑   ↑↑          ↑↑↑        ",
    "       ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "        ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "          ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "            ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑",
    "                 ↑↑↑↑↑↑↑↑",
  };
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
// function to get memory available
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
//function to get memory speed
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
//function to get os name
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
    fclose(file);
    return strcat(os_name,os_version);
  }
  else{
    fclose(file);
    return failed;
  }
}
//function to get cpu information
char* get_cpuname(){
  FILE *file=fopen("/proc/cpuinfo","r");
  static char line[256];
  if(file==NULL){
    fclose(file);
    return failed;
  }
  while(fgets(line,sizeof(line),file)){
    if(strncmp(line,"model name",10)==0){
      fclose(file);
      return line+13;
    }
  }
  fclose(file);
  return failed;
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
  char* memtypval=get_memtype();
  char* memspdval=get_memspeed();
  char memtyp[256];
  char memspd[256];
  strcpy(memtyp,memtypval);
  strcpy(memspd,memspdval);
  memtyp[strlen(memtyp) - 1] = '\0';
  memspd[strlen(memspd) - 1] = '\0';
  char* cpuname=get_cpuname();
  printf("\n");
  for(int i=0;i<19;i++){
    if(i%2==0){
      printf("\033[94m%s\033[0m    ",logo[i]);
      printf("\033[42G");
    }else{
      printf("\033[35m%s\033[0m    ",logo[i]);
      printf("\033[42G");
    }
    if(i==0){
      printf("\033[34m%-20s\033[0m %s\n", "Operating system:", os);
    }else if(i==1){
      printf("\033[34m%-20s\033[0m Linux %s\n", "Kernel:", kernel);
    }else if(i==2){
      printf("\033[34m%-20s\033[0m %s\n", "Hostname:", hostname);
    }else if(i==3){
      printf("\033[34m%-20s\033[0m %s\n", "Architecture:", architecture);
    }else if(i==4){
      if (memtotval!=failed && memavaival!=failed){
        double memtot=(strtoul(memtotval,NULL,10)/1024.0)/1024.0;
        double memavai=(strtoul(memavaival,NULL,10)/1024.0)/1024.0;
        int mempercent = ((memtot - memavai) / memtot) * 100;
        printf("\033[34m%-20s\033[0m %.1f GB / %.1f GB \033[32m(%d%%)\n", "Memory:", memavai,memtot,mempercent);
      }
      else{
        printf("\033[34m%-20s\033[0m %s\n", "Memory:", failed);
      }
   }else if(i==5){
      printf("\033[34m%-20s\033[0m %s\n", "Memory type:", memtyp);
   }else if(i==6){
      printf("\033[34m%-20s\033[0m %s\n", "Memory speed:", memspd);
   }else if(i==7){
      printf("\033[34m%-20s\033[0m %s\n", "CPU:", cpuname);
   }else{
      printf("\n");
   }
  }
  printf("\n\n");
  return 0;
}
