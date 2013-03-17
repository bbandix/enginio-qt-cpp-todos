Todos example application for Qt (C++)
======================================

Simple todo-list example application using Enginio service. Demonstrates how basic data storage and query operations can be executed with Enginio Qt C++ API. Application is data compatible with other Enginio Todos examples.


# System Requirements
* Qt 5.0 or newer
* OpenSSL library 
  * Windows: Get the installer from http://slproweb.com/products/Win32OpenSSL.html (light version is enough, copy DLLs to windows system directory when asked).
  * Linux: Seach for `libssl` in your distribution's package repository.
* Enginio library and examples have been tested in Linux and in Windows with MinGW compiler. Other platforms are not currently officially supported.


# Running the application
* Sign up to Enginio service on [Enginio website](https://www.engin.io/)
* Then either:
  * Go to Enginio Dashboard, create new backend and in 'backend type' selection choose 'Todos'
  * Download example application source code package from Enginio Dashboard (for Qt C++)  
  * Extract package and open `enginio-qt-cpp-todos.pro` file in Qt Creator
  * Run the project
* Or:
  * Clone the repository (and its submodules) from [GitHub](https://github.com/enginio/enginio-qt-cpp-todos)   
    * I.e. use `git clone --recursive` 
  * Open `enginio-qt-cpp-todos.pro` file in Qt Creator
  * Go to Enginio Dashboard and create new blank backend
  * Copy Backend Id and Backend Secret from Enginio Dashboard to `applicationconfig.h` file (Qt Creator > cpp_todos > Headers)
  * Run the project 


# Copyright and License
See LICENSE file. 
