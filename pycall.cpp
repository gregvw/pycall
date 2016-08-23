// Include Python.h first, otherwise we will get warnings about "_POSIX_C_SOURCE" redefined etc
#include <Python.h>

#include <iostream>
#include <stdlib.h>

int main( int argc, char *argv[]) {

  PyObject *pModuleName, *pModule, *pFunc, *pArgs, *pValue, *sys, *path;
  PyObject *pFuncName;
  PyObject *pA, *pB;

  // Module name for numerics.py
  std::string numerics("numerics");

  // Command line input
  std::string fname(argv[1]);
  double a = atof(argv[2]);
  double b = atof(argv[3]);

  // Start Python interpreter
  Py_Initialize();

  // Look for our module in the current path
  sys  = PyImport_ImportModule("sys");
  path = PyObject_GetAttrString(sys,"path");
  PyList_Append(path, PyString_FromString("."));

  // Get the name of the Python module we want to import 
  // Note that we need to call the method c_str() on our basic string to convert
  // to char* 
  pModuleName = PyString_FromString((char*)numerics.c_str());

  // Import the module
  pModule = PyImport_Import(pModuleName);

  // Get the Python function we want to use
  pFuncName = PyString_FromString(fname.c_str());

  // Check if the module has the method that we want 
  if( PyObject_HasAttr( pModule, pFuncName ) ) {

    // Get the function
    pFunc = PyObject_GetAttr(pModule,pFuncName);

    // Creat Python float objects from input doubles
    pA = PyFloat_FromDouble(a);
    pB = PyFloat_FromDouble(b);

    // Store arguments in tuple
    pArgs = PyTuple_New(2);
    PyTuple_SetItem(pArgs,0,pA);
    PyTuple_SetItem(pArgs,1,pB);

    // Evaluate the function with the argumemts
    pValue = PyObject_CallObject(pFunc,pArgs);

    // Convert the result to double
    double result = PyFloat_AsDouble(pValue);

    std::cout << "Calling Python"  << std::endl;
    std::cout << "numerics." << fname << "(" << a << "," << b << ")" << std::endl;
    std::cout << "result = " << result << std::endl;

  }
  else {

    std::cout << "Python module " << numerics << " has no method " << fname << std::endl; 

  }

  // Quit Python Interpreter
  Py_Finalize();

  return 0;
}
