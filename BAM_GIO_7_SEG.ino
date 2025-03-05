// Khai báo chân kết nối giữa Arduino và LED 7 thanh
const int digitPins[] = {2, 3, 4, 5}; // Chân kết nối với các LED 7 thanh
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // Chân kết nối với các đèn LED trên mỗi LED 7 thanh và led báo

// Mảng 2 chiều lưu trữ trạng thái các đèn LED cho các số từ 0 đến 9
// Trạng thái 1 là đèn sáng, trạng thái 0 là đèn tắt
const int digitSegments[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // Số 0
  {0, 1, 1, 0, 0, 0, 0}, // Số 1
  {1, 1, 0, 1, 1, 0, 1}, // Số 2
  {1, 1, 1, 1, 0, 0, 1}, // Số 3
  {0, 1, 1, 0, 0, 1, 1}, // Số 4
  {1, 0, 1, 1, 0, 1, 1}, // Số 5
  {1, 0, 1, 1, 1, 1, 1}, // Số 6
  {1, 1, 1, 0, 0, 0, 0}, // Số 7
  {1, 1, 1, 1, 1, 1, 1}, // Số 8
  {1, 1, 1, 1, 0, 1, 1}  // Số 9
};
#define tang A0
#define giam A1
#define Star A2
#define RST A3
bool tt = false;
int phut, giay;
long time;
void setup() {
  // Khai báo các chân là OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  
}

void loop() {
  // Hiển thị các số từ 0 đến 9999
  if(!tt){
    if(digitalRead(tang) == 0){
      phut = phut +1;
      delay(50);
    }
    if(digitalRead(giam) == 0){
      phut = phut - 1;
      delay(50);
    }
    constrain(phut,0,10);
    displayNumber(phut);
  }
  if(digitalRead(RST) == 0){
    phut = 0;
    giay = 0;
    int thoigian = (phut * 100) + giay;
    tt = false;
    displayNumber(thoigian);
  }
 if(digitalRead(Star) == 0) tt = true;
 if(tt){
  if(millis() - time >= 100){
    giay = giay - 1;
    if(phut > 0){
    if(giay <= 0){
      giay = 0;
      phut = phut -1;
      giay = 59;
    } 
  }
  time = millis();
 }
 digitalWrite(segmentPins[7], LOW);
 if(phut <=0 && giay <= 0){
  tt = false;
  digitalWrite(segmentPins[7], HIGH);
 }
 int thoigian = (phut * 100) + giay;
 displayNumber(thoigian);
 }
    
}

// Hàm hiển thị số trên các LED 7 thanh
void displayNumber(int number) {
  // Tách các chữ số
  int digits[4];
  digits[0] = number % 10; // Số hàng đơn vị
  digits[1] = (number / 10) % 10; // Số hàng chục
  digits[2] = (number / 100) % 10; // Số hàng trăm
  digits[3] = (number / 1000) % 10; // Số hàng nghìn

  // Quét qua từng LED 7 thanh để hiển thị các chữ số
  for (int i = 0; i < 4; i++) {
    // Hiển thị chữ số tương ứng trên LED 7 thanh hiện tại
    for (int j = 0; j < 7; j++) {
      digitalWrite(segmentPins[j], digitSegments[digits[i]][j]);
    }

    // Kích hoạt LED 7 thanh hiện tại bằng cách đặt chân LOW
    digitalWrite(digitPins[i], HIGH);

    // Delay nhỏ để tạo hiệu ứng quét
    delay(5);

    // Tắt LED 7 thanh hiện tại bằng cách đặt chân HIGH
    digitalWrite(digitPins[i], LOW);
  }
}
