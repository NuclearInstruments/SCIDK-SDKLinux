# SCIDK SDK for Linux

## Pre-requisites: Install FTDI driver
### Download driver from FTDI
- Download the driver package https://www.ftdichip.com/Drivers/D2XX.htm and unzip it
- Install driver in the system
``` 
sudo cp  /releases/build/lib*  /usr/local/lib
cd /usr/local/lib
sudo ln -s libftd2xx.so.1.4.8 libftd2xx.so 
sudo chmod 0755 libftd2xx.so.1.4.8
``` 

- Install udev rules
Enter in the folder udev of this repository
There are two files:    
    - 98-rpdev.rules
    - 99-rpdev.rules
``` 
sudo cp *.rules /etc/udev/rules.d/
udevadm control --reload-rules && udevadm trigger
``` 
## Compiling library and examples

### Compile and install library
Enter in SCIDK-SDK folder and compile with make:
``` 
make 
```
Install the library in /usr/local/lib
```
sudo make install
```

### RUN EXAMPLE - C
In the folder Linux you will find SciDKSDK_test

Run the example
``` 
./SciDKSDK_test
```
It will acquire data from the oscilloscope and will print a couple of value

### RUN EXAMPLE - PYTHON
Compile and install this library as explained above.

Run the example in pythonTest folder
``` 
pip install matplotlib 
python3 MyFirstProject_example.py
```
It will acquire data from the oscilloscope and will open a picture rappresenting the input signal


