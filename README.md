# taur-os
TaurOS is a basic operating system aimed for Intel 64bit arch using x64BareBones (https://bitbucket.org/RowDaBoat/x64barebones/wiki/Home), one of this project objective was to define and implement the interrupt descriptor table to have hardware interrupts (keyboard/timertick), software interrupts (syscalls) and exceptions (only implemented invalid opcode and div by 0). Another objective was to have a reusable api (via syscalls) to draw into the video memory for which we used to draw our chess game on userland.

## Requirements
```
qemu
```

## Compile
```
$ cd Toolchain
$ make all
$ cd ..
$ make all
```
## Clean
```
$ make clean
```

## Run
```
$ ./run.sh
```
