import serial
import time

# configure the serial port
ser = serial.Serial('/dev/ttyACM0', 9600) # replace '/dev/cu.usbmodem1301' with the name of your serial port

print("Available Inputs: ''S  = Stop, 'F' = Forward, 'B' = Backwards, 'L' = Turn Left, 'R' = Turn Right, 'SP 100' = Set Speed to 100 (Max 255)")

# Loop indefinitely
while True:
    # Prompt the user for a command
    command = input("Enter a command ('Q' to quit): ")

    # Send the command to the Arduino
    ser.write(command.encode())

    # If the user enters 'Q', exit the loop
    if command.upper() == 'Q':
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
