// // // int in1 = 22;
// // // int in2 = 23;
// // // int ena = 5;

// // // void setup() {
// // //   pinMode(in1, OUTPUT);
// // //   pinMode(in2, OUTPUT);
// // //   pinMode(ena, OUTPUT);
// // // }

// // // void loop() {

// // //   analogWrite(ena, 200);

// // //   // forward
// // //   digitalWrite(in1, HIGH);
// // //   digitalWrite(in2, LOW);
// // //   delay(500);

// // //   // stop
// // //   digitalWrite(in1, LOW);
// // //   digitalWrite(in2, LOW);
// // //   delay(300);

// // //   // reverse
// // //   digitalWrite(in1, LOW);
// // //   digitalWrite(in2, HIGH);
// // //   delay(500);

// // //   // stop
// // //   digitalWrite(in1, LOW);
// // //   digitalWrite(in2, LOW);
// // //   delay(1000);
// // // }



// // int motors[5][3] = {
// //   {22,23,5},
// //   {24,25,6},
// //   {26,27,7},
// //   {28,29,8},
// //   {30,31,9}
// // };

// // void setup() {

// //   for(int i=0;i<5;i++){
// //     pinMode(motors[i][0], OUTPUT);
// //     pinMode(motors[i][1], OUTPUT);
// //     pinMode(motors[i][2], OUTPUT);
// //   }

// // }

// // void loop() {

// //   for(int i=0;i<5;i++){

// //     analogWrite(motors[i][2],180);

// //     digitalWrite(motors[i][0],HIGH);
// //     digitalWrite(motors[i][1],LOW);
// //     delay(300);

// //     digitalWrite(motors[i][0],LOW);
// //     digitalWrite(motors[i][1],LOW);
// //     delay(200);

// //     digitalWrite(motors[i][0],LOW);
// //     digitalWrite(motors[i][1],HIGH);
// //     delay(300);

// //     digitalWrite(motors[i][0],LOW);
// //     digitalWrite(motors[i][1],LOW);
// //     delay(800);
// //   }
// // }















// char command;

// void setup() {
//   Serial.begin(9600);

//   pinMode(22, OUTPUT);
//   pinMode(23, OUTPUT);
//   pinMode(5, OUTPUT);
// }

// void loop() {

//   if (Serial.available()) {

//     command = Serial.read();

//     if (command == 'L') {
//       analogWrite(5,180);
//       digitalWrite(22,HIGH);
//       digitalWrite(23,LOW);
//       delay(300);
//     }

//     if (command == 'R') {
//       analogWrite(5,180);
//       digitalWrite(22,LOW);
//       digitalWrite(23,HIGH);
//       delay(300);
//     }

//     digitalWrite(22,LOW);
//     digitalWrite(23,LOW);
//   }
// }





// char cmd;

// void setup() {

//   Serial.begin(9600);

//   pinMode(22, OUTPUT);
//   pinMode(23, OUTPUT);
//   pinMode(5, OUTPUT);

//   pinMode(24, OUTPUT);
//   pinMode(25, OUTPUT);
//   pinMode(6, OUTPUT);

//   pinMode(26, OUTPUT);
//   pinMode(27, OUTPUT);
//   pinMode(7, OUTPUT);

//   pinMode(28, OUTPUT);
//   pinMode(29, OUTPUT);
//   pinMode(8, OUTPUT);

//   pinMode(30, OUTPUT);
//   pinMode(31, OUTPUT);
//   pinMode(9, OUTPUT);
// }

// void stopMotor(int in1, int in2) {
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, LOW);
// }

// void moveMotor(int in1, int in2, int en, bool dir) {

//   analogWrite(en, 180);

//   if(dir){
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//   } else {
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);
//   }

//   delay(80);
//   stopMotor(in1, in2);
// }

// void loop() {

//   if(Serial.available()) {

//     cmd = Serial.read();

//     if(cmd == 'G') moveMotor(22,23,5,true);   // Gripper close
//     if(cmd == 'H') moveMotor(22,23,5,false);  // Gripper open

//     if(cmd == 'W') moveMotor(24,25,6,true);   // Wrist forward
//     if(cmd == 'Y') moveMotor(24,25,6,false);

//     if(cmd == 'S') moveMotor(26,27,7,true);   // Shoulder up
//     if(cmd == 'X') moveMotor(26,27,7,false);

//     if(cmd == 'E') moveMotor(28,29,8,true);   // Elbow forward
//     if(cmd == 'Z') moveMotor(28,29,8,false);

//     if(cmd == 'B') moveMotor(30,31,9,true);   // Base rotate left
//     if(cmd == 'N') moveMotor(30,31,9,false);

//   }
// }

// #define BASE_IN1 30
// #define BASE_IN2 31

// void setup()
// {
//   Serial.begin(9600);

//   pinMode(BASE_IN1, OUTPUT);
//   pinMode(BASE_IN2, OUTPUT);
// }

// void loop()
// {
//   if (Serial.available())
//   {
//     char cmd = Serial.read();

//     if (cmd == 'L')
//     {
//       digitalWrite(BASE_IN1, HIGH);
//       digitalWrite(BASE_IN2, LOW);
//     }

//     else if (cmd == 'R')
//     {
//       digitalWrite(BASE_IN1, LOW);
//       digitalWrite(BASE_IN2, HIGH);
//     }

//     else if (cmd == 'C')
//     {
//       digitalWrite(BASE_IN1, LOW);
//       digitalWrite(BASE_IN2, LOW);
//     }
//   }
// }




char cmd;

// Movement timing (tune later if needed)
#define BASE_DELAY 100
#define SHOULDER_DELAY 120
#define ELBOW_DELAY 110
#define WRIST_DELAY 90
#define GRIPPER_DELAY 200


void setup()
{
  Serial.begin(9600);

  // GRIPPER
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(5, OUTPUT);

  // WRIST
  pinMode(24, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(6, OUTPUT);

  // SHOULDER
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(7, OUTPUT);

  // ELBOW
  pinMode(28, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(8, OUTPUT);

  // BASE
  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(9, OUTPUT);
}


// MOTOR FUNCTION

void moveMotor(int in1, int in2, int en, int moveDelay, bool dir)
{
  analogWrite(en, 180);

  if(dir)
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  else
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }

  delay(moveDelay);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}


void loop()
{
  if(Serial.available())
  {
    cmd = Serial.read();


    // BASE
    if(cmd == 'B') moveMotor(30,31,9,BASE_DELAY,true);
    if(cmd == 'N') moveMotor(30,31,9,BASE_DELAY,false);
    if(cmd == 'C'){ digitalWrite(30,LOW); digitalWrite(31,LOW); }


    // SHOULDER
    if(cmd == 'S') moveMotor(26,27,7,SHOULDER_DELAY,true);
    if(cmd == 'X') moveMotor(26,27,7,SHOULDER_DELAY,false);
    if(cmd == 'D'){ digitalWrite(26,LOW); digitalWrite(27,LOW); }


    // ELBOW
    if(cmd == 'E') moveMotor(28,29,8,ELBOW_DELAY,true);
    if(cmd == 'Z') moveMotor(28,29,8,ELBOW_DELAY,false);
    if(cmd == 'F'){ digitalWrite(28,LOW); digitalWrite(29,LOW); }


    // WRIST
    if(cmd == 'W') moveMotor(24,25,6,WRIST_DELAY,true);
    if(cmd == 'Y') moveMotor(24,25,6,WRIST_DELAY,false);
    if(cmd == 'U'){ digitalWrite(24,LOW); digitalWrite(25,LOW); }


    // GRIPPER
    if(cmd == 'G') moveMotor(22,23,5,GRIPPER_DELAY,true);
    if(cmd == 'H') moveMotor(22,23,5,GRIPPER_DELAY,false);
  }
}

// char cmd;
// int motorSpeed = 180;


// // ===== MOTOR FUNCTIONS =====

// void moveMotor(int in1, int in2, int en, bool dir)
// {
//   analogWrite(en, motorSpeed);

//   if(dir)
//   {
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//   }
//   else
//   {
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);
//   }
// }

// void stopMotor(int in1, int in2)
// {
//   digitalWrite(in1, LOW);
//   digitalWrite(in2, LOW);
// }


// // ===== SETUP =====

// void setup()
// {
//   Serial.begin(9600);

//   // Gripper
//   pinMode(22, OUTPUT);
//   pinMode(23, OUTPUT);
//   pinMode(5, OUTPUT);

//   // Wrist
//   pinMode(24, OUTPUT);
//   pinMode(25, OUTPUT);
//   pinMode(6, OUTPUT);

//   // Shoulder
//   pinMode(26, OUTPUT);
//   pinMode(27, OUTPUT);
//   pinMode(7, OUTPUT);

//   // Elbow
//   pinMode(28, OUTPUT);
//   pinMode(29, OUTPUT);
//   pinMode(8, OUTPUT);

//   // Base
//   pinMode(30, OUTPUT);
//   pinMode(31, OUTPUT);
//   pinMode(9, OUTPUT);
// }


// // ===== LOOP =====

// void loop()
// {
//   if(Serial.available())
//   {
//     cmd = Serial.read();

//     // BASE
//     if(cmd == 'B') moveMotor(30,31,9,true);
//     if(cmd == 'N') moveMotor(30,31,9,false);
//     if(cmd == 'C') stopMotor(30,31);

//     // SHOULDER
//     if(cmd == 'S') moveMotor(26,27,7,true);
//     if(cmd == 'X') moveMotor(26,27,7,false);
//     if(cmd == 'D') stopMotor(26,27);

//     // ELBOW
//     if(cmd == 'E') moveMotor(28,29,8,true);
//     if(cmd == 'Z') moveMotor(28,29,8,false);
//     if(cmd == 'F') stopMotor(28,29);

//     // WRIST
//     if(cmd == 'W') moveMotor(24,25,6,true);
//     if(cmd == 'Y') moveMotor(24,25,6,false);
//     if(cmd == 'U') stopMotor(24,25);

//     // GRIPPER
//     if(cmd == 'G') moveMotor(22,23,5,true);
//     if(cmd == 'H') moveMotor(22,23,5,false);
//     if(cmd == 'I') stopMotor(22,23);   // NEW STOP COMMAND

//     // SPEED CONTROL
//     if(cmd >= '0' && cmd <= '9')
//     {
//       motorSpeed = map(cmd - '0', 0, 9, 80, 255);
//     }
//   }
// }