Prerequisites:

1.Software:

- visual studio 2012 
- [CMake 3.0](http://www.cmake.org/download/)
- [Active perl 5.2](http://www.activestate.com/activeperl/downloads)
  
2.Libs:
  
- [guslib](https://github.com/dezGusty/guslib)
- [boost 1.56](http://www.boost.org/)
- [openssl 1.0](https://www.openssl.org/source/)
- [gtest](https://code.google.com/p/googletest/) (optional,needed if you want the unit tests built)


Install Steps: 

The specified software and lib versions are the minimum requirements, new versions may work without a problem. 
 
Boost:
 
1. Download and unzip Boost
2. Go to the boost root directory and run bootstrap.bat
3. Open command prompt 
4. cd top the boost root directory 
5. execute ``b2 --build-dir=build-directory toolset=toolset-name --build-type=complete stage``
 - *build-dir* isn't strictly necessary 
 - *toolset* specifies the compiler used (msvc for visual studio)
 - *type* specifies the libs build. Warning: Installing everything takes a really long time. Needed libs are DATE_TIME, REGEX and SYSTEM. 
6. Set the root folder boost as an envirorment variable as **BOOST_ROOT **


OpenSSL:

1. Download and unzip OpenSSL 
2. Download and install ActivePerl (make sure to set the environment path during the installation)
3. Open visual studio command prompt
4. cd into the OpenSSL source folder
5. Follow the commands found at INSTALL.W32 or INSTALL.W64, depending on your system.  	
6. Specify OPENSSL_ROOT_DIR environment variable with the root folder.

GTEST:

1. Download and unzip gtest
2. Open CMake, set the source and build folder (usually '{gtest_root}/build')
3. Open the .sln file, build it in debug and release mode.
4. Set GTEST_ROOT environment variable 

GUSLIB:

1. Clone or download guslib
2. Open CMake, set source and output folder, usually {guslib root}/build. 
3. Configure and generate guslib
4. Open the .sln file in visual studio and build it for debug and release.
5. Set GUSLIB_ROOT as an environment variable for the root guslib folder

SERPENTS-RPC

1. Clone or download serpents-rpc
2. Open CMake, set source and output folder, usually {guslib root}/build.
3. Configure and generate 
4. Open the .sln file in visual studio and build it for debug and release.

GENERATE A SELF SIGNED SSL CERT:

1. Go to {openssl_root}/build.
2. Execute openssl.exe
3. Type: ``openssl req -x509 -newkey rsa:2048 -keyout key.pem -out cert.pem -days XXX`` replace the number of days with the desired value.
4. Run through the setup, keep in mind what password you set for the certificate. 
5. Place the .pem files in the root folder of your project. 