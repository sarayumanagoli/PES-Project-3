## PES Project 3 ReadMe <br />
# **Team members**<br /> 
Gitanjali Suresh (gisu9983) and Sarayu Managoli (sama2321)<br /><br />
# **Description**<br />
This repository contains custom Makefile along with the source codes for the implementation of Project 3 for the course Principles of Embedded Software.
The Makefile consists of mainly two build targets, PC and FB along with the `clean` target.<br /><br />
# **Installation/Execution notes**<br />
1.	Open `MCUXpresso IDE`
2.	Create a new project
3.	Select `Files` > `New` > `Project` > `MCUXpresso IDE` > `New C/C++ Project` 
4.	Select `frdmkl25z` board
5.	Click on `Next` and provide `project suffix` name
6.	Click on `Next`
7.	Select `Redirect SDK “PRINTF” to C library “printf”`
8.	Click on `Finish`
9.	In order to use our own Makefile, we must uncheck the option to auto-generate it
10.	To do the above, click on the Project `settings` on your left
11.	Right click on `Option` > `Edit Options` > `C/C++ Builds` > Uncheck `Generate Makefiles automatically`
12. Create your own empty `debug` folder<br /><br />

# **Build using targets**<br />
1.	Right click on the project created
2.	Select `Build Target`
3.	Click on `create`
4.	Provide different build targets. Here, targets `all VERSION = FB`,`all VERSION = PC` and `clean` are created
5.	Only files under these targets will be built<br /><br />

# **PC mode**<br />

1.	After building the target for PC, click on `Run` > `Debug as` > `PEMicro Probes`
2.	After the debug process is complete, an executable file is generated in the `debug` folder as `PES_Project_3.exe`
3.	Run this executable directly on the command terminal<br /><br />

# **FB mode**<br />
1.  After building the target for FB, click on `Run` > `Debug as` > `PEMicro Probes`
2.	After the debug process is complete, an executable file is generated in the `debug` folder as `PES_Project_3.axf`
3.	To open a terminal window, click `Crtl+Alt+Shift+T` and select the `Serial Terminal` from the `Choose Terminal` drop-down
4.	Click on `Run` on the Toolbar, the output can be seen on the Terminal window
5.	Before viewing output from each run, the terminal window can be cleared<br /><br />

# **Difficulties faced**<br />
1. Working with the `display_memory ()` and `verify_pattern ()` since both the functions involved returning a pointer.<br />
2. Understanding uC Unit Tests and writing the same for our piece of code.<br />
3. We tried implementing custom Malloc and Free functions for the FB version and found it a little hard to understand where the memory is being allocated.<br /><br />
Reading a few references and documentations for the above difficulties helped us in solving the first two difficulties.<br /><br />

# **Clarifications with the Professor**<br />
Regarding the display of 32-bit address in a 64-bit system in the PC version, we are getting an output that is 24-bit instead of 32. This involves a few things to be taken care of in terms of formatting the address. Hence, we have clarified with the professor that output obtained is good enough for Project 3 and the address manipulation is outside the scope of this project.<br /><br />

# **Documentation for output**<br />
Output files are captured in a separate PDF to show the different versions in which they were generated, PC and FB.<br /><br />



