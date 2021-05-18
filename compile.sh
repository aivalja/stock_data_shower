arduino-cli compile --fqbn arduino:avr:uno ./price_display/price_display
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno ./price_display/price_display
