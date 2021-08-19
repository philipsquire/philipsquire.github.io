#include "DHT.h" //Adds the libarary necessary for the humidity and temeperature sensor (DHT)
#include "U8glib.h" //This line adds the u8glib library to the code.
#define DHTPIN 2 // Specifies the DHT device's data cable is plugged into 2
#define DHTTYPE DHT11 // Specifies the model of the DHT device

U8GLIB_SH1106_128X64 u8g(8, 7, 6, 5, 4); //creates the object necessary for the OLED Screen, and specifies which ports it uses
DHT dht(DHTPIN, DHTTYPE); //Creates the object for the DHT device
int blue = 9; //pin numbers for the red, blue, and green components of the RBG LED
int green = 10;
int red = 11;
float h = 50; //Creates the default values for humidity and temperature
float t = 20; 
int concern_level = 0; //defaults the device to having no warning
String outputstring = ""; //initializes output text

void setup() {
  pinMode(red, OUTPUT); //Starts the connection between the Arudino and the RGB LED (each component is separate)
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600); //begins logging information to the computer
  dht.begin(); //begins monitoring the DHT device
}

void print_to_oled(String input_string) { //prints text to the OLED screen
  u8g.setFont(u8g_font_unifont); //Sets the font of the text
  u8g.setPrintPos(0, 20); //Sets the position of the text
  u8g.print(input_string); //Outputs text
}

//bool packet_loss(){  //checks for packet loss on the network
//  if (packets_dropped/packets > 0.03){ //if the percent of packets dropped is higher than 3%
//     return TRUE;} // return that there is packet loss
//  else{
//     return FALSE;} // return that there is not a significant amount of packet loss
//}
//

int CheckUp(float humidity, float temperature){ //routine check for humidity, temperature, 
  if ((temperature < 10) or (temperature > 28) ){
    Serial.print("There is a problem with temperature. Please take care of this issue immediately.");
    concern_level = 2;
  };
  if ((humidity > 60) or (humidity < 40)){
    Serial.print("There is an issue with humidity. Please take action immediately.");
    concern_level = 2;
  };
  //if (packet_loss()== true;){
  //  Serial.print(There may be packet loss occuring on the network. Please monitor network activity.)
  //  if (concern_level < 2){ 
  //      concern_level = 1
  //    }
  
  if (concern_level == 2){ //If the concern level is high
    digitalWrite(green, LOW); //turn off the green light 
    digitalWrite(red, HIGH); //power on the red light, creating a red light on the LED

  }
  else if (concern_level == 1){ //If the conern level is medium
    digitalWrite(green, HIGH); //Make the LED yellow by turning both the green and red light on
    digitalWrite(red, HIGH);
  }
  else{ //If everything is normal
    digitalWrite(green, HIGH); //Turn on the green light
    digitalWrite(red, LOW); //Turn off the red light
    concern_level = 0;
  };
  return concern_level; //Return concern level
  
}


void loop() {
  delay(5000); // Wait a few seconds between measurements
  h = dht.readHumidity();//Check humidity
  t = dht.readTemperature();//Check temperature
  int level = CheckUp(h,t);//See if it has a problem with either of those values (in addition to testing for packet loss and electrical problems
  String warning;//Creates an empty string to put the warning if necessary
  if (level > 0){
    warning = "\nPlease check warnings, and contact supervisor if applicable. After you have solved the error, please reboot this device."; //adds a warning message in case it detects at least one problem
  };
  outputstring = String("The current temperature is ") + String(round(t)) + String("°C and the humidity is ") + String(round(h)) + String("%.") + String(warning); //combines everything into one string
  u8g.firstPage(); //Start sending data to the screen
  do {
    print_to_oled(outputstring); //This calls the function "print_to_oled" which requires a string (the message you wanted printed) as the input.
      } while ( u8g.nextPage() ); //We need to put this in a while loop to allow the data to be fully transmitted without interruption.
}
