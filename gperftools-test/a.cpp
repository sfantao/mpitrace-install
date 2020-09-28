#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <chrono>
#include <iostream>

#include "gperftools/profiler.h"

using namespace std;

volatile int MyProfileControl = 0;
int MyProfileController(void *arg) {
  return *static_cast<int*> (arg);
}

int main (int argc, char *argv[]) {
  double a = atof(argv[2]);
  double res = 1.0;
  int i = atoi(argv[1]);
  
  struct ProfilerOptions MyProfileOptions;
  memset(&MyProfileOptions, 0, sizeof MyProfileOptions);
  MyProfileOptions.filter_in_thread = &MyProfileController;
  MyProfileOptions.filter_in_thread_arg = (void*)&MyProfileControl;

  auto start = std::chrono::system_clock::now();
  
  { 
    cout << "Starting GPERF" << endl ; 
    ProfilerStartWithOptions("a.out.perf", &MyProfileOptions); 
    MyProfileControl = 1; 
  }
  
  for(; i>0; --i) {
    res = sqrt(res) * a;
  }
  
  {
    ProfilerStop(); 
    ProfilerFlush(); 
    cout << "Stopped GPERF" << endl; 
  }
   
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<double> elapsed_seconds = end-start;

  printf("%f - elapsed time %fs\n", res,elapsed_seconds.count());

  return 0;
}
