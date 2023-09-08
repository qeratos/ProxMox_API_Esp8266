# ProxMox_API_Esp8266


## Description
This project aimed to interaction between ESP8266 And ProxMox virtualization environment. 
Here used main API of ProxMox [Documentation](https://pve.proxmox.com/pve-docs/api-viewer/index.html).

## How to use
1. You need to create ProxMox User for your device.
2. Generate API secret key and API-Username.
3. Download this code and copy to your project directory.
4. Install Aditional libraries from Library Manager in ArduinoIDE. You also can install them manualy.


## Dependences
1. [ESP8266HTTPClient](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266HTTPClient)
2. [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
3. [Arduino_JSON](https://github.com/arduino-libraries/Arduino_JSON)


## Installation 
1. Download repo to your PC.
2. Unzip it to your work directory.
3. Include file in your code.


## Example
```CPP
#include "ProxMoxer.hpp"  // Include library class
#define MachinesCount 2
ProxMoxer proxmox("ESP API-USername", "API-Secret-key", "https://ProxMoxIP:8006", MachinesCount);  
/*
* Create a server object at "https://ProxMoxIP:8006"
* With the generated API key "API-Secret-key" and API-Username "ESP API-USername"
* Machines quantity equal to 2
*/

void setup(){
  proxmox.SetNodeParams(0, 100, "pve"); // Set parameters for the machine with ID 100: node name "pve" and serial number 0 for access to machine from the library
}

void loop(){
  proxmox.GetNodeState(0); // Recieve status data from current node. Returned object of  Node structure
}
```

### Node Structure example
```CPP
struct Node{
    int VMID = 100;          // Machine ID 
    String NodeName = "pve"; // Node name
    String MachineName = "", // Machine name 
            Tags = "";       // Different tags
    int OSType = 0,          // OS type
        Status = 0,          // Status
        PID = 0,             // Machine PID
        CPU = 0,             // CPU count
        DISK = 0,            // Disk space
        MEM = 0;             // Ram space
};
```

## Creating API User and Key 

### 1. Goto Datacenter tab. Next to Permissions and to Users
<p>
  <img  src="https://github.com/younDev1/ProxMox_API_Esp8266/blob/main/img/screen1.png"  width="350" alt="Users Tab"/>
</p>


### 2. Create new user for api. It better than use your root for all activities.
<p>
  <img  src="https://github.com/younDev1/ProxMox_API_Esp8266/blob/main/img/screen2.png"  width="350" alt="Users Tab"/>
</p>
- Give user name and other setting like in screenshoot.


### 3. Create Token. It must be your secret key.
<p>
  <img  src="https://github.com/younDev1/ProxMox_API_Esp8266/blob/main/img/screen3.png"  width="350" alt="Users Tab"/>
</p>
- Move to `API Tokens` tab. Select user which you create and give it ID.
- You must write it somwhere because you not be able to see it again.

### 4. Add token permissions.
<p>
  <img  src="https://github.com/younDev1/ProxMox_API_Esp8266/blob/main/img/screen4.png"  width="350" alt="Users Tab"/>
</p>
- For all activites which this library gives you, select administrator role for this API token.