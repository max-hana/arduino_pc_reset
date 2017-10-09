/*
 * arduino_pc_reset
 * (C) Masa Hanada 2017
 */

int pin_RESET = 9;
int pin_POWER = 8;

char buf[32];

void setup() {
  // put your setup code here, to run once:
  pinMode(pin_RESET, OUTPUT);
  pinMode(pin_POWER, OUTPUT);

  Serial.begin(9600);


}

void printHelp(){
  Serial.println("? ...  help");
  Serial.println("----command-----------------");
  Serial.println("set RESET=1 ...  reset on");
  Serial.println("set RESET=0 ...  reset off");
  Serial.println("set RESET=* ...  reset on -(1 sec)- off");
  Serial.println("set POWER=1 ...  power on");
  Serial.println("set POWER=0 ...  power off");
  Serial.println("set POWER=* ...  power on -(10 sec)- off");
  Serial.println("----pinout------------------");
  Serial.println("arduino D9 ... RESET");
  Serial.println("arduino D8 ... POWER");
  Serial.println("----------------------------");
}

void processLine(){
  char *cmd;
  char *key;
  char *val;

  if('?'==buf[0])
  {
    printHelp();
    return;
  }

  cmd=strtok(buf, " ");
  key=strtok(NULL, "=");
  val=strtok(NULL, "\n;");
  if(cmd == NULL  || key == NULL || val == NULL){
    Serial.println("Error:001");
    return;
  }

//  Serial.println(cmd);
//  Serial.println(key);
//  Serial.println(val);

  if ( 0 == strcmp(cmd,"set")){
    if ( 0 == strcmp(key,"RESET")){
      if ( 0 == strcmp(val,"1")){
        digitalWrite(pin_RESET, HIGH);
        delay(500);
        Serial.println("OK");
      }else
      if ( 0 == strcmp(val,"0")){
        digitalWrite(pin_RESET, LOW);
        delay(500);
        Serial.println("OK");
      }else
      if ( 0 == strcmp(val,"*")){
        digitalWrite(pin_RESET, HIGH);
        delay(1000);
        digitalWrite(pin_RESET, LOW);
        Serial.println("OK");
      }
    }else
    if ( 0 == strcmp(key,"POWER")){
      if ( 0 == strcmp(val,"1")){
        digitalWrite(pin_POWER, HIGH);
        delay(500);
        Serial.println("OK");
      }else
      if ( 0 == strcmp(val,"0")){
        digitalWrite(pin_POWER, LOW);
        delay(500);
        Serial.println("OK");
      }else
      if ( 0 == strcmp(val,"*")){
        digitalWrite(pin_POWER, HIGH);
        delay(1000); // 1
        delay(1000); // 2
        delay(1000); // 3
        delay(1000); // 4
        delay(1000); // 5
        delay(1000); // 6
        delay(1000); // 7
        delay(1000); // 8
        delay(1000); // 9
        delay(1000); // 10
        digitalWrite(pin_POWER, LOW);
        Serial.println("OK");
      }
    }
  }
}

int buf_i = 0;

void loop() {
  static bool bLineDetected = false;

  if(bLineDetected){
    bLineDetected = false;
    processLine();
  }else
  while (Serial.available()){
    char c = Serial.read();
    buf[buf_i++] = c;
    if(buf_i >= sizeof(buf)-1) buf_i = 0;

    if(c == '\n' || c== ';'){ 
      buf[buf_i] = '\0';
      buf_i = 0;
      bLineDetected = true;
    }

  }
}
