si SWD
speed auto
device nrf51
r
w4 4001e504 2
Sleep 200
w4 4001e50c 1
Sleep 200
w4 4001e514 1
Sleep 200
w4 4001e504 0
Sleep 200
r
loadfile led_button.bin 0x00000000
r
Sleep 200
g
