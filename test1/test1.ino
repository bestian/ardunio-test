#include <Servo.h>

// 定義音符頻率
#define NOTE_E4  330
#define NOTE_DS4 311
#define NOTE_D4  294
#define NOTE_C4  262
#define NOTE_B3  247
#define NOTE_A3  220
#define NOTE_GS3 208
#define NOTE_AS3 233
#define NOTE_E3  165  // 添加 E3 音符的定義

// 定義引腳
const int LIGHT_SENSOR_PIN = A0;
const int SERVO_PIN = 8;
const int BUZZER_PIN = 3;

Servo myServo;
int lightThreshold = 150; // 光線閾值，可根據實際情況調整

// 定義音樂旋律（給愛麗絲前段）
int melody[] = {
  NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_B3, NOTE_D4, NOTE_C4, NOTE_A3,
  NOTE_C4, NOTE_E4, NOTE_A3, NOTE_B3, NOTE_E3, NOTE_GS3, NOTE_B3, NOTE_C4
};

// 定義音符持續時間
int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 2, 4, 4, 4, 2
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  myServo.attach(SERVO_PIN);
  Serial.begin(9600);
}

void loop() {
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.println(lightValue);

  if (lightValue < lightThreshold) {
    // 光線變暗時
    playMelody();  // 先播放音樂
    myServo.write(90); // 音樂播放完後，伺服馬達轉到90度
  } else {
    // 光線正常時
    myServo.write(0); // 伺服馬達回到0度
    noTone(BUZZER_PIN);
  }

  delay(500); // 短暫延遲以避免讀取過於頻繁
}

void playMelody() {
  for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}
