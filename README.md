# OiAK
Repository for Uni Project. 


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
6. Now go to debug/release folder which is inside your C/C++ project folder(it depends on which configuration option you have chosen during editing project properties).
7. Paste there Python Script ex. "YourPythonScript.py".
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
    

#Instrukcja podłączenia i użycia skryptów Pythona wewnątrz kodu C++#

Najważniejsze rzeczy do ustawienia w środowisku VisualStudio.
1. Kliknij prawym przyciskiem myszy na właściwości projektu.
2. Przejdź do opcji C/C++. W sekcji "Dodatkowe katalogi pliki nagłówkowych" wklej ścieżkę do folderu Include będącym podfolderem folderu Python. W moim przypadku jest to: C:/Python38/Include.
3. Przejdź do opcji Konsolidator -> "Ogólne". W sekcji "Dodatkowe katalogi biblioteki" wklej ścieżkę do folderu libs folderu Python (NIE LIB). W moim przypadku jest to: C:/Python38/libs.
4. Przejdź do opcji Konsolidator -> "Dane wejściowe". W sekcji "Dodatkowe zależności" wklej nazwy plików .lib z folderu libs Pythona. W moim przypadku są to: "python3.lib" oraz "python38.lib".
5. Pierwszymi #include, jakie mają znaleźć się w projekcie C/C++ są:
   a. #include <Python.h>
   b. #include <conio.h>
   c. #include <stdio.h>
6. Następnie przejdź do folderu debug/release, który znajduje się w folderze z projektem (debug/release zależy od opcji konfiguracji, która została wybrana podczas edycji ustawień wykonanych w krokach 2-4).
7. Następnie w danym folderze wklej skrypt Pythona, np. "YourPythonScript.py".
8. W projekcie C++ wklej następującą funkcję.

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
Przykładowy skrypt Pythona, może zawierać: 

YourPythonScript.py

```
def YourPythonFunctionName(args):
    print(args)
    print(type(args))
```

