#include "ProxMoxer.hpp"


ProxMoxer::ProxMoxer(String UID, String Secret, String ServerAddr, int NodeCount = 10){
    this->UID = UID;
    this->Secret = Secret;
    this->ServerAddr = ServerAddr;
    this->MaxNodeCount = NodeCount;
    this->Nodes = new Node[MaxNodeCount];
     
}


void ProxMoxer::SetNodeParams(int InternalID,  int VMID, String NodeName = "pve"){
    this->Nodes[InternalID].VMID = VMID;
    this->Nodes[InternalID].NodeName = NodeName;
    this->NodeCount +=1;
}

void ProxMoxer::RebootAll(){
    NodeActionAll(REBOOT);
}

void ProxMoxer::ResumeAll(){
    NodeActionAll(RESUME);
}

void ProxMoxer::ResetAll(){
    NodeActionAll(RESET);
}

void ProxMoxer::ShutdownAll(){
    NodeActionAll(SHUTDOWN);
}

void ProxMoxer::StartAll(){
    NodeActionAll(START);
}

void ProxMoxer::SuspendAll(){
    NodeActionAll(SUSPPEND);
}

void ProxMoxer::RebootNode(int NodeID){
    NodeManagmentPOST(NodeID, REBOOT);
}
void ProxMoxer::ResumeNode(int NodeID){
    NodeManagmentPOST(NodeID, RESUME);
}
void ProxMoxer::ResetNode(int NodeID){
    NodeManagmentPOST(NodeID, RESET);
}   
void ProxMoxer::ShutdownNode(int NodeID){
    NodeManagmentPOST(NodeID, SHUTDOWN);
}
void ProxMoxer::StartNode(int NodeID){
    NodeManagmentPOST(NodeID, START);
}
void ProxMoxer::SuspendNode(int NodeID){
    NodeManagmentPOST(NodeID, SUSPPEND);
}


Node ProxMoxer::GetNodeState(int NodeId){
    return NodeManagmentGET(this->Nodes[NodeId].VMID);
}

Node ProxMoxer::NodeManagmentGET(int NodeID){
    Node Data;
    std::unique_ptr<BearSSL::WiFiClientSecure>Client(new BearSSL::WiFiClientSecure);
    Client->setInsecure();
    char Request[1024], Authorization[512];
    sprintf(Request, "%s%s%s%s%d%s%s", this->ServerAddr, this->FRequest, this->Nodes[NodeID].NodeName, this->SRequest, this->Nodes[NodeID].VMID, this->StatusCmd,  Commands[0][STATUS]);
    Http.begin(*Client, Request);
    delay(50);
    sprintf(Authorization, "%s%s%c%s", this->FAuthorization, this->UID, '=', this->Secret);
    Http.addHeader("Authorization", Authorization);
    int Return = Http.GET();
    
    if (Return>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(Return);
        this->ServerAnswer = Http.getString();
        Serial.println(this->ServerAnswer);
    }
    Http.end();

    return Data;
}

void ProxMoxer::NodeManagmentPOST(int NodeID, int Action){
    char Request[1024], Authorization[512];
    std::unique_ptr<BearSSL::WiFiClientSecure>Client(new BearSSL::WiFiClientSecure);
    Client->setInsecure();
    sprintf(Request, "%s%s%s%s%d%s%s", this->ServerAddr, this->FRequest, this->Nodes[NodeID].NodeName, this->SRequest, this->Nodes[NodeID].VMID, this->StatusCmd,  Commands[0][Action]);
    Http.begin(*Client, Request);
    delay(50);
    sprintf(Authorization, "%s%s%c%s", this->FAuthorization, this->UID, '=', this->Secret);
    Http.addHeader("Authorization", Authorization);
    int Return = Http.POST("");

    if (Return>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(Return);
        this->ServerAnswer = Http.getString();
        Serial.println(this->ServerAnswer);
    }
    Http.end();
}

void ProxMoxer::NodeActionAll(int Action){
    for(int i = 0; i < this->NodeCount; i++){
        NodeManagmentPOST(i, Action);
    }
}

void ProxMoxer::Update(){
    for (int i = 0; i < this->NodeCount; i++){
        NodeManagmentGET(this->Nodes[i].VMID);
    }
}

