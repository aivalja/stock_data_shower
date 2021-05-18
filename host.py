from yahoo_fin import stock_info
from serial import Serial
import time
import stat
for i in range(10):
    try:
        ser = Serial('/dev/ttyACM'+str(i),9600)
    except:
        pass
running = True
currentPrice = 0
stonks = 0
while(running):
    currentPrice = stock_info.get_live_price('GME')
    close = stock_info.get_data('GME').tail(2).iloc[0][3] # Get previous close price
    change = currentPrice/close - 1
    if(change > 10):
        stonks = 10
    elif(change > 1):
        stonks = 9
    elif(change > 0.5):
        stonks = 8
    elif(change > 0.1):
        stonks = 7
    elif(change > 0.02):
        stonks = 6
    elif(change > -0.02):
        stonks = 5
    elif(change > -0.1):
        stonks = 4
    elif(change > -0.5):
        stonks = 3
    elif(change > -0.75):
        stonks = 2
    elif(change > -0.9):
        stonks = 1
    else:
        stonks = 0
    print((str(round(currentPrice))+':'+str(stonks)+',').encode())
    ser.write((str(round(currentPrice))+':'+str(stonks)+',').encode())
    time.sleep(30)
