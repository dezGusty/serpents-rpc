[block:api-header]
{
  "type": "basic",
  "title": "closeProcessByName"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": " static void closeProcessByName(const std::string processPath);",
      "language": "cplusplus",
      "name": "closeProcessByName"
    }
  ]
}
[/block]
* **@IN processPath** the path of the executable. The application tries to extract the name of the process in order to be able to obtain the process Handle. Calls closeProcessByHandle after finding the corresponding handle
[block:api-header]
{
  "type": "basic",
  "title": "closeProcessByHandle"
}
[/block]
 if a processs exists this method closes it 
 * *NOTE:* ExitProcess() detaches the process, TerminateProcess() kills the process 
[block:code]
{
  "codes": [
    {
      "code": "static void closeProcessByHandle(HANDLE& Handle);",
      "language": "cplusplus",
      "name": "closeProcessByHandle"
    }
  ]
}
[/block]
* **@IN: HANDLE& Handle** process to close