#include <M5Core2.h>
#include <M5Touch.h>
#include <M5Display.h>

//defining colors
#define orange 0xFC64
#define dark 0x02F3
#define darkOrange 0xC18A
#define red 0xFC7F
#define purple 0xC18A
#define light 0xCF3E

//progress bar variables
#define hb 10
int wb = 1;
int xb = 10, yb = 68;
int norm=100;
int bvar=20;
int numwb=0;
//step counter vars
int step = 0;
float total = 0;
int ctr = 0;
float avg = 1.1;
float width = avg / 10;
bool state = 0, prevState=0;
//bmi and calories vars
int height = 160;
int weight = 50;
double weightlbs = 0;
double cal = 0, calperstep = 0;

//BMI calculator function
void bmicalc()
{
  //drawing the back button
  M5.Lcd.clear(darkOrange);
  M5.Lcd.fillRect(80, 190, 160, 50, RED);
  M5.Lcd.drawRect(80, 190, 160, 50, WHITE);
  M5.Lcd.setCursor(110, 201);
  M5.Lcd.setTextSize(4);
  M5.Lcd.printf("BACK");
  //getting coordinates of the touchpoint
  TouchPoint_t m = M5.Touch.getPressPoint();
  int xm = m.x;
  int ym = m.y;
  //entering the loop
  //while back button is not pressed, the following executes:
  while (!(xm>80 && xm < 240 && ym > 190 && ym <250))
  {  
    //once again drawing the back button
  M5.Lcd.fillRect(80, 190, 160, 50, RED);
  M5.Lcd.drawRect(80, 190, 160, 50, WHITE);
  M5.Lcd.setCursor(110, 201);
  M5.Lcd.setTextSize(4);
  M5.Lcd.printf("BACK");
  //getting coordinates of the touchpoint
  TouchPoint_t m = M5.Touch.getPressPoint();
  int xm = m.x;
  int ym = m.y;
  //printing text
    M5.Lcd.setTextSize (2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("Body Mass Index Calculator");

    M5.Lcd.setTextSize (2);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(20, 20);
    M5.Lcd.print("Enter the details:");

    //drawing buttons for regulating height
    M5.Lcd.fillRect(90, 60, 35, 35, RED);
    M5.Lcd.drawRect(90, 60, 35, 35, WHITE);
    M5.Lcd.setTextSize (3);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(97, 67);
    M5.Lcd.print("<");
    M5.Lcd.fillRect(180, 60, 35, 35, RED);
    M5.Lcd.drawRect(180, 60, 35, 35, WHITE);
    M5.Lcd.setTextSize (3);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(192, 67);
    M5.Lcd.print(">");
    M5.Lcd.setTextSize (2);
    //getting coordinates of the touchpoint
    m = M5.Touch.getPressPoint();
    xm = m.x;
    ym = m.y;  
    //if "<" button is pressed, decrement height
    if (height>1 && xm>90 && xm<125 && ym>60 && ym<95)
    {
      height = height - 1;      
    }
    //if ">" button is pressed, increment height
    if (height<300 && xm>180 && xm<215 && ym>60 && ym<95)
    {
      height = height + 1;      
    }
    //displaying height
    M5.Lcd.setCursor(0, 40);
    M5.Lcd.print("Your height (in cm):");
    M5.Lcd.fillRect(130, 63, 40, 35, darkOrange);
    M5.Lcd.setCursor(110, 70);
    M5.Lcd.printf("%5d", height);

    //drawing buttons for regulating weight
    M5.Lcd.fillRect(90, 120, 35, 35, RED);
    M5.Lcd.drawRect(90, 120, 35, 35, WHITE);
    M5.Lcd.setTextSize (3);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(97, 127);
    M5.Lcd.print("<");
    M5.Lcd.fillRect(180, 120, 35, 35, RED);
    M5.Lcd.drawRect(180, 120, 35, 35, WHITE);
    M5.Lcd.setTextSize (3);
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(192, 127);
    M5.Lcd.print(">");
    M5.Lcd.setTextSize (2);
    //getting coordinates of the touchpoint
    m = M5.Touch.getPressPoint();
    xm = m.x;
    ym = m.y;  
    //if "<" button is pressed, decrement weight
    if (weight>1 && xm>90 && xm<125 && ym>120 && ym<155)
    {
      weight = weight - 1;      
    }
    //if ">" button is pressed, increment weight
    if (weight<200 && xm>180 && xm<215 && ym>120 && ym<155)
    {
      weight = weight + 1;      
    }
    //printing weight
    M5.Lcd.setCursor(0, 100);
    M5.Lcd.print("Your weight (in kg):");
    M5.Lcd.fillRect(130, 123, 40, 35, darkOrange);
    M5.Lcd.setCursor(105, 130);
    M5.Lcd.printf("%5d", weight);
    
    //calculating bmi
    double heightsquare = (double) height*height/10000;
    double bmi = (double) weight/heightsquare;

    //displaying BMI
    M5.Lcd.fillRect(0, 159, 300, 25, darkOrange);
    if (bmi < 18.5)
    {
      M5.Lcd.setCursor(0, 160);
      M5.Lcd.printf("BMI=%.1f (Underweight)", bmi);
    }

    else if (bmi > 25)
    {
      M5.Lcd.setCursor(0, 160);
      M5.Lcd.printf("BMI=%.1f (Overweight)", bmi);
    }

    else
    {
      M5.Lcd.setCursor(0, 160);
      M5.Lcd.printf("BMI=%.1f (Normal range)", bmi);
    }
    //getting coordinates of the touchpoint
    m = M5.Touch.getPressPoint();
    xm = m.x;
    ym = m.y;

    //if back button is pressed, break the loop
    if (xm>80 && xm < 240 && ym > 190 && ym <250)
      break;    
    delay(50);
  }
  //clearing the screen
  M5.Lcd.clear(orange); 
  //printing progress bar
  M5.Lcd.fillRect(10, yb, wb*numwb, hb, GREEN); 
}

void setup() {
//setup code
M5.begin();
M5.IMU.Init();
//printing initial text
M5.Lcd.fillScreen (purple);
M5.Lcd.setTextColor(WHITE);
M5.Lcd.setTextSize (4);
M5.Lcd.setTextDatum(MC_DATUM);
M5.Lcd.setCursor(10, 85);
M5.Lcd.print ("FITNESS TOOL");
delay (3000);
//clearing the screen
M5.Lcd.clear(orange);
}

void loop() {
  //main code
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(0,0);
  float accX = 0;
  float accY = 0;
  float accZ = 0;

  // Get acceleration
  M5.IMU.getAccelData(&accX, &accY, &accZ);
  float accel = sqrt(accX * accX + accY * accY + accZ * accZ);

  // Calibrating for average acceleration
  if (ctr < 100) {
    total += accel;
    ctr += 1;
  } else {
    avg = total / ctr;
    width = avg / 6;
    total = avg;
    ctr = 1;
  }

  //if current acceleration is more than average + some width
  if (accel > avg + width) {
    state = true;
  } else if (accel < avg - width) {
    state = false;
  }

  //printing text for progress bar
    M5.Lcd.setCursor(0, 35);
    M5.Lcd.setTextSize(3);
    M5.Lcd.printf("Today's progress:");
    M5.Lcd.drawRect(10, 68, 240, hb, BLACK);
  //Increment step
  if (!prevState && state)
  {
    step = step + 1;
    //calculating calories
    weightlbs = (double) weight/2.2;
    calperstep = 0.57*weightlbs/2200;
    cal = calperstep*step;
  //progress bar code
  if ((xb<235)&&(step%bvar==0))
  {
    M5.Lcd.fillRect(xb, yb, wb, hb, GREEN);
    xb=xb+wb;
    numwb++;
  }
  }
  
  prevState = state;
     //Displaying step
     M5.Lcd.setTextSize (4);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Step: ");
    M5.Lcd.fillRect(115, 0, 150, 38, orange);
    M5.Lcd.setCursor(110, 0);
    M5.Lcd.printf("%5d", step);

//getting coordinates of the touchpoint
TouchPoint_t p = M5.Touch.getPressPoint();
int xp = p.x;
int yp = p.y;
//drawing bmi calculator button
M5.Lcd.fillRect(80, 150, 160, 50, RED);
M5.Lcd.drawRect(80, 150, 160, 50, WHITE);
M5.Lcd.setCursor(150, 154);
M5.Lcd.setTextSize(2);
M5.Lcd.printf("BMI");
M5.Lcd.setCursor(110, 174);
M5.Lcd.printf("CALCULATOR");
//if the button is pressed, bmi calculator function is executed
  if (xp>80 && xp < 240 && yp > 150 && yp <200)
  {
    bmicalc();
  }
  
  //display the calories
  M5.Lcd.fillRect(0, 109, 200, 34, orange);  
  M5.Lcd.setCursor(0, 85);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Calories burned:");
  M5.Lcd.setCursor(0, 110);
  M5.Lcd.printf("%.3f", cal);

  delay(50);
}