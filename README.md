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
