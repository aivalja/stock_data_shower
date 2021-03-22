from yahoo_fin import stock_info
from serial import Serial
import time
ser = Serial('/dev/ttyACM0',9600)
running = True
currentPrice = 0

while(running):
    currentPrice = str(round(stock_info.get_live_price('GME')))
    
    ser.write((currentPrice+',').encode())
    time.sleep(10)
