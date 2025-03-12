## ESP32 setup

We will be using ESP-IDFv4.1 (an older version) for the initial part of this project. This will not help us in sending the frames but it provides a good starting point and there is no issues with reinventing the wheel for a while.

### Install ESP-IDFv4.1

```bash
git clone -b v4.1 --recursive https://github.com/espressif/esp-idf.git
```

Then,

```bash
cd ./esp-idf && ./install.sh esp32
```

```sh
. ./export.sh
```

### Building and flashing

To flash your code into the ESP32, follow these steps

1. Create a project directory
2. Create a `main.c` file inside a `main` directory
3. Use `idf.py set-target esp32` to configure ESP-IDF for ESP32s.
4. Use `idf.py build` to build the project. This creates a `.elf` file as well.
5. To flash the code, use this command

```sh
idf.py -p /dev/ttyUSB0 flash
```

> [!NOTE]
> You might have to change the USB port depending on your computer.

To add your username to the dialout and give it the right permissions run the below command.

```sh
sudo adduser <your-username> dialout && sudo chmod a+rx /dev/<connected-usb-port>
```

6. After flashing, you can monitor and read serial logs using the following command

```bash
idf.py -p /dev/ttyUSB0 monitor
```