import serial

ser=serial.Serial()
ser.baudrate = 115200
#ser.port = '/dev/ttyUSB0'
ser.port = 'COM3'
ser.timeout = 3
ser.open()
print (ser)
print(ser.isOpen())

cmd = input("cmd:")
while cmd != 'q':
    if cmd == 'r':
        ser.write([0x31,0x0d])
    if cmd == 'l':
        ser.write([0x32,0x0d])
    if cmd == 'd':
        ser.write([0x33,0x0d])
    if cmd == 'u':
        ser.write([0x34,0x0d])
    cmd = input("cmd:")

ser.close()

print('end')
