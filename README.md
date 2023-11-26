
## Installation on Local Machine
NOTE: This is for Linux only.

Install OpenMP
```bash
$ sudo apt-get install libomp-dev
```

Follow this tutorial till "sudo make install" command: https://www.geeksforgeeks.org/how-to-install-opencv-in-c-on-linux/

Run

```bash
  $ sudo apt-get install libopencv-dev
```
Git Clone

```bash
$ git clone https://github.com/muzammilmalik01/OpenMP-OpenCV-C-.git

```
Compiling 
```bash
$ cd OpenMP-OpenCV-C-
$ g++ -fopenmp your_code.cpp -o your_executable $(pkg-config --cflags --libs opencv4)
```
Executing
```bash
$ ./your_executable
```
