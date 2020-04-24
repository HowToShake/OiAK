# OiAK
Repository for Uni. 


# Instruction to use Python Script inside C++ code #

The most important things to set on VisualStudio.
1. Click right mouse button on project properties. 
2. Go to C/C++. In section Header Files Additional Directories paste path to Python Include Folder. In my case is: C:/Python38/Include.
3. Go to Linker -> General. In section Additional Library Directories paste path to Python "libs" Folder (No LIB). In my case: C:/Python38/libs.
4. Go to Linker -> Input. In section Additional Dependencies paste lib files from folder libs. In my case these files are "python3.lib" and "python38.lib".
5. First #include that you have to paste in your C/C++ project are:
  a. #include <Python.h>
  b. #include <conio.h>
  c. #include <stdio.h>
6. Now go to debug/release section in folder where is your C/C++ project (it depends on which configuration option you have chosen during editing project properties).
7. Paste there Python Script ex. "XYZ.py".
8. Paste example code in main function: 

```
void callPythonFunction(string input) {

    Py_Initialize();
    PyObject* pModule = PyImport_ImportModule("YourPythonScript"); //Without .py
    PyObject* pValue;
   
    if (pModule) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, "YourPythonFunctionName");
        
        if (pFunc && PyCallable_Check(pFunc)) {
            pValue = PyObject_CallFunction(pFunc,"s",input.c_str());
        }
        else {
            cout << "ERROR: FUNCTION NOT FOUND."<<endl;
        }
       
    }
    else {
        cout << "ERROR: MODULE NOT IMPORTED" << endl;
    }

    Py_Finalize();
}
```

AND Python script:

YourPythonScript.py

```
def YourPythonFunctionName(args):
    print(args)
    print(type(args))
```
    

