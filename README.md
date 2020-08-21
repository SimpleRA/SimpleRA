# SimpleRA

## Getting the source code

If a repository hasn't yet been created for you, you can get the source code from the public repository (https://github.com/SimpleRA/SimpleRA.git). In your local system, run the following command

```
git clone https://github.com/SimpleRA/SimpleRA.git SimpleRA
```

This will download all the source files into a directory called "SimpleRA"

## Compilation Instructions

We use ```make``` to compile all the files and creste the server executable. ```make``` is used primarily in Linux systems, so those of you who want to use Windows will probably have to look up alternatives (I hear there are ways to install ```make``` on Windows). To compile

```cd``` into the SimpleRA directory
```
cd SimpleRA
```
```cd``` into the soure directory (called ```src```)
```
cd src
```
To compile
```
make clean
make
```

## To run

Post compilation, an executable names ```server``` will be created in the ```src``` directory
```
./server
```
