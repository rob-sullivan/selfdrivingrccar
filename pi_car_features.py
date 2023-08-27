class Car:
    def __init__(self):
        self.motor1 = AF_DCMotor(1)
        self.motor2 = AF_DCMotor(2)
        self.speed = 150

    def move_forward(self):
        self.motor1.setSpeed(self.speed)
        self.motor1.run(FORWARD)
        self.motor2.setSpeed(self.speed)
        self.motor2.run(FORWARD)

    def move_backward(self):
        self.motor1.setSpeed(self.speed)
        self.motor1.run(BACKWARD)
        self.motor2.setSpeed(self.speed)
        self.motor2.run(BACKWARD)

    def turn_left(self):
        self.motor1.setSpeed(self.speed)
        self.motor1.run(BACKWARD)
        self.motor2.setSpeed(self.speed)
        self.motor2.run(FORWARD)

    def turn_right(self):
        self.motor1.setSpeed(self.speed)
        self.motor1.run(FORWARD)
        self.motor2.setSpeed(self.speed)
        self.motor2.run(BACKWARD)

    def stop(self):
        self.motor1.run(RELEASE)
        self.motor2.run(RELEASE)

    def setSpeed(self, speed):
        self.speed = speed
