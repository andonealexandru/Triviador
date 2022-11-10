# Triviador



## Build on Windows

- Prefered Windows OS: **Windows 10 x64**

required software:
1) visual studio 2019
		- go to tools --> get tools and features --> individual components or look at installation detalis
		- make sure that the following options are selected:
			1) **MSVC v142 - VS 2019 C++ x64/x84 build tools**
			2) **C++ CMake tools for Windows**
2) CMake (minimum 3.14). Downloadable [here](https://cmake.org/download/)
3) vcpkg --> [here](https://vcpkg.io/en/getting-started.html)
4) Qt 6.4.0 (Qt online installer) [here](https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4)


#### Steps for building
1) configure vcpkg
	 -  in C: (or your main drive) create a directory called "dev"
	 - Clone the repo (you can do it any way you want)
		 - Open git bash, go to "C:\dev" and execute 
		 - `git clone https://github.com/Microsoft/vcpkg.git`
		 - `.\vcpkg\strap-vcpkg.bat`
		 - `.\vpckg integrate install`
	 - In the search box write "Edit the system environment variables", click it -->Environment Variables
		 - In user variables double click on Path --> New --> type "C:\dev\vcpkg" --> click Ok
		 - At user variables click New
			 - Variable Name: "VCPKG_DEFAULT_TRIPLET"
			 - Variable Value: "x64-windows"
			 - click Ok
		 - Anywhere in git bash or cmd, execute: `vcpkg install sqlite-orm`
 2) Install Qt6 
	 1) download Qt online installer
	 2) You'll need to create an acount, the gui will prompt that.
	 3) Select installation folder C:\dev\Qt (or anywhere you want)
	 4) Select custom installation
	 5) Select  Qt 6.4.0 and deselect
		 1) WebAssembly
		 2) MSVC 2019 ARM64
		 3) Android
	 6) Finish the installation  (this will take a while)
	 7) go to environment variables
	 8) At system variables click New
		 1) Variable name: "QTDIR"
		 2) Variable value: Select the path to the compiler (browse directory) "msvc2019_64" C:\dev\Qt\6.4.0\msvc2019_64
		 3) Select the Path variable, click edit and add 2 new values
			 1) %QTDIR%\lib
			 2) %QTDIR%\bin
3) Build project
	1) Install CMake
	2) Open cmake-gui (search it in the box)
		1) where is the source code: add the path to the cloned repository
		2) where to build the binaries: add the path to the cloned repository/build
	3) click configure
		1) Select "Visual Studio 16 2019" as generator
		2) Select x64
		3) click finish
	4) generate
