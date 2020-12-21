# The chiara translator program 

Thechiara interprate instructions from riscv64,x86,arm64,ppc and alpha translates  and executes it
Writed by Elliot-Gaspard COURCHINOUX

[his website](https://gaspard.courchinoux.org)


This program uses libopcodes from binutils  !!! 

to compile : 

```
make 
```

to install 

```
make install
```
make install install thechiara on /usr/bin/thechiara

so, to call thechiara simply type in a terminal : 

```
thechiara
```
thechiara will show to you basic usage of the program

# An example of thechiara command's : 


```
thechiara -rawriscv yourbinriscv
```
With this command thechiara will decompiles and executes a raw file that contains raw riscv instruction 

consult issues.txt to see the know issues 


don't  hesitate to contact thechiara team  and to contribute to thechiara project !

Enjoy !! 


[the project website](https://thechiara.org)
