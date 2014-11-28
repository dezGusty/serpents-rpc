You should have python installed. Tested and working with Python 3.3.2.

To add an external tool to Visual Studio, go to the [Tools] menu, and select [External Tools...].
Click the [Add] button, then fill in the fields as follows:
- add "[srp] cpplint" as the title.
- set the path to the python executable as the command. If you have it in the path, you can just use the exe name (E.g. "python.exe") (without quotes).  
- set the arguments to (with quotes): "C:\Users\vlad.petrescu\Documents\GitHub\serpents-rpc\tools\cpplint\cpplint.py" --output=vs12 "$(ItemPath)"
- adjust it to your location of cpplint.py
- set the initial directory to "$(ItemDir)" (without quotes).
- enable "Use Output window"
- hit OK/Apply
