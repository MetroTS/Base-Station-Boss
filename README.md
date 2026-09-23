# Base Station Boss!
A tiny, invisible SteamVR plugin that turns your Lighthouse base stations on when SteamVR starts and puts them to sleep when it closes — for **any** headset.

## Why?
SteamVR can power base stations on and off automatically, but it sends those commands through the Bluetooth radio built into Valve and HTC headsets. Headsets without that radio — inside-out headsets used with Lighthouse controllers/trackers (PSVR2, WMR, Quest via Link/Virtual Desktop) or other Lighthouse headsets — never get this feature.

Base Station Boss does the same job using your PC's Bluetooth adapter. It runs inside SteamVR as a driver, shows up nowhere as a device, and is configured from the SteamVR settings menu.


## Requirements

- Windows 10/11 or Linux
- SteamVR
- A Bluetooth LE adapter in range of your base stations
- Lighthouse base stations 1.0 and/or 2.0

## Supported Hardware
| Base Station | Status | Modes | ID Readout required? |
| - | - | - | - |
| Base Station 2.0 | planned | - | x |
| Base Station 1.0 | ✓ | Wake/Sleep | x


## Initial Setup

### Git Clone the Repository




## SteamVR overview

-



## Troubleshooting
The included CLI Tool can verify that the Processes for Reading Protocol, assembling Commands and Bluetooth work correctly. If so you encounter any problems you can test via running the individual scripts.

## Credits

Bluetooth protocol details based on the work of the Lighthouse community, including
[lighthouse-manager](https://github.com/atomicflag/lighthouse-manager) and
[VRBS_Power_Control](https://github.com/MissingNO123/VRBS_Power_Control).

## License

MIT - see [LICENSE](LICENSE)