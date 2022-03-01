#include "myRemote.h"
#include "myDefinitions.h"


remoteControlClass::remoteControlClass() : ps2() , Pan(), Tilt()
{
    XValue = 90;
    YValue = 90;
    pan = 120;
    tilt = 90;  
    newData = false;
    encoderBool = false;
    pinMode(PanPin, OUTPUT);
    pinMode(TiltPin, OUTPUT);
}

void remoteControlClass::init()
{
    Pan.attach(PanPin);
    Tilt.attach(TiltPin);
    ps2.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, vibrate);
}

void remoteControlClass::update()
{
    checkPS2();
}


int remoteControlClass::checkPS2()
{
    ps2.read_gamepad(false, 0);
   // if (ps2.NewButtonState()) newData = true;           //commented out because this is in parse command
    xJoyOld = xJoy;   yJoyOld = yJoy;
    xJoy = ps2.Analog(PSS_LX); yJoy = ps2.Analog(PSS_LY);
   
     //take absolute value
    XValueDiff = xJoy > xJoyOld ? xJoy - xJoyOld : xJoyOld - xJoy;
    YValueDiff = yJoy > yJoyOld ? yJoy - yJoyOld : yJoyOld - yJoy;

 
    if ((XValueDiff > 10) || (YValueDiff > 10))
    {
        newData = true;
        XValue = xJoy;
        YValue = yJoy;
    }

    tiltOld = tilt; panOld = pan;
    tilt = ps2.Analog(PSS_RY); pan = ps2.Analog(PSS_RX);
    tilt = map(tilt, 0, 255, 60, 120); pan = map(pan, 0, 255, 120, 60);

    if ((85 < pan) && (pan < 95)) pan = 90;
    if ((85 < tilt) && (tilt < 95)) tilt = 90;
    //absolute value
    panDiff = pan > panOld ? pan - panOld : panOld - pan;
    tiltDiff = tilt > tiltOld ? tilt - tiltOld : tiltOld - tilt;
    if ((panDiff > 5) || (tiltDiff > 5))
    {
        Pan.write(pan); delay(50); Tilt.write(tilt);
    } 

    if (ps2.ButtonReleased(PSB_RED))
    {
        XValue = 127; YValue = 127;
        newData = true;
    }

    if (ps2.ButtonReleased(PSB_PINK))
    {
        XValue = 127; YValue = 200;
        newData = true;
    }

    if (ps2.ButtonReleased(PSB_BLUE))
    {
        XValue = 127; YValue = 50;
        newData = true;
    }

    if (ps2.ButtonReleased(PSB_GREEN))
    {
        encoderBool = true;
        newData = true;
    }

    if (ps2.Button(PSB_L1))// take commands from PI while held
    {
        XValue = 127; YValue = 170;
        newData = true;
       
    }
        
    if (ps2.ButtonReleased(PSB_L1))
    {
        XValue = 127; YValue = 127;
        newData = true;
    }
 }
//if (ps2.ButtonReleased(PSB_BLUE)) parseCommand('c'); //back
//if (ps2.ButtonReleased(PSB_GREEN)) parseCommand('t'); //home
//if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) parseCommand('c'); //go backwards if either is held
//if(ps2x.ButtonReleased(PSB_L1) || ps2x.ButtonReleased(PSB_R1)) motors.estop();//stop going backwards when released
/*
        if (ps2.Button(PSB_L1)) parseCommand('a');   // motorL back if L1 held
        if (ps2.ButtonReleased(PSB_L1)) myMotors.speedL = 90;
        if (ps2.Button(PSB_R1)) parseCommand('b');   // motorR back if R1 held
        if (ps2.ButtonReleased(PSB_R1)) myMotors.speedR = 90;//stop going backwards when released

        if (ps2.Button(PSB_R2)) parseCommand('q');   // motorL forward if R2 held
        if (ps2.ButtonReleased(PSB_R2)) parseCommand('w');  // stop when released

        if (ps2.Button(PSB_L2)) parseCommand('e'); // motorR forward if L2 held
        if (ps2.ButtonReleased(PSB_L2)) parseCommand('r');//stop when released

        if (ps2.ButtonReleased(PSB_START)) parseCommand('6');   //follow me

        if (ps2.ButtonReleased(PSB_PAD_LEFT)) parseCommand('1');
        if (ps2.ButtonReleased(PSB_PAD_RIGHT)) parseCommand('3');
        if (ps2.ButtonReleased(PSB_PAD_DOWN)) parseCommand('4');
        if (ps2.ButtonReleased(PSB_PAD_UP)) parseCommand('2');

        if (ps2.Button(PSB_GREEN)) { parseCommand('a'); };
        if (ps2.ButtonPressed(PSB_RED)) { parseCommand('b'); };
        if (ps2.ButtonReleased(PSB_PINK)) { parseCommand('c'); };
        if (ps2.NewButtonState(PSB_BLUE)) { parseCommand('d'); };
        */


int remoteControlClass::parseCommand(char input)
{
    newData = true;
    switch (input) {
    case 'a':
        XValue = 0;
        YValue = 127;
        // leftMotor = 120;
        // rightMotor = 130;
        break;

    case 'b': 
        XValue = 0;
        YValue = 122;
        //leftMotor = 120;
        //rightMotor = 120;
        break;

    case 'c':
       // leftMotor = 130;
       // rightMotor = 120;
        break;

    case 'd':
        XValue = 0;
        YValue = -40;
        //leftMotor = 70;
        //rightMotor = 70;
        break;

    default:
        break;
    }
}
/*   char mystring[6];
   switch (input) {
   case '1': // LEFT
     //  myMotors.speedL -= 15;
       robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL();
       robot.myDisplay.println("left");
       // myMotors.speedR += 15;
       break;
   default:
       break;
       */
       /*   case '2': // UP  faster
              (myMotors.speedL == 90) ? myMotors.speedL = 120 : myMotors.speedL += 15;
              myMotors.speedR = myMotors.speedL;
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("up");
              break;
          case '3': // RIGHT
              myMotors.speedL += 15;
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("right");
              myMotors.speedR -= 15;
              break;
          case '4': // brake
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("brake");
              myMotors.speedL -= 15; myMotors.speedR -= 15;
              break;
          case '7': //select spin Left
            //add joystick mode here
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("7");
              myMotors.speedL = 45; myMotors.speedR = 135;
              break;
          case '6': //start spin right
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("start");
              //followMe = true;
              break;
              //      if (notOnStart < 2) notOnStart++;
               //     else {followMe = true; break;}
                   //myMotors.speedL = 135; myMotors.speedR = 45; break;

          case 't': // triangle+
              //goHome();
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("home");
              break;

          case 'a': // Back
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("back a");
              myMotors.speedL = 60; break;

          case 'b': // Back
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("back b");
              myMotors.speedR = 60; break;

          case 'c': // Back
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("back c");
              myMotors.speedL = 60; myMotors.speedR = 60; break;

          case 's': // square
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("stop");
              myMotors.speedL = 90; myMotors.speedR = 90; break;

          case '9': // X
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("xxxx");
              myMotors.encoderL = 0; myMotors.encoderR = 0; //displayInfo();
              break;
          case 'q': // L2
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("L2");
              myMotors.speedL = 145;
              break;
          case 'w': // L2 Release
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("w");
              myMotors.speedL = 90;
              break;
          case 'e': // R2
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("e");
              myMotors.speedR = 145;
              break;
          case 'r': // R2 Release
              robot.myDisplay.setCursor(0, 4); robot.myDisplay.clearToEOL(); robot.myDisplay.println("r");
              myMotors.speedR = 90;
              break;

          default:
              break;
          }
          */
