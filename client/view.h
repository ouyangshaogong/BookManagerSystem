
#include <list>
#include <string>

using namespace std;

struct NotifyView
{
    int nCmd;
};

class View;

void RegisterView(View *view);
//send data to view
void SendNotifyCation(int nMsg, void *pCommonData);

class View
{
public:

    virtual list<int> ReceiveMsg();
    virtual void HandleNotifyCation(NotifyView notifydata);

    //deal all other class send this class allowed receive msg
private:
    
    


};