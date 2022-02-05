#pragma once

#include <stdint.h>

namespace drivers {

//     CONTROL REGISTER
//     Control register map is shown below.

//     Address      Register      R/W     Initial value      Register setting 
//     00H      NOOP      R/W      00H      No function assigned 
//     01H      VMON      R/W      00H      Battery cell voltage Measurement 
//     02H      IMON      R/W      00H      Current measurement setting 
//     03H      FET      R/W      00H      FET setting 
//     04H      PSENSE      R/W      00H      PSENSE pin comparator setting 
//     05H      RSENSE      R/W      00H     Short current detection setting RSENSE pin comparator setting 
//     06H      POWER      R/W      00H      Power save, Power down control 
//     07H      STATUS      R/W      00H      Internal Status 
//     08H      CBALH      R/W      00H     Upper 8 cell balancing switch ON/OFF setting 
//     09H      CBALL      R/W      00H     Lower 8 cell balancing switch ON/OFF setting 
//     0AH      SETSC      R/W      00H      Short current detecting voltage setting 
//     others      TEST      R/W      00H      TEST (Don’t use) 


// 1. NOOP register (Adrs = 00H)
//                 7       6       5       4       3       2       1       0 
// Bit name       NO7     NO6     NO5     NO4     NO3     NO2     NO1     NO0 
// R/W            R/W     R/W     R/W     R/W     R/W     R/W     R/W     R/W 
// Initial value   0       0       0       0       0       0       0       0 
// No function is assigned to NOOP register, there is no status changes in the LSI even if this register is
// written or read. In the read operation written data is read



// 2. VMON register (Adrs = 01H)
// 
// 7      6      5      4      3      2      1      0 
// Bit name      −      −      −      OUT      CN3      CN2      CN1      CN0 
// R/W      R      R      R      R/W      R/W      R/W      R/W      R/W 
// Initial value      0      0      0      0      0      0      0      0 
// VMON register sets the battery cell outputted to the VMON pin.
// Select the battery cell by CN0, CN1, CN2, CN3 bits, and OUT bit enable the output from VMON
// pin.

// OUT      CN3      CN2      CN1      CN0      Battery cell selection 
// 0      −      −      −      −      VMON pin = 0V (initial value) 
// 1      0      0      0      0      V1 cell (lower most) 
// 1      0      0      0      1      V2 cell 
// 1      0      0      1      0      V3 cell 
// 1      0      0      1      1      V4 cell 
// 1      0      1      0      0      V5 cell 
// 1      0      1      0      1      V6 cell 
// 1      0      1      1      0      V7 cell 
// 1      0      1      1      1      V8 cell 
// 1      1      0      0      0      V9 cell 
// 1      1      0      0      1      V10 cell 
// 1      1      0      1      0      V11 cell 
// 1      1      0      1      1      V12 cell 
// 1      1      1      0      0      V13 cell 
// 1      1      1      0      1      V14 cell 
// 1      1      1      1      0      V15 cell 
// 1      1      1      1      1      V16 cell (upper most) 

// 3. IMON register (Adrs = 02H)
// 
// 7      6      5      4      3      2      1      0 
// Bit name      −      −      −      OUT      GCAL1      GCAL0      ZERO      GIM 
// R/W      R      R      R      R/W      R/W      R/W      R/W      R/W 
// Initial value      0      0      0      0      0      0      0      0 
// 
// IMON register set the current measuring.
// GIM bit set the voltage gain of current measuring amplifier.
// 
// GIM      Voltage gain GIM 
// 0      10 times (initial value) 
// 1      50 times 
// 
// ZERO bit set the zero-correction of current measuring amplifier.
// 
// ZERO      ISP input      ISM input 
// 0      Pin input      Pin input 
// 1      GND level      GND level 
// 
// 
// Voltage gain of current measuring amplifier is corrected by GCAL0, GCAL1 bits.
// GCAL0 bit changes the ISP and ISM pin input to GND or internal reference voltage (20mV/100mV).
// GCAL1 bit changes the IMON pin output to internal reference voltage output.
// 
// GCAL1     GCAL0      ISP input      ISM input      IMON output 
// 0      0      Pin input      Pin input      Amplified output 
// 0      1     GIM=0  100mV GIM=1  20mV      GND level  GND level      2V (typ)  2V (typ) 
// 1 1      0  1      Pin input  GIM=0  100mV GIM=1  20mV     Pin input  GND level  GND level      Amplified output Reference voltage output 100mV (typ) Reference voltage output 20mV (typ) 
// 
// 
// 
// If the ZERO bit is set “1”, setting GCAL1 and GCAL0 bits are neglected.
// OUT bit enables to output the current measuring amplifier from IMON pin.
// gain correction is held, OUT bit is set “1” too.
// 
// OUT      IMON pin output 
// 0      0V (initial value) 
// 1      Current measuring amplifier output 
// 
// Current measurement is executed with current sensin resistor (RSENSE) connected between ISP pin
// and ISM pin and by measuring input voltage difference between these pins.
// Voltage difference between ISP and ISM is converted to voltage, its center is 1.0V (typ), and
// outputted from IMON pin. IMON pin output voltage VIMON is given by the following equation with
// the current sensing resistor RSENSE and its current I SENSE.
// 
// V IMON  =  (ISENSE × RSENSE) × GIM + 1.0 





// 4. FET register (Adrs = 03H)
// 
// 7      6      5      4      3      2      1      0 
// Bit name      −      −      −      DRV      −      −      CF      DF 
// R/W      R      R      R      R/W      R      R      R/W      R/W 
// Initial value      0      0      0      0      0      0      0      0 
// FET register control the turn ON/OFF of the C_FET and D_FET pin, and read the state of its output.
// DF bit sets the D_FET pin output state. If the short current is detected, the DF bit is automatically
// cleared to ”0”. Because the DF bit is not automatically set “1” even if the state is changed from short
// detection to normal state, external MCU must set this bit “1”.
// 
// 
// 
// DF      Discharge FET      D_FET pin output 
// 0      OFF (initial value)      0V 
// 1      ON      14V (typ) 
// 
// 
// CF bit set the C_FET pin output state. If the short current is detected, the CF bit is automatically
// cleared tot “0”. Because the CF bit is not automatically set “1” even if the state is changed from short
// detection to normal state, external MCU must set this bit “1”.
// 
// CF      Charge FET      C_FET pin output 
// 0      OFF (initial value)      Hi-Z 
// 1      ON      14V (typ) 
// 
// DRV bit set the output current drive capacity of internal FET driver. If the DRV bit is set “1”, the
// rising time of D_FET, C_FET pins is short.
// The duration to set the DRV bit “1” should be set depend on the capacitance load of the D_FET,
// C_FET pins. DRV bit should be cleared to “0”, after the D_FET, C_FET pin output level is fully risen
// to “H”.
// If the DRV bit is left “1”, power consumption or the “H” output voltage of D_FET, C_FET might be
// higher than the level specified in the electrical characteristics.
// 
// DRV     FET driver output capacity 
// 0     Normal (initial value) 
// 1     enhanced 



// 5. PSENSE register (Adrs = 04H)
// 
// 7      6      5      4      3      2      1      0 
// Bit name      EPSH      IPSH      RPSH      PSH      EPSL      IPSL      RPSL      PSL 
// R/W      R/W      R/W      R/W      R      R/W      R/W      R/W      R 
// Initial value      0      0      0      0      0      0      0      0 
// 
// 
// PSENSE register set the parameters of comparators which detect charger connection/disconnection
// with PSENSE pin input.
// Two comparators with difference threshold are connected to PSENSE pin to manage ON and OFF
// states of discharge FET.
// For detecting charger disconnection in the state of discharge FET ON, low level threshold (0.2V
// (typ) ) type comparator is selected, because PSENSE pin voltage is clamped by the body-diode of
// charge FET.
// Low level threshold type comparator is selected mainly for detecting charger open in the state of
// charge over-current detected,
// Parameters of the low level threshold type comparator for detecting the charger open is set in EPSL,
// IPSL, and RPSL bits. Comparator output is assigned to PSL bit.
// EPSL bit set the run/stop of the comparator for detecting charger open. If EPSL bit is set running,
// 500kΩ pull-up resistor is connected to PSENSE pin in the LSI.
// 
// 
// EPSL     State of comparator for  detecting charger open     PSENSE pin status 
// 0      Stop (initial value)      Hi-Z (initial value) 
// 1      Run      500kΩ pull-up 
// 
// IPSL bit enables asserting the interrupt from /INTO pin, if the output of comparator detecting
// charger open (PSL bit) is changed from “0” to “1”. IPSL bit should be set “1” more than 1 msec later
// from setting the EPSL bit “1”.
// 
// IPSL      Interrupt enable 
// 0      Disable (initial value) 
// 1      enable 
// 
// 
// RPSL bit indicates the interrupt assertion if the output of comparator detecting charger open (PSL
// bit) is changed from “0” to “1”. To clear this interrupt, write “0” in the RPSL bit. Writing “1” in the
// RPSL bit is neglected. If IPSL bit is “0”, RPSL bit is fixed to “0”.
// 
// 
// RPSL      Interrupt occurred 
// 0      No interrupt (initial value) 
// 1      Interrupted 
// 
// 
// PSL bit indicates the state of charger connected. If the EPSL bit is “0”, PSL bit is fixed to “0”.
// Writing “1” in the PSL bit is neglected.
// 
// PSL      Charger connection      PSENSE pin voltage 
// 0     Charger connected  (initial value)     0.2V or less 
// 1      Charger disconnected      Larger than 0.2V 
// 
// For detecting charger disconnection in the state of discharge FET OFF, high level threshold
// (VDD×0.75) type comparator is selected, because PSENSE pin voltage rise up to power supply voltage
// (VDD).
// High level threshold comparator is selected mainly for detecting charger open if the status changes to
// power down state.
// Parameters of the high level threshold type comparator for detecting the charger open is set in EPSH,
// IPSH, and RPSH bits. Comparator output is assigned to PSH bit.
// EPSH bit set the run/stop of the comparator for detecting charger open. If EPSH bit is set running,
// 500kΩ pull-up resistor is connected to PSENSE pin in the LSI.
// 
// EPSH     State of comparator for  detecting charger open     PSENSE pin status 
// 0      Stop (initial value)      Hi-Z (initial value) 
// 1      Running      500kΩ pull-up 
// 
// IPSH bit enables asserting the interrupt from /INTO pin, if the output of comparator detecting
// charger open (PSH bit) is changed from “0” to “1”. IPSH bit should be set “1” more than 1 msec later
// from setting the EPSH bit “1”.
// 
// IPSH      Interrupt enable 
// 0      Disable (initial value) 
// 1      enabled 
// 
// RPSH bit indicates the interrupt assertion if the output of comparator detecting charger open (PSH
// bit) is changed from “0” to “1”. To clear this interrupt, write “0” in the RPSH bit. Writing “1” in the
// RPSH bit is neglected. If IPSH bit is “0”, RPSH bit is fixed to “0”.
// 
// 
// RPSH      Interrupt occurred 
// 0      No interrupt (initial value) 
// 1      interrupted 
// 
// PSH bit indicates the state of charger connected. If the EPSH bit is “0”, PSH bit is fixed to “0”.
// Writing “1” in the PSH bit is neglected.
// 
// 
// PSH      Charger connection      PSENSE pin voltage 
// 0     Charger connected  (initial value)     VDD×0.75 or less 
// 1      Charger disconnected      Larger than VDD×0.75 







// 6. RSENSE register (Adrs = 05H)
// 
// 
// 7      6      5      4      3      2      1      0 
// Bit name      ESC      ISC      RSC      SC      ERS      IRS      RRS      RS 
// R/W      R/W      R/W      R/W      R      R/W      R/W      R/W      R 
// Initial value      0      0      0      0      0      0      0      0 
// 
// RSENSE register set the parameters of detecting short current and the parameters of comparator
// which detect load connection/disconnection with RSENSE pin input.
// ESC bit set the run/stop of the circuit detecting short current.
// 
// ESC     Status of the circuit detecting short current 
// 0      Stop (initial value) 
// 1      Run 
// 
// ISC bit enables asserting the interrupt from /INTO pin, if the short current is detected.
// 
// ISC      Interrupt enable 
// 0      Disable (initial value) 
// 1      enable 
// 
// RSC bit indicates the interrupt assertion if the short current is detected. To clear the interrupt, write
// “0” in the RSC bit. Writing “1” in the RSC bit is neglected. If ISC bit is “0”, RSC bit is fiexed to “0”.
// 
// RSC      Interrupt occurred 
// 0      No interrupt (initial value) 
// 1      interrupted 
// 
// SC bit indicates the output from the comparator detecting short current.
// If the SC bit is changed from “0” to “1”, charging the capacitor connected to CDLY pin is started. If
// this charging is finished, the RSC bit is automatically changed to “1” and the DF bit and the CF bit in
// the FET register is automatically cleared to “0”. If the short current status is cleared before charging
// the capacitor connected to CDLY pin is finished, charging the CDLY pin is stopped and the CDLY pin
// is fixed to GND level.
// If the ESC bit is “0”, SC bit is fixed to “0”. Writing “1” in the SC bit is neglected.
// 
// SC     Status of the comparator  output detecting short current         ISP-ISM voltage 
// 0     Short current is not detected (initial value)           Short current detecting voltage or lower 
// 1      Short current is detected         Higher than short current detecting voltage 
// 
// Short current detecting delay time is set with the charging time of capacitor CDLY which is connected
// to CDLY pin ; calculated with following formula.
// 
// Short current detecting delay time tsc [μs] = C DLY[nF] ×100 
// 
// ERS bit set the run/stop of the comparator for detecting load open. If ERS bit is set running, 2MΩ
// pull-down resistor is connected to RSENSE pin in the LSI.
// 
// ERS     State of comparator for  detecting load open     RSENSE pin status 
// 0      Stop (initial value)      Hi-Z (initial value) 
// 1      Running      2MΩ pull-down 
// IRS bit enables asserting the interrupt from /INTO pin, if the output of comparator detecting load
// open (RS bit) is changed from “0” to “1”. IRS bit should be set “1” more than 1 msec later from setting
// the ERP bit “1”.
// 
// IRS      Interrupt enable 
// 0      Disable (initial value) 
// 1      enabled 
// 
// 
// RRS bit indicates the interrupt assertion if he output of comparator detecting load open(RS bit) is
// changed from “0” to “1”. To clear this interrupt, write “0” in the RRS bit. Writing “1” in the RRS bit is
// neglected. If IRS bit is “0”, RRS bit is fixed to “0”.
// 
// RRS      Interrupt occurred 
// 0      No interrupt (initial value) 
// 1      interrupted 
// 
// RS bit indicates the state of load connected. If the ERS bit is “0”, RS bit is fixed to “0”. Writing “1”
// in the RS bit is neglected.
// 
// RS      Load connection      RSENSE pin voltage 
// 0      Load connected (initial value)      2.4V or higher 
// 1      Load disconnected      Lower than 2.4V 


// 7. POWER register (Adrs = 06H)
// 
// 7      6      5      4      3      2      1      0 
// Bit name      PUPIN      −      −      PDWN      −      −      −      PSV 
// R/W      R      R      R      R/W      R      R      R      R/W 
// Initial value      0      0      0      0      0      0      0      0 
// 
// Power register control the power save and the power down.
// PSV bit set the state transition to power save.
// 
// 
// 
// PSV      Power save 
// 0      Normal state (initial value) 
// 1      Power save state 
// In the power save state, circuits for VREG output and VREF output is operating, cell voltage
// measuring and current measuring is stopped, and the power consumption is reduced. FET driving and
// short detecting circuit works in the power save state. Comparators in the PSENSE pin and the
// RSENSE pin are stopped.
// Clearing the PSV bit to “0” and the status is recovered from power save state to normal state.
// To set the comparators in the PSENSE pin and the RSENSE pin running, set these comparators to
// run after recovering from the power save state.
// PDWN bit set the state transition to power down
// 
// 
// PDWN      Power down 
// 0      Normal state (initial value) 
// 1      Power down state 
// 
// If the PDWN bit is set “1”, 500kΩ pull-up resistor is automatically connected to PSENSE pin in the
// LSI and all the circuit is stopped, and the /RES pin output is “L”.
// Before setting the PDWN bit “1”, C_FET and D_FET should be set OFF and charger disconnection
// should be confirmed with the PSENSE register. When the /PUPIN pin input is “L”, even if PDOWN
// bit is set to “1”, the state doesn’t get changed to power-down until the /PUPIN pin input rises to “H”.
// Before setting the PDWN bit “1”, it should be confirmed that /PUPIN pin is not “L” by reading the
// PUPIN bit.
// 
// 
// PUPIN     /PUPIN pin state 
// 0     “H” level 
// 1     “L” level 
// If charger connection is detected with PSENSE pin or if /PUPIN pin is asserter “L” input, the LSI is
// recovered from power down state to normal state.
// In the power down state, VREG output which is power supply for external micro-computer is set
// GND level. In recovering from power down state, every initial setting should be held after VREG is
// fully risen and after /RES pin output is fully changed from “L” level to “H” level.


// 8. STATUS register (Adrs = 07H)
// 
// 
// 7      6      5      4      3      2      1      0 
// Bit name      RSC      RRS      RPSH      RPSL      INT      PSV      CF      DF 
// R/W      R      R      R      R      R      R      R      R 
// Initial value      0      0      0      0      0      0      0      0 
// STATUS register indicates each status.
// DF bit indicates the D_FET pin output status.
// 
// DF      D_FET pin status 
// 0      OFF (initial value) 
// 1      ON 
// 
// CF bit indicates the C_FET pin output status.
// 
// CF      C_FET pin status 
// 0      OFF (initial value) 
// 1      ON 
// PSVbit indicates the power save state.
// 
// PSV      Power save state 
// 0      Normal state (initial value) 
// 1      Power save state 
// 
// INT bit indicates the /INTO pin output status.
// 
// INT      /INTO pin output status 
// 0      No interrupt (initial value) 
// 1      Interrupted 
// RPSL bit indicates interrupt status of charger disconnecting interrupt if charge over-current detected.
// 
// RPSL      Status of charger disconnecting interrupt if charge over-current detected. 
// 0      No interrupt (initial value) 
// 1      Charger disconnecting interrupt 
// RPSH bit indicates interrupt status of charger disconnecting interrupt if the status is power down.
// 
// 
// RPSH      Status of charger disconnecting interrupt if the status is power down 
// 0      No interrupt (initial value) 
// 1      Charger disconnecting interrupt 
// 
// 
// RRS bit indicates interrupt status of load disconnecting interrupt
// 
// RRS      Status of load disconnecting interrupt 
// 0      No interrupt (initial value) 
// 1      Load disconnecting interrupt 
// 
// RSC bit indicates interrupt status of short current detecting interrupt.
// RSC          Status of short current detecting interrupt 
// 0          No interrupt (initial value) 
// 1          Short current detecting interrupt. 

    
    
// 9. CBALH register (Adrs = 08H)
// 
// 7      6      5      4      3      2      1      0 
// Bit name      SW16      SW15      SW14      SW13      SW12      SW11      SW10      SW9 
// R/W      R/W      R/W      R/W      R/W      R/W      R/W      R/W      R/W 
// Initial value      0      0      0      0      0      0      0      0 
// CBALH register set the cell balancing switches turning ON/OFF of upper 8 cells.
// SW16~SW9 bit sets switches turning ON/OFF of each cell.
// 
// More than one switch can be turned on in the same time, but following settings are inhibited because
// internal cell balancing switch might be broken.
// (1) Side-by-side cell balancing switches are inhibited to be turned on in the same time.
// (2) the cell balancing switches of both side of a cell balancing switch which is turned off is inhibited
// to be turned on in the same time.
// 
// 
// SW16     SW15     SW14     SW13     SW12     SW11     SW10     SW9      Switch ON/OFF 
// 0      0      0      0      0      0      0      0     Upper 8 cells OFF (initial value) 
// 0      0      0      0      0      0      0      1      V9-V8 pin switch ON 
// 0      0      0      0      0      0      1      0      V10-V9 pin switch ON 
// 0      0      0      0      0      1      0      0      V11-V10 pin switch ON 
// 0      0      0      0      1      0      0      0      V12-V11 pin switch ON 
// 0      0      0      1      0      0      0      0      V13-V12 pin switch ON 
// 0      0      1      0      0      0      0      0      V14-V13 pin switch ON 
// 0      1      0      0      0      0      0      0      V15-V14 pin switch ON 
// 1      0      0      0      0      0      0      0      V16-V15 pin switch ON 
// IC heats by cell balancing current and cell balancing switch resistor, restrict the number of switches
// of ON and time of ON, in order to keep the power consumption of cell balancing switch less than
// allowable power dissipation,
// If cell voltage is outputted from VMON pin, the voltage of a cell whose cell balancing switch is
// turned on is measured as the voltage difference between two ports of cell balancing switch.


// 10. CBALL register (Adrs = 09H)
// CBALL register set the cell balancing switches turning ON/OFF of lower 8 cells.
// SW8~SW1 bit sets switches turning ON/OFF of each cell.
// 
// 7      6      5      4      3      2      1      0 
// Bit name      SW8      SW7      SW6      SW5      SW4      SW3      SW2      SW1 
// R/W      R/W      R/W      R/W      R/W      R/W      R/W      R/W      R/W 
// Initial value      0      0      0      0      0      0      0      0 
// SW8      SW7      SW6          SW5      SW4      SW3      SW2     SW1      Switch ON/OFF 
// 0      0      0          0      0      0      0      0     lower 8 cells OFF (initial value) 
// 0      0      0          0      0      0      0      1      V1-V0 pin switch ON 
// 0      0      0          0      0      0      1      0      V2-V1 pin switch ON 
// 0      0      0          0      0      1      0      0      V3-V2 pin switch ON 
// 0      0      0          0      1      0      0      0      V4-V3 pin switch ON 
// 0      0      0          1      0      0      0      0      V5-V4 pin switch ON 
// 0      0      1          0      0      0      0      0      V6-V5 pin switch ON 
// 0      1      0          0      0      0      0      0      V7-V6 pin switch ON 
// 1      0      0          0      0      0      0      0      V8-V7 pin switch ON 
// More than one switch can be turned on in the same time, but following settings are inhibited because
// internal cell balancing switch might be broken.
// (1) Side-by-side cell balancing switches are inhibited to be turned on in the same time.
// (2) the cell balancing switches of both side of a cell balancing switch which is turned off is inhibited
// to be turned on in the same time.
// 
// 
// 
// IC heats by cell balancing current and cell balancing switch resistor, restrict the number of switches
// of ON and time of ON, in order to keep the power consumption of cell balancing switch less than
// allowable power dissipation,
// If cell voltage is outputted from VMON pin, the voltage of a cell whose cell balancing switch is
// turned on is measured as the voltage difference between two ports of cell balancing switch.



// 11. SETSC register (Adrs = 0AH)
// 
// 7      6      5      4      3      2      1      0 
// Bit name      −      −      −      −      −      −      SC1      SC0 
// R/W      R      R      R      R      R      R      R/W      R/W 
// Initial value      0      0      0      0      0      0      0      0 
// SETSC register sets the short current detecting voltage.
// Short current detecting voltage is selected with SC0 and SC1 bit depend on current sensing resistor
// value.
// 
// 
// SC1      SC0     Short current detecting voltage       Short current detecting current if Current sensing resistor value = 3mΩ 
// 0      0      0.1V (initial value)      33.3A 
// 0      1      0.2V      66.6A 
// 1      0      0.3V      100A 
// 1      1      0.4V      133.3A 
// 
// 
// 
// Number of          V15 to                                         
// Connected      V16      V10      V9      V8      V7      V6      V5      V4      V3      V2      V1      V0 
// cells                                                 
// 15      VDD_SW      cell      cell      cell      cell      cell      cell      cell      cell      cell      cell      cell 
// 14      VDD_SW      cell      cell      cell      cell      cell      cell      cell      cell      cell      cell      GND 
// 13      VDD_SW      cell      cell      cell      cell      cell      cell      cell      cell      cell      GND      GND 
// 12      VDD_SW     cell      cell      cell      cell       cell      cell      cell      cell     GND      GND      GND 
// 11      VDD_SW      cell      cell      cell      cell      cell      cell      cell      GND      GND      GND      GND 
// 10      VDD_SW      cell      cell      cell      cell      cell      cell      GND      GND      GND      GND      GND 
// 9      VDD_SW      cell      cell      cell      cell      cell      GND      GND      GND      GND      GND      GND 
// 8      VDD_SW      cell      cell      cell      cell      GND      GND      GND      GND      GND      GND      GND 
// 7      VDD_SW      cell      cell      cell      GND      GND      GND      GND      GND      GND      GND      GND 
// 6      VDD_SW     cell       cell     GND      GND      GND      GND      GND      GND      GND      GND      GND 
// 5      VDD_SW      cell      GND      GND      GND      GND      GND      GND      GND      GND      GND      GND 





}  // namespace drivers

