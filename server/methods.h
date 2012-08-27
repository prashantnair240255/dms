/*
 *	methods.h
 */
void* TransactWithClient(void *);
void ServerSignalHandler();
void CleanExit(void*);
int DatabaseConnect();
void SocketConnect(char*[]);
int Command(const char *, ...);
void ReadFromConfig();
void SigHandler(int);
void RequestMonitor(int);
void ViewMonitoringStatus(int);
void Exit(void*);
int CheckStatus(char*);
char* ExtractFile(char [][200]);
void ConvertnWrite(int);
void StartMonitor(char (*)[200],int,int);
int FileExists(char*,int);
void DisplayInotifyEvent(struct inotify_event *,char (*)[200]);
void ReadFromFiles(int,int);
void FetchFromTable(int);
void MakeLogFiles(char [][200],int);
void WriteToLog(char p_cFilePath[][200]);
int FileIsFull(char *p_cPath,int nCount,char szFilePath[][200]);
void ClearAllFiles(char *p_cFile,char *p_cUser);
void CreateTable();
void ClientConnect();
