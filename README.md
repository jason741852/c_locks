# Lock Implementations
Written in C, we measure the effectiveness of different types of locks under varying conditions. The number of threads, and amount of work done inside and outside the critical section is varied, the critical section being the part of code that is locked each time. 

## Types of Locks 
Besides the Linux built-in pthread mutex and pthread spinlock, in sync.h/.c I have created my own version of spin (using Test-and-Set and Test-and-Test-and-Set), mutex (exponential-back off), and queue locks. 

## Data Collection
Data are collected and outputted in the Time_data sub-directory and then are analyzed and plotted using MATLAB scripts.   

## Compile Instructions 
Compile in the linux environment using the gcc compiler. 

![alt tag](Data_plot/time_vs_numThreads.png)
