// board pins used
#define LED_GREEN   (0) // P0
#define LED_YELLOW  (1) // P1
#define LED_RED     (2) // P2
#define USER_BUTTON (3) // P3

// button timings
#define DEBOUNCE       (25)
#define LONG_PRESS_DLY (1000)

// main algorythm timings
#define BLINK_DLY      (500)
#define SWITCH_DLY     (5000)
#define OFF_MODE_DLY   (30000)

typedef enum {
  BTN_FREE,
  BTN_PUSH,
  BTN_LONG_PRESS,
} btn_state_t;

// the declaration is necessary due to the specifics of the Arduino IDE
btn_state_t get_btn_state(uint8_t _pin);

// base initialization
void setup(){
  pinMode(LED_GREEN , OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED   , OUTPUT);

  digitalWrite(LED_GREEN , LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_RED   , LOW);

  pinMode(USER_BUTTON, INPUT_PULLUP);
}

// Time interval calculation. Provides for a possible system timer overflow.
uint16_t pass_tm(uint16_t _start_time){
  const uint16_t curr = millis();
  return curr - _start_time;
}

// returns the push and long press events of the button
btn_state_t get_btn_state(uint8_t _pin){
  static uint8_t prev_state = 1;
  static uint16_t long_press_tmr = 0;
  btn_state_t result = BTN_FREE;
  
  delay(DEBOUNCE);
  const uint8_t new_state = digitalRead(_pin);

  if (new_state == 0)
    long_press_tmr += DEBOUNCE;
  else
    long_press_tmr = 0;
  
  if (prev_state == 1 && new_state == 0)
    result = BTN_PUSH;
  else if (long_press_tmr >= LONG_PRESS_DLY)
    result = BTN_LONG_PRESS;

  prev_state = new_state;
  return result;
}

// LED on
void led_light(uint8_t _pin, uint16_t _time){
  const uint16_t start_time = millis();
  digitalWrite(_pin, HIGH);
  
  while (true
         && pass_tm(start_time) <= _time
         && get_btn_state(USER_BUTTON) == BTN_FREE
         );

  digitalWrite(_pin, LOW);
}

// LED blink
void led_blink(uint8_t _pin, uint16_t _time){
  const uint16_t start_time = millis();
  digitalWrite(_pin, HIGH);
  
  while (true
         && pass_tm(start_time) <= _time
         && get_btn_state(USER_BUTTON) == BTN_FREE
         )
    digitalWrite(_pin, (pass_tm(start_time) % (BLINK_DLY * 2)) > BLINK_DLY ? LOW : HIGH);

  digitalWrite(_pin, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  static const uint8_t series[] = {LED_RED, LED_YELLOW, LED_GREEN, LED_YELLOW};

  for (byte i = 0; i < sizeof(series); ++i){
    led_light(series[i] , SWITCH_DLY);
    led_blink(series[i] , SWITCH_DLY);
    if (get_btn_state(USER_BUTTON) == BTN_LONG_PRESS) break;
  }

  while (get_btn_state(USER_BUTTON) == BTN_LONG_PRESS);

  led_blink(LED_YELLOW, OFF_MODE_DLY);
}

