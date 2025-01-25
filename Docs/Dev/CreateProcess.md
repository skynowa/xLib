# Create Process

[`std::system` vs `::CreateProcess` vs `::ShellExecute`](https://asawicki.info/news_1767_launching_process_programmatically_system_vs_createprocess_vs_shellexecute)

|     | system() | CreateProcess()  <br>lpApplicationName | CreateProcess()  <br>lpCommandLine | ShellExecuteEx() |
| --- | --- | --- | --- | --- |
| Works without extension? `"Test"` | Yes | No  | Yes | Yes |
| Searching dir of the host app? | No  | No  | Yes | No  |
| Searching current dir? | Yes | Yes | Yes | Yes |
| Searching PATH env var? | Yes | No  | Yes | Yes |
| Path with spaces unescaped: `My Program\Test.exe` | No  | Yes | No  | Yes |
| Path with spaces enclosed with quotes: `"My Program\Test.exe"` | Yes | No  | Yes | Yes |
| Spaces escaped with `^`: `My^ Program\Test.exe` | Yes | No  | No  | No  |
