void* TransactWithClient(void *);
void ServerSignalHandler();
void CleanExit(void*);
int DatabaseConnect();
void SocketConnect(char*[]);
int Command(const char *, ...);
void SigHandler(int);
