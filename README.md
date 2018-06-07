# INetSyphon_RaspberryPi_SDK

Just Sample for RaspberryPi3 Jessie and Stretch

## Running the code
From a fresh sd card with raspbian lite installed, you will need to add the following :
```
sudo apt-get install git
sudo apt-get install libavahi-compat-libdnssd-dev
```
then clone this repo and build :
```
git clone https://github.com/z37soft/INetSyphon_RaspberryPi_SDK.git
cd INetSyphon_RaspberryPi_SDK/RaspberryPi3_Stretch
make
```

at the end, you will need to change the permissions and run it :
```
chmod +x TCPSClient.bin
cp TCPSClient.bin ~
```

## NOTE
- Current version supports to receive JPEG encode only. I recommend “TurboJPEG”.
- When you use -c option, then you can choose a server. usage; ./TCPSClient.bin -c 192.168.0.130 -p 7778, the software will try connecting to that addredd when it is disconnected.
- You can choose a network port, "-p port-number"
- Trim source area. default is whole area ( the same as "-s 0,0,1,1" )
> -s left(0),top(0),right(1),bottom(1)
- Change show position. default is fit screen ( the same as "-d 0,0,1920,1080" )
> -d x(0),y(0),width(1920),height(1080)
- When server closes session, then this software will quit.
- When image resolution is changed, then this software will refuse it.
- If you want to quit, then shoot CTRL+C
