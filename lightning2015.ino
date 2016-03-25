/* File:    lightning2015.ino
 * By:      Jean René Clemenceau
 * Created: 10/21/2015
 * Controls lightning for storm cloud costume
*/

//LIGHT SETTING CONSTANTS
const int LIGHT_NUMBER = 3;   //Number of different light strips
const int PATH_NUMBER = 7;    //Number of different lightning paths
int LIGHT_PIN[] = {13,12,11}; //Array of pins where light strips are
int LIGHTNING_PATHS[7][3]={   //Array describing paths (referencing LIgHT_PIN order)
  {0,0},
  {1,1},
  {2,2},
  {0,1},
  {0,2},
  {0,1},
  {0,2} 
};


//TIMING CONSTANTS
const int PRESHOOT_DELAY = 35;    //Blinking interval during lightning pre-shot ( High and Low)
const int SHOOT_DELAY = 50;       //Time first segment of lighning path is ON
const int SHOOT_FINAL = 100;      //Time second segment of lighning path is ON
const int MIN_INTERVAL = 5000;    //Minimum time between lightning shoots
const int MAX_INTERVAL = 60000;   //Maximum time between lightning shoots


void setup() {
  //Initialize pins
  for(int i=0; i<LIGHT_NUMBER; i++){
    pinMode(LIGHT_PIN[i], OUTPUT);
  }
}

void loop() {
  //Select and deploy random path
  int new_path = random(0,PATH_NUMBER);
  deploy(new_path);


  //Set Random delay for next lightning
  int next_lightning = random(MIN_INTERVAL, MAX_INTERVAL);
  delay(next_lightning);
}

//Activates lightning
void deploy(int path_num){
  int pin_one = LIGHT_PIN[ LIGHTNING_PATHS[path_num][0] ];
  int pin_two = LIGHT_PIN[ LIGHTNING_PATHS[path_num][1] ];

  //Set number of strobe blinks
  int timer = 200 / PRESHOOT_DELAY;

  //pre-shoot pin one (strobe effect)
  for(int i=0; i<timer; i++){
    digitalWrite(pin_one,HIGH);
    delay(PRESHOOT_DELAY);
    digitalWrite(pin_one,LOW);
    delay(PRESHOOT_DELAY);
  }

  //SHOOT pin one
  digitalWrite(pin_one, HIGH);
  delay(SHOOT_DELAY);

  //Shoot pin two
  digitalWrite(pin_two, HIGH);
  delay(SHOOT_FINAL);

  //End Lightning
  digitalWrite(pin_one,LOW);
  digitalWrite(pin_two,LOW);
  
  return;
}
