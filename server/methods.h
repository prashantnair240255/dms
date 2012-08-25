/*
 *	methods.h
 */
void* TransactWithClient(void *);
void ServerSignalHandler();
void CleanExit(void*);
int DatabaseConnect();
void SocketConnect(char*[]);
int Command(const char *, ...);
void SigHandler(int);
void RequestMonitor(int);
void ViewMonitoringStatus(int);
void Exit();
int CheckStatus(char*);
char* ExtractFile(char [][200]);
void StartMonitor(char (*)[200],int,int);
int FileExists(char*,int);
void DisplayInotifyEvent(struct inotify_event *,char (*)[200]);
void MakeLogFiles(char [][200],int);
void WriteToLog(char p_cFilePath[][200]);
int FileIsFull(char *p_cPath,int nCount,char szFilePath[][200]);
void ClearAllFiles(char *p_cFile,char *p_cUser);
void CreateTable();
void ClientConnect();
