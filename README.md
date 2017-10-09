
# arduino_pc_reset
This project is about making Arduino usb key for manipulating PC's reset/power buttons.

- This tiny circuit makes it possible to do hardware resetting by pc itself.
- This comes quite handy when you need to recover from hardware error that no software reset recovers. (ex. PCIe link error, GPU hangs)
- By adding a single line of code to your shell script, you will be able to hardware reset auto matically. (or just power off)


## Layout
  ![Breadboard](./arduino_pc_reset_BreadBoard.png)

## pin out


 | Pin     | Direction  | Purpose |
 | ------- |:----------:| -------:|
 | D9      | OUTPUT     | RESET   |
 | D8      | OUTPUT     | POWER   |

## protocol

Send the following command on 9600bps.


- ? ...  show help"
- set RESET=1 ...  reset on
- set RESET=0 ...  reset off
- set RESET=* ...  reset on for 1 sec
- set POWER=1 ...  power on");
- set POWER=0 ...  power off");
- set POWER=* ...  power on for 10 sec

Receive result

- OK

  
