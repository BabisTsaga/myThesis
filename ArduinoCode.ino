#include <SoftwareSerial.h>//Δήλωση της βιβλιοθήκης του bluetooth
#include <AFMotor.h>//Δήλωση της βιβλιοθήκης των κινητήρων.


//Εγκαθίδρυση την σύνδεσης του bluetooth με την πλακέτα Arduino.
//Δήλωση των pins που χρησημοποιούντε για την 
SoftwareSerial btSerial(A3, A5); // RX, TX

//Δήλωση του κάθε κινητήρα ξεχωριστά.
//Motor objects
AF_DCMotor motor1(1, MOTOR12_8KHZ);//Back right
AF_DCMotor motor2(2, MOTOR12_8KHZ);//Front right
AF_DCMotor motor3(3, MOTOR12_8KHZ);//Front left
AF_DCMotor motor4(4, MOTOR12_8KHZ);//Back left

//Χρησημοποιέιτε η μέγιστη ταχύτητα σε κάθε κινητήτα
int Speeed = 255;
//Μεταβλητές για την καθυστέρηση κινήσεων του ρομπότ
int stepTime = 2000; //Time for each step in ms


void setup()
{

  // Open serial communications and wait for port to open
  //Εγκαθίδρυση της σεριακής επικοινωνίας και αναμονή εώς ότου συνδεθεί με κάποιο port.
  Serial.begin(9600);
  btSerial.begin(9600);
  btSerial.listen();
  //Ρύθμιση της ταχύτητας των κινητήρων.
  motor1.setSpeed(Speeed);
  motor2.setSpeed(Speeed);
  motor3.setSpeed(Speeed);
  motor4.setSpeed(Speeed);
  //Σταμάτημα όλως των κινητήρων
  Stop();


  //ΝΑ ΦΥΓΟΥΝ
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(5000);
  Stop();
  //ΝΑ ΦΥΓΟΥΝ


  
}
void loop() {
  Serial.print(".");
  //Η συσκεύη του Arduino δέχεται δεδομένα που αποστέλοντε απο τον υπολογιστή στο bluetooth
  while (btSerial.available())
  {
    //Δεχόμαστε ένα byte κάθε φορά.
    //Δηλαδή αριθμούς απο το 0 εως το 255
    byte code = btSerial.read();//Με την εντολή read() επιστρέφει το byte που μόλις έφθασε.    
    //Κάθε δεκαεξαδικός αριθμός ισούται με τον αριθμό που στέλνεται απο τα σύμβολα.
    //Forward step
    if (code == 0x1F) { //31
      ForwardStep(stepTime);
    }
    //Backward step
    if (code == 0x5D) { //93
      BackwardStep(stepTime);
    }
    //Left step
    if (code == 0x37) { //55
      LeftStep(stepTime);
    }
    //Right step
    if (code == 0x3B) { //59
      RightStep(stepTime);
    }

    ///***Allagi ta codes
    
    //Stop
    if (code == 0x57) { //87
      Stop();             
    }
    //Forward movement
    if (code == 0x5B) { //91
      Forward();        
    }
    //Backward movement
    if (code == 0x3D) { //61
      Backward();        
    }
    //Left movement
    if (code == 0x4F) { //79
      Left();      
    }
    //Right movement
    if (code == 0x67) { //103
      Right();        
    }


//Ένα απο τα σύμβολα χρησημοποιείτε για την ομαλή λειτουργία των κινήσεων του ρομπότ.
    if(code == 0x6D){ // 109
      delay(2000);        // 2s Delay
    }

    
  }

}



//function για λειτουργία του ρομπότ προς τα εμπρός.
void Forward()
{
  //Ρύθμιση να πηγένουν εμπρός όλοι οι κινητήρες.
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
//function για λειτουργία του ρομπότ να πηγένει προς τα εμπρός για ένα 1s.
void ForwardStep(int time_ms){
  Forward();          //Start moving forward
  delay(time_ms);    //Delay stepTime in ms
  Stop();             //Stop the movement
}
//function για λειτουργία του ρομπότ προς τα πίσω.
void Backward()
{
    //Ρύθμιση να πηγένουν πίσω όλοι οι κινητήρες.
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
//function για λειτουργία του ρομπότ να πηγένει προς τα πίσω για ένα 1s.
void BackwardStep(int time_ms){
  Backward();          //Start moving forward
  delay(time_ms);    //Delay stepTime in ms
  Stop();             //Stop the movement
}
//function για λειτουργία του ρομπότ να στρίβει δεξία  90 μοίρες.
void Right()
{
  //Ρύθμιση να πηγένουν 2 κινήτηρες εμπρός και 2 πίσω
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
//function για λειτουργία του ρομπότ να πηγένει στρίβει δεξία  90 μοίρες για 1s.
void RightStep(int time_ms){
  Right();          //Start moving forward
  delay(time_ms);    //Delay stepTime in ms
  Stop();             //Stop the movement
}
//function για λειτουργία του ρομπότ να  στρίβει αριστερά  90 μοίρες.
void Left()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
//function για λειτουργία του ρομπότ να  στρίβει αριστερά  90 μοίρες για 1s.
void LeftStep(int time_ms){
  Left();          //Start moving forward
  delay(time_ms);    //Delay stepTime in ms
  Stop();             //Stop the movement
}
//function για να σταματήσει το ρομπότ.
void Stop()
{
 //Σταματάνε όλοι οι κινητήρες.
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
