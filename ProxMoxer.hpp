#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

#define START 0
#define RESET 1
#define REBOOT 2
#define RESUME 3
#define STATUS 6
#define SHUTDOWN 4
#define SUSPPEND 5

struct Node{
            int VMID = 100;
            String NodeName = "pve";
            String MachineName = "",
                    Tags = "";
            int OSType = 0,
                Status = 0,
                PID = 0,
                CPU = 0,
                DISK = 0,
                MEM = 0;
};

class ProxMoxer{
    public:
        ProxMoxer(String UID, String Secret, String ServerAddr, int NodeCount);
        void SetNodeParams(int InternalID,  int VMID, String NodeName);

        Node GetNodeState(int NodeId);

        //Control Functions
        void RebootNode(int NodeID);
        void ResumeNode(int NodeID);
        void ResetNode(int NodeID);
        void ShutdownNode(int NodeID);
        void StartNode(int NodeID);
        void SuspendNode(int NodeID);

        void RebootAll();
        void ResumeAll();
        void ResetAll();
        void ShutdownAll();
        void StartAll();
        void SuspendAll();

        //Update Method
        void Update();

    private:
        void NodeActionAll(int Action);
        Node NodeManagmentGET(int NodeID);
        void NodeManagmentPOST(int NodeID, int Action);
        void UpdateCurrentNode(int NodeID);
        void PrepareMessage();

        HTTPClient Http;

        // /api2/json/nodes/pve/qemu/101/status/start
        const char* FRequest = "/api2/json/nodes/",
                *SRequest = "qemu/",
                *StatusCmd = "/status/",
                *FAuthorization = "PVEAPIToken=";

        const char *Commands[1][7] = {"start",
                                     "reset",
                                     "reboot",
                                     "resume",
                                     "shutdown",
                                     "suspend",
                                     "current"};

        int NodeCount = 0, MaxNodeCount = 0;
        String ServerAnswer = "";
        Node *Nodes = NULL;
        String Secret = "",
                UID = "",
                ServerAddr = "";
};