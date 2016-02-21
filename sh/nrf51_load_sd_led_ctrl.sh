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
loadfile stack_img/s110_softdevice.hex 0
r
Sleep 200
loadbin sd_led_app/sd_led_app.bin 0X18000
Sleep 200
r
Sleep 200
g
