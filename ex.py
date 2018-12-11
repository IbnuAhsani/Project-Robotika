import serial

ser1 = serial.Serial('COM7', 9600)

t = 0

while t<8000:

#   # if(t%10 == 0):
#   if t >= 0 and t <= 3000:
#     ser1.write('1'.encode())
#   elif t >= 3001 and t <= 5000:
#     ser1.write('0'.encode())
#   else:
#     ser1.write('2'.encode())
#   print(t)
    t += 1
    ser1.write('0'.encode())
print("donez")
