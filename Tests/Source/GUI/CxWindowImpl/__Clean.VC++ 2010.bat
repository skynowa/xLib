del *.obj;*.ilk;*.tlb;*.tli;*.tlh;*.tmp;*.rsp;*.pgc;*.pgd;*.plg;*.ncb;*.suo;*.opt;*.user;*.meta;*.pch;*.pdb;*.idb;*.manifest;*.exp;*.lib;*.res;*.dep;*.aps; /f /s /q
del *.cdf;*.cache;*.obj;*.ilk;*.resources;*.tlb;*.tli;*.tlh;*.tmp;*.rsp;*.pgc;*.pgd;*.meta;*.tlog;*.manifest;*.res;*.pch;*.exp;*.idb;*.rep;*.xdc;*.pdb;*_manifest.rc;*.bsc;*.sbr;*.xml;*.sdf;  /f /s /q
del UpgradeLog.XML;*.sln.old;*.vcproj.old; /f /s /q

rd /s /q ipch
rd /s /q Debug
rd /s /q Release