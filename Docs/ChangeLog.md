# Change Log {#id_changelog}

## console-win-review (#464)

- **Commit:** [7e3ed682f](https://github.com/skynowa/xLib/commit/7e3ed682f)
- **Author:** skynowa
- **Date:** 2025-06-16

[Win] Console - rm extra ONLY Windows functionality

## Console-Attrs (#460)

- **Commit:** [07dc70945](https://github.com/skynowa/xLib/commit/07dc70945)
- **Author:** skynowa
- **Date:** 2025-06-14

Console attributes review/impl/fix

## log-trace-as-cout (#462)

- **Commit:** [4b86910a9](https://github.com/skynowa/xLib/commit/4b86910a9)
- **Author:** skynowa
- **Date:** 2025-06-13

Log Trace transform to Cout

## TraceStream-levels-impl (#461)

- **Commit:** [46579ee79](https://github.com/skynowa/xLib/commit/46579ee79)
- **Author:** skynowa
- **Date:** 2025-06-11

* TraceStream-levels: LogStream.h (+3) [14+/9-] - impl

* TraceStream-levels: LogStream.h [2+/2-] - impl

* TraceStream-levels: LogStream.h [18+/16-] - impl

* TraceStream-levels: LogStream.h [6+/6-] - impl

* TraceStream-levels: Test_Trace.cpp (+2) [6+/4-] - impl

* TraceStream-levels: LogStream.h [7+/7-] - impl

* TraceStream-levels: LogStream.h (+2) [15+/13-] - impl

* TraceStream-levels: LogStream.h (+2) [8+/7-] - impl

* TraceStream-levels: LogStream.h [1+/1-] - impl

* TraceStream-levels: ILog.h [1+] - log(s)

* TraceStream-levels: TODO.md [4+] - todo(s)

* TraceStream-levels: Test_Trace.cpp [2+/2-] - test(s)

## variadic-va-impl (#457)

- **Commit:** [9613bdf67](https://github.com/skynowa/xLib/commit/9613bdf67)
- **Author:** skynowa
- **Date:** 2025-06-05

* variadic-va: ILog.cpp (+2) [5+/2-] - impl

* variadic-va: ILog.inl (+10) [219+/139-] - impl

* variadic-va: SystemLog.cpp [1-] - impl

* variadic-va: ILog.inl (+5) [9+/105-] - impl

* variadic-va: FileLog.h (+3) [3+/3-] - impl

* variadic-va: Test_FileLog.cpp (+2) [2+/2-] - impl

* variadic-va: FormatC.cpp (+2) [14+/14-] - impl

* variadic-va: ILog.inl (+3) [30+/31-] - impl

* variadic-va: Doxyfile [1+/1-] - impl

## ilog-review (#454)

- **Commit:** [b050d4669](https://github.com/skynowa/xLib/commit/b050d4669)
- **Author:** skynowa
- **Date:** 2025-05-29

* ilog-review: ThreadPool.inl (+14) [67+/95-] - review

* ilog-review: FileLog.cpp (+9) [38+/14-] - review

* ilog-review: ILog.h [1+/1-] - todo(s)

* ilog-review: ILog.h [1+/1-] - doc(s)

* ilog-review: SystemLog.cpp (+2) [2+/2-] - review

* ilog-review: Trace.h (+6) [7+/10-] - review

* ilog-review: SystemLog.cpp (+3) [5+/5-] - review

* ilog-review: FileLog.inl (+7) [12+/97-] - remove

* ilog-review: FileLog.h (+3) [18-] - remove

* ilog-review: Test_FileLog.cpp (+2) [7+/3-] - review

* ilog-review: FileLog.cpp (+2) [3+/2-] - revert

* ilog-review: Trace.h (+4) [7+/5-] - revert

* ilog-review: Trace.h [2+/2-] - revert

* ilog-review: FileLog.cpp (+2) [16-] - Mutability - impl

* ilog-review: FileLog.cpp [6+] - merge

* ilog-review: Test_FileLog.cpp [2+/2-] - review

* ilog-review: ILog.h [2+/1-] - impl

* ilog-review: Test_Console.cpp (+24) [83+/128-] - operator << - rm

* ilog-review: test_unit.sh [2+/1-] - test(s)

* ilog-review: ILog.cpp [90+] - impl

* ilog-review: Test_Trace.cpp (+4) [37+/89-] - test(s)

* ilog-review: Event.cpp (+38) [1+/38-] - operator << - rm

* ilog-review: Unit.cpp (+2) [2+/3-] - revert

* ilog-review: Test_SystemLog.cpp [1+/1-] - test(s)

## AutoProfiler-AutoLog: Profiler.cpp (+12) [17+/296-] - remove (#455)

- **Commit:** [cc41249b7](https://github.com/skynowa/xLib/commit/cc41249b7)
- **Author:** skynowa
- **Date:** 2025-05-21



## SourceInfo-review (#453)

- **Commit:** [20ff2f4e2](https://github.com/skynowa/xLib/commit/20ff2f4e2)
- **Author:** skynowa
- **Date:** 2025-05-17

* SourceInfo-review: Test_SourceInfo.cpp (+4) [41+/14-] - review

* SourceInfo-review: Defines.h [3+/4-] - review

* SourceInfo-review: Test_SourceInfo.cpp [1+/1-] - review

* SourceInfo-review: Test_SourceInfo.cpp [6+/7-] - review

## env-namespace-fix (#451)

- **Commit:** [8b83d3d0b](https://github.com/skynowa/xLib/commit/8b83d3d0b)
- **Author:** skynowa
- **Date:** 2025-04-24

* env-namespace: Test_Env.cpp (+7) [92+/52-] - impl

* env-namespace: Env.cpp (+2) [4+] - impl

* env-namespace: Env.cpp [1+] - impl

* env-namespace: Env_unix.inl (+4) [11+/5-] - impl

* env-namespace: Env_unix.inl [1-] - code style

* env-namespace: Env.h [1+/1-] - fix

* env-namespace: Env.h [6+/6-] - code style

* env-namespace: Test_Env.cpp (+3) [35+/5-] - impl

* env-namespace: Test_Env.cpp [3-] - impl

* env-namespace: Doxyfile [1+/1-] - impl

* env-namespace: Env.cpp [1+/4-] - impl

* env-namespace: Env.cpp (+3) [2+/16-] - revert

* env-namespace: Test_Env.cpp [10-] - revert

* env-namespace: Test_Env.cpp [1-] - code style

## dll-review (#452)

- **Commit:** [d5717457c](https://github.com/skynowa/xLib/commit/d5717457c)
- **Author:** skynowa
- **Date:** 2025-04-24

* dll-review: Test_Dll.cpp (+2) [24+/6-] - impl

* dll-review: Test_Dll.cpp (+7) [34+/22-] - impl

* dll-review: Process_win.inl (+3) [3+/4-] - impl

* dll-review: Dll.h (+2) [14+/1-] - impl

* dll-review: Test_Dll.cpp (+6) [13+/12-] - impl

* dll-review: Test_Dll.cpp [14-] - impl

* dll-review: Os_unix.inl (+5) [44+/15-] - impl

* dll-review: Process_win.inl [4+/4-] - impl

* dll-review: Test_Dll.cpp (+7) [30+/33-] - impl

* dll-review: Process_win.inl [2+/2-] - review

* dll-review: Os_unix.inl [31-] - Test Win build - rm

* dll-review: Dll.h [1-] - impl

* dll-review: Test_Dll.cpp [45+/45-] - test(s)

* dll-review: Test_Dll.cpp [9+/18-] - test(s)

* dll-review: Test_Dll.cpp [17+/8-] - test(s)

* dll-review: Test_Dll.cpp [5+/13-] - test(s)

* dll-review: Test_Dll.cpp [5+/3-] - test(s)

* dll-review: Test_Dll.cpp [11+] - test(s)

* dll-review: Test_Dll.cpp [7+/7-] - test(s)

* dll-review: Test_Dll.cpp [2+/2-] - test(s), fix

* dll-review: Test_Dll.cpp [1-] - test(s), fix

* dll-review: Path_win.inl [1+/1-] - review

* dll-review: Dll.cpp (+4) [7+/17-] - impl

* dll-review: Dll_unix.inl (+4) [54-] - impl

* dll-review: Dll.h (+2) [34+/10-] - impl

* dll-review: Dll.h (+2) [4+/4-] - impl

* dll-review: Dll.cpp (+5) [9+/9-] - impl

* Revert "dll-review: Dll.cpp (+5) [9+/9-] - impl"

This reverts commit 8ee7aa129ae8bfca9db09f2d6d041c119814a17f.

* dll-review: Dll.h [7-] - impl

* dll-review: Dll.h (+2) [6+/2-] - impl

* dll-review: Test_Dll.cpp (+2) [5+/22-] - impl

* dll-review: Defines.h (+2) [10+/1-] - impl

* dll-review: Defines.h (+2) [4+/4-] - impl

* dll-review: Os_win.inl [1+/1-] - impl

* dll-review: Defines.h [3+/1-] - impl

* dll-review: Process_win.inl (+5) [5+/5-] - impl

* dll-review: Doxyfile [1+/1-] - impl

* dll-review: Defines.h [3+/9-] - impl

* dll-review: Defines.h [3+/5-] - impl

* dll-review: ProcessInfo_win.inl [1+/1-] - impl

* dll-review: Process_win.inl [1+/1-] - impl

* dll-review: Cpu_win.inl [1+/1-] - impl

* dll-review: Os_win.inl [1+] - impl

## env-prefix-impl (#450)

- **Commit:** [4defc7e07](https://github.com/skynowa/xLib/commit/4defc7e07)
- **Author:** skynowa
- **Date:** 2025-03-25

* env-prefix: Env.cpp (+2) [13+/1-] - impl

* env-prefix: Env.cpp [4+/4-] - impl

* env-prefix: Env_unix.inl (+5) [23+/22-] - impl

* env-prefix: Test_Env.cpp [109+/97-] - test(s)

* env-prefix: Test_Env.cpp (+3) [61+/39-] - test(s)

* env-prefix: Test_Env.cpp [62+/52-] - test(s)

* env-prefix: Env_win.inl [1+/1-] - review

* env-prefix: Env.cpp [1-] - review

* env-prefix: Env.h [1+/1-] - review

* env-prefix: Test_Env.cpp [1+/1-] - test(s)

* env-prefix: Env.h (+3) [6+/2-] - doc(s)

* env-prefix: Doxyfile (+2) [5+/5-] - doc(s)

* env-prefix: ChangeLog.md (+2) [2+/438-] - doc(s)

* env-prefix: ChangeLog.md [437+] - doc(s)

* env-prefix: Doxyfile (+2) [11+/11-] - doc(s)

* env-prefix: Doxyfile [1+/1-] - doc(s)

* env-prefix: CmdOptions.h [2-] - doc(s)

## ErrorReport-ctor: Test.h (+5) [55+/67-] - impl (#449)

- **Commit:** [7c04e6aa5](https://github.com/skynowa/xLib/commit/7c04e6aa5)
- **Author:** skynowa
- **Date:** 2025-03-20



## source-includes-review (#447)

- **Commit:** [11d3ca140](https://github.com/skynowa/xLib/commit/11d3ca140)
- **Author:** skynowa
- **Date:** 2025-03-20

* source-includes: Env.cpp (+4) [38+/25-] - review

* source-includes: Profiler.cpp (+2) [1+/1-] - review

* source-includes: FileType.h [2-] - review

* source-includes: Warnings.h [2+/1-] - review

* source-includes: Env.cpp (+2) [10+/27-] - review

* source-includes: Env.cpp [3+/4-] - review

* source-includes: Env.cpp [9+/19-] - revert

## doxygen-impl (#444)

- **Commit:** [7e3ff38c7](https://github.com/skynowa/xLib/commit/7e3ff38c7)
- **Author:** skynowa
- **Date:** 2025-03-05

* doxygen-impl: build_ui.sh (+2) [14+/1-] - impl

* doxygen-impl: Doxyfile [7+/6-] - impl

* doxygen-impl: DoxygenLayout.xml (+4) [276+/8-] - impl

* doxygen-impl: build.sh (+2) [2+/2-] - impl

* doxygen-impl: .gitignore [2+] - impl

* doxygen-impl: Doxyfile [1+/1-] - impl

* doxygen-impl: xLib.h [13-] - impl

* doxygen-impl: Doxyfile (+2) [18+/6-] - impl

* doxygen-impl: .gitignore (+2) [15+/9-] - impl

* doxygen-impl: Test_ThreadPool.cpp (+5) [8+/10-] - impl

* doxygen-impl: Test_Thread.cpp [3+/3-] - impl

* doxygen-impl: Test_Thread.cpp [3+/3-] - impl

* doxygen-impl: BuildInfo.h (+3) [3+/3-] - impl

* doxygen-impl: Test_ThreadPool.cpp [1+/1-] - impl

* doxygen-impl: FsWatcher.h (+3) [3+/3-] - impl

* doxygen-impl: README.md [2+/5-] - impl

* doxygen-impl: ApplicationInfo.cpp (+2) [2+/2-] - impl

* doxygen-impl: String.cpp [1+/1-] - impl

* doxygen-impl: Algos.inl [1+/1-] - impl

* doxygen-impl: FileLog.cpp [1+/1-] - impl

* doxygen-impl: ICompare.inl [1+/1-] - impl

* doxygen-impl: Application.h [3+/3-] - impl

* doxygen-impl: CMakeLists.txt [10+] - impl

* doxygen-impl: CMakeLists.txt [13+/13-] - Doxygen - OFF

* doxygen-impl: CMakeLists.txt [16+/13-] - Doxygen - OFF

* doxygen-impl: Doxyfile (+3) [1+/1-] - impl

* doxygen-impl: DoxygenLayout.xml [8+] - impl

* doxygen-impl: ApplicationInfo.h [5+/2-] - impl

* doxygen-impl: ApplicationInfo.h (+5) [22+/8-] - impl

* doxygen-impl: ApplicationInfo.h [2+/2-] - impl

* doxygen-impl: Float.h (+2) [12+/20-] - impl

* doxygen-impl: Doxyfile [2+/2-] - impl

* doxygen-impl: Path.h (+2) [4+/4-] - impl

* doxygen-impl: Doxyfile [1+/1-] - impl

* doxygen-impl: ApplicationInfo.h [4+] - impl

* doxygen-impl: Float.h [2+/2-] - impl

* doxygen-impl: Float.h [1+/2-] - fix

* doxygen-impl: SysDefines.h (+2) [3+/2-] - todo(s)

* doxygen-impl: Core.h [1+] - impl

* doxygen-impl: Doxyfile [1+/1-] - impl

* doxygen-impl: Config.h.in [15+/15-] - impl

* doxygen-impl: Config.h.in (+2) [6+/10-] - todo(s)

* doxygen-impl: Doxyfile [2+/1-] - impl

* doxygen-impl: Doxyfile.in [28+/12-] - impl

* doxygen-impl: CMakeLists.txt [13+/15-] - impl

* doxygen-impl: Doxyfile [1+/1-] - impl

* doxygen-impl: TODO.md [1+/2-] - impl

## change-log-gen (#445)

- **Commit:** [f46398c83](https://github.com/skynowa/xLib/commit/f46398c83)
- **Author:** skynowa
- **Date:** 2025-03-03

* change-log: ChangeLog.md (+2) [378+] - impl

* change-log: ChangeLog.md (+2) [84+/78-] - impl

## cmake-doxygen-doc-2 (#443)

- **Commit:** [feb502980](https://github.com/skynowa/xLib/commit/feb502980)
- **Author:** skynowa
- **Date:** 2025-02-06

* cmake-doxygen: Doxyfile.in (+5) [2658+/18-] - impl

* cmake-doxygen: CMakeLists.txt (+2) [23+/11-] - impl

* cmake-doxygen: template_generate.sh (+3) [18-] - impl

* cmake-doxygen: CMakeLists.txt [2+/2-] - impl

* cmake-doxygen: Config.cmake [1+/1-] - fix

* cmake-doxygen: Template.cmake (+11) [12+/10-] - impl

* cmake-doxygen: CMakeLists.txt (+3) [11+/10-] - impl

* cmake-doxygen: CMakeLists.txt (+4) [17+/6-] - impl

* cmake-doxygen: CMakeLists.txt [1-] - code style

* cmake-doxygen: CMakeLists.txt [2+/5-] - impl

* cmake-doxygen: CMakeLists.txt (+2) [22+/22-] - impl

* cmake-doxygen: CMakeLists.txt [2+/2-] - impl

* cmake-doxygen: conan_file.txt [1-] - revert

* cmake-doxygen: conan_file.txt [1-] - revert

* cmake-doxygen: Configure.cmake [1+/1-] - revert

* cmake-doxygen: Configure.cmake [4+/4-] - revert

* cmake-doxygen: CMakeLists.txt [1-] - revert

* cmake-doxygen: CMakeLists.txt (+2) [16-] - revert

* cmake-doxygen: Doxyfile [1+/1-] - revert

* cmake-doxygen: gen_template.sh [4+/1-] - impl

* cmake-doxygen: gen_template.sh [1+] - impl

* cmake-doxygen: Configure.cmake [1+/1-] - impl

* cmake-doxygen: Doxyfile (+2) [1+/2628-] - remove

* cmake-doxygen: CMakeLists.txt [1+/1-] - --amend

* cmake-doxygen: Config.cmake (+3) [6+/1-] - impl

* cmake-doxygen: Configure.cmake [1+/1-] - revert

* cmake-doxygen: Config.cmake [3+/3-] - impl

* cmake-doxygen: Doxyfile.in [1+/1-] - impl

* cmake-doxygen: Config.h.in [2-] - revert

## defines-review (#441)

- **Commit:** [38d6b2753](https://github.com/skynowa/xLib/commit/38d6b2753)
- **Author:** skynowa
- **Date:** 2025-01-17

* defines-review: Defines.h [61+/123-] - code style

* defines-review: Enum.h [6+/5-] - --amend

* defines-review: Defines.h [23+/21-] - review

* defines-review: Defines.h [2+/2-] - doc(s), fix

* defines-review: Defines.h [1+/2-] - fix

* defines-review: Defines.h (+3) [23+/16-] - fix

* defines-review: custom.css (+2) [5+/5-] - add

## doxygen-docs-fix (#440)

- **Commit:** [03973d8f2](https://github.com/skynowa/xLib/commit/03973d8f2)
- **Author:** skynowa
- **Date:** 2025-01-16

* doxygen-docs: Doxyfile [3+/3-] - fix

* doxygen-docs: Doxyfile [1+/1-] - review

* doxygen-docs: Doxyfile [1+/1-] - impl

* doxygen-docs: Doc.cpp [3+/1-] - fix

* doxygen-docs: Doxyfile [3+/1-] - fix

* doxygen-docs: .gitignore [2+] - add

* doxygen-docs: Doxyfile [1689+/964-] - Update with new Doxyfen version

* doxygen-docs: Defines.h (+99) [169+/167-] - fix

* doxygen-docs: Test_Application.cpp [1+/1-] - fix

* doxygen-docs: Result.cpp (+2) [3+/1-] - fix

* doxygen-docs: Limits.h (+2) [3+/1-] - fix

* doxygen-docs: Config.cpp (+34) [38+/41-] - fix

* doxygen-docs: Node.cpp (+2) [14+/14-] - fix

* doxygen-docs: Unit.cpp [2+/2-] - fix

* doxygen-docs: Client.cpp (+11) [50+/48-] - fix

* doxygen-docs: Thread.cpp (+2) [4+/4-] - fix

* doxygen-docs: Thread.cpp (+2) [3+/3-] - --amend

* doxygen-docs: Doxyfile (+2) [4+/2-] - fix

* doxygen-docs: Float.h [2+/2-] - fix

* doxygen-docs: Float.h [1+] - fix

* doxygen-docs: Float.h [2+/2-] - fix

* doxygen-docs: Application.cpp [2+/2-] - fix

* doxygen-docs: Bitset.inl (+2) [17+/16-] - Inline - add

* doxygen-docs: Application.cpp [1+/1-] - fix

* doxygen-docs: Float.h [1+/1-] - fix

* doxygen-docs: Doxyfile [2+] - fix

* doxygen-docs: Doxyfile [1+/1-] - fix

* doxygen-docs: DateTime.h [1+/1-] - fix

* doxygen-docs: Format.h (+2) [2+/2-] - fix

* doxygen-docs: OStream.h (+2) [2+/2-] - fix

## GitClient-remoteRepoNames-impl (#438)

- **Commit:** [69c5c8c39](https://github.com/skynowa/xLib/commit/69c5c8c39)
- **Author:** skynowa
- **Date:** 2025-01-13

* GitClient-remoteRepoNames: GitClient.cpp (+3) [24+/1-] - impl

* GitClient-remoteRepoNames: GitClient.cpp (+2) [33+/11-] - impl

* GitClient-remoteRepoNames: GitClient.cpp [3+/3-] - doc(s)

## cpp-standart-review (#437)

- **Commit:** [c651f41bd](https://github.com/skynowa/xLib/commit/c651f41bd)
- **Author:** skynowa
- **Date:** 2024-12-31

* cpp-standart: SysDefines.h (+5) [29+/14-] - impl

* cpp-standart: gen_eclipse.sh [1-] - impl

* cpp-standart: CMakeLists.txt (+2) [7+/1-] - impl

* cpp-standart: CMakeLists.txt [1+/6-] - impl

* cpp-standart: Test_BuildInfo.cpp (+2) [3-] - impl

* cpp-standart: Test_BuildInfo.cpp [3+/2-] - impl

## finder-is-dot (#436)

- **Commit:** [cbc1b2e0b](https://github.com/skynowa/xLib/commit/cbc1b2e0b)
- **Author:** skynowa
- **Date:** 2024-11-13

* finder-is: Finder.cpp (+2) [15+] - impl

* finder-is: Finder.cpp (+2) [17+/19-] - impl

* finder-is: Finder.cpp [1+/1-] - impl

## path-proc-with-pred (#435)

- **Commit:** [ecc276c27](https://github.com/skynowa/xLib/commit/ecc276c27)
- **Author:** skynowa
- **Date:** 2024-10-05

* path-proc: Path_unix.inl (+4) [62+/2-] - impl

* path-proc: Path_unix.inl (+2) [1+/1-] - impl

* path-proc: Utils.cpp (+8) [35+/45-] - impl

* path-proc: Utils.cpp (+2) [7+/22-] - impl

* path-proc: Test_Path.cpp [1+/3-] - impl

* path-proc: Path_unix.inl (+2) [59+/31-] - impl

* path-proc: Path_unix.inl [1+/28-] - impl

* path-proc: Path_unix.inl [1+/1-] - impl

* path-proc: Path_unix.inl [13+] - impl

* path-proc: Path_unix.inl (+3) [41+/39-] - impl

* path-proc: Path_unix.inl (+3) [50-] - impl

* path-proc: Path_unix.inl [2+/8-] - review

* path-proc: Path_unix.inl [2+/2-] - impl

## demangleName-impl (#434)

- **Commit:** [bc1560f3f](https://github.com/skynowa/xLib/commit/bc1560f3f)
- **Author:** skynowa
- **Date:** 2024-09-27

* demangleName-impl: Functions.cpp (+3) [53+/30-] - impl

* demangleName-impl: Functions.cpp (+3) [23+/25-] - impl

* demangleName-impl: StackTrace_unix.inl (+2) [1+/29-] - impl

* demangleName-impl: Functions.h (+4) [11+/2-] - impl

* demangleName-impl: test_unit.sh [2+/2-] - test(s)

* demangleName-impl: StackTrace_unix.inl (+2) [2+/2-] - impl

* demangleName-impl: Functions.cpp (+2) [2+/2-] - fix

* demangleName-impl: test_unit.sh [1+/1-] - dead(s), remove

* demangleName-impl: Functions.cpp [1+/1-] - impl

* demangleName-impl: SysDefines.h [2+/2-] - impl

* demangleName-impl: Test_BuildInfo.cpp (+4) [19+/43-] - impl

* demangleName-impl: test_unit.sh [2+/2-] - impl

* demangleName-impl: SysDefines.h [2+/2-] - impl

* demangleName-impl: StackTrace_win.inl (+2) [4+/11-] - impl

* demangleName-impl: Functions.cpp [2+/3-] - impl

## type-review (#433)

- **Commit:** [3e92dcce7](https://github.com/skynowa/xLib/commit/3e92dcce7)
- **Author:** skynowa
- **Date:** 2024-09-24

* type-review: Type.inl (+3) [47+/47-] - review

* type-review: Type.inl (+2) [17+/20-] - review

## xml-with: Doc.cpp (+4) [66+/3-] - impl (#432)

- **Commit:** [a43bfe80f](https://github.com/skynowa/xLib/commit/a43bfe80f)
- **Author:** skynowa
- **Date:** 2024-09-16



## xml-is-valid (#431)

- **Commit:** [3af301d01](https://github.com/skynowa/xLib/commit/3af301d01)
- **Author:** skynowa
- **Date:** 2024-09-12

* xml-is: Doc.cpp (+3) [67+/9-] - impl

* xml-is: Doc.cpp (+3) [72-] - remove

* xml-is: Doc.cpp [1+/1-] - review

* xml-is: Doc.cpp (+2) [15-] - remove

* xml-is: test_unit.sh [2+] - test(s)

* xml-is: Test_Xml.cpp [3+/1-] - test(s)

* xml-is: Doc.cpp [1-] - remove

## DataToIption-review (#430)

- **Commit:** [c0b94a718](https://github.com/skynowa/xLib/commit/c0b94a718)
- **Author:** skynowa
- **Date:** 2024-09-08

* DataToIption-review: HttpClient.cpp (+45) [290+/290-] - rename

* DataToIption-review: HttpClient.cpp [3+/3-] - review

* DataToIption-review: HttpClient.cpp (+2) [114+/114-] - rename

* DataToIption-review: HttpClient.cpp (+2) [5+/5-] - review

* DataToIption-review: Client.cpp [4+/4-] - review

* DataToIption-review: Translate.cpp (+2) [6+/6-] - rename

* DataToIption-review: Test_HttpClient.cpp [31+/31-] - rename

## StackTrace-addrline-impl (#426)

- **Commit:** [d9177e820](https://github.com/skynowa/xLib/commit/d9177e820)
- **Author:** skynowa
- **Date:** 2024-08-05

* StackTrace-addrline: StackTrace_unix.inl [106+/7-] - impl

* StackTrace-addrline: StackTrace_unix.inl [10+/7-] - review

* StackTrace-addrline: StackTrace_unix.inl [3+/3-] - fix

* StackTrace-addrline: StackTrace_unix.inl [2+/1-] - log(s)

* StackTrace-addrline: StackTrace_unix.inl [3+] - --amend

* StackTrace-addrline: StackTrace_unix.inl [4+/6-] - --amend

* StackTrace-addrline: StackTrace_unix.inl [14+/12-] - impl

* StackTrace-addrline: CMakeLists.txt (+2) [6+/2-] - impl

* StackTrace-addrline: Test_StackTrace.cpp [37+/12-] - test(s)

* StackTrace-addrline: StackTrace.cpp (+2) [4+/2-] - test(s)

* StackTrace-addrline: StackTrace.h (+3) [7+/3-] - test(s)

* StackTrace-addrline: StackTrace_unix.inl [1+] - code style

* StackTrace-addrline: test_unit.sh [2+/2-] - impl

* StackTrace-addrline: Test_StackTrace.cpp [19-] - impl

* StackTrace-addrline: StackTrace_unix.inl [1+/1-] - impl

* StackTrace-addrline: StackTrace_unix.inl [1-] - impl

* StackTrace-addrline: CMakeLists.txt [5+/3-] - fix

* StackTrace-addrline: StackTrace_unix.inl (+2) [6+/6-] - impl

* StackTrace-addrline: StackTrace_unix.inl [17+/116-] - impl

## file-text-impl (#429)

- **Commit:** [f0c7648d2](https://github.com/skynowa/xLib/commit/f0c7648d2)
- **Author:** skynowa
- **Date:** 2024-08-04

* file-text: FileText.cpp (+3) [301+/2-] - impl

* file-text: FileText.h [1+/1-] - impl

* file-text: FileBin.cpp (+4) [113+/56-] - impl

* file-text: FileBin.cpp (+2) [16-] - impl

* file-text: File.cpp (+13) [53+/280-] - impl

* file-text: Config.cpp (+4) [14+/5-] - impl

* file-text: Test_File.cpp (+5) [222+/186-] - impl

* file-text: FileBin.cpp [5+/1-] - impl

* file-text: FileText.cpp (+2) [7+/3-] - check(s)

* file-text: Config.cpp (+3) [15+/7-] - impl

* file-text: FileBin.h (+3) [2+/2-] - impl

* file-text: FileText.h [1+/1-] - impl

* file-text: Test_FileBin.cpp (+2) [8+/5-] - impl

* file-text: Test_FileText.cpp [24+/18-] - impl

## Revert "mmap_tstring_t-to: Unit.h (+9) [51+/45-] - impl (#427)" (#428)

- **Commit:** [32c5881a9](https://github.com/skynowa/xLib/commit/32c5881a9)
- **Author:** skynowa
- **Date:** 2024-07-04

This reverts commit be7e3fbc6c256e6f98af224be7b54afc62f5fdf8.

## mmap_tstring_t-to: Unit.h (+9) [51+/45-] - impl (#427)

- **Commit:** [be7e3fbc6](https://github.com/skynowa/xLib/commit/be7e3fbc6)
- **Author:** skynowa
- **Date:** 2024-07-04



## stack-trace-review (#425)

- **Commit:** [d38fcaf45](https://github.com/skynowa/xLib/commit/d38fcaf45)
- **Author:** skynowa
- **Date:** 2024-06-04

* stack-trace: StackTrace.cpp (+6) [33+/26-] - impl

* stack-trace: StackTrace.cpp (+4) [11+/11-] - impl

* stack-trace: StackTrace.cpp (+4) [19+/4-] - test(s)

* stack-trace: StackTrace.cpp (+2) [3+/2-] - impl

* stack-trace: CMakeLists.txt [5+] - impl

* stack-trace: Test_StackTrace.cpp (+3) [34+/6-] - test(s)

* stack-trace: Test_StackTrace.cpp [2+/2-] - test(s)

* stack-trace: StackTrace.cpp [12+/8-] - Args placeholder - impl

* stack-trace: Test_StackTrace.cpp (+5) [10+/10-] - code style

* stack-trace: StackTrace.h [2-] - review

* stack-trace: StackTrace.cpp [2-] - review

* stack-trace: Test_StackTrace.cpp [2+/5-] - review

## float-operators-impl (#424)

- **Commit:** [41e398abd](https://github.com/skynowa/xLib/commit/41e398abd)
- **Author:** skynowa
- **Date:** 2024-05-24

* float-operators: Float.h (+2) [58+] - impl

* float-operators: Test_Float.cpp [11+/7-] - impl

* float-operators: Test_Float.cpp [1+/1-] - impl

* float-operators: Float.inl (+2) [30+/17-] - impl

* float-operators: Float.inl [12+/7-] - impl

* float-operators: Float.h [1+/1-] - impl

* float-operators: Float.inl (+3) [42+] - impl

* float-operators: Float.inl [4+/1-] - impl

* float-operators: Float.h [1+] - impl

* float-operators: Float.inl [1+/1-] - doc(s)

* float-operators: Float.h [2+] - doc(s)

## conan-2.0 (#423)

- **Commit:** [7ca4d5ca1](https://github.com/skynowa/xLib/commit/7ca4d5ca1)
- **Author:** skynowa
- **Date:** 2024-04-30

* conan-2.0: CMakeLists.txt (+8) [30+/27-] - impl

* conan-2.0: conan_file.txt [1-] - impl

* conan-2.0: Configure.cmake [2+] - impl

* conan-2.0: .gitignore (+2) [5+] - impl

* conan-2.0: conan_file.txt [1+] - impl

* conan-2.0: conan_file.txt [1-] - impl

* conan-2.0: conan_file.txt [1+/1-] - impl

* conan-2.0: Configure.cmake (+2) [2+/2-] - impl

* conan-2.0: Configure.cmake (+3) [9+/5-] - test(s)

* conan-2.0: .editorconfig [20+] - impl

* conan-2.0: Core_linux.h [5+/2-] - impl

* conan-2.0: Core_linux.h [2+/5-] - impl

* conan-2.0: gen_eclipse.sh (+2) [2+/2-] - Version - 4.25

* conan-2.0: Core_linux.h [5-] - dead(s), remove

* conan-2.0: Cpu_unix.inl [1-] - review

* conan-2.0: Configure.cmake [1+/1-] - impl

* conan-2.0: Configure.cmake [1+/1-] - impl

* conan-2.0: Configure.cmake [3+/2-] - impl

* conan-2.0: Configure.cmake [2+/10-] - impl

* conan-2.0: CMakeLists.txt [3+/1-] - impl

* conan-2.0: CMakeLists.txt (+2) [4+/21-] - impl

* conan-2.0: Configure.cmake [2+/2-] - impl

* conan-2.0: CMakeLists.txt [16-] - impl

* conan-2.0: CMakeLists.txt [1+/1-] - impl

* conan-2.0: conan_file.txt [1+/2-] - review

* conan-2.0: gen_eclipse.sh [1+/1-] - impl

* conan-2.0: EnumArray.h [1+/1-] - fix

* Revert "Double.h [3+/1-] - fix"

This reverts commit f06cbe44b4b703789a341d34eddd0289e75266cf.

* conan-2.0: test_unit.sh [2+/1-] - test(s)

* conan-2.0: Test_Double.cpp (+3) [42+/18-] - impl

* conan-2.0: Test_Double.cpp [5+/5-] - test(s)

* conan-2.0: test_unit.sh [2+/2-] - test(s)

* conan-2.0: Double.h [2+/2-] - impl

* conan-2.0: test_unit.sh [1+/1-] - impl

## environment-value-first-of-impl (#422)

- **Commit:** [67fde67f1](https://github.com/skynowa/xLib/commit/67fde67f1)
- **Author:** skynowa
- **Date:** 2024-02-05

* environment-value: Test_Environment.cpp (+6) [66+/5-] - impl

* environment-value: Test_Environment.cpp (+5) [6+/6-] - impl

* environment-value: Environment.h [1+/1-] - impl

* environment-value: User_unix.inl (+2) [2+/6-] - impl

* environment-value: User_unix.inl (+2) [30-] - impl

* environment-value: User.cpp (+3) [20+/17-] - review

* environment-value: User.cpp [1+/1-] - code style

* environment-value: User.cpp [19+/13-] - review

* environment-value: Test_Environment.cpp [6+/6-] - code style

## environment-review-4 (#421)

- **Commit:** [f2cb79090](https://github.com/skynowa/xLib/commit/f2cb79090)
- **Author:** skynowa
- **Date:** 2024-01-08

* environment-review: Environment.cpp (+4) [86+/85-] - impl

* environment-review: Environment.h (+2) [5+/2-] - impl

* environment-review: Test_Environment.cpp [2+] - todo(s)

* environment-review: Test_Environment.cpp [35+/35-] - test(s)

* environment-review: Test_Environment.cpp [5+/1-] - test(s)

* environment-review: Environment_unix.inl (+4) [8+/17-] - impl

* environment-review: Environment.cpp [5+/5-] - review

* environment-review: Environment.cpp [1+/1-] - review

* environment-review: Environment.h [5+] - impl

* environment-review: ProcessInfo_win.inl [1+/1-] - impl

## environment-review-3 (#420)

- **Commit:** [bdb4a42ab](https://github.com/skynowa/xLib/commit/bdb4a42ab)
- **Author:** skynowa
- **Date:** 2024-01-08

* environment-review: Environment.cpp (+2) [18+/10-] - review

* environment-review: Environment.cpp (+3) [4+/16-] - review

* environment-review: Environment.cpp (+2) [2+/2-] - rename

* environment-review: Environment.h [1+/1-] - doc(s)

* environment-review: Environment.cpp (+4) [18+/2-] - impl

* environment-review: Environment.cpp (+3) [9+/15-] - impl

* environment-review: Environment.h [5+/5-] - impl

* environment-review: Environment.cpp (+2) [3+/3-] - impl

* environment-review: Environment.cpp (+2) [32+/30-] - review

## environment-review-2 (#419)

- **Commit:** [204b93dc3](https://github.com/skynowa/xLib/commit/204b93dc3)
- **Author:** skynowa
- **Date:** 2024-01-07

* environment-review: Environment.cpp (+4) [21+/21-] - review

* environment-review: Environment.cpp (+2) [3+/3-] - review

* environment-review: Environment.cpp (+4) [4+/4-] - review

* environment-review: Environment.cpp (+10) [21+/21-] - review

* environment-review: Test_Environment.cpp [1+/1-] - review

* environment-review: Test_Environment.cpp (+3) [4+/4-] - review

* environment-review: Test_Environment.cpp [25+/25-] - test(s)

* environment-review: Test_Environment.cpp (+3) [6+/6-] - test(s)

* environment-review: Test_Environment.cpp [16+/8-] - test(s)

## environment-review (#418)

- **Commit:** [3f11cf661](https://github.com/skynowa/xLib/commit/3f11cf661)
- **Author:** skynowa
- **Date:** 2024-01-06

* environment-review: Test_Process.cpp (+4) [32+/11-] - impl

* environment-review: Process_unix.inl (+3) [12+/12-] - impl

* environment-review: Test_Environment.cpp (+3) [21+/3-] - test(s)

* environment-review: Process_unix.inl (+2) [7+/3-] - fix

* environment-review: Test_Process.cpp [1+/1-] - test(s)

* environment-review: Process_win.inl (+2) [8+/5-] - fix

* environment-review: Environment.h [1+/1-] - doc(s)

* environment-review: Test_Process.cpp [34+/17-] - test(s)

* environment-review: Process.cpp (+2) [5+/1-] - fix

* environment-review: Process_win.inl [3+/4-] - fix

* environment-review: Test_Process.cpp [2+/2-] - test(s)

* environment-review: Test_Process.cpp [2+/4-] - test(s), fix

* environment-review: Test_Process.cpp [1+/3-] - test(s), fix

* environment-review: Test_Process.cpp (+2) [3+/19-] - log(s), remove

* environment-review: Process.cpp [7+/3-] - todo(s)

* environment-review: Process.cpp (+2) [1+/4-] - todo(s)

* environment-review: Process.h [1+] - todo(s)

* environment-review: Process.cpp [3+/3-] - code style

* environment-review: test_unit.sh [1+/1-] - test(s)

## process-unix-impl (#417)

- **Commit:** [3f1d71fbe](https://github.com/skynowa/xLib/commit/3f1d71fbe)
- **Author:** skynowa
- **Date:** 2024-01-02

* process-unix: Process_unix.inl [42+/47-] - impl

* process-unix: Process_unix.inl [5+/11-] - impl

* process-unix: Process_unix.inl [1+/1-] - impl

## process-shellExecute-impl (#416)

- **Commit:** [a2fcc3112](https://github.com/skynowa/xLib/commit/a2fcc3112)
- **Author:** skynowa
- **Date:** 2023-12-29

* process-shellExecute: Process.cpp (+2) [31+] - impl

* process-shellExecute: Process.cpp [13+/12-] - impl

* process-shellExecute: Process.cpp [1+] - todo(s)

* process-shellExecute: Process.cpp [2+] - todo(s)

* process-shellExecute: Process.cpp [3+/3-] - fix

* process-shellExecute: Process.cpp [42+/16-] - impl

* process-shellExecute: Process.cpp [2+/2-] - impl

* process-shellExecute: Process.cpp [21+/19-] - impl

* process-shellExecute: Process.cpp (+2) [9+/14-] - impl

* process-shellExecute: Process.cpp [6+/7-] - impl

* process-shellExecute: Process.cpp (+4) [62+/46-] - impl

* process-shellExecute: Process_unix.inl [1+/4-] - impl

* process-shellExecute: Process_unix.inl (+4) [65+/12-] - impl

* process-shellExecute: Test_Process.cpp [2+/2-] - impl

* process-shellExecute: Process_unix.inl (+2) [22+/4-] - impl

* process-shellExecute: Test_Process.cpp (+6) [34+/17-] - impl

* process-shellExecute: Test_Process.cpp (+2) [3+/4-] - impl

* process-shellExecute: Process_unix.inl (+3) [29+/28-] - impl

* process-shellExecute: Process.cpp [1+/1-] - impl

* process-shellExecute: Debug.h (+2) [2+/2-] - impl

* process-shellExecute: Debug.h [1-] - impl

* process-shellExecute: Debug.h [1+] - STD_TRACE_MSGBOX - impl

* process-shellExecute: Process.cpp [1-] - impl

* process-shellExecute: Test_Process.cpp [1+/1-] - impl

* process-shellExecute: Test_Process.cpp [3+/3-] - impl

* process-shellExecute: Process.cpp [1+] - impl

* process-shellExecute: Process_unix.inl (+2) [7+/4-] - impl

* process-shellExecute: Process_unix.inl [2+/3-] - impl

* process-shellExecute: Process_unix.inl [43-] - dead(s), remove

* process-shellExecute: Process_unix.inl [4+/6-] - impl

* process-shellExecute: Process_unix.inl [16+/17-] - impl

* process-shellExecute: Process.cpp [1+/1-] - impl

* process-shellExecute: Test_Process.cpp [1+/1-] - impl

* process-shellExecute: Test_Process.cpp [3+/3-] - impl

* process-shellExecute: Process_unix.inl [2+/2-] - impl

* process-shellExecute: Test_Process.cpp (+2) [6+/4-] - impl

* process-shellExecute: Process_win.inl [5+/3-] - impl

* process-shellExecute: Process_win.inl [15+/15-] - impl

* process-shellExecute: Process_win.inl [1+/1-] - impl

* process-shellExecute: Process_win.inl [2+/2-] - impl

* process-shellExecute: Process_unix.inl (+4) [23+/26-] - impl

* process-shellExecute: Process.cpp (+2) [11+/1-] - impl

* process-shellExecute: TODO.md [4+] - todo(s)

## backup-exception-rm (#415)

- **Commit:** [616d1bf4a](https://github.com/skynowa/xLib/commit/616d1bf4a)
- **Author:** skynowa
- **Date:** 2023-12-17

* backup-exception: Backup.cpp (+4) [55+/40-] - impl

* backup-exception: Backup.cpp (+2) [2+/2-] - impl

* backup-exception: Backup.cpp (+2) [17+/15-] - impl

* backup-exception: Backup.cpp [4-] - impl

* backup-exception: Backup.cpp [7+/7-] - impl

* backup-exception: Backup.cpp [2+/2-] - impl

* backup-exception: Backup.cpp (+2) [9+/6-] - impl

* backup-exception: Test_Backup.cpp [2+/2-] - impl

* backup-exception: Backup.h (+2) [4+/11-] - impl

* backup-exception: Backup.cpp (+3) [5+/3-] - impl

* backup-exception: File.h (+4) [26+/9-] - impl

* backup-exception: test_unit.sh [13+/3-] - test(s)

* backup-exception: test_unit.sh [8+/6-] - test(s)

* backup-exception: test_unit.sh [1+/1-] - impl

* backup-exception: File.cpp [7-] - dead(s), remove

* backup-exception: test_unit.sh [1+/1-] - impl

## double-impl (#414)

- **Commit:** [86d5c60a0](https://github.com/skynowa/xLib/commit/86d5c60a0)
- **Author:** skynowa
- **Date:** 2023-12-16

* double-impl: Double.inl (+2) [9+] - impl

* double-impl: Double.inl (+3) [58+/22-] - impl

* double-impl: Double.inl (+2) [13+/11-] - impl

* double-impl: Double.h [1+] - doc(s)

* double-impl: Double.inl (+2) [11+] - doc(s)

* double-impl: Double.h (+2) [4+/4-] - impl

* double-impl: Test_Double.cpp [2+] - test(s)

## dll-review (#413)

- **Commit:** [9f0aff962](https://github.com/skynowa/xLib/commit/9f0aff962)
- **Author:** skynowa
- **Date:** 2023-12-12

* dll-review: Dll.cpp (+6) [23+/21-] - review

* dll-review: Dll.cpp (+2) [2+/1-] - review

* dll-review: Test_Dll.cpp [8+/4-] - code style

## curl-split-files (#412)

- **Commit:** [ab6c43b0c](https://github.com/skynowa/xLib/commit/ab6c43b0c)
- **Author:** skynowa
- **Date:** 2023-12-12

* curl-split: Common.h (+7) [19+/8-] - impl

* curl-split: Test_Translate.cpp [1+/1-] - fix

## xml-split-file (#411)

- **Commit:** [96ee1de78](https://github.com/skynowa/xLib/commit/96ee1de78)
- **Author:** skynowa
- **Date:** 2023-12-12

* xml-split: Xml.cpp (+9) [945+/844-] - impl

* xml-split: Test_Xml.cpp (+3) [17+/18-] - impl

* xml-split: Node.h (+5) [6-] - impl

* xml-split: Test_Xml.cpp [2+] - impl

* xml-split: Node.h (+2) [4+/1-] - impl

* xml-split: Test_Xml.cpp [0+/0-] - move

* xml-split: Common.h (+4) [23+/18-] - impl

* xml-split: Common.h [5-] - impl

* xml-split: Common.h [1+/1-] - impl

* xml-split: Doc.h [1-] - todo(s)

* xml-split: Error.cpp (+4) [5+/5-] - impl

* xml-split: Doc.cpp [41+/14-] - impl

* xml-split: Doc.h [1-] - todo(s)

* xml-split: Node.cpp (+3) [3+/4-] - todo(s)

* xml-split: TODO.md [6+] - todo(s)

## curl-verison-review (#410)

- **Commit:** [10ba628c2](https://github.com/skynowa/xLib/commit/10ba628c2)
- **Author:** skynowa
- **Date:** 2023-12-08

* curl-verison: Version.cpp (+4) [19+/29-] - review

* curl-verison: Version.cpp [2+/2-] - review

* curl-verison: Version.cpp [2+/2-] - review

* curl-verison: Version.cpp [1+] - review

## donate-rm (#409)

- **Commit:** [b3a70a9c1](https://github.com/skynowa/xLib/commit/b3a70a9c1)
- **Author:** skynowa
- **Date:** 2023-12-08

* donate-rm: Donate.h (+6) [107-] - remove

* donate-rm: TODO.md [1+/1-] - impl

## curl-error (#408)

- **Commit:** [f02caa5e3](https://github.com/skynowa/xLib/commit/f02caa5e3)
- **Author:** skynowa
- **Date:** 2023-12-08

* curl-error: Error.cpp (+7) [159+/52-] - impl

* curl-error: Client.cpp [27-] - impl

* curl-error: Error.h (+4) [13+/16-] - impl

* curl-error: Error.h (+2) [2+/6-] - impl

* curl-error: TODO.md [4+] - todo(s)

* curl-error: TODO.md [4+] - todo(s)

## ILastError-review (#407)

- **Commit:** [7a9b244bc](https://github.com/skynowa/xLib/commit/7a9b244bc)
- **Author:** skynowa
- **Date:** 2023-12-04

* ILastError-review: ILastError.inl (+6) [35+/27-] - impl

* ILastError-review: Xml.h [1+/1-] - todo(s)

* ILastError-review: ILastError.inl (+6) [18+/18-] - impl

* ILastError-review: ILastError.inl [1+/1-] - review

* ILastError-review: ILastError.inl [4+/4-] - code style

* ILastError-review: Error.cpp [2-] - dead(s)

## xml-unique-ptrs-impl (#406)

- **Commit:** [bee513468](https://github.com/skynowa/xLib/commit/bee513468)
- **Author:** skynowa
- **Date:** 2023-12-04

* xml-unique: Xml.cpp (+2) [34+/16-] - impl

* xml-unique: Xml.cpp (+3) [31+/39-] - impl

* xml-unique: Xml.cpp (+2) [15+/17-] - impl

* xml-unique: Xml.cpp (+2) [10+/7-] - impl

* xml-unique: Utils.inl (+4) [24+/10-] - impl

* xml-unique: Xml.cpp [3+/6-] - impl

* xml-unique: Xml.cpp [5+/5-] - impl

* xml-unique: Xml.cpp [1+/1-] - impl

* xml-unique: Xml.cpp [3+/3-] - test(s)

* xml-unique: Xml.cpp [1+/1-] - todo(s)

* xml-unique: Xml.cpp [4+/1-] - test(s)

* xml-unique: Utils.inl (+2) [4+/3-] - code style

* xml-unique: Xml.cpp [20-] - dead(s)

## double-compare-ops (#405)

- **Commit:** [d5d87c4df](https://github.com/skynowa/xLib/commit/d5d87c4df)
- **Author:** skynowa
- **Date:** 2023-08-15

* double-compare: Double.inl [9+/1-] - Compare - fix

* double-compare: Test_Double.cpp [50+/16-] - test(s)

* double-compare: Test_Double.cpp [29+] - test(s)

* double-compare: Test_Double.cpp [29+] - test(s)

* double-compare: Test_Double.cpp [29-] - test(s)

* double-compare: Test_Double.cpp [167+/167-] - test(s)

* double-compare: Test_Double.cpp [8-] - test(s)

* double-compare: Test_Double.cpp [9+/2-] - test(s)

* double-compare: Test_Double.cpp [1+/1-] - test(s)

## config-re-impl (#404)

- **Commit:** [5111aa9da](https://github.com/skynowa/xLib/commit/5111aa9da)
- **Author:** skynowa
- **Date:** 2023-08-15

* path-re: Config.cpp (+2) [5+/15-] - impl

* path-re: Config.cpp (+2) [1+/15-] - impl

* path-re: Config.h [1-] - code style

* path-re: Test_Config.cpp (+3) [14+/25-] - impl

* path-re: Config.cpp (+2) [5+/2-] - impl

* path-re: Config.cpp [1+/3-] - impl

* path-re: File.cpp (+4) [24+/3-] - impl

* path-re: Config.cpp (+2) [10+/7-] - impl

* path-re: Config.h (+2) [12+/13-] - code style

* path-re: Config.cpp (+2) [1+/3-] - impl

* path-re: Config.h (+2) [9+/4-] - impl

* path-re: Config.h [1-] - impl

* path-re: Test_Config.cpp (+3) [15+/15-] - rename

* path-re: Config.cpp [1+/5-] - impl

* path-re: Config.h [2+/2-] - doc(s)

* path-re: Config.cpp [2-] - dead(s), remove

* path-re: Config.h (+2) [10+/9-] - impl

* path-re: Test_Config.cpp (+2) [6+/14-] - test(s)

* path-re: Test_File.cpp [7+] - test(s)

* path-re: Test_Config.cpp (+2) [4+/1-] - code style

* path-re: File.cpp [6+/6-] - code style

## xml-error-impl (#403)

- **Commit:** [71d4970ed](https://github.com/skynowa/xLib/commit/71d4970ed)
- **Author:** skynowa
- **Date:** 2023-08-11

* xml-error: Xml.cpp (+2) [56+/32-] - impl

* xml-error: Xml.cpp (+2) [1+/6-] - impl

* xml-error: ILastError.inl (+4) [22+/1-] - impl

* xml-error: Xml.cpp [1+/1-] - review

* xml-error: Xml.cpp (+2) [104+/102-] - impl

* xml-error: Xml.cpp (+2) [2+/2-] - todo(s)

* xml-error: ILastError.h [2-] - revert

* xml-error: Xml.cpp [2+] - code style

## double-ops (#402)

- **Commit:** [1f51a6aff](https://github.com/skynowa/xLib/commit/1f51a6aff)
- **Author:** skynowa
- **Date:** 2023-08-11

* double-ops: Double.inl (+2) [25+/71-] - impl

* double-ops: Double.inl [1+/1-] - fix

* double-ops: Test_MySql.cpp (+2) [8+/2-] - test(s), off

* double-ops: Double.h (+2) [15+/15-] - impl

## validator-impl (#401)

- **Commit:** [37b9a78c0](https://github.com/skynowa/xLib/commit/37b9a78c0)
- **Author:** skynowa
- **Date:** 2023-08-04

* validator-impl: IValid.h (+3) [61+/1-] - impl

* validator-impl: IValid.h (+2) [3+/3-] - code style

* validator-impl: IValid.h (+4) [14+/6-] - impl

* validator-impl: ILastError.inl (+6) [7+/37-] - impl

* validator-impl: Error.h (+4) [21+/19-] - impl

* Revert "validator-impl: Error.h (+4) [21+/19-] - impl"

This reverts commit 29c981d7529e916799c9e28fda252cfdcf42cff7.

* Revert "validator-impl: ILastError.inl (+6) [7+/37-] - impl"

This reverts commit 921516763a2c3c00a2bdaf963eca500f9f43bc21.

* validator-impl: ILastError.h (+2) [8+/5-] - review

* validator-impl: ILastError.h [2+/2-] - doc(s)

* validator-impl: ILastError.h (+2) [2+/2-] - doc(s)

* validator-impl: IValid.h [1+/1-] - doc(s)

## path-rvo (#398)

- **Commit:** [7236fa86f](https://github.com/skynowa/xLib/commit/7236fa86f)
- **Author:** skynowa
- **Date:** 2023-08-03

* ConsoleUI-split: Console.cpp (+8) [190+/140-] - impl

* ConsoleUI-split: Console.cpp [2+/1-] - impl

* ConsoleUI-split: Console.cpp [6+/6-] - impl

* ConsoleUI-split: Test_Console.cpp (+3) [4+/4-] - impl

* ConsoleUI-split: Test_Console.cpp (+3) [8+/8-] - impl

* ConsoleUI-split: Console.cpp (+4) [10+/7-] - impl

* ConsoleUI-split: Debugger.cpp [1+/1-] - impl

* ConsoleUI-split: Console.h [2+/2-] - impl

* ConsoleUI-split: Debugger.cpp (+3) [5+/3-] - impl

* ConsoleUI-split: Debugger.cpp [3+/3-] - impl

* ConsoleUI-split: Config.h.in [1-] - impl

* ConsoleUI-split: ConsoleUI.cpp (+12) [455+/265-] - impl

* ConsoleUI-split: ConsoleUI.cpp [2+/2-] - fix

* ConsoleUI-split: ConsoleUI_unix.inl (+3) [12-] - impl

* ConsoleUI-split: ConsoleUI.h (+3) [168+/168-] - impl

* ConsoleUI-split: Console.h (+2) [1+/79-] - impl

* ConsoleUI-split: ConsoleUI.cpp (+2) [4+/4-] - review

* ConsoleUI-split: Test_ConsoleUI.cpp [15+/16-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [1+/1-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [1+/1-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [4+/4-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [3+/6-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [2+/2-] - impl

* path-rvo: Console.cpp (+7) [287+/10-] - impl

* path-rvo: ConsoleUI.cpp (+5) [408-] - revert

* path-rvo: Path.cpp (+2) [2+] - log(s)

* path-rvo: Test_Path.cpp (+2) [20+/20-] - test(s)

* path-rvo: Path.h [1+/1-] - test(s)

* path-rvo: Test_Path.cpp (+2) [37+/34-] - test(s)

* path-rvo: Path.h [1+/1-] - remove

* path-rvo: Path.h [1+/1-] - revert

* path-rvo: Path.h [17-] - revert

## char-unprintable-impl (#400)

- **Commit:** [6b292bdbc](https://github.com/skynowa/xLib/commit/6b292bdbc)
- **Author:** skynowa
- **Date:** 2023-08-03

* char-unprintable: OStream.inl (+5) [61+/70-] - impl
* char-unprintable: Char.inl (+2) [3+/2-] - impl
* char-unprintable: Char.inl [1+/1-] - impl
* char-unprintable: Char.inl (+2) [3+/3-] - impl
* char-unprintable: Test_Char.cpp (+2) [9+/9-] - impl

## char-review (#399)

- **Commit:** [5f0774c57](https://github.com/skynowa/xLib/commit/5f0774c57)
- **Author:** skynowa
- **Date:** 2023-08-02

* char-review: Char.inl (+2) [6+/6-] - review
* char-review: Functors.h (+2) [2+/2-] - review
* char-review: Translate.cpp [5+/5-] - review
* char-review: OStream.inl (+6) [8+/8-] - review
* char-review: ConsoleUI.cpp [1+/1-] - review
* char-review: TODO.md [3+] - todo(s)
* char-review: Functors.h [1+/1-] - code style
* char-review: IGet.h (+4) [37+/3-] - impl
* char-review: IGet.h [2+/2-] - impl
* char-review: Char.inl [1+/2-] - review

## ConsoleUI-split (#397)

- **Commit:** [76d1d4a38](https://github.com/skynowa/xLib/commit/76d1d4a38)
- **Author:** skynowa
- **Date:** 2023-01-27

* ConsoleUI-split: Console.cpp (+8) [190+/140-] - impl

* ConsoleUI-split: Console.cpp [2+/1-] - impl

* ConsoleUI-split: Console.cpp [6+/6-] - impl

* ConsoleUI-split: Test_Console.cpp (+3) [4+/4-] - impl

* ConsoleUI-split: Test_Console.cpp (+3) [8+/8-] - impl

* ConsoleUI-split: Console.cpp (+4) [10+/7-] - impl

* ConsoleUI-split: Debugger.cpp [1+/1-] - impl

* ConsoleUI-split: Console.h [2+/2-] - impl

* ConsoleUI-split: Debugger.cpp (+3) [5+/3-] - impl

* ConsoleUI-split: Debugger.cpp [3+/3-] - impl

* ConsoleUI-split: Config.h.in [1-] - impl

* ConsoleUI-split: ConsoleUI.cpp (+12) [455+/265-] - impl

* ConsoleUI-split: ConsoleUI.cpp [2+/2-] - fix

* ConsoleUI-split: ConsoleUI_unix.inl (+3) [12-] - impl

* ConsoleUI-split: ConsoleUI.h (+3) [168+/168-] - impl

* ConsoleUI-split: Console.h (+2) [1+/79-] - impl

* ConsoleUI-split: ConsoleUI.cpp (+2) [4+/4-] - review

* ConsoleUI-split: Test_ConsoleUI.cpp [15+/16-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [1+/1-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [1+/1-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [4+/4-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [3+/6-] - impl

* ConsoleUI-split: Test_ConsoleUI.cpp [2+/2-] - impl

* ConsoleUI-split: Path.h (+2) [3+/22-] - revert

## handle-policy-move (#396)

- **Commit:** [f8016d5ac](https://github.com/skynowa/xLib/commit/f8016d5ac)
- **Author:** skynowa
- **Date:** 2023-01-11

* HandlePolicy.h [1+/2-] - review
* handle-policy: Handle.inl (+7) [388+/515-] - remove
* handle-policy: Handle.h [4+/9-] - remove
* handle-policy: Handle.inl [4+/4-] - code style
* handle-policy: Handle_win.inl [3+/3-] - fix
* handle-policy: Handle.inl [2+/2-] - code style
* handle-policy: Handle.h [3-] - rename

## file-io-attach-detach-rm (#395)

- **Commit:** [07b942184](https://github.com/skynowa/xLib/commit/07b942184)
- **Author:** skynowa
- **Date:** 2023-01-10

* file-io: FileTemp.cpp (+9) [10+/296-] - remove
* file-io: FsWatcher.cpp [3+/2-] - remove
* file-io: Functions_ansi.h [13-] - remove
* file-io: FileIO.h (+3) [9+/13-] - remove

## Handle policy review 2 (#388)

- **Commit:** [8f1dbbe78](https://github.com/skynowa/xLib/commit/8f1dbbe78)
- **Author:** skynowa
- **Date:** 2023-01-09

* handle-policy: HandlePolicy.h [67+/57-] - review
* handle-policy: HandlePolicy_unix.inl (+8) [386+/455-] - review
* handle-policy: HandlePolicy.inl [7+/1-] - review
* handle-policy: CMakeLists.txt [155+/129-] - revert
* handle-policy: CMakeLists.txt [144+/28-] - revert
* Revert "handle-policy: CMakeLists.txt [144+/28-] - revert"
This reverts commit 9d85e93ecd4a07f17c880b7e371b20fc6db60a25.
* Revert "handle-policy: CMakeLists.txt [155+/129-] - revert"
This reverts commit a868f66e89b827d66f0f553bdb1dffdf6fe6d208.
* handle-policy: HandlePolicy_unix.inl (+4) [503+/578-] - merge
* handle-policy: HandlePolicyType.h [13+/13-] - revert
* handle-policy: CMakeLists.txt [144+/28-] - merge
* handle-policy: HandlePolicy.h [5+/15-] - code style
* handle-policy: HandlePolicy.h [5+/1-] - merge
* handle-policy: HandlePolicy.inl [8+/4-] - fix
* handle-policy: HandlePolicy.inl [9+/5-] - fix
* handle-policy: HandlePolicy.inl [3+/3-] - fix
* handle-policy: Handle.h [4+] - fix
* handle-policy: Pipe.h [1+/1-] - fix
* handle-policy: HandlePolicy.h [5+/5-] - fix
* handle-policy: HandlePolicy.inl [12+/6-] - fix
* handle-policy: HandlePolicy_unix.inl (+4) [375+/424-] - impl
* handle-policy: HandlePolicy.inl [3+] - fix
* handle-policy: HandlePolicy.inl [6+/4-] - fix
* handle-policy: HandlePolicy.inl [2+/1-] - fix
* handle-policy: HandlePolicy_win.inl (+2) [2+/80-] - remove
* handle-policy: HandlePolicy_unix.inl (+2) [243-] - remove
* handle-policy: HandlePolicyType.h (+2) [1+/28-] - remove
* handle-policy: Handle.h [1-] - remove
* handle-policy: Handle.h (+2) [9+/48-] - remove
* handle-policy: HandlePolicy.h [2+/2-] - review
* handle-policy: HandlePolicy.inl [1+/1-] - fix
* handle-policy: HandlePolicy.inl [3+/3-] - test(s)
* handle-policy: HandlePolicy.inl (+2) [1+/23-] - close - review
* handle-policy: HandlePolicy.inl [13+/5-] - close - impl
* handle-policy: HandlePolicy.inl [3+/3-] - close - review
* handle-policy: HandlePolicy.inl [2+/2-] - close - review
* handle-policy: HandlePolicy.inl [4+/1-] - close - fix
* handle-policy: HandlePolicy.inl [3-] - close - todo
* handle-policy: HandlePolicy.inl [1+/1-] - close - fix

## system-info-review (#391)

- **Commit:** [4b0aa928a](https://github.com/skynowa/xLib/commit/4b0aa928a)
- **Author:** skynowa
- **Date:** 2023-01-04

* system-info: Os_win.inl (+34) [279+/279-] - rename
* system-info: PowerSupply.h (+16) [32+/32-] - comment(s)
* system-info: Os_linux.inl (+8) [44+/45-] - review

## system-info (#390)

- **Commit:** [1e297b6bf](https://github.com/skynowa/xLib/commit/1e297b6bf)
- **Author:** skynowa
- **Date:** 2023-01-04

* system-info: Cpu_win.inl (+57) [2792+] - impl
* system-info: SystemInfo_win.inl (+21) [333+/2206-] - impl
* system-info: Test_Cpu.cpp (+8) [8+/8-] - fix
* system-info: Test_PowerSupply.cpp [2+/2-] - fix
* system-info: Test_Os.cpp [20+/20-] - fix
* system-info: Cpu_win.inl (+2) [2+/2-] - fix
* system-info: Cpu_apple.inl [6-] - fix
* system-info: Test_Translate.cpp [5+] - test(s)
* system-info: Test_HttpClient.cpp [5+] - test(s)
* system-info: Cpu.cpp (+8) [8+/8-] - fix
* system-info: Cpu.cpp (+8) [45+/45-] - fix
* system-info: Test_SmtpClient.cpp [1+/1-] - log(s)
* system-info: Cpu.cpp (+8) [44-] - Includes - fix
* system-info: Test_Thread.cpp (+11) [12+/12-] - review
* system-info: Cpu.cpp [1+] - fix
* system-info: Test_Client.cpp [5+] - test(s)
* system-info: Core.h [1-] - revert
* system-info: Core.h [1+/3-] - fix
* system-info: Test_Os.cpp (+3) [24+/24-] - fix
* system-info: Core.h [1-] - fix
* system-info: Archive.cpp [6+/6-] - fix
* system-info: Archive.h [5+/10-] - code style
* system-info: Archive.cpp [13+/13-] - code style
* system-info: Archive.cpp [7+/7-] - revert

## ui-msgbox-rm (#389)

- **Commit:** [bc13271d2](https://github.com/skynowa/xLib/commit/bc13271d2)
- **Author:** skynowa
- **Date:** 2023-01-03

* ui-msgbox: XcbMsgBox.cpp (+19) [1079-] - remove
* ui-msgbox: CMakeLists.txt [5-] - remove
* ui-msgbox: Test_ErrorReport.cpp (+2) [1+/2-] - remove
* ui-msgbox: Test_ErrorReport.cpp [2+] - remove
* ui-msgbox: Test_Debugger.cpp [3+/2-] - remove
* ui-msgbox: CMakeLists.txt [5-] - remove
* ui-msgbox: Test_ErrorReport.cpp [2+/2-] - remove
* ui-msgbox: Test_ErrorReport.cpp [6+/5-] - remove
* ui-msgbox: Test_ErrorReport.cpp [2+/2-] - remove
* ui-msgbox: Test_ErrorReport.cpp [6+/6-] - revert
* ui-msgbox: Core.h [2-] - remove

## handle-policy-review (#387)

- **Commit:** [2047232a3](https://github.com/skynowa/xLib/commit/2047232a3)
- **Author:** skynowa
- **Date:** 2022-01-02

* handle-policy: HandlePolicy.h [45+/62-] - review

* handle-policy: HandlePolicy.h [1+/1-] - review

## net-mail: Pop3Client.cpp - remove (#386)

- **Commit:** [7809426fa](https://github.com/skynowa/xLib/commit/7809426fa)
- **Author:** skynowa
- **Date:** 2021-09-13



## source-info-expr (#384)

- **Commit:** [d99da5aab](https://github.com/skynowa/xLib/commit/d99da5aab)
- **Author:** skynowa
- **Date:** 2021-07-07

* source-info: Test_SourceInfo.cpp - implementation

* source-info: ErrorReport.inl - implementation

* source-info: ErrorReport.cpp - code style

* source-info: Test_SourceInfo.cpp - review

* source-info: Test_SourceInfo.cpp - test(s)

* source-info: Test_SourceInfo.cpp - test(s)

* source-info: Guid.cpp - test(s)

* source-info: SourceInfo.h - comment(s)

* source-info: SourceInfo.cpp - review

* source-info: Test.h - review

* source-info: ErrorReport.cpp - review

* source-info: SourceInfo.cpp - implementation

* source-info: DateTime.cpp - review

* source-info: Test_SourceInfo.cpp - test(s)

* source-info: Test_Debugger.cpp - test(s)

* source-info: Test_SourceInfo.cpp - test(s)

* source-info: Test_ErrorReport.cpp - fix

## path-trash (#382)

- **Commit:** [e5e785956](https://github.com/skynowa/xLib/commit/e5e785956)
- **Author:** skynowa
- **Date:** 2021-06-27

* Path.h - add todo(s)

* path-trash: Path.cpp - implementation

* path-trash: Path_apple.inl - update

* path-trash: Path.cpp - doc(s)

* path-trash: Path_unix.inl - implementation

* path-trash: Path_unix.inl - review

* path-trash: Path_unix.inl - test(s)

* path-trash: Test_Path.cpp - implementation

* path-trash: Path.h - implementation

* path-trash: Path_unix.inl - implementation

* path-trash: Path_win.inl - update

* path-trash: Path.cpp - implementation

* path-trash: Path_win.inl - implementation

## Enum-as-object (#381)

- **Commit:** [94b7f0658](https://github.com/skynowa/xLib/commit/94b7f0658)
- **Author:** skynowa
- **Date:** 2021-06-24

* Enum-as: Enum.inl - implementation

* Enum-as: Test_Enum.cpp - implementation

* Enum-as: Enum.inl - implementation

* Enum-as: Enum.h - implementation

* Enum-as: Enum.inl - implementation

* Enum-as: Enum.h - implementation

* Enum-as: Enum.inl - implementation

* Enum-as: Enum.h - implementation

* Enum-as: Operators.inl - implementation

* Enum-as: Enum.inl - implementation

* Enum-as: Enum.inl - implementation

* Enum-as: Roadmap.md - add

* Enum-as: Roadmap.md => Roadmap.txt - update

* Enum-as: Roadmap.txt - remove

* Enum-as: Roadmap.md - add

* Enum-as: Roadmap.md - add

* Enum-as: Test_Enum.cpp - implementation

* Enum-as: Enum.inl - implementation

* Enum-as: Roadmap.md - revert

* Enum-as: Test_Enum.cpp - implementation

* Enum-as: Enum.inl - implementation

## path-object-review (#378)

- **Commit:** [9a40231ae](https://github.com/skynowa/xLib/commit/9a40231ae)
- **Author:** skynowa
- **Date:** 2020-12-28

* path-object: PathExe.cpp - implementation

* path-object: PathExe.h - implementation

* path-object: PathDll_unix.inl - implementation

* path-object: Path.h - implementation

* path-object: PathExe.cpp - implementation

* path-object: Path_unix.inl - implementation

* path-object: PathExe_unix.inl - implementation

* path-object: Path.h - implementation

* path-object: Path.h - implementation

* path-object: Path.h - implementation

* path-object: Path.h - implementation

* path-object: Path.h - implementation

* path-object: Config.cpp - implementation

* path-object: Internal.h - implementation

* path-object: PathDll.cpp - implementation

* path-object: Path.cpp - implementation

* path-object-review-2 (#379)

* path-object: Path.h - implementation

* path-object: Path.h - implementation

* path-object: Path.cpp - implementation

* path-object: Test_Path.cpp - implementation

* Path object review 2 (#380)

* path-object: Path.h - implementation

* path-object: Path.h - implementation

* path-object: Path.cpp - implementation

* path-object: Test_Path.cpp - implementation

* path-object: Test_Path.cpp - test(s)

* path-object: Path.h - fix todo(s)

* path-object: Path.cpp - implementation

* path-object: Path.cpp - test(s)

* path-object: Path.cpp - test(s)

* path-object: Path.cpp - test(s)

* path-object: Path.cpp - implementation

## tests-data-move (#377)

- **Commit:** [2a65cd7a0](https://github.com/skynowa/xLib/commit/2a65cd7a0)
- **Author:** skynowa
- **Date:** 2020-09-07

* tests-data: Unit.cpp - implementation

* tests-data: Test_Path.cpp - review

* tests-data: Test_FsWatcher.cpp - fix test(s)

* tests-data: Test_FsWatcher.cpp - implementation

* tests-data: Test_FsWatcher.cpp - fix test(s)

* tests-data: Configure.cmake - implementation

* tests-data: Config.h.in - implementation

* tests-data: FindxLibData.cmake - implementation

* tests-data: Test_FsWatcher.cpp - implementation

* tests-data: Unit.cpp - implementation

* tests-data: Unit.cpp - implementation

* tests-data: Unit.cpp - implementation

* tests-data: Config.h.in - implementation

* tests-data: Unit.cpp - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: FindxLibData.cmake - implementation

* tests-data: FindxLibData.cmake - implementation

* tests-data: Configure.cmake - implementation

* tests-data: FindxLibData.cmake - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: install_apps.sh - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: install_apps.sh - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: FindxLibData.cmake - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* Merge: master -> tests-data-move

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: Test_FsWatcher.cpp - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: Unit.cpp - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: README.md - force deploy

* tests-data: main.yml - implementation

* tests-data: main.yml - implementation

* tests-data: Path.h - doc(s)

Co-authored-by: Sergey Shevchenko <skynowa@fabrica.net.ua>

## DirTemp-impl (#376)

- **Commit:** [a63460aaf](https://github.com/skynowa/xLib/commit/a63460aaf)
- **Author:** skynowa
- **Date:** 2020-09-06

* DirTemp-impl: DirTemp.cpp - add

* DirTemp-impl: DirTemp.h - review

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: DirTemp_apple.inl - remove

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: DirTemp.h - code style

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: Dir.h - implementation

* DirTemp-impl: DirTemp.h - comment(s)

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: DirTemp.cpp - implementation

* DirTemp-impl: Unit.cpp - implementation

Co-authored-by: Sergey Shevchenko <skynowa@fabrica.net.ua>

## Merge pull request #152 from skynowa/File-impl

- **Commit:** [06799db1e](https://github.com/skynowa/xLib/commit/06799db1e)
- **Author:** skynowa
- **Date:** 2020-08-24

File-impl

## Merge pull request #151 from skynowa/FileIO-impl

- **Commit:** [3ede04f9c](https://github.com/skynowa/xLib/commit/3ede04f9c)
- **Author:** skynowa
- **Date:** 2020-08-24

FileIO-impl

## Merge pull request #150 from skynowa/File-OpenMode-review

- **Commit:** [2d3bcf2fe](https://github.com/skynowa/xLib/commit/2d3bcf2fe)
- **Author:** skynowa
- **Date:** 2020-08-23

File-OpenMode-review

## Merged in File-buffering-review (pull request #9)

- **Commit:** [21dab6ae6](https://github.com/skynowa/xLib/commit/21dab6ae6)
- **Author:** skynowa
- **Date:** 2020-08-21

File-buffering-review


## Merged in FileInfo-impl (pull request #8)

- **Commit:** [13903af22](https://github.com/skynowa/xLib/commit/13903af22)
- **Author:** skynowa
- **Date:** 2020-08-20

FileInfo impl

* FileInfo-impl: File.cpp - fix

* FileInfo-impl: File.h - add todo(s)

* FileInfo-impl: File.h - review

* FileInfo-impl: Test_AutoProfiler.cpp - review

* FileInfo-impl: Test_File.cpp - test(s)

* FileInfo-impl: Test_File.cpp - test(s)

* FileInfo-impl: FileInfo.cpp - review

* FileInfo-impl: Test_File.cpp - review

* FileInfo-impl: File.h - review

* FileInfo-impl: Finder.h - review


## Merged in Cpp11-data-member-initializers (pull request #7)

- **Commit:** [a56e47c9e](https://github.com/skynowa/xLib/commit/a56e47c9e)
- **Author:** skynowa
- **Date:** 2018-10-01

Cpp11 data member initializers

Approved-by: skynowa <skynowa@gmail.com>


## Merged in cpp11-enums (pull request #6)

- **Commit:** [a02ed74db](https://github.com/skynowa/xLib/commit/a02ed74db)
- **Author:** skynowa
- **Date:** 2018-09-27

Cpp11 enums


## Merged in StdStreamV2 (pull request #2)

- **Commit:** [83db0e072](https://github.com/skynowa/xLib/commit/83db0e072)
- **Author:** skynowa
- **Date:** 2018-06-01

StdStreamV2

Approved-by: skynowa <skynowa@gmail.com>


## Merged in FsWatcher (pull request #5)

- **Commit:** [410b82c3a](https://github.com/skynowa/xLib/commit/410b82c3a)
- **Author:** skynowa
- **Date:** 2017-11-24

FsWatcher


## Merged in CurlClient (pull request #3)

- **Commit:** [59c19831e](https://github.com/skynowa/xLib/commit/59c19831e)
- **Author:** skynowa
- **Date:** 2017-11-16

CurlClient

