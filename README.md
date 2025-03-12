# Wi-Fi Bunny

A tool to easily set up a evil twin attack system on vulnerable Wi-Fi networks.

Read the proposal: [proposal](./docs/proposal.txt)
Find some references here: [references](./docs/references.txt)

## Setup

## Theory

Wi-Fi works on these wireless security protocols, WPA, WPA2, WPA3 and WEP. The differences in between them is listed in this table below

![wireless security protocols table](./images/WEP-vs-WPA-vs-WPA2-vs-WPA3-2.png)

The SSID that we target (initially) is `iitmwifi`. This is protected by a WPA2-enterprise security protocol (enterprise implies every user needs to enter their LDAP or AD credentials).

![security protocol for IITM routers](./images/iitmwifi_security.png)