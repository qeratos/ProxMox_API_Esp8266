#include "ProxMoxer.hpp"

ProxMoxer proxmox("esp32@pve!ESAP", "3440157a-0410-472d-b63d-3413cbc54879", "https://192.168.31.178:8006", 2);

void setup(){
  proxmox.SetNodeParams(0, 100, "pve");
  proxmox.SetNodeParams(1, 101, "pve");
}

void loop(){
  proxmox.GetNodeState(0);
  proxmox.GetNodeState(1);
}