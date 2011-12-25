=======================================
=======================================
=============== Readme ================
=======================================
=======================================

Note:	1. Please read this file and also if required refer to ./doc/index.html for complete documentation.
	2. To run the application, first set "Allow execution" option under "Permissions" tab in Properties page of 'algosim' by right-clicking 'algosim'. Then double-click the 'algosim' icon.
	3. It requires g++ package installed.
	4. If you have any trouble, please contact me: nidheeshdas@gmail.com or 9969010620
	
AlgoSim
---------------------------------------

Contents of the package:
1. algos : This folder contains the algorithms, the source code and any images, particular to the algorithm to be simulated. 
	a. common : This folder contains the common files required to compile the algorithms, like headers.
2. doc : The complete documentation generated out of source code using Doxygen. To begin reading documentation, start with index.html file in the doc folder.
3. lib : This folder contains the compiled form of external libraries used in the project. 
	1. libmgrxX.a : The MGRX graphics library. Compiled to archive, has no other dependencies.
	2. libptypes.a: The Portable Types library. Used for multithreading. All animations and message passing is done using this library. This requires 'pthread' library, which is present in all Linux machines.
	Subfolder 'src' has the source code of these two libraries.
4. src : This folder contains the entire source code of AlgoSim. The file 'compile' contains the command-line required to compile the code. To compile, 'libjpeg', 'libpthread' and 'libX11' libraries are required which is present in most Linux systems.
5. algosim : The executable file. Just double-click the 'algosim' to run the application.
6. README : This file.


How it works?
---------------------------------------
	To run the application just double-click the 'algosim'. The external libraries are linked statically, hence it can run on virtually any Linux machines. When AlgoSim is run, it looks for the algos folder and compiles the .cpp files in the folders in algos folder and builds a Shared Object (.so file; Shared Object is the same as Dynamic Link Library or .dll in Windows). Then it attempts to load the Shared Object and reads information about the algorithm. Then it lists the available algorithms and asks user to choose one. Once user chooses an algorithm the control is passed on to the selected algorithm.
	Algosim provides this basic mechanism to dynamically load algorithms. This allows algorithms to be added without recompiling the main application. Thus algorithms are just like plugins plugged into the main application.
	Algosim also provides some functionalities and support systems, to help write new algorithms easily. These includes an Animation library which supports sprite based animations. It also provides asynchronous message passing.


How to write a new Algorithm?
---------------------------------------
	Implementing a new algorithm is very easy. We just need to include the main library header and create some classes which inherits some Base classes and implement some virtual functions to get the skelton up and running. Further algorithm specific logic can be added easily. You may use support libraries and functions provided by the algosim to speed up the development process. Please refer to the two algorithms, Booth and Robertson algorithms, which will guide you through the process of developing a new algorithm
	
	
Future?
---------------------------------------
	Many more algorithms can simulated using AlgoSim which has diagrametic representation and can be expressed through simple sprite animation. Also there are some Thread Synchronisation problems in Algosim, which is due to the fact that the graphics library used here was not designed keeping multithreading in mind. So you may observe some issues regarding color mixups.
	
	
