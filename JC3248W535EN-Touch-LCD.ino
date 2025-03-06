#include <src/JC3248W535EN-Touch-LCD.h>

JC3248W535EN screen;

uint16_t touchX, touchY;
int xIncr = 60;
int yIncr = 30;

void setup() {
  Serial.begin(115200);

  // Initialize the screen
  if (!screen.begin()) {
    Serial.println("Screen initialization failed!");
    return;
  }
  screen.clear(0, 0, 0);
  drawGrid();
}

void processSerialCommand() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    
    // Split the command by delimiter '|'
    int params[10];  // Array to store numeric parameters
    String textParam = "";  // For text parameter
    String parts[11];  // To store parts of the command
    
    int partCount = 0;
    int startIndex = 0;
    int delimiterIndex;
    
    while ((delimiterIndex = command.indexOf('|', startIndex)) != -1 && partCount < 11) {
      parts[partCount++] = command.substring(startIndex, delimiterIndex);
      startIndex = delimiterIndex + 1;
    }
    
    // Add the last part
    if (startIndex < command.length() && partCount < 11) {
      parts[partCount++] = command.substring(startIndex);
    }
    
    if (partCount < 1) {
      Serial.println("Invalid command format");
      return;
    }
    
    String cmd = parts[0];
    
    // Process based on command
    if (cmd == "prt" && partCount >= 4) {
      textParam = parts[1];
      for (int i = 0; i < 3; i++) {
        params[i] = parts[i+2].toInt();
      }
      screen.prt(textParam, params[0], params[1], params[2]);
      Serial.println("Text printed: " + textParam);
    }
    else if (cmd == "clear" && partCount >= 1) {
      if (partCount >= 4) {
        for (int i = 0; i < 3; i++) {
          params[i] = parts[i+1].toInt();
        }
        screen.clear(params[0], params[1], params[2]);
      } else {
        screen.clear(); // Use default values
      }
      Serial.println("Screen cleared");
    }
    else if (cmd == "setColor" && partCount >= 4) {
      for (int i = 0; i < 3; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.setColor(params[0], params[1], params[2]);
      Serial.println("Color set");
    }
    else if (cmd == "drawQRCode" && partCount >= 11) {
      textParam = parts[1];
      for (int i = 0; i < 9; i++) {
        params[i] = parts[i+2].toInt();
      }
      screen.drawQRCode(textParam.c_str(), params[0], params[1], params[2], 
                        params[3], params[4], params[5], params[6], params[7], params[8]);
      Serial.println("QR code drawn");
    }
    else if (cmd == "drawFillRect" && partCount >= 5) {
      for (int i = 0; i < 4; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawFillRect(params[0], params[1], params[2], params[3]);
      Serial.println("Rectangle filled");
    }
    else if (cmd == "drawRect" && partCount >= 5) {
      for (int i = 0; i < 4; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawRect(params[0], params[1], params[2], params[3]);
      Serial.println("Rectangle drawn");
    }
    else if (cmd == "drawLine" && partCount >= 5) {
      for (int i = 0; i < 4; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawLine(params[0], params[1], params[2], params[3]);
      Serial.println("Line drawn");
    }
    else if (cmd == "drawFillCircle" && partCount >= 4) {
      for (int i = 0; i < 3; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawFillCircle(params[0], params[1], params[2]);
      Serial.println("Circle filled");
    }
    else if (cmd == "drawCircleOutline" && partCount >= 4) {
      for (int i = 0; i < 3; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawCircleOutline(params[0], params[1], params[2]);
      Serial.println("Circle outline drawn");
    }
    else if (cmd == "drawTriangle" && partCount >= 7) {
      for (int i = 0; i < 6; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawTriangle(params[0], params[1], params[2], params[3], params[4], params[5]);
      Serial.println("Triangle drawn");
    }
    else if (cmd == "drawFillTriangle" && partCount >= 7) {
      for (int i = 0; i < 6; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawFillTriangle(params[0], params[1], params[2], params[3], params[4], params[5]);
      Serial.println("Triangle filled");
    }
    else if (cmd == "drawRoundRect" && partCount >= 6) {
      for (int i = 0; i < 5; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawRoundRect(params[0], params[1], params[2], params[3], params[4]);
      Serial.println("Rounded rectangle drawn");
    }
    else if (cmd == "drawFillRoundRect" && partCount >= 6) {
      for (int i = 0; i < 5; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawFillRoundRect(params[0], params[1], params[2], params[3], params[4]);
      Serial.println("Rounded rectangle filled");
    }
    else if (cmd == "drawEllipse" && partCount >= 5) {
      for (int i = 0; i < 4; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawEllipse(params[0], params[1], params[2], params[3]);
      Serial.println("Ellipse drawn");
    }
    else if (cmd == "drawFillEllipse" && partCount >= 5) {
      for (int i = 0; i < 4; i++) {
        params[i] = parts[i+1].toInt();
      }
      screen.drawFillEllipse(params[0], params[1], params[2], params[3]);
      Serial.println("Ellipse filled");
    }
    else if (cmd == "flush") {
      screen.flush();
      Serial.println("Screen flushed");
    }
    else {
      Serial.println("Unknown or incomplete command: " + cmd);
    }
  }
}

void loop() {
  screen.clear(0, 0, 0);
}

void drawGrid(){
  screen.setColor(40,40,40);
for(int i = xIncr; i <= 480; i = i+xIncr){ // ver lines
screen.drawLine(i,0,i,320);
}
for(int i = yIncr; i <= 320; i = i+yIncr){ // hor lines
screen.drawLine(0,i,480,i);
}
screen.flush();
}