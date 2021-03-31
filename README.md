Written in C++ and using Clang and CMake, this program is a command line word prediction program that predicts
what the user is typing according to what they have already typed.

To run the program, do the following: 
1. ```mkdir build```; Make a build directory to contain all build files
2. ```cp dictionary.txt build```; Copy the dictionary.txt file into build directory you just made
3. ```cd build```; change directories into the build directory
4. ```cmake ..```; call Cmake
5. ```make```; Build the executable files
6. ```./TypeAhead```; Run the word prediction program

When running, the program will just show a blank black terminal screen with no path. At this point, you can
start typing words and it will show the predictions as you type. To exit the program, type CTRL-C.

In the project is also are unit tests that determines if words correctly stored in the tree and can be found.
You can run the unit tests by going through the first 5 steps, then using the command ```./UnitTestRunner```.

[Steps 1-3](/images/steps1-3.png)
[Step 4](/images/step4.png)
[Step 5](/images/step5.png)
[Step 6](/images/step6.png)
[Running 1](/images/running1.png)
[Running 2](/images/running2.png)
[Running 3](/images/running3.png)
[Unit Tests](/images/altStep6.png)
[Running Unit Tests](/images/unitTests.png)

