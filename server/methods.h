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
void StartMonitor(char (*)[200],int,int);
int FileExists(char*,int);
void DisplayInotifyEvent(struct inotify_event *,char (*)[200]);
void MakeLogFiles(char [][200],int);
