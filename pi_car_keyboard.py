import serial
import time
import sys
import tty
import termios

# configure the serial port
ser = serial.Serial('/dev/ttyACM0', 9600) # replace '/dev/ttyACM0' with the name of your serial port

# Define the function to read a single key from the terminal
def getch():
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        ch = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return ch

# Loop indefinitely
while True:
    # Read the keyboard input
    key = getch()

    # Send the corresponding command to the Arduino based on the key pressed
    if key == '^[[A': # Up arrow
        ser.write('F'.encode())
    elif key == '^[[B': # Down arrow
        ser.write('B'.encode())
    elif key == '^[[C': # Right arrow
        ser.write('R'.encode())
    elif key == '^[[D': # Left arrow
        ser.write('L'.encode())
    else:
        # Stop the motors if any other key is pressed
        ser.write('S'.encode())

    # If the user enters 'Q', exit the loop
    if key.upper() == 'Q':
        break

    # Wait for the Arduino to respond
    while ser.inWaiting() == 0:
        pass

    # Read the response from the Arduino
    response = ser.readline().decode().strip()

    # Print the response
    print("Arduino received command:", response)

# Close the serial port
ser.close()
