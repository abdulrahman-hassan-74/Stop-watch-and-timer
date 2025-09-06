# ATmega32 Timer & Stopwatch ⏱️

This project demonstrates how to implement a **countdown timer** and a **stopwatch** on the ATmega32 microcontroller using C language and AVR libraries.  
It uses hardware timers (Timer1), external interrupts, and button inputs to control time counting and display it on 7-segment displays.

---

## ⚡ Features
- Works as **both a countdown timer** and a **stopwatch**.
- Supports **hours, minutes, and seconds** display.
- Buttons allow:
  - Start/Stop toggling
  - Increment/Decrement hours, minutes, seconds
  - Reset time to `00:00:00`
- Uses **Interrupts** (`INT0`, `INT1`, `INT2`) for reset, pause, and resume.
- LED indicators:
  - Blinks to show countdown
  - Lights up when time reaches `00:00:00`

---

## 🛠️ Hardware Requirements
- ATmega32 Microcontroller
- 7-Segment Displays (6 digits, multiplexed via `PORTA` + `PORTC`)
- Push Buttons (for start/stop, increment/decrement, reset, pause, resume)
- LEDs (status indication)
- Resistors & wiring

---

## 🔧 Pin Connections
- **Display Control**:  
  - `PORTA` → Digit enable (6 control lines)  
  - `PORTC (lower nibble)` → Segment data  

- **Buttons**:  
  - Connected to `PORTB` and `PORTD` pins with pull-ups  

- **LEDs**:  
  - Connected to `PORTD` pins for status indication  

---

## ⚙️ Software Overview
- **Timer1 (CTC mode)** generates 1-second interrupts.  
- **External Interrupts**:
  - `INT0`: Reset time  
  - `INT1`: Pause  
  - `INT2`: Resume  
- **Main Loop** handles button scanning and updates hours/min/sec.  
- **ISR** routines:
  - Update timer/stopwatch values
  - Control LEDs
  - Manage reset/pause/resume

---

## ▶️ How to Use
1. Flash the code into ATmega32.  
2. Use buttons to set the desired time (hours/minutes/seconds).  
3. Press **Start/Stop button**:
   - Timer mode → counts down to zero  
   - Stopwatch mode → counts up continuously  
4. Reset anytime using the reset button (`INT0`).  
5. Pause/Resume using `INT1` and `INT2`.  

---

## 📂 Project Structure
- `project2-ec.c` → contains the full implementation (timer, stopwatch, interrupts, display handling).

---

## 🚀 Future Improvements
- Add buzzer/alarm when timer reaches zero.  
- Improve debounce handling for buttons.  
- Add EEPROM saving of last set time.  

---

## 📜 License
This project is open-source. Feel free to use and modify for learning or personal projects.
