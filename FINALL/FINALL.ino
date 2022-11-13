#define button1 A1
#define button2 A2
#define button3 A3
#define button4 A4

#define daMo A5
#define daDong A0

#define latchPin 11
#define clockPin 3
#define dataPin 12

#define loa 2

#define tang1 8
#define tang2 9
#define tang3 10
#define tang4 13

#define IN1 4
#define IN2 7
#define IN3 5
#define IN4 6

const unsigned long delay_step = 3000, delay_step_loa = 500;
unsigned long last, cua_last, time, time_loa, loa_last;

int hienHanh = 0, tangCuoi = 0, tinhTrang, x = 0;
boolean yeuCau1 = false, yeuCau2 = false, yeuCau3 = false, yeuCau4 = false;
char carbinMode = 'S';
boolean y = true;

const int Seg[10] = {
  0b11000000, //0
  0b11111001, //1
  0b10100100, //2
  0b10110000, //3
  0b10011001, //4
  0b10010010, //5
  0b10000011, //6
  0b11111000, //7
  0b10000000, //8
  0b10010000, //9
};

void setup() {
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  pinMode(tang1, INPUT);
  pinMode(tang2, INPUT);
  pinMode(tang3, INPUT);
  pinMode(tang4, INPUT);
  pinMode(daMo, INPUT);
  pinMode(daDong, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(loa, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  Serial.begin(9600);
}

void led7Doan() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, Seg[hienHanh]);
  digitalWrite(latchPin, HIGH);
}

void LOA() {
  while (1) {
    Serial.print(hienHanh);
    Serial.print(yeuCau1);
    Serial.print(yeuCau2);
    Serial.print(yeuCau3);
    Serial.print(yeuCau4);
    Serial.print(tangCuoi);
    Serial.print("L");
    Serial.print("\n");
    if (digitalRead(button1) == HIGH) {
      yeuCau1 = true;
    } else if (digitalRead(button2) == HIGH) {
      yeuCau2 = true;
    } else if (digitalRead(button3) == HIGH) {
      yeuCau3 = true;
    } else if (digitalRead(button4) == HIGH) {
      yeuCau4 = true;
    }
    if (y) {
      y = false;
      digitalWrite(loa, HIGH);
      time_loa = millis();
      loa_last = time_loa;
    } else if (millis() - loa_last >= delay_step_loa) {
      digitalWrite(loa, LOW);
      break;
    }
  }
}

void diLen() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}
void diXuong() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}
void dungLai() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void moCua() {
  analogWrite(IN3, 100);
  analogWrite(IN4, 0);
}
void dongCua() {
  analogWrite(IN3, 0);
  analogWrite(IN4, 100);
}
void dungCua() {
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void CUA() {
  while (1) {
    Serial.print(hienHanh);
    Serial.print(yeuCau1);
    Serial.print(yeuCau2);
    Serial.print(yeuCau3);
    Serial.print(yeuCau4);
    Serial.print(tangCuoi);
    Serial.print("C");
    Serial.print("\n");
    if (digitalRead(button1) == HIGH) {
      yeuCau1 = true;
    } else if (digitalRead(button2) == HIGH) {
      yeuCau2 = true;
    } else if (digitalRead(button3) == HIGH) {
      yeuCau3 = true;
    } else if (digitalRead(button4) == HIGH) {
      yeuCau4 = true;
    }
    if (digitalRead(daMo) == LOW) {
      tinhTrang = 1;
    } else if (digitalRead(daDong) == LOW) {
      tinhTrang = 2;
    }
    if ((tinhTrang == 1) && (x == 0)) {
      dungCua();
      x = 1;
      time = millis();
      cua_last = time;
    } else if ((millis() - cua_last >= delay_step) && (x == 1)) {
      dongCua();
      x = 2;
    } else if ((tinhTrang == 2) && (x == 2)) {
      dungCua();
      break;
    }
  }
}

void loop() {
  x = 0;
  y = true;
  if (digitalRead(button1) == HIGH) {
    yeuCau1 = true;
  } else if (digitalRead(button2) == HIGH) {
    yeuCau2 = true;
  } else if (digitalRead(button3) == HIGH) {
    yeuCau3 = true;
  } else if (digitalRead(button4) == HIGH) {
    yeuCau4 = true;
  }
  if (digitalRead(tang1) == LOW) {
    hienHanh = 1;
    led7Doan();
  } else if (digitalRead(tang2) == LOW) {
    hienHanh = 2;
    led7Doan();
  } else if (digitalRead(tang3) == LOW) {
    hienHanh = 3;
    led7Doan();
  } else if (digitalRead(tang4) == LOW) {
    hienHanh = 4;
    led7Doan();
  }
  Serial.print(hienHanh);
  Serial.print(yeuCau1);
  Serial.print(yeuCau2);
  Serial.print(yeuCau3);
  Serial.print(yeuCau4);
  Serial.print(tangCuoi);
  Serial.print("E");
  Serial.print("\n");
  switch (carbinMode) {
    case 'S':
      if (yeuCau1) {
        yeuCau1 =  false;
        tangCuoi = 1;
        if (tangCuoi < hienHanh) {

          carbinMode = 'D';
          break;
        } else if (tangCuoi > hienHanh) {

          carbinMode = 'U';
          break;
        } else if (tangCuoi == hienHanh) {
          moCua();
          CUA();
        } yeuCau1 =  false;
      } else if (yeuCau2) {
        yeuCau2 = false;
        tangCuoi = 2;
        if (tangCuoi < hienHanh) {

          carbinMode = 'D';
          break;
        } else if (tangCuoi > hienHanh) {

          carbinMode = 'U';
          break;
        } else if (tangCuoi == hienHanh) {
          moCua();
          CUA();
        } yeuCau2 = false;
      } else if (yeuCau3) {
        yeuCau3 = false;
        tangCuoi = 3;
        if (tangCuoi < hienHanh) {

          carbinMode = 'D';
          break;
        } else if (tangCuoi > hienHanh) {

          carbinMode = 'U';
          break;
        } else if (tangCuoi == hienHanh) {
          moCua();
          CUA();
        } yeuCau3 = false;
      } else if (yeuCau4) {
        yeuCau4 = false;
        tangCuoi = 4;
        if (tangCuoi < hienHanh) {

          carbinMode = 'D';
          break;
        } else if (tangCuoi > hienHanh) {

          carbinMode = 'U';
          break;
        } else if (tangCuoi == hienHanh) {
          moCua();
          CUA();
        } yeuCau4 = false;
      }
      break;

    case 'U':
      diLen();
      if (tangCuoi == hienHanh) {
        diXuong();
        dungLai();
        LOA();
        moCua();
        CUA();
        carbinMode = 'S';
      } if ( yeuCau1 && (hienHanh == 1)) {
        diXuong();
        dungLai();
        yeuCau1 = false;
        LOA();
        moCua();
        CUA();
      } else if (yeuCau2 && (hienHanh == 2)) {
        diXuong();
        dungLai();
        yeuCau2 = false;
        LOA();
        moCua();
        CUA();
      } else if (yeuCau3 && (hienHanh == 3)) {
        diXuong();
        dungLai();
        yeuCau3 = false;
        LOA();
        moCua();
        CUA();
      } else if (yeuCau4 && (hienHanh == 4)) {
        diXuong();
        dungLai();
        yeuCau4 = false;
        LOA();
        moCua();
        CUA();
      }
      break;
    case 'D':
      diXuong();
      if (tangCuoi == hienHanh) {
        diLen();
        dungLai();
        LOA();
        moCua();
        CUA();
        carbinMode = 'S';
      } if ( yeuCau1 && (hienHanh == 1)) {
        diLen();
        dungLai();
        yeuCau1 = false;
        LOA();
        moCua();
        CUA();
      } else if (yeuCau2 && (hienHanh == 2)) {
        diLen();
        dungLai();
        yeuCau2 = false;
        LOA();
        moCua();
        CUA();
      } else if (yeuCau3 && (hienHanh == 3)) {
        diLen();
        dungLai();
        yeuCau3 = false;
        LOA();
        moCua();
        CUA();
      } else if (yeuCau4 && (hienHanh == 4)) {
        diLen();
        dungLai();
        yeuCau4 = false;
        LOA();
        moCua();
        CUA();
      }
      break;
  }
}
