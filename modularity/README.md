# Modularity

## Begins

I all starts with prototype and then development of new generation of engine test bench measuring equipment. It was not very complicated devices which main task was:

- get raw measurement from sensors
- do online processing
- send it to main test bench computer

Device was simple raspberry like ARM computer with linux system with connected sensors by SPI, I2C, RS233/RS485, CAN, EthCAT, Ethernet and some other. Main output was mainly Ethernet or RS.

Prototype was working nice also with first production devices. So far so good, but I was never fully satisfied with system architecture which was created. It was done according to SOLID principles but still has some quirks and not intuitive to use in some cases. It fails in this one principles which I found through my working experience be the most important ...

> Make doing the right things easy and the wrong things hard. Peoples are not bad or good. In first place they are lazy.

Now some time pass I have greater skills ( I hope so :-) ) and we have c++17 instead of c++11. So now I should make it better.

## Requirements

As I already said system was not very complicated so requirements can be listed in few points:

- operating system linux
  - I like it :)
- near realtime capabilities
  - without hacking linux realtime is not possible but we can make fun with system scheduler and cgroups
- written in C++
  - I want it C++ some one can argue for rust or go or whatever
- modular - easy to add and remove modules
- modules must communicated between each other
- system modules and signals are defined before runtime
  - hardware for measuring device is not changed during lifetime so we can make software per device  
  - so modules and signal configuration can be compile time checked

What I spot as very interesting property of system is fact that configuration is static for each device. Hardware and therefore software modules will not change during runtime. Active modules list can vary between different devices but for each one is very well defined. In such case we can move some part of initialization, assertion to compilation time. Thanks that we can implement such architecture in which developer simple cannot make mistake with connecting various modules into device configuration. If modules are implemented correctly then integration must be correct and we eliminate big amount of possible errors.  

## Didn't someone already done it?

Of course before I try to implement something great I search through internet if some done it already. Usually I am searching in this order:

1. cpp reference - just to be sure that I don't miss something basic
1. boost libraries - second after good STL
1. apache foundation - home of very nice library
1. poco framework - set of libraries to make job done
1. https://github.com/fffaraz/awesome-cpp/pulls - another list of nice stuff
1. github search - home of many nice, claver, crazy and mostly not very mature projects
1. conan search
1. google - just as last step to confirm that there is nothing on web

In time of prototype I don't found library which will be easy and fast to introduce and in the same time fullfil requirements so I focus to make my own solution. Now I also want to try on my own just for learning and practice but they are some frameworks and library which can be used with success.  

Library to discus:

- boost::asio
- qt::signals
- boost::signals

## Main concepts

My imagination about module is simple. It is one file which define every behavior of module. One file so developer will see everything. He don't need to search through project, folders, includes and source code to gather knowledge how module is working or remember what is where. One file, one place to define work, one place to make modification. If this can be achieve we can prevent many bugs before happen. But we cannot just put everything into one function and have thousands of line of code and have one spaghetti mess. We need to remove all code which is not module specific to outside. Therefore loading configuration must be separate system which is as easy and have clean API so in final module source code it will be only few lines. The same philosophy should be applied to every part of module body. No boiler plate code, no repetitive API calls, only code which matters must be there.

### Module configuration

As with all complicated systems configuration from simple few parameters may grows to hundreds. We need to have system which can handle this big amount of different parameters in some strictly defined way so everyone will known how system should behave. We are talking about hundreds of parameters so of course we will use parameters file to store it. Most of time we would like to load configuration from file but what when we would like for test or experiments change few of them? Easy solution modify config file. But modification of original config file may be not good idea so lets copy it name it newConfigTmp and run. After a while we will get mess of this configuration file just for tests or by mistake change original config files without noticing it. I think better option is to make some kind of hierarchical parameters system so we can use it to override lower level. If there is command line option we will use this value, if not lets check config file and the if still we don't have value lest get with defaults. Thanks that system you can also put another level without changing architecture. For example lets put loading parameters from some remote server between command line and config file.

So far so good but during my work on various project I spot some things that many of them were missing. I get executable and now I need to create config file to run it. So I need to get old configuration from somewhere and modify it to new program looks easy? Some time I spent hours and many talks and calls to get information what exactly set of parameters should looks like. In most cases program already known what parameters needs so lets make simple function which will output default configuration.  

Most important thing is that for module code whatever system will be must be completely transparent and hidden. Developer which create module needs only to define parameter names, type and default value then get value. Done. Nothing more.

To summarize:

- hierarchical fetching system
- default configuration file creation
- clean API with only few methods

#### Libraries

I was using for years boost program option library which was nice and fun to use. Ok may by documentation was far from perfect and syntax was unusual but was working well. Sadly in time of c++17 using program option library which was written in c++03 is counter productive. Nice list which presents popular command line parser utilities with biassed opinion is available here [https://github.com/CLIUtils/CLI11](https://github.com/CLIUtils/CLI11#other-parsers).

Because I would like to load arguments from config file and also from command line I choose CLI11 library.

### Module identification

### Module work

### Module communication
