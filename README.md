Todos example application for Qt (C++)
======================================

Simple todo-list example for Qt platform. Demonstrates how to do basic data storage and query operations. Application is backed up by the Enginio service and it is data compatible with other Enginio Todos example applications.


# System Requirements
* Qt 5.0 or newer
* OpenSSL library. Windows installer: http://slproweb.com/products/Win32OpenSSL.html (light version is enough, copy DLLs to windows system directory when asked). In Linux seach for `libssl` in your distribution's package repository.
* Enginio library and examples have been tested in Linux and in Windows with MinGW compiler. Other platforms are not currently officially supported.


# Running the application
* Sign up to Enginio service on [Enginio website](http://www.engin.io/)
* Sign in to [Enginio dashboard](http://dashboard.engin.io) and create new backend. In 'backend type' selection choose 'Todos'.
* Either:
  * Download example source code package for Qt from Enginio Dashboard
  * Extract package and open enginio-qt-cpp-todos.pro file in Qt Creator
  * Run the project
* Or:
  * Clone the repository on [GitHub](https://github.com/enginio/enginio-qt-cpp-todos)
  * Example app project includes Enginio client library as Git submodule under enginio-qt directory. After fresh clone submodule directories are empty. You must tell Git to fetch submodule code by giving following commands (in root directory enginio-qt-cpp-todos):
    * `git submodule init`
    * `git submodule update`
  * Open enginio-qt-cpp-todos.pro file in Qt Creator
  * Copy Backend Id and Backend Secret from Enginio Dashboard to applicationconfig.h file (in cpp_todos > Headers)
  * Run the project


# Copyright
Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
Contact http://qt.digia.com/contact-us

